import FWCore.ParameterSet.Config as cms

from RecoHI.HiCentralityAlgos.CentralityFilter_cfi import *

centFilter1st = centralityFilter.clone(selectedBins = cms.vint32(0))
centFilter2nd = centralityFilter.clone(selectedBins = cms.vint32(1,2))
centFilter3rd = centralityFilter.clone(selectedBins = cms.vint32(3,4))
centFilter4th = centralityFilter.clone(selectedBins = cms.vint32(5,6,7,8,9))
