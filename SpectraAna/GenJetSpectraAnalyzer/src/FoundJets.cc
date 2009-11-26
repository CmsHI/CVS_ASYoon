#include "SpectraAna/GenJetSpectraAnalyzer/interface/FoundJets.h"

ClassImp(FoundJets)


FoundJets::FoundJets()
{

   fPt = 0.0;
   fRapid = 0.0;
   iCharge = 0;
   iStatus = 0; 
   iPdgId = 0;
   iFromHQ = 0;
   iFromAnyHQ = 0;
   //bIsMortherPartonQuark = true;

}

FoundJets::~FoundJets()
{
   Clear();
}


