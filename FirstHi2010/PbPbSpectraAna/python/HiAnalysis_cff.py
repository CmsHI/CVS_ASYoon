import FWCore.ParameterSet.Config as cms

from FirstHi2010.PbPbSpectraAna.HiAnalyzers_cff import *
from edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff import *

hiAnalysisSeq = cms.Sequence(extraCentDist*                    # centrality dist. for events with jet threshold
                             hipxltrackAna*                    # low pt pixel track
                             hipxltrkEffAna*
                             (hihightrkval    + higoodtrkval)* # hitrack validator 
                             (hihightrackAna  + hihightrackAna_jetMode1 + hihightrackAna_jetMode2)*
                             (hitrackAna      + hitrackAna_jetMode1     + hitrackAna_jetMode2 )*
                             (hihightrkEffAna + hitrkEffAna))
