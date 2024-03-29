//
// Original Author:  Edward Wenger
//         Created:  Thu Apr 29 14:31:47 CEST 2010
// $Id: TrkEffAnalyzer.cc,v 1.9 2010/05/05 10:47:22 edwenger Exp $
//

#include <vector>


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
#include "edwenger/TrkEffAnalyzer/interface/TrkEffAnalyzer.h"

//#define DEBUG

TrkEffAnalyzer::TrkEffAnalyzer(const edm::ParameterSet& iConfig)
:
  trackTags_(iConfig.getUntrackedParameter<edm::InputTag>("tracks")),
  label_tp_effic_(iConfig.getUntrackedParameter<edm::InputTag>("label_tp_effic")),
  label_tp_fake_(iConfig.getUntrackedParameter<edm::InputTag>("label_tp_fake")),
  associatorMap_(iConfig.getUntrackedParameter<edm::InputTag>("associatormap")),
  vtxTags_(iConfig.getUntrackedParameter<edm::InputTag>("vertices")),
  bsTags_(iConfig.getUntrackedParameter<edm::InputTag>("beamspot")),
  doAssociation_(iConfig.getUntrackedParameter<bool>("doAssociation",true)),
  dThetaCut_(iConfig.getUntrackedParameter<double>("dThetaCut",0.17))
{

  histograms = new TrkEffHistograms(iConfig);

}


// ------------ method called for each event  ------------
void
TrkEffAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  const TrackAssociatorByHits * theAssociatorByHits;

  // sim track collections

  edm::Handle<TrackingParticleCollection>  TPCollectionHeff ;
  iEvent.getByLabel(label_tp_effic_,TPCollectionHeff);
  const TrackingParticleCollection tPCeff = *(TPCollectionHeff.product());
  
  edm::Handle<TrackingParticleCollection>  TPCollectionHfake ;
  iEvent.getByLabel(label_tp_fake_,TPCollectionHfake);
  const TrackingParticleCollection tPCfake = *(TPCollectionHfake.product());

  // reco track, vertex, beamspot collections

  edm::Handle<edm::View<reco::Track> >  trackCollection;
  iEvent.getByLabel(trackTags_,trackCollection);

  iEvent.getByLabel(vtxTags_,vertexCollectionH);
  iEvent.getByLabel(bsTags_,beamSpotH);

  // association map

  reco::RecoToSimCollection recSimColl;
  reco::SimToRecoCollection simRecColl;

  if(doAssociation_){
     edm::ESHandle<TrackAssociatorBase> theAssociator;
     iSetup.get<TrackAssociatorRecord>().get("TrackAssociatorByHits",theAssociator);
     theAssociatorByHits = (const TrackAssociatorByHits*) theAssociator.product();
     simRecColl= theAssociatorByHits->associateSimToReco(trackCollection,TPCollectionHeff,&iEvent);
     recSimColl= theAssociatorByHits->associateRecoToSim(trackCollection,TPCollectionHfake,&iEvent);
  }else{
     edm::Handle<reco::SimToRecoCollection > simtorecoCollectionH;
     iEvent.getByLabel(associatorMap_,simtorecoCollectionH);
     simRecColl= *(simtorecoCollectionH.product());

     edm::Handle<reco::RecoToSimCollection > recotosimCollectionH;
     iEvent.getByLabel(associatorMap_,recotosimCollectionH);
     recSimColl= *(recotosimCollectionH.product());
  }



  // SIM loop
  float cuts = (float) dThetaCut_;
  int mults = getEvtMultiplicity(TPCollectionHeff);
  
  for(TrackingParticleCollection::size_type i=0; i<tPCeff.size(); i++) {

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
     
    std::pair<int,float> trkdensity =  getLocalTrkDensity(TPCollectionHeff,*tp,cuts);

    SimTrack_t s = setSimTrack(*tp, *mtr, nrec, trkdensity.second, trkdensity.first, mults);
    histograms->fillSimHistograms(s);  

#ifdef DEBUG
    if(nrec) edm::LogTrace("TrkEffAnalyzer") 
      << "TrackingParticle #" << i << " with pt=" << tp->pt() 
      << " associated with quality:" << rt.begin()->second;
#endif
  }


  // RECO loop
  //int multr = getEvtMultiplicity(trackCollection);
  int multr = (int)trackCollection->size();
  
  for(edm::View<reco::Track>::size_type i=0; i<trackCollection->size(); ++i){
    
    edm::RefToBase<reco::Track> track(trackCollection, i);
    reco::Track* tr=const_cast<reco::Track*>(track.get());
    
    std::vector<std::pair<TrackingParticleRef, double> > tp;
    const TrackingParticle *mtp=0;
    size_t nsim=0;

    if(recSimColl.find(track) != recSimColl.end()){
      tp = recSimColl[track];
      nsim=tp.size();
      if(nsim) mtp = tp.begin()->first.get();       
    }

    std::pair<int,float> trkdensity_r =  getLocalTrkDensity(trackCollection,*tr,cuts);


    RecTrack_t r = setRecTrack(*tr, *mtp, nsim, trkdensity_r.second, trkdensity_r.first, multr);
    histograms->fillRecHistograms(r); 

#ifdef DEBUG
    if(nsim) edm::LogTrace("TrkEffAnalyzer") 
      << "reco::Track #" << i << " with pt=" << track->pt() 
      << " associated with quality:" << tp.begin()->second;
#endif
  }

}


// ------------ method called once each job just before starting event loop  ------------
void 
TrkEffAnalyzer::beginJob()
{

  histograms->declareHistograms();

}

// ------------ method called at the beginning of each new run  ------------
void
TrkEffAnalyzer::beginRun(const edm::Run& r, const edm::EventSetup& es)
{

  // Get tracker geometry
  edm::ESHandle<TrackerGeometry> tracker;
  es.get<TrackerDigiGeometryRecord>().get(tracker);
  theTracker = tracker.product();

}

// ------------ method called once each job just after ending the event loop  ------------
void 
TrkEffAnalyzer::endJob()
{

  histograms->writeHistograms();

}

// ------------
SimTrack_t 
TrkEffAnalyzer::setSimTrack(TrackingParticle& tp, const reco::Track& mtr, size_t nrec, float closestTheta, int trackInside, int mults)
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
  edm::LogTrace("TrkEffAnalyzer")  
    << "primary simtrack pt=" << s.pts 
    << " eta=" << s.etas
    << " hits=" << s.hits
    << " pdgId=" << s.ids;
#endif

  s.nrec = nrec;
  s.ctheta = closestTheta;
  s.density = trackInside;
  s.mults = mults;

  if(nrec > 0) {
    double dxy=0.0, dz=0.0;
    testVertex(*const_cast<reco::Track*>(&mtr),dxy,dz);
    s.d0 = dxy;
    s.dz = dz;
    s.pterr = mtr.ptError();
    s.d0err = mtr.d0Error();
    s.dzerr = mtr.dzError();
    s.hitr = mtr.numberOfValidHits();
    s.algo = mtr.algo();
  } else {
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
TrkEffAnalyzer::setRecTrack(reco::Track& tr, const TrackingParticle& tp, size_t nsim, float closestTheta, int trackInside, int multr)
{

  RecTrack_t r;
  r.charge = tr.charge();
  r.etar = tr.eta();
  r.ptr = tr.pt();
  r.phir = tr.phi();

  double dxy=0.0, dz=0.0;
  if(!testVertex(tr,dxy,dz)) 
    std::cout << "used the beamspot as there is no vertex" << std::endl;
  r.d0 = dxy;
  r.dz = dz;
  
  r.pterr = tr.ptError();
  r.d0err = tr.d0Error(); // FIX ME (include vtx error in quadrature?)
  r.dzerr = tr.dzError(); // FIX ME 
  r.hitr = tr.numberOfValidHits();
  r.algo = tr.algo();

#ifdef DEBUG
  edm::LogTrace("TrkEffAnalyzer")  
    << "reco track pt=" << r.ptr
    << " eta=" << r.etar
    << " hits=" << r.hitr;
#endif

  r.nsim = nsim;

  if(nsim>0) {
    r.ids = tp.pdgId();
    r.parids = 0; // FIX ME (add parent id)
    r.etas = tp.eta();
    r.pts = tp.pt();
  } else {
    r.ids = 0;
    r.parids = 0;
    r.etas = 0.0;
    r.pts = 0.0;
  }
  
  r.ctheta = closestTheta;
  r.density = trackInside;
  r.multr = multr;

  return r;

}

// ------------
bool
TrkEffAnalyzer::testVertex(reco::Track& tr, double &dxy, double &dz)
{

  const reco::VertexCollection *vtxs = vertexCollectionH.product();

  if(vtxs->size() == 0 || vtxs->begin()->isFake()) {
    dxy = tr.dxy(beamSpotH->position());
    dz  = 0.0;
    return false;
  } else {
    dxy = tr.dxy(vtxs->begin()->position()); // FIX ME (use most populated vertex?)
    dz  = tr.dz(vtxs->begin()->position());  // FIX ME (or closest vertex to track?)
    return true;
  }

}

// ------------
std::pair<bool,bool> 
TrkEffAnalyzer::isAccepted(TrackingParticle & tp)
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
      (f[BPix2] && f[FPix2_neg]) );

  return std::pair<bool,bool>(canBeTriplet, canBePair);
}

// ------------
int 
TrkEffAnalyzer::getLayerId(const PSimHit & simHit)
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
int
TrkEffAnalyzer::getEvtMultiplicity(edm::Handle<TrackingParticleCollection>& tPColl)
{
   int mlt = 0;

   for(TrackingParticleCollection::size_type i=0; i<tPColl.product()->size(); i++) {
      TrackingParticleRef tpref(tPColl, i);
      TrackingParticle* tpTrack=const_cast<TrackingParticle*>(tpref.get());
      if(tpTrack->status() < 0 || tpTrack->charge()==0) continue; //only charged primaries       
      mlt++;
   }
   return mlt;
}

int
TrkEffAnalyzer::getEvtMultiplicity(edm::Handle<edm::View<reco::Track> >& trackColl)
{
   int mlt = 0;

   for(edm::View<reco::Track>::size_type i=0; i<trackColl->size(); ++i){
      edm::RefToBase<reco::Track> trackref(trackColl, i);
      reco::Track* trTrack=const_cast<reco::Track*>(trackref.get());
      mlt++;
   }

   return mlt;
}

// ------------
std::pair<int,float>
TrkEffAnalyzer::getLocalTrkDensity(edm::Handle<TrackingParticleCollection>& tPColl, TrackingParticle & tpa, float &cut)
{
   
   int trkDensity = 0;
   float closestTheta = -999; 
   std::vector<float> vdTheta;

   float px1 = tpa.px(), py1 = tpa.py(), pz1 = tpa.pz();
   float p1_mag = sqrt(px1*px1+py1*py1+pz1*pz1);

   for(TrackingParticleCollection::size_type i=0; i<tPColl.product()->size(); i++) {
      TrackingParticleRef tpref(tPColl, i);
      TrackingParticle* tpa2=const_cast<TrackingParticle*>(tpref.get());
      if(tpa2->status() < 0 || tpa2->charge()==0) continue; //only charged primaries

      float px2 = tpa2->px(), py2 = tpa2->py(), pz2 = tpa2->pz();
      float p2_mag = sqrt(px2*px2+py2*py2+pz2*pz2);
      float p1dotp2 = px1*px2+py1*py2+pz1*pz2;
      if(px1==px2 && py1==py2 && pz1==pz2) continue;

      float dTheta  =  acos(p1dotp2/(p1_mag*p2_mag));

      vdTheta.push_back(dTheta);
      if(dTheta<cut) trkDensity++;
   }

   if(vdTheta.size()!=0) {
      sort(vdTheta.begin(),vdTheta.end());
      size_t index = 0;
      closestTheta = vdTheta[index];
   }else {
      closestTheta = -999;
   }
   return std::pair<int,float>(trkDensity, closestTheta);
}

std::pair<int,float>
TrkEffAnalyzer::getLocalTrkDensity(edm::Handle<edm::View<reco::Track> >& trackColl, reco::Track& tra, float &cut)
{

   int trkDensity = 0;
   float closestTheta = -999;
   std::vector<float> vdTheta;

   float px1 = tra.px(), py1 = tra.py(), pz1 = tra.pz();
   float p1_mag = sqrt(px1*px1+py1*py1+pz1*pz1);

   for(edm::View<reco::Track>::size_type i=0; i<trackColl->size(); ++i){
      edm::RefToBase<reco::Track> trackref(trackColl, i);
      reco::Track* tra2=const_cast<reco::Track*>(trackref.get());

      float px2 = tra2->px(), py2 = tra2->py(), pz2 = tra2->pz();
      float p2_mag = sqrt(px2*px2+py2*py2+pz2*pz2);
      float p1dotp2 = px1*px2+py1*py2+pz1*pz2;
      if(px1==px2 && py1==py2 && pz1==pz2) continue;

      float dTheta  =  acos(p1dotp2/(p1_mag*p2_mag));

      vdTheta.push_back(dTheta);
      if(dTheta<cut) trkDensity++;
   }

   if(vdTheta.size()!=0) {
      sort(vdTheta.begin(),vdTheta.end());
      size_t index = 0;
      closestTheta = vdTheta[index];
   }else {
      closestTheta = -999;
   }
   return std::pair<int,float>(trkDensity, closestTheta);
}


//define this as a plug-in
DEFINE_FWK_MODULE(TrkEffAnalyzer);
