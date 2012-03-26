#ifndef ROOT_GENPARTIClEINFO_H
#define ROOT_GENPARTIClEINFO_H

#include "TObject.h"
#include <vector>

using namespace std;

class GenParticleInfo : public TObject {

 public:
   GenParticleInfo();          // constructor
   virtual ~GenParticleInfo(); // desctructor
   
   float fPt, fEta, fPhi;
   int iCharge,iStatus,iPdgId;
   
   // see Adding class to ROOT (http://root.cern.ch/drupal/content/adding-your-class-root-classdef)
   ClassDef(GenParticleInfo,1) //  ClassDef(ClassName,ClassVersionID) 
      
};
      
#endif
