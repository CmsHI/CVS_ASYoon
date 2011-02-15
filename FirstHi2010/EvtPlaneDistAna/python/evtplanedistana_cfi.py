import FWCore.ParameterSet.Config as cms

evtPlnAna = cms.EDAnalyzer('EvtPlaneDistAna',
            epLabel=cms.untracked.string("Calo")  # later, change it to vector of string
)
