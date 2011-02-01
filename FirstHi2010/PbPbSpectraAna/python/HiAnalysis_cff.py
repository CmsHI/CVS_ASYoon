import FWCore.ParameterSet.Config as cms

from FirstHi2010.PbPbSpectraAna.HiAnalyzers_cff import *
from edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff import *

hiAnalysisSeq = cms.Sequence(hipxltrackAna*                    # low pt pixel track
                             hipxltrkEffAna*
                             (hihightrkval    + higoodtrkval)* # hitrack validator 
                             (hihightrackAna  + hitrackAna)*
                             (hihightrkEffAna + hitrkEffAna))
