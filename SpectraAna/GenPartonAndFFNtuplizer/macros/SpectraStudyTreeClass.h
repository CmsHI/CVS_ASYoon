#ifndef SpectraStudyTreeClass_h
#define SpectraStudyTreeClass_h

// Convinient Output Classes

class SpectraStudyTreeClass {
public :
   SpectraStudyTreeClass() : 
   fPthat(-999), fCrossx(-999), nJets(0)
   {
   }

   // Declaration of leaf types
   float fPthat, fCrossx;
   int   nJets;
   int   nTrks[1000];  //[nJets]
   float fJPt[1000];   //[nJets]
   float fJEt[1000];   //[nJets]
   float fJEta[1000];   //[nJets]
   float fJPhi[1000];   //[nJets]

   void clear() {
      fPthat = -999; fCrossx = -999; nJets = 0;
   }
};

#endif

