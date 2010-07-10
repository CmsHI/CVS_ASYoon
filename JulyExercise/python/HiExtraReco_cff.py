import FWCore.ParameterSet.Config as cms

from edwenger.Skims.HiLowPtPxlRereco_cff import *
from edwenger.Skims.HiCentralityInfo_cff import *
from edwenger.Skims.HiTrackRefit_cff import *

hiextraReco = cms.Sequence(hicentProd*
                           hiLowPtPixelTracks*
                           hitrackRefit)
