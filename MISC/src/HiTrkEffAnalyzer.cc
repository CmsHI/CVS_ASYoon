//
// Original Author:  Edward Wenger
//         Created:  Thu Apr 29 14:31:47 CEST 2010
// $Id: HiTrkEffAnalyzer.cc,v 1.3 2010/09/30 15:09:18 sungho Exp $
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
  nearJetMode_(iConfig.getUntrackedParameter<int>("nearJetMode",0)),
  binsEtaPhi_(iConfig.getUntrackedParameter<std::vector<int> >("binsEtaPhi")),
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
  if(pixelMultMode_){
     pixelMult = 1200;
  } 

  if(!centrality_) centrality_ = new CentralityProvider(iSetup);
  centrality_->newEvent(iEvent,iSetup);
  float cent = (float) centrality_->getBin();

  // PAT jet, to get leading jet ET

  float jet_et = 0.0;
  float jet_eta_near=0.0, jet_eta_away=0.0;
  float jet_phi_near=0.0, jet_phi_away=0.0;

  std::vector<const pat::Jet *> sortedJets;

  if(useJetEt_){
     edm::Handle<std::vector<pat::Jet> > jets;
     iEvent.getByLabel(jetTags_, jets);
     
     //std::vector<const pat::Jet *> sortedJets;
     
     for(unsigned it=0; it<jets->size(); ++it){
	const pat::Jet* jts = &((*jets)[it]);
	sortedJets.push_back( & *jts);
	sortByEtRef (&sortedJets);
     }
     
     for(unsigned it=0; it<sortedJets.size(); ++it){
	if(it==0) jet_et = sortedJets[it]->et(), jet_eta_near = sortedJets[it]->eta(), jet_phi_near = sortedJets[it]->phi();
	if(it==1) jet_eta_away =sortedJets[it]->eta(), jet_phi_away = sortedJets[it]->phi();
     }
  }


  // pre-RECO loop to determine local track density
  hNtrkEtaPhi->Reset(); // need to be reset for every event
  for(edm::View<reco::Track>::size_type j=0; j<trackCollection->size(); ++j){

     edm::RefToBase<reco::Track> track(trackCollection, j);
     reco::Track* tr=const_cast<reco::Track*>(track.get());
     
     hNtrkEtaPhi->Fill(tr->eta(),tr->phi());
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

      // dR of tracks with respect leading and sub-leading jet ------------------------------------
      if(useJetEt_){

	 float deta_near = jet_eta_near - tp->eta();
	 float deta_away = jet_eta_away - tp->eta();
	 
	 float dphi_near = jet_phi_near - tp->phi();
	 float dphi_away = jet_phi_away - tp->phi();

	 if(fabs(dphi_near)>(TMath::Pi()))
	    dphi_near = (dphi_near>0) ? dphi_near - (float) 2.*TMath::Pi() : dphi_near + (float) 2.*TMath::Pi(); 

	 if(fabs(dphi_away)>(TMath::Pi()))
	    dphi_away = (dphi_away>0) ? dphi_away - (float) 2.*TMath::Pi() : dphi_away + (float) 2.*TMath::Pi();
	 
	 float dR_near = TMath::Sqrt(deta_near*deta_near + dphi_near*dphi_near);
	 float dR_away = TMath::Sqrt(deta_away*deta_away + dphi_away*dphi_away);
	 
	 if(nearJetMode_ == 1 && dR_near>0.7) continue; // only tracks around leading jet
	 if(nearJetMode_ == 2 && dR_away>0.7) continue; // only tracks around sub-leading jet 
	 if(nearJetMode_ == 3 && (dR_near<0.7 || dR_away<0.7)) continue; // only tracks outside leading,sub-leading jets
      }
      //---------------------------------------------------------------------------------------------

      std::vector<std::pair<edm::RefToBase<reco::Track>, double> > rt;
      const reco::Track* mtr=0;
      size_t nrec=0;
      
      if(simRecColl.find(tpr) != simRecColl.end()){
	rt = (std::vector<std::pair<edm::RefToBase<reco::Track>, double> >) simRecColl[tpr];
	nrec=rt.size();   
	if(nrec) mtr = rt.begin()->first.get();      
      }

      int eta_bin = hNtrkEtaPhi->GetXaxis()->FindBin(tp->eta());
      int phi_bin = hNtrkEtaPhi->GetYaxis()->FindBin(tp->phi());
      float slocaltrkmult 
	 = hNtrkEtaPhi->GetBinContent(eta_bin,phi_bin);
      
      /*
      if(nearJetMode_ == 0) {
	 std::cout<<"found bin x = "<<eta_bin<<" found bin y = "<<phi_bin<<std::endl;
	 std::cout<<"local track density = "<<slocaltrkmult<<std::endl;
      }
      */

      SimTrack_t s = setSimTrack(*tp, *mtr, nrec, slocaltrkmult);
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
    
    // dR of tracks with respect leading and sub-leading jet -------------------------------------
    if(useJetEt_){
       float deta_near = jet_eta_near - tr->eta();
       float deta_away = jet_eta_away - tr->eta();

       float dphi_near = jet_phi_near - tr->phi();
       float dphi_away = jet_phi_away - tr->phi();

       if(fabs(dphi_near)>(TMath::Pi()))
	  dphi_near = (dphi_near>0) ? dphi_near - (float) 2.*TMath::Pi() : dphi_near + (float) 2.*TMath::Pi();

       if(fabs(dphi_away)>(TMath::Pi()))
	  dphi_away = (dphi_away>0) ? dphi_away - (float) 2.*TMath::Pi() : dphi_away + (float) 2.*TMath::Pi();

       float dR_near = TMath::Sqrt(deta_near*deta_near + dphi_near*dphi_near);
       float dR_away = TMath::Sqrt(deta_away*deta_away + dphi_away*dphi_away);

       if(nearJetMode_ == 1 && dR_near>0.7) continue; // only tracks around leading jet                                                                   
       if(nearJetMode_ == 2 && dR_away>0.7) continue; // only tracks around sub-leading jet                                                               
       if(nearJetMode_ == 3 && (dR_near<0.7 || dR_away<0.7)) continue; // only tracks outside leading,sub-leading jets
    }
    //---------------------------------------------------------------------------------------------

    std::vector<std::pair<TrackingParticleRef, double> > tp;
    const TrackingParticle *mtp=0;
    size_t nsim=0;

    if(hasSimInfo_ && recSimColl.find(track) != recSimColl.end()){
      tp = recSimColl[track];
      nsim=tp.size();
      if(nsim) mtp = tp.begin()->first.get();       
    }

    int eta_bin = hNtrkEtaPhi->GetXaxis()->FindBin(tr->eta());
    int phi_bin = hNtrkEtaPhi->GetYaxis()->FindBin(tr->phi());
    float rlocaltrkmult 
       = hNtrkEtaPhi->GetBinContent(eta_bin,phi_bin);

    hCentVsLocalTrkDen->Fill(cent,rlocaltrkmult);

    RecTrack_t r = setRecTrack(*tr, *mtp, nsim, rlocaltrkmult);
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
  hNtrkEtaPhi = f->make<TH2F>("hNtrkEtaPhi","local track density grid",binsEtaPhi_[0],-2.5,2.5, binsEtaPhi_[1],-3.2,3.2); 
  hCentVsLocalTrkDen = f->make<TH2F>("hCentVsLocalTrkDen","centrality vs loc. trk. density;centrality;#rho_{trk}",40,0,40,50,0,50);

}

// ------------ method called at the beginning of each new run  ------------
void
HiTrkEffAnalyzer::beginRun(const edm::Run& r, const edm::EventSetup& es)
{
  // Get tracker geometry
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

  // histogram for reco track density
  //histograms->declareHistGrid();
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiTrkEffAnalyzer::endJob()
{

  histograms->writeHistograms();

}

// ------------
SimTrack_t 
HiTrkEffAnalyzer::setSimTrack(TrackingParticle& tp, const reco::Track& mtr, size_t nrec, float jet)
{

  SimTrack_t s;
  s.ids = tp.pdgId();
  s.etas = tp.eta();
  s.pts = tp.pt();
  s.hits = tp.matchedHit();
  s.status = tp.status();
  std::pair<bool,bool> acc = isAccepted(tp);
  s.acc = acc.first || acc.second;

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
    s.ptr = mtr.pt();
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

  return s;

}

// ------------
RecTrack_t 
HiTrkEffAnalyzer::setRecTrack(reco::Track& tr, const TrackingParticle& tp, size_t nsim, float jet)
{

  RecTrack_t r;
  r.charge = tr.charge();
  r.etar = tr.eta();
  r.ptr = tr.pt();
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
    r.pts = tp.pt();
  } else {
    r.status = 0;
    r.ids = 0;
    r.parids = 0;
    r.etas = 0.0;
    r.pts = 0.0;
  }
  
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

//define this as a plug-in
DEFINE_FWK_MODULE(HiTrkEffAnalyzer);
