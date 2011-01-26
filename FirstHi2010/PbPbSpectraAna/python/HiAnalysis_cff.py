import FWCore.ParameterSet.Config as cms

from FirstHi2010.PbPbSpectraAna.HiAnalyzers_cff import *
from edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff import *

hiAnalysisSeq = cms.Sequence(hipxltrackAna*
                             hipxltrkEffAna*
                             #(hitrackAna + hirefitTrackAna + hicompTrackAna)*
                             #(hitrackAna + hirefitTrackAna)
                             (higoodtrkval)* # hitrack validator 
                             (hitrackAna + hicaloTrackAna)*
                             (hiseltrkEffAna + hitrkEffAna))
