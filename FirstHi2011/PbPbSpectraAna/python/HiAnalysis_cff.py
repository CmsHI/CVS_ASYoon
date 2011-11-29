import FWCore.ParameterSet.Config as cms

from FirstHi2011.PbPbSpectraAna.HiAnalyzers_cff import *
from edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff import *

hiAnalysisSeq = cms.Sequence(extraCentDist*                    # centrality dist. for events with jet threshold
                             higoodtrkval_all*                 # hitrack validator 
                             (hitrackAna       + hitrackAna_jetMode1     + hitrackAna_jetMode2)*
                             hitrkEffAna)
