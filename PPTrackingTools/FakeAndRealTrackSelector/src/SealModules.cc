#include "FWCore/PluginManager/interface/ModuleDef.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "PPTrackingTools/FakeAndRealTrackSelector/interface/FakeAndRealTrackSelector.h"



using reco::modules::FakeAndRealTrackSelector;


DEFINE_FWK_MODULE(FakeAndRealTrackSelector);
