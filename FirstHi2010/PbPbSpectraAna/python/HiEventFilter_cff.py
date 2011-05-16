import FWCore.ParameterSet.Config as cms

from RecoHI.HiCentralityAlgos.CentralityFilter_cfi import *
from FirstHi2010.PbPbSpectraAna.hieventSelection_cff import *
from FirstHi2010.PbPbSpectraAna.hihfCoincFilter_cff import *
from FirstHi2010.PbPbSpectraAna.HiAnalyzers_cff import *

# Common HI ana
from HeavyIonsAnalysis.Configuration.collisionEventSelection_cff import *
primaryVertexFilter.cut=cms.string("!isFake && abs(z) <= 15 && position.Rho <= 2 && tracksSize >= 2") # to cut on |vz|<15 cm

# see FirstHi2010/PbPbSpectraAna/python/hicustomise_cfi.py 
centFilter = centralityFilter.clone(selectedBins = cms.vint32())

eventFilter = cms.Sequence(preTrgTest *
                           minBiasBscFilter *    # L1 and(or) HLT filter
                           postTrgTest *
                           collisionEventSelection * #
                           postEvtSelTest *
                           spikeCleaning
                           )
                           

jetEvtFilter = cms.Sequence(jetEtaSel)
