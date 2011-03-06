//
// Original Author:  Edward Wenger
//         Created:  Thu Apr 29 14:31:47 CEST 2010
// $Id: HiTrkEffAnalyzer.cc,v 1.6 2011/01/20 20:53:22 sungho Exp $
//

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorByHits.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h"
#include "edwenger/HiTrkEffAnalyzer/interface/HiTrkEffAnalyzer.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
//#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

#include <stdio.h>
#include <math.h>

//#define DEBUG

HiTrkEffAnalyzer::HiTrkEffAnalyzer(const edm::ParameterSet& iConfig)
:
  trackTags_(iConfig.getUntrackedParameter<edm::InputTag>("tracks")),
  jetTags_(iConfig.getUntrackedParameter<edm::InputTag>("jets")),
  label_tp_effic_(iConfig.getUntrackedParameter<edm::InputTag>("label_tp_effic")),
  label_tp_fake_(iConfig.getUntrackedParameter<edm::InputTag>("label_tp_fake")),
  associatorMap_(iConfig.getUntrackedParameter<edm::InputTag>("associatormap")),
  vtxTags_(iConfig.getUntrackedParameter<edm::InputTag>("vertices")),
  bsTags_(iConfig.getUntrackedParameter<edm::InputTag>("beamspot")),
  doAssociation_(iConfig.getUntrackedParameter<bool>("doAssociation",true)),
  hasSimInfo_(iConfig.getUntrackedParameter<bool>("hasSimInfo",false)),
  pixelMultMode_(iConfig.getUntrackedParameter<bool>("pixelMultMode",false)),
  useJetEt_(iConfig.getUntrackedParameter<bool>("useJetEt",true)),
  oneOverPtMode_(iConfig.getParameter<bool>("oneOverPtMode")),
  centrality_(0)
{

  histograms = new HiTrkEffHistograms(iConfig);

}


// ------------ method called for each event  ------------
void
HiTrkEffAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  edm::ESHandle<TrackAssociatorBase> theAssociator;
  const TrackAssociatorByHits * theAssociatorByHits;
  edm::Handle<reco::SimToRecoCollection > simtorecoCollectionH;
  edm::Handle<reco::RecoToSimCollection > recotosimCollectionH;
  edm::Handle<TrackingParticleCollection>  TPCollectionHeff, TPCollectionHfake;
  reco::RecoToSimCollection recSimColl;
  reco::SimToRecoCollection simRecColl;


  // reco track, vertex, beamspot collections

  edm::Handle<edm::View<reco::Track> >  trackCollection;
  iEvent.getByLabel(trackTags_,trackCollection);

  iEvent.getByLabel(vtxTags_,vertexCollectionH);
  iEvent.getByLabel(bsTags_,beamSpotH);

  LogDebug("HiTrkEffAnalyzer") <<" number of rec tracks = "<<trackCollection->size()<<std::endl;

  // Centrality information ----------------------
  double pixelMult = 0.0;

  centrality_ = new CentralityProvider(iSetup);
  centrality_->newEvent(iEvent,iSetup);
  int cbin = centrality_->getBin();

  if(pixelMultMode_){
     pixelMult = centrality_->raw()->multiplicityPixel();
     pixelMult = pixelMult/100.; // scale it (120K -> 1200)
  } 

  // PAT jet, to get leading jet ET

  float jet_et = 0.0;

  if(useJetEt_){
     edm::Handle<std::vector<pat::Jet> > jets;
     iEvent.getByLabel(jetTags_, jets);
     
     std::vector<const pat::Jet *> sortedJets;
     
     for(unsigned it=0; it<jets->size(); ++it){
	const pat::Jet* jts = &((*jets)[it]);
	sortedJets.push_back( & *jts);
	sortByEtRef (&sortedJets);
     }
     
     for(unsigned it=0; it<sortedJets.size(); ++it){
	jet_et = sortedJets[it]->et();
	break;
     }
  }

  // pre-RECO loop to determine local track density
  bool fillHist = false;
  hNtrkEtaPhi->Reset(); // need to be reset for every event
  if(hNtrkEtaPhi_Cent[cbin]->GetEntries()==0) fillHist=true;

  for(edm::View<reco::Track>::size_type j=0; j<trackCollection->size(); ++j){

     edm::RefToBase<reco::Track> track(trackCollection, j);
     reco::Track* tr=const_cast<reco::Track*>(track.get());

     hNtrkEtaPhi->Fill(tr->eta(),tr->phi());
     if(fillHist) hNtrkEtaPhi_Cent[cbin]->Fill(tr->eta(),tr->phi()); // fill only once 
  }


  // sim track collections
  float occHandle = 0.0;

  if(pixelMultMode_) occHandle = (float) pixelMult;
  else occHandle = jet_et;


  if(hasSimInfo_) {

    // sim track collections
    
    iEvent.getByLabel(label_tp_effic_,TPCollectionHeff);
    iEvent.getByLabel(label_tp_fake_,TPCollectionHfake);

    LogDebug("HiTrkEffAnalyzer") <<" number of sim tracks (for eff) = "<<TPCollectionHeff->size()
				 <<" number of sim tracks (for fake) = "<<TPCollectionHfake->size()<<std::endl;
    
    
    // association map generated on-the-fly or read from file
    
    if(doAssociation_){
      iSetup.get<TrackAssociatorRecord>().get("TrackAssociatorByHits",theAssociator);
      theAssociatorByHits = (const TrackAssociatorByHits*) theAssociator.product();
      
      simRecColl= theAssociatorByHits->associateSimToReco(trackCollection,TPCollectionHeff,&iEvent);
      recSimColl= theAssociatorByHits->associateRecoToSim(trackCollection,TPCollectionHfake,&iEvent);
      LogDebug("HiTrkEffAnalyzer") <<" association is done on the fly! \n"
				   <<" sim for eff = ["<<label_tp_effic_<<" ] \n"
				   <<" sim for fake = ["<<label_tp_fake_<<" ] \n";
    }else{
      iEvent.getByLabel(associatorMap_,simtorecoCollectionH);
      simRecColl= *(simtorecoCollectionH.product());
      
      iEvent.getByLabel(associatorMap_,recotosimCollectionH);
      recSimColl= *(recotosimCollectionH.product());
      LogDebug("HiTrkEffAnalyzer") <<" association is from the following association map \n"
                                   <<" map = ["<<associatorMap_<<" ] \n";
    }
    
    // -------------------- SIM loop ----------------------------------------
    
    for(TrackingParticleCollection::size_type i=0; i<TPCollectionHeff->size(); i++) {
      
      TrackingParticleRef tpr(TPCollectionHeff, i);
      TrackingParticle* tp=const_cast<TrackingParticle*>(tpr.get());
      
      if(tp->status() < 0 || tp->charge()==0) continue; //only charged primaries
      
      std::vector<std::pair<edm::RefToBase<reco::Track>, double> > rt;
      const reco::Track* mtr=0;
      size_t nrec=0;
      
      if(simRecColl.find(tpr) != simRecColl.end()){
	rt = (std::vector<std::pair<edm::RefToBase<reco::Track>, double> >) simRecColl[tpr];
	nrec=rt.size();   
	if(nrec) mtr = rt.begin()->first.get();      
      }

      std::pair<float,float> slocal = getLocalTrkDensity(hNtrkEtaPhi,tp->eta(),tp->phi());
      float sdr = slocal.first;
      float slocaltrkmult = slocal.second;

      slocaltrkmult = sdr;

      //slocaltrkmult = slocaltrkmult*log(tp->pt()); // pt weighted local track density
      //SimTrack_t s = setSimTrack(*tp, *mtr, nrec, occHandle, cbin);
      SimTrack_t s = setSimTrack(*tp, *mtr, nrec, slocaltrkmult, cbin);   
      histograms->fillSimHistograms(s);  
      
#ifdef DEBUG
      if(nrec) edm::LogVerbatim("HiTrkEffAnalyzer") 
	<< "TrackingParticle #" << i << " with pt=" << tp->pt() 
	<< " associated with quality:" << rt.begin()->second;
#endif
    }
    

  } //end if(hasSimInfo_)
    
  // -------------------- RECO loop ----------------------------------------

  for(edm::View<reco::Track>::size_type i=0; i<trackCollection->size(); ++i){
    
    edm::RefToBase<reco::Track> track(trackCollection, i);
    reco::Track* tr=const_cast<reco::Track*>(track.get());
    
    std::vector<std::pair<TrackingParticleRef, double> > tp;
    const TrackingParticle *mtp=0;
    size_t nsim=0;

    if(hasSimInfo_ && recSimColl.find(track) != recSimColl.end()){
      tp = recSimColl[track];
      nsim=tp.size();
      if(nsim) mtp = tp.begin()->first.get();       
    }

    //int rbin = hNtrkEtaPhi->FindBin(tr->eta(),tr->phi());
    //float rlocaltrkmult 
    //= hNtrkEtaPhi->GetBinContent(rbin);

    std::pair<float,float> rlocal = getLocalTrkDensity(hNtrkEtaPhi,tr->eta(),tr->phi());
    float rdr = rlocal.first;
    float rlocaltrkmult = rlocal.second;

    rlocaltrkmult = rdr;
    //rlocaltrkmult = rlocaltrkmult*log(tr->pt());  // pt weighted local track density
    /*
    hLocalTrkMultDist->Fill(rlocaltrkmult);
    hCentVsLocalTrkDen->Fill(cbin,rlocaltrkmult);
    hJetEtVsLocalTrkDen->Fill(occHandle,rlocaltrkmult);
    */
    hdRDist->Fill(rdr);

    RecTrack_t r = setRecTrack(*tr, *mtp, nsim, rlocaltrkmult, cbin);  
    //RecTrack_t r = setRecTrack(*tr, *mtp, nsim, occHandle, cbin);
    histograms->fillRecHistograms(r); 

#ifdef DEBUG
    if(nsim) edm::LogVerbatim("HiTrkEffAnalyzer") 
      << "reco::Track #" << i << " with pt=" << track->pt() 
      << " associated with quality:" << tp.begin()->second;
#endif
  }

}


// ------------ method called once each job just before starting event loop  ------------
void 
HiTrkEffAnalyzer::beginJob()
{

  histograms->declareHistograms();
  TFileDirectory subDir = f->mkdir( "trackDensity" );
  int nbins = 1575;
  int nbins_z = 80;

  hNtrkEtaPhi = subDir.make<TH2F>("hNtrkEtaPhi","local track density grid",1250,-2.5,2.5,nbins,-3.15,3.15); 
  for(int i=0;i<40;i++){
     hNtrkEtaPhi_Cent.push_back(subDir.make<TH2F>("","local track density grid",nbins,-3.15,3.15,nbins,-3.15,3.15));
     hNtrkEtaPhi_Cent[i]->SetName(Form("hNtrkEtaPhi_Cent%d",i));
  }
  hLocalTrkMultDist = subDir.make<TH1F>("hLocalTrkMultDist","local track density distribution",nbins_z,0.0,2000);
  hCentVsLocalTrkDen = subDir.make<TH2F>("hCentVsLocalTrkDen","centrality vs loc. trk. density;centrality;#rho_{trk}",40,0,40, nbins_z,0.0,2000);
  hJetEtVsLocalTrkDen = subDir.make<TH2F>("hJetEtVsLocalTrkDen","jet et vs loc. trk. density;E_{T} [GeV];#rho_{trk}",50,0,1000, nbins_z,0.0,2000);

  // dR is quantized. i.e minimum quanta is dbin, therefore bin width should be matched with deta (dphi) 
  hdRDist = subDir.make<TH1F>("hdRDist","dR distribution of closest track",250,0.0,1.0);  
  

}

// ------------ method called at the beginning of each new run  ------------
void
HiTrkEffAnalyzer::beginRun(const edm::Run& r, const edm::EventSetup& es)
{

  // Get tracker geometry
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiTrkEffAnalyzer::endJob()
{

  histograms->writeHistograms();

}

// ------------
SimTrack_t 
HiTrkEffAnalyzer::setSimTrack(TrackingParticle& tp, const reco::Track& mtr, size_t nrec, float jet, int cent)
{

  SimTrack_t s;
  s.ids = tp.pdgId();
  s.etas = tp.eta();
  if(oneOverPtMode_) s.pts = 1./tp.pt();
  else s.pts = tp.pt();
  s.hits = tp.matchedHit();
  s.status = tp.status();
  std::pair<bool,bool> acc = isAccepted(tp);
  s.acc = acc.first; // for HI tracking, only triplet should be taken 

#ifdef DEBUG
  edm::LogVerbatim("HiTrkEffAnalyzer")  
    << "primary simtrack pt=" << s.pts 
    << " eta=" << s.etas
    << " hits=" << s.hits
    << " pdgId=" << s.ids;
#endif

  s.nrec = nrec;
  s.jetr = jet;
  
  if(nrec > 0) {
    double dxy=0.0, dz=0.0, d0err=0.0, dzerr=0.0;
    testVertex(*const_cast<reco::Track*>(&mtr),dxy,dz,d0err,dzerr);
    if(oneOverPtMode_) s.ptr = 1./mtr.pt();
    else s.ptr = mtr.pt();
    s.d0 = dxy;
    s.dz = dz;
    s.d0err = d0err;
    s.dzerr = dzerr;
    s.pterr = mtr.ptError();
    s.hitr = mtr.numberOfValidHits();
    s.algo = mtr.algo();
  } else {
    s.ptr = 0.0;
    s.dz = 0.0;
    s.d0 = 0.0;
    s.pterr = 0.0;
    s.d0err = 0.0;
    s.dzerr = 0.0;
    s.hitr = 0;
    s.algo = 0;
  }

  s.cbin = cent;

  return s;

}

// ------------
RecTrack_t 
HiTrkEffAnalyzer::setRecTrack(reco::Track& tr, const TrackingParticle& tp, size_t nsim, float jet, int cent)
{

  RecTrack_t r;
  r.charge = tr.charge();
  r.etar = tr.eta();
  if(oneOverPtMode_) r.ptr = 1./tr.pt();
  else r.ptr = tr.pt();
  r.phir = tr.phi();

  double dxy=0.0, dz=0.0, d0err=0.0, dzerr=0.0;
  if(!testVertex(tr,dxy,dz,d0err,dzerr)) 
    edm::LogWarning("HiTrkEffAnalyzer") << "used the beamspot as there is no reco::Vertex";
  r.d0 = dxy;
  r.dz = dz;
  r.d0err = d0err;
  r.dzerr = dzerr;
  
  r.pterr = tr.ptError();
  r.hitr = tr.numberOfValidHits();
  r.algo = tr.algo();

#ifdef DEBUG
  edm::LogVerbatim("HiTrkEffAnalyzer")  
    << "reco track pt=" << r.ptr
    << " eta=" << r.etar
    << " hits=" << r.hitr;
#endif

  r.nsim = nsim;
  r.jetr = jet;

  if(nsim>0) {
    r.status = tp.status();
    r.ids = tp.pdgId();
    
    int parentId=0;
    if(tp.parentVertex()->nSourceTracks() > 0) {
      parentId = (*(tp.parentVertex()->sourceTracks_begin()))->pdgId();
      edm::LogVerbatim("HiTrkEffAnalyzer") 
    	<< "pdg Id = " << tp.pdgId()
    	<< " parent Id = " << parentId;
    }
    r.parids = parentId;
    
    r.etas = tp.eta();
    if(oneOverPtMode_) r.pts = tp.pt();
    else r.pts = 1./tp.pt();
  } else {
    r.status = 0;
    r.ids = 0;
    r.parids = 0;
    r.etas = 0.0;
    r.pts = 0.0;
  }
  
  r.cbin = cent;
  
  return r;

}

// ------------
bool
HiTrkEffAnalyzer::testVertex(reco::Track& tr, double &dxy, double &dz, double &d0err, double &dzerr)
{

  d0err = tr.d0Error();
  dzerr = tr.dzError();

  const reco::VertexCollection *vtxs = vertexCollectionH.product();

  if(vtxs->size() == 0 || vtxs->begin()->isFake()) {
    dxy = tr.dxy(beamSpotH->position());
    dz  = 0.0;
    d0err = sqrt ( (d0err*d0err) + (beamSpotH->BeamWidthX()*beamSpotH->BeamWidthY()) );
    dzerr = 0.0;
    return false;
  } else {
    dxy = tr.dxy(vtxs->begin()->position()); // FIX ME (use most populated vertex?)
    dz  = tr.dz(vtxs->begin()->position());  // FIX ME (or closest vertex to track?)
    d0err = sqrt ( (d0err*d0err) + (vtxs->begin()->xError()*vtxs->begin()->yError()) );
    dzerr = sqrt ( (dzerr*dzerr) + (vtxs->begin()->zError()*vtxs->begin()->zError()) );
    return true;
  }

}

// ------------
std::pair<bool,bool> 
HiTrkEffAnalyzer::isAccepted(TrackingParticle & tp)
{
  std::vector<bool> f(nLayers, false);

  const std::vector<PSimHit> & simHits = tp.trackPSimHit(DetId::Tracker);
  
  for(std::vector<PSimHit>::const_iterator simHit = simHits.begin();
                                      simHit!= simHits.end(); simHit++)
  {
    int id = getLayerId(*simHit);

    if(id != -1)
      f[id] = true;
  }

  bool canBeTriplet =
    ( (f[BPix1] && f[BPix2]     && f[BPix3]) ||
      (f[BPix1] && f[BPix2]     && f[FPix1_pos]) ||
      (f[BPix1] && f[BPix2]     && f[FPix1_neg]) ||
      (f[BPix1] && f[FPix1_pos] && f[FPix2_pos]) ||
      (f[BPix1] && f[FPix1_neg] && f[FPix2_neg]) );

  bool canBePair =
    ( (f[BPix1] && f[BPix2]) ||
      (f[BPix1] && f[BPix3]) ||
      (f[BPix2] && f[BPix3]) ||
      (f[BPix1] && f[FPix1_pos]) ||
      (f[BPix1] && f[FPix1_neg]) ||
      (f[BPix1] && f[FPix2_pos]) ||
      (f[BPix1] && f[FPix2_neg]) ||
      (f[BPix2] && f[FPix1_pos]) ||
      (f[BPix2] && f[FPix1_neg]) ||
      (f[BPix2] && f[FPix2_pos]) ||
      (f[BPix2] && f[FPix2_neg]) ||
      (f[FPix2_neg] && f[FPix2_neg]) ||
      (f[FPix2_pos] && f[FPix2_pos]) );

  return std::pair<bool,bool>(canBeTriplet, canBePair);
}

// ------------
int 
HiTrkEffAnalyzer::getLayerId(const PSimHit & simHit)
{
  unsigned int id = simHit.detUnitId();

  if(theTracker->idToDetUnit(id)->subDetector() ==
       GeomDetEnumerators::PixelBarrel)
  {
    PXBDetId pid(id);
    return pid.layer() - 1; // 0, 1, 2
  }

  if(theTracker->idToDetUnit(id)->subDetector() ==
       GeomDetEnumerators::PixelEndcap)
  {
    PXFDetId pid(id);
    return BPix3 + ((pid.side()-1) << 1) + pid.disk(); // 3 -
  }

  // strip
  return -1;
}

// ------------  
std::pair<float,float>
HiTrkEffAnalyzer::getLocalTrkDensity(TH2F*& hist, double eta, double phi){

   int obin = hist->FindBin(eta,phi); /// starting bin
   float tot_trk_ij = hist->GetBinContent(obin);
   int nx = hist->GetNbinsX() + 2; // needed for global 1d bin scheme
   float dbin = hist->GetXaxis()->GetBinWidth(1); // assuming same bin size in x,y
   

   int iter = 0; // +- 1, 2, 3, ... 
   float tot_trk_around = 0.0;

   while(tot_trk_around<1.0 && iter<50){ // cut off on iter

      iter++;

      // low bin ~ high bin : all the adjcent bin around the starting bin
      int bin_range = iter*(1+nx);
      int lowbin = obin -1*bin_range;
      int highbin = obin + bin_range;
      
      for(int i = lowbin; i<highbin+1; i++){ // search bins around ith,jth bin
	 float ntrk = 0.0;
	 if(i!=obin) 
	    ntrk = hist->GetBinContent(i);
	 tot_trk_around = tot_trk_around + ntrk; // count all tracks around 
      }
   }

   //std::cout<<"index = "<<iter<<std::endl;

   //float dr  = 0.5*dbin + (float) iter*dbin;
   float dr  = (float) iter*dbin;
   //float trk_density = (tot_trk_ij + tot_trk_around)/(dr*dr*20.); // an arbitrary scale factor applied
   float trk_density = (tot_trk_ij + tot_trk_around)/(dr*dr*50.);
   //trk_density = 0.05*pow(trk_density,1.5); // arbitrary scaling

   //std::cout<<"dR = "<<dr<<std::endl;

   return std::pair<float,float>(dr, trk_density);
   
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiTrkEffAnalyzer);