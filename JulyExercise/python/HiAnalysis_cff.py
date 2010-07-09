import FWCore.ParameterSet.Config as cms

from edwenger.Skims.HiAnalyzers_cff import *

hiAnalysisSeq = cms.Sequence(hipxltrackAna*
                             hipxltrackAnaMult*
                             hipxltrkEffAna*
                             hitrackAna*
                             hitrackAnaMult*
                             hitrkEffAna)
