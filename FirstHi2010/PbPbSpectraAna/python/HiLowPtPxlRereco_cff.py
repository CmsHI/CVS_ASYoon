import FWCore.ParameterSet.Config as cms

from RecoLocalTracker.SiPixelRecHits.SiPixelRecHits_cfi import *
from RecoHI.HiTracking.LowPtTracking_PbPb_cff import *

hiLowPtPixelTracks = hiPixel3PrimTracks.clone()
hiLowPtPixelTracks.RegionFactoryPSet.RegionPSet.ptMin = cms.double(0.2)
hiLowPtPixelTracks.FilterPSet.ptMin = cms.double(0.2)
hiLowPtPixelTracks.FilterPSet.nSigmaTipMaxTolerance = cms.double(4.0)
hiLowPtPixelTracks.FilterPSet.tipMax = cms.double(0.2)
hiLowPtPixelTracks.FilterPSet.nSigmaLipMaxTolerance = cms.double(4.0)
hiLowPtPixelTracks.FilterPSet.lipmax = cms.double(0.2)
hiLowPtPixelTracks.OrderedHitsFactoryPSet.GeneratorPSet.maxElement = 5000000

