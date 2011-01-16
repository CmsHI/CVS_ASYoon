#include "PbPbTrackingTools/HiTrackValidator/interface/HiTrackValidator.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

HiTrackValidator::HiTrackValidator(const edm::ParameterSet& iConfig)
:
   bslabel_(iConfig.getUntrackedParameter<edm::InputTag>("bslabel")),
   vtxlabel_(iConfig.getUntrackedParameter<edm::InputTag>("vtxlabel")),
   trklabel_(iConfig.getUntrackedParameter<edm::InputTag>("trklabel")),
   jetlabel_(iConfig.getUntrackedParameter<edm::InputTag>("jetlabel")),
   nTracksBins_(iConfig.getUntrackedParameter<int>("nTracksBins")),
   jetTrkVerticesCorr_(iConfig.getUntrackedParameter<bool>("jetTrkVerticesCorr"))
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

   //------- Tracks -----------------------
   edm::Handle<std::vector<reco::Track> > tracks;
   iEvent.getByLabel(trklabel_, tracks);

   const std::string qualityString = "highPurity";

   std::vector<const reco::Track *> sortedTrks;

   for(unsigned it=0; it<tracks->size(); ++it){
      const reco::Track & trk = (*tracks)[it];

      if(!trk.quality(reco::TrackBase::qualityByName(qualityString))) continue;

      // basic hit level quality varialbes
      uint32_t nlayers     = trk.hitPattern().trackerLayersWithMeasurement();
      uint32_t nlayers3D   = trk.hitPattern().pixelLayersWithMeasurement() + 
	 trk.hitPattern().numberOfValidStripLayersWithMonoAndStereo();
      uint32_t nlayersLost = trk.hitPattern().trackerLayersWithoutMeasurement();
      uint32_t nhits = trk.numberOfValidHits();

      // basic track level quality variables
      double pt = trk.pt(), eta = trk.eta(), phi = trk.phi(); 
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
   int nmaxhits = 40;

   hVtxSize = f->make<TH1D>("hVtxSize","number of veritces; N_{vertex}",5,0.0,5.0);
   hNlayers = f->make<TH1D>("hNlayers","number of layers with tracker hits; N_{hits}", nmaxhits,0.,(double)nmaxhits);
   hNlayers3D = f->make<TH1D>("hNlayers3D","number of layers with pixel and tracker mono and streohits; N_{hits}", 
			      nmaxhits,0.,(double)nmaxhits);
   hNlayersLost = f->make<TH1D>("hNlayersLost","number of layers with no tracker hits; N_{hits}", nmaxhits,0.,(double)nmaxhits);
   hNvalidHits = f->make<TH1D>("hNvalidHits","number of valid hits", nmaxhits,0.,(double)nmaxhits);
   hChi2n = f->make<TH1D>("hChi2n","normalized track chi2;chi^{2}/ndof", 20,0.0,1.5);
   hRelPtErr = f->make<TH1D>("hRelPtErr","relative track p_{T} error; p_{T} err/p_{T}", 50,0.0,1.2);
   hdzErr = f->make<TH1D>("hdzErr","dz error; dz error", 50,0.0,5.0);
   hd0Err = f->make<TH1D>("hd0Err","d0 error; d0 error", 50,0.0,5.0);
   hdzErrPV = f->make<TH1D>("hdzErrPV","dz error with vz error summed ; dz error", 50,0.0,5.0);
   hd0ErrPV = f->make<TH1D>("hdzErrPV","d0 error with vz error summed ; d0 error", 50,0.0,5.0);
   hvzErr = f->make<TH1D>("hvzErr","vz error; vz error", 50,0.0, 20.0);
   hvtErr = f->make<TH1D>("hvtErr","vxy error; vxy error", 50,0.0, 20.0);
   hdzOverdzErr = f->make<TH1D>("hdzOverdzErr","dz/dzError; dz/dzError", 50,-15.0,15.0);
   hd0Overd0Err = f->make<TH1D>("hd0Overd0Err","d0/d0Error; d0/d0Error", 50,-15.0,15.0);
   hdzOverdzErrPV =  f->make<TH1D>("hdzOverdzErrPV","dz/dzError with PV error; dz/dzError", 50,-15.0,15.0);
   hd0Overd0ErrPV = f->make<TH1D>("hd0Overd0ErrPV","d0/d0Error with PV error; d0/d0Error", 50,-15.0,15.0);
   
   hNlayersdPt = f->make<TH2D>("hNlayersdPt","number of layers with tracker hits; p_{T};N_{hits}", 
			       150,0.0,150.0, nmaxhits,0.,(double)nmaxhits);
   


}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiTrackValidator::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiTrackValidator);
