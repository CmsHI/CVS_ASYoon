#ifndef ROOT_FOUNDJETS_H
#define ROOT_FOUNDJETS_H

#include "TObject.h"
#include <vector>

using namespace std;

class FoundJets : public TObject {

 public:
   FoundJets();          // constructor
   virtual ~FoundJets(); // desctructor
   
   float fP,fPt,fRapid,fEta;
   int iCharge,iStatus,iPdgId;
   int iFromHQc,iFromAnyHQc;
   int iFromHQb,iFromAnyHQb;
   //bool bIsMortherPartonQuark;
   
   ClassDef(FoundJets,10)
      
};
      
#endif
