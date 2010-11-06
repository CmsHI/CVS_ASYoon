#include "FWCore/PluginManager/interface/ModuleDef.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "PbPbTrackingTools/CaloCompatibleTrackSelector/interface/CaloCompatibleTrackSelector.h"



using reco::modules::CaloCompatibleTrackSelector;


DEFINE_FWK_MODULE(CaloCompatibleTrackSelector);
