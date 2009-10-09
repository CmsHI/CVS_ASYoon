#ifndef ROOT_FOUNDJETS_H
#define ROOT_FOUNDJETS_H

#include "TObject.h"
#include <vector>

using namespace std;

class FoundJets : public TObject {

 public:
   FoundJets();          // constructor
   virtual ~FoundJets(); // desctructor
   
   float fPt,fRapid;
   int iCharge,iStatus,iPdgId;
   int iFromHQ,iFromAnyHQ;
   //bool bIsMortherPartonQuark;
   
   ClassDef(FoundJets,7)
      
};
      
#endif
