#include "PbPbTrackingTools/HiTrackValidator/interface/HiTrackValidator.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

HiTrackValidator::HiTrackValidator(const edm::ParameterSet& iConfig)
:
   bslabel_(iConfig.getUntrackedParameter<edm::InputTag>("bslabel")),
   vtxlabel_(iConfig.getUntrackedParameter<edm::InputTag>("vtxlabel")),
   trklabel_(iConfig.getUntrackedParameter<edm::InputTag>("trklabel")),
   simtrklabel_(iConfig.getUntrackedParameter<edm::InputTag>("simtrklabel")),
   associatorMap_(iConfig.getUntrackedParameter<edm::InputTag>("associatorMap")),
   etaMax_(iConfig.getUntrackedParameter<double>("etaMax")),
   hasSimInfo_(iConfig.getUntrackedParameter<bool>("hasSimInfo")),
   selectFake_(iConfig.getUntrackedParameter<bool>("selectFake")),
   useQaulityStr_(iConfig.getUntrackedParameter<bool>("useQaulityStr")),
   neededCentBins_(iConfig.getUntrackedParameter<std::vector<int> >("neededCentBins")),
   centrality_(0)
{

}


// ------------ method called to for each event  ------------
void
HiTrackValidator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   using namespace edm;
   using namespace std;
   using namespace reco;

   //------- Beam spot --------------------
   edm::Handle<reco::BeamSpot> beamsp;
   iEvent.getByLabel(bslabel_, beamsp);
   reco::BeamSpot vertexBeamSpot = *beamsp;

   //------- Vertices ---------------------
   edm::Handle<reco::VertexCollection> vtxsH;
   iEvent.getByLabel(vtxlabel_,vtxsH);

   reco::VertexCollection vtxs = *vtxsH;

   bool isPV = false;
   if(vtxs.size()!=0) isPV = true;
   hVtxSize->Fill(vtxs.size());


   //------- Centrality information --------
   centrality_ = new CentralityProvider(iSetup);
   centrality_->newEvent(iEvent,iSetup);
   int cbin = centrality_->getBin();

   //------ Sim tracks -------------------
   edm::Handle<TrackingParticleCollection>  TPCollectionHfake;
   edm::Handle<edm::View<reco::Track> >  trackCollection;
   edm::ESHandle<TrackAssociatorBase> theAssociator;
   const TrackAssociatorByHits *theAssociatorByHits;
   reco::RecoToSimCollection recSimColl;

   iEvent.getByLabel(trklabel_,trackCollection); // track collection ref base 

   if(hasSimInfo_) {
      iEvent.getByLabel(simtrklabel_,TPCollectionHfake);
      iSetup.get<TrackAssociatorRecord>().get("TrackAssociatorByHits",theAssociator);
      theAssociatorByHits = (const TrackAssociatorByHits*) theAssociator.product();  
      recSimColl= theAssociatorByHits->associateRecoToSim(trackCollection,TPCollectionHfake,&iEvent); // to find fake
   }
   
   //------- Tracks -----------------------
   edm::Handle<std::vector<reco::Track> > tracks;
   iEvent.getByLabel(trklabel_, tracks);

   const std::string qualityString = "highPurity";


   for(unsigned it=0; it<tracks->size(); ++it){

      const reco::Track & trk = (*tracks)[it];

      if(useQaulityStr_ && !trk.quality(reco::TrackBase::qualityByName(qualityString))) continue;

      // rec to sim association
      edm::RefToBase<reco::Track> track(trackCollection, it);
      std::vector<std::pair<TrackingParticleRef, double> > tp;
      bool isFake = false;

      if(hasSimInfo_ && recSimColl.find(track) != recSimColl.end()){
	 tp = recSimColl[track];
      } else {
	 isFake = true;
      }

      if(selectFake_ && !isFake) continue; // fill histograms for fake tracks only

      // basic kinematic variable
      double pt = trk.pt(), eta = trk.eta(), phi = trk.phi();

      hEtaPhi->Fill(eta,phi);
      
      // centrality binned
      for(unsigned i=0;i<neededCentBins_.size();i++){
	 if(i==0){
	    if(cbin<=neededCentBins_[i+1]) 
	       hEtaPhi_Cent[i]->Fill(eta,phi);
	 }else{
	    if(cbin>neededCentBins_[i] && cbin<=neededCentBins_[i+1])
	       hEtaPhi_Cent[i]->Fill(eta,phi);
	 }
      }

      if(etaMax_<eta) continue; // only for a given eta range


      // basic hit level quality varialbes
      uint32_t nlayers     = trk.hitPattern().trackerLayersWithMeasurement();
      uint32_t nlayers3D   = trk.hitPattern().pixelLayersWithMeasurement() + 
	 trk.hitPattern().numberOfValidStripLayersWithMonoAndStereo();
      uint32_t nlayersLost = trk.hitPattern().trackerLayersWithoutMeasurement();
      uint32_t nhits = trk.numberOfValidHits();

      // basic track level quality variables
      double relpterr = trk.ptError()/pt, chi2n =  trk.normalizedChi2();

      // compatibility variables
      // if no primary vertex is present, calculate dz(d0) w.r.t the beam spot position 
      double dz = (isPV) ? trk.dz(vtxs[0].position()) : trk.dz(vertexBeamSpot.position());
      double d0 = (isPV) ? trk.dxy(vtxs[0].position()) : trk.dxy(vertexBeamSpot.position());

      double dzE =  trk.dzError();
      double d0E =  trk.d0Error();

      // parameterized d0, dz resolution
      double nomd0E = sqrt(99999.*99999.+(99999./max(pt,1e-9))*(99999./max(pt,1e-9)));
      double nomdzE = nomd0E*(std::cosh(eta));
      
      // again if no PV, error from BS
      double vzE = (isPV) ? vtxs[0].zError() : vertexBeamSpot.z0Error();
      double vtE = (isPV) ? sqrt(vtxs[0].xError()*vtxs[0].yError()) 
	 : sqrt(vertexBeamSpot.x0Error()*vertexBeamSpot.y0Error());
      
      double dzErrPV = sqrt(dzE*dzE+vzE*vzE);
      double d0ErrPV = sqrt(d0E*d0E+vtE*vtE);
      
      double dzOverdZErr = dz/dzE;
      double d0Overd0Err = d0/d0E;

      double dzOverdZErrPV = dz/dzErrPV;
      double d0Overd0ErrPV = d0/d0ErrPV;

      // histogram filling
      hNlayers->Fill(nlayers);
      hNlayers3D->Fill(nlayers3D);
      hNlayersLost->Fill(nlayersLost);
      hNvalidHits->Fill(nhits);
      hChi2n->Fill(chi2n);
      hRelPtErr->Fill(relpterr);
      hdzErr->Fill(dzE);
      hd0Err->Fill(d0E);
      hdzErrPV->Fill(dzErrPV);
      hd0ErrPV->Fill(d0ErrPV);
      hvzErr->Fill(vzE);
      hvtErr->Fill(vtE);
      hdzOverdzErr->Fill(dzOverdZErr); 
      hd0Overd0Err->Fill(d0Overd0Err);
      hdzOverdzErrPV->Fill(dzOverdZErrPV);
      hd0Overd0ErrPV->Fill(d0Overd0ErrPV);

      // histogram filling 2D
      hNlayersdPt->Fill(pt,nlayers);
      hNlayers3DdPt->Fill(pt,nlayers3D);
      hNlayersLostdPt->Fill(pt,nlayersLost);
      hNvalidHitsdPt->Fill(pt,nhits);
      hChi2ndPt->Fill(pt,chi2n);
      hRelPtErrdPt->Fill(pt,relpterr);
      hdzErrdPt->Fill(pt,dzE);
      hd0ErrdPt->Fill(pt,d0E);
      hdzErrPVdPt->Fill(pt,dzErrPV);
      hd0ErrPVdPt->Fill(pt,d0ErrPV);
      hvzErrdPt->Fill(pt,vzE);
      hvtErrdPt->Fill(pt,vtE);
      hdzOverdzErrdPt->Fill(pt,dzOverdZErr);
      hd0Overd0ErrdPt->Fill(pt,d0Overd0Err);
      hdzOverdzErrPVdPt->Fill(pt,dzOverdZErrPV);
      hd0Overd0ErrPVdPt->Fill(pt,d0Overd0ErrPV);

      // correlation
      hdzErrd0Err->Fill(dzE,d0E);
      hdzErrd0ErrPV->Fill(dzErrPV,d0ErrPV);
      hdzOverdzErrd0Err->Fill(dzOverdZErr,d0Overd0Err);
      hdzOverdzErrd0ErrPV->Fill(dzOverdZErrPV,d0Overd0ErrPV);


      // centrality binned
      for(unsigned i=0;i<neededCentBins_.size();i++){
         if(i==0){
            if(cbin<=neededCentBins_[i+1]){
	       hNvalidHits_Cent[i]->Fill(nhits);
	       hChi2n_Cent[i]->Fill(chi2n);
	       hRelPtErr_Cent[i]->Fill(relpterr);
	       hdzErrPV_Cent[i]->Fill(dzErrPV);
	       hd0ErrPV_Cent[i]->Fill(d0ErrPV);
	       hdzOverdzErrPV_Cent[i]->Fill(dzOverdZErrPV);
	       hd0Overd0ErrPV_Cent[i]->Fill(d0Overd0ErrPV);
	       hNvalidHitsdPt_Cent[i]->Fill(pt,nhits);
	       hChi2ndPt_Cent[i]->Fill(pt,chi2n);
	       hRelPtErrdPt_Cent[i]->Fill(pt,relpterr);
	       hdzErrPVdPt_Cent[i]->Fill(pt,dzErrPV);
	       hd0ErrPVdPt_Cent[i]->Fill(pt,d0ErrPV);
	       hdzOverdzErrPVdPt_Cent[i]->Fill(pt,dzOverdZErrPV);
	       hd0Overd0ErrPVdPt_Cent[i]->Fill(pt,d0Overd0ErrPV);
	       hdzOverdzErrd0Err_Cent[i]->Fill(dzOverdZErr,d0Overd0Err);
	       hdzOverdzErrd0ErrPV_Cent[i]->Fill(dzOverdZErrPV,d0Overd0ErrPV);
	    }
         }else{
            if(cbin>neededCentBins_[i] && cbin<=neededCentBins_[i+1]){
	       hNvalidHits_Cent[i]->Fill(nhits);
	       hChi2n_Cent[i]->Fill(chi2n);
	       hRelPtErr_Cent[i]->Fill(relpterr);
	       hdzErrPV_Cent[i]->Fill(dzErrPV);
	       hd0ErrPV_Cent[i]->Fill(d0ErrPV);
	       hdzOverdzErrPV_Cent[i]->Fill(dzOverdZErrPV);
	       hd0Overd0ErrPV_Cent[i]->Fill(d0Overd0ErrPV);
	       hNvalidHitsdPt_Cent[i]->Fill(pt,nhits);
	       hChi2ndPt_Cent[i]->Fill(pt,chi2n);
	       hRelPtErrdPt_Cent[i]->Fill(pt,relpterr);
	       hdzErrPVdPt_Cent[i]->Fill(pt,dzErrPV);
	       hd0ErrPVdPt_Cent[i]->Fill(pt,d0ErrPV);
	       hdzOverdzErrPVdPt_Cent[i]->Fill(pt,dzOverdZErrPV);
	       hd0Overd0ErrPVdPt_Cent[i]->Fill(pt,d0Overd0ErrPV);
	       hdzOverdzErrd0Err_Cent[i]->Fill(dzOverdZErr,d0Overd0Err);
	       hdzOverdzErrd0ErrPV_Cent[i]->Fill(dzOverdZErrPV,d0Overd0ErrPV);
	    }
         }
      }


   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
HiTrackValidator::beginJob()
{

   // pt bins
   const double small = 1e-3;
   double ptb;

   // simple rebinning possible with a rebinning factor n = 2, 3, 4 !
   for(ptb =   0  ; ptb <   1.2-small; ptb +=  0.05) ptBins.push_back(ptb); // 24 bins
   for(ptb =   1.2; ptb <   2.4-small; ptb +=  0.1 ) ptBins.push_back(ptb); // 12 bins
   for(ptb =   2.4; ptb <   7.2-small; ptb +=  0.2 ) ptBins.push_back(ptb); // 24 bins
   for(ptb =   7.2; ptb <  13.2-small; ptb +=  0.5 ) ptBins.push_back(ptb); // 12 bins
   for(ptb =  13.2; ptb <  25.2-small; ptb +=  1.0 ) ptBins.push_back(ptb); // 12 bins
   for(ptb =  25.2; ptb <  61.2-small; ptb +=  3.0 ) ptBins.push_back(ptb); // 12 bins
   for(ptb =  61.2; ptb < 121.2-small; ptb +=  5.0 ) ptBins.push_back(ptb); // 12 bins
   for(ptb = 121.2; ptb < 361.2-small; ptb += 10.0 ) ptBins.push_back(ptb); // 24 bins
   ptBins.push_back(361.2);


   //histograms
   int nmaxhits = 30;

   hVtxSize = f->make<TH1D>("hVtxSize","number of veritces; N_{vertex}",5,-0.5,4.5);
   hNlayers = f->make<TH1D>("hNlayers","number of layers with tracker hits; N_{hits}", nmaxhits,0.,(double)nmaxhits);
   hNlayers3D = f->make<TH1D>("hNlayers3D","number of layers with pixel and tracker mono and streohits; N_{hits}", 
			      nmaxhits,0.,(double)nmaxhits);
   hNlayersLost = f->make<TH1D>("hNlayersLost","number of layers with no tracker hits; N_{hits}", nmaxhits,0.,(double)nmaxhits);
   hNvalidHits = f->make<TH1D>("hNvalidHits","number of valid hits; N_{hits}", nmaxhits,0.,(double)nmaxhits);
   hChi2n = f->make<TH1D>("hChi2n","normalized track chi2;chi^{2}/ndof", 60,0.0,5.0);
   hRelPtErr = f->make<TH1D>("hRelPtErr","relative track p_{T} error; p_{T} err/p_{T}", 100,0.0,0.4);
   hdzErr = f->make<TH1D>("hdzErr","dz error; dz error", 60,0.0,1.2);
   hd0Err = f->make<TH1D>("hd0Err","d0 error; d0 error", 60,0.0,1.2);
   hdzErrPV = f->make<TH1D>("hdzErrPV","dz error with vz error summed ; dz error", 60,0.0,1.2);
   hd0ErrPV = f->make<TH1D>("hd0ErrPV","d0 error with vz error summed ; d0 error", 60,0.0,1.2);
   hvzErr = f->make<TH1D>("hvzErr","vz error; vz error", 100,0.0, 0.08);
   hvtErr = f->make<TH1D>("hvtErr","vxy error; vxy error", 100,0.0, 0.08);
   hdzOverdzErr = f->make<TH1D>("hdzOverdzErr","dz/dzError; dz/dzError", 80,-10.0,10.0);
   hd0Overd0Err = f->make<TH1D>("hd0Overd0Err","d0/d0Error; d0/d0Error", 80,-10.0,10.0);
   hdzOverdzErrPV =  f->make<TH1D>("hdzOverdzErrPV","dz/dzError with PV error; dz/dzError", 80,-10.0,10.0);
   hd0Overd0ErrPV = f->make<TH1D>("hd0Overd0ErrPV","d0/d0Error with PV error; d0/d0Error", 80,-10.0,10.0);

   // as a function of pt
   hNlayersdPt = f->make<TH2D>("hNlayersdPt","number of layers with tracker hits vs p_{T}; p_{T};N_{hits}", 150,0.0,150.0, nmaxhits,0.,(double)nmaxhits);
   hNlayers3DdPt = f->make<TH2D>("hNlayers3DdPt","number of layers with tracker hits vs p_{T}; p_{T};N_{hits}", 150,0.0,150.0, nmaxhits,0.,(double)nmaxhits);
   hNlayersLostdPt = f->make<TH2D>("hNlayersLostdPt","number of layers with no tracker hits vs p_{T}; p_{T}; N_{hits}", 150,0.0,150.0, nmaxhits,0.,(double)nmaxhits);
   hNvalidHitsdPt = f->make<TH2D>("hNvalidHitsdPt","number of valid hits vs p_{T}; p_{T}; N_{hits}", 150,0.0,150.0, nmaxhits,0.,(double)nmaxhits);
   hChi2ndPt = f->make<TH2D>("hChi2ndPt","normalized track chi2 vs p_{T}; p_{T};chi^{2}/ndofnormalized track", 150,0.0,150.0, 60,0.0,5.0);
   hRelPtErrdPt = f->make<TH2D>("hRelPtErrdPt","relative track p_{T} error vs p_{T}; p_{T}; p_{T} err/p_{T}", 150,0.0,150.0, 100,0.0,0.4);
   hdzErrdPt = f->make<TH2D>("hdzErrdPt","dz error vs p_{T}; p_{T}; dz error", 150,0.0,150.0, 60,0.0,1.2);
   hd0ErrdPt = f->make<TH2D>("hd0ErrdPt","d0 error vs p_{T}; p_{T}; d0 error", 150,0.0,150.0, 60,0.0,1.2);
   hdzErrPVdPt = f->make<TH2D>("hdzErrPVdPt","dz error with vz error summed vs p_{T}; p_{T}; dz error", 150,0.0,150.0, 60,0.0,1.2);
   hd0ErrPVdPt = f->make<TH2D>("hd0ErrPVdPt","d0 error with vz error summed vs p_{T}; p_{T}; d0 error", 150,0.0,150.0, 60,0.0,1.2);
   hvzErrdPt =  f->make<TH2D>("hvzErrdPt","vz error vs p_{T}; p_{T}; vz error", 150,0.0,150.0, 100,0.0,0.08);
   hvtErrdPt = f->make<TH2D>("hvtErrdPt","vxy error vs p_{T}; p_{T}; vxy error", 150,0.0,150.0, 100,0.0,0.08);
   hdzOverdzErrdPt = f->make<TH2D>("hdzOverdzErrdPt","dz/dzError vs p_{T}; p_{T}; dz/dzError", 150,0.0,150.0, 80,-10.0,10.0);
   hd0Overd0ErrdPt = f->make<TH2D>("hd0Overd0ErrdPt","d0/d0Error vs p_{T}; p_{T}; d0/d0Error", 150,0.0,150.0, 80,-10.0,10.0);
   hdzOverdzErrPVdPt = f->make<TH2D>("hdzOverdzErrPVdPt","dz/dzError with PV error vs p_{T}; p_{T}; dz/dzError", 150,0.0,150.0, 80,-10.0,10.0);
   hd0Overd0ErrPVdPt = f->make<TH2D>("hd0Overd0ErrPVdPt","d0/d0Error with PV error vs p_{T}; p_{T}; d0/d0Error", 150,0.0,150.0, 80,-10.0,10.0);
   
   // correlation
   hdzErrd0Err = f->make<TH2D>("hdzErrd0Err","dz error vs d0 error;dz error;d0 error", 60,0.0,1.2, 60,0.0,1.2);
   hdzErrd0ErrPV = f->make<TH2D>("hdzErrd0ErrPVt","dz error vs d0 error (vz error summed);dz error;d0 error", 60,0.0,1.2, 60,0.0,1.2);
   hdzOverdzErrd0Err = f->make<TH2D>("hdzOverdzErrd0Err","dz/dzError vs d0/d0Error", 80,-10.0,10.0, 80,-10.0,10.0);
   hdzOverdzErrd0ErrPV = f->make<TH2D>("hdzOverdzErrd0ErrPV","dz/dzError with PV error vs d0/d0Error with PV error", 80,-10.0,10.0, 80,-10.0,10.0);

   // kinematic distributions
   hEtaPhi = f->make<TH2D>("hEtaPhi","eta vs phi;#eta;#phi", 20,-2.65,2.65, 40,-1.05*TMath::Pi(),1.05*TMath::Pi());


   // centrality binned histogram 
   for(unsigned i=0;i<neededCentBins_.size()-1;i++){

      hNvalidHits_Cent.push_back(f->make<TH1D>("","number of valid hits; N_{hits}", nmaxhits,0.,(double)nmaxhits));
      hChi2n_Cent.push_back(f->make<TH1D>("","normalized track chi2;chi^{2}/ndof", 60,0.0,5.0));
      hRelPtErr_Cent.push_back(f->make<TH1D>("","relative track p_{T} error; p_{T} err/p_{T}", 100,0.0,0.4));
      hdzErrPV_Cent.push_back(f->make<TH1D>("","dz error with vz error summed ; dz error", 60,0.0,1.2));
      hd0ErrPV_Cent.push_back(f->make<TH1D>("","d0 error; d0 error", 60,0.0,1.2));
      hdzOverdzErrPV_Cent.push_back(f->make<TH1D>("","dz/dzError with PV error; dz/dzError", 80,-10.0,10.0));
      hd0Overd0ErrPV_Cent.push_back(f->make<TH1D>("","d0/d0Error with PV error; d0/d0Error", 80,-10.0,10.0));

      hNvalidHitsdPt_Cent.push_back(f->make<TH2D>("","number of valid hits vs p_{T}; p_{T}; N_{hits}",150,0.0,150.0, nmaxhits,0.,(double)nmaxhits));
      hChi2ndPt_Cent.push_back(f->make<TH2D>("","normalized track chi2 vs p_{T}; p_{T};chi^{2}/ndofnormalized track", 150,0.0,150.0, 60,0.0,5.0));
      hRelPtErrdPt_Cent.push_back(f->make<TH2D>("","relative track p_{T} error vs p_{T}; p_{T}; p_{T} err/p_{T}", 150,0.0,150.0, 100,0.0,0.4));
      hdzErrPVdPt_Cent.push_back(f->make<TH2D>("","dz error with vz error summed vs p_{T}; p_{T}; dz error", 150,0.0,150.0, 60,0.0,1.2));
      hd0ErrPVdPt_Cent.push_back(f->make<TH2D>("","d0 error with vz error summed vs p_{T}; p_{T}; d0 error", 150,0.0,150.0, 60,0.0,1.2));
      hdzOverdzErrPVdPt_Cent.push_back(f->make<TH2D>("","dz/dzError with PV error vs p_{T}; p_{T}; dz/dzError", 150,0.0,150.0, 80,-10.0,10.0));
      hd0Overd0ErrPVdPt_Cent.push_back(f->make<TH2D>("","d0/d0Error with PV error vs p_{T}; p_{T}; d0/d0Error", 150,0.0,150.0, 80,-10.0,10.0));

      hdzOverdzErrd0Err_Cent.push_back(f->make<TH2D>("","dz/dzError vs d0/d0Error", 80,-10.0,10.0, 80,-10.0,10.0));
      hdzOverdzErrd0ErrPV_Cent.push_back(f->make<TH2D>("","dz/dzError with PV error vs d0/d0Error with PV error", 80,-10.0,10.0, 80,-10.0,10.0));
      hEtaPhi_Cent.push_back(f->make<TH2D>("","eta vs phi;#eta;#phi", 20,-2.65,2.65, 40,-1.05*TMath::Pi(),1.05*TMath::Pi()));
      
      if(i==0){
         hNvalidHits_Cent[i]->SetName(Form("hNvalidHits_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
         hChi2n_Cent[i]->SetName(Form("hChi2n_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
         hRelPtErr_Cent[i]->SetName(Form("hRelPtErr_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
         hdzErrPV_Cent[i]->SetName(Form("hdzErrPV_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
         hd0ErrPV_Cent[i]->SetName(Form("hd0ErrPV_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
         hdzOverdzErrPV_Cent[i]->SetName(Form("hdzOverdzErrPV_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
         hd0Overd0ErrPV_Cent[i]->SetName(Form("hd0Overd0ErrPV_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 
	 hNvalidHitsdPt_Cent[i]->SetName(Form("hNvalidHitsdPt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hChi2ndPt_Cent[i]->SetName(Form("hChi2ndPt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hRelPtErrdPt_Cent[i]->SetName(Form("hRelPtErrdPt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hdzErrPVdPt_Cent[i]->SetName(Form("hdzErrPVdPt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hd0ErrPVdPt_Cent[i]->SetName(Form("hd0ErrPVdPt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hdzOverdzErrPVdPt_Cent[i]->SetName(Form("hdzOverdzErrPVdPt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hd0Overd0ErrPVdPt_Cent[i]->SetName(Form("hd0Overd0ErrPVdPt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));

	 hdzOverdzErrd0Err_Cent[i]->SetName(Form("hdzOverdzErrd0Err_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hdzOverdzErrd0ErrPV_Cent[i]->SetName(Form("hdzOverdzErrd0ErrPV_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));

      }else{
         hNvalidHits_Cent[i]->SetName(Form("hNvalidHits_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
         hChi2n_Cent[i]->SetName(Form("hChi2n_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
         hRelPtErr_Cent[i]->SetName(Form("hRelPtErr_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
         hdzErrPV_Cent[i]->SetName(Form("hdzErrPV_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
         hd0ErrPV_Cent[i]->SetName(Form("hd0ErrPV_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
         hdzOverdzErrPV_Cent[i]->SetName(Form("hdzOverdzErrPV_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
         hd0Overd0ErrPV_Cent[i]->SetName(Form("hd0Overd0ErrPV_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));

	 hNvalidHitsdPt_Cent[i]->SetName(Form("hNvalidHitsdPt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hChi2ndPt_Cent[i]->SetName(Form("hChi2ndPt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hRelPtErrdPt_Cent[i]->SetName(Form("hRelPtErrdPt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hdzErrPVdPt_Cent[i]->SetName(Form("hdzErrPVdPt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hd0ErrPVdPt_Cent[i]->SetName(Form("hd0ErrPVdPt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hdzOverdzErrPVdPt_Cent[i]->SetName(Form("hdzOverdzErrPVdPt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hd0Overd0ErrPVdPt_Cent[i]->SetName(Form("hd0Overd0ErrPVdPt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));

	 hdzOverdzErrd0Err_Cent[i]->SetName(Form("hdzOverdzErrd0Err_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hdzOverdzErrd0ErrPV_Cent[i]->SetName(Form("hdzOverdzErrd0ErrPV_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
      }

   }

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiTrackValidator::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiTrackValidator);
