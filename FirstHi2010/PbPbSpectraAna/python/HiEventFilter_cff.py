import FWCore.ParameterSet.Config as cms

from RecoHI.HiCentralityAlgos.CentralityFilter_cfi import *
from FirstHi2010.PbPbSpectraAna.hieventSelection_cff import *
from FirstHi2010.PbPbSpectraAna.hihfCoincFilter_cff import *
from FirstHi2010.PbPbSpectraAna.HiAnalyzers_cff import *

# Common HI ana
from HeavyIonsAnalysis.Configuration.collisionEventSelection_cff import *

# see FirstHi2010/PbPbSpectraAna/python/hicustomise_cfi.py 
centFilter = centralityFilter.clone(selectedBins = cms.vint32())

eventFilter = cms.Sequence(preEvtSelVtxAna *
                           minBiasBscFilter *    # L1 and(or) HLT filter
                           collisionEventSelection * #
                           postEvtSelVtxAna)

