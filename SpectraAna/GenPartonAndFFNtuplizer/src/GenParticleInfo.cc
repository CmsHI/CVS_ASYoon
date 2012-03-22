#include "SpectraAna/GenPartonAndFFNtuplizer/interface/GenParticleInfo.h"

ClassImp(GenParticleInfo)


GenParticleInfo::GenParticleInfo()
{

   fPt = 0.0;
   fEta = 0.0;
   fPhi = 0.0;
   iCharge = 0;
   iStatus = 0; 
   iPdgId = 0;
}

GenParticleInfo::~GenParticleInfo()
{
   Clear();
}
