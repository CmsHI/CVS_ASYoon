#include "SpectraAna/GenJetSpectraAnalyzer/interface/FoundJets.h"

ClassImp(FoundJets)


FoundJets::FoundJets()
{

   fP = 0.0;
   fPt = 0.0;
   fRapid = 0.0;
   fEta = 0.0;
   iCharge = 0;
   iStatus = 0; 
   iPdgId = 0;
   iFromHQc = 0;
   iFromAnyHQc = 0;
   iFromHQb = 0;
   iFromAnyHQb = 0;
   //bIsMortherPartonQuark = true;

}

FoundJets::~FoundJets()
{
   Clear();
}



