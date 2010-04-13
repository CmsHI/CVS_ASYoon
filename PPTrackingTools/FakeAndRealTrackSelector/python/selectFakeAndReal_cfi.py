import FWCore.ParameterSet.Config as cms

selectFakeAndReal = cms.EDProducer("FakeAndRealTrackSelector",
    src = cms.InputTag("generalTracks"),
    keepAllTracks = cms.bool(False), ## if set to true tracks failing this filter are kept in the output
    beamspot = cms.InputTag("offlineBeamSpot"),
    selectFake = cms.untracked.bool(False),
    qualityString = cms.string('highPurity'),                                   

    vertices = cms.InputTag("pixelVertices"),
    vtxNumber = cms.int32(-1),
    vtxTracks = cms.uint32(3), ## at least 3 tracks
    vtxChi2Prob = cms.double(0.01), ## at least 1% chi2nprobability (if it has a chi2)

    #untracked bool copyTrajectories = true // when doing retracking before
    copyTrajectories = cms.untracked.bool(False),
    copyExtras = cms.untracked.bool(True), ## set to false on AOD
    qualityBit = cms.string('highPurity'), ## set to '' or comment out if you don't want to set the bit


    # parameters for adapted optimal cuts on chi2 and primary vertex compatibility
    chi2n_par = cms.double(0.9),
    res_par = cms.vdouble(0.003, 0.001),
    d0_par1 = cms.vdouble(0.3, 4.0),
    dz_par1 = cms.vdouble(0.35, 4.0),
    d0_par2 = cms.vdouble(0.4, 4.0),
    dz_par2 = cms.vdouble(0.4, 4.0),
    # Boolean indicating if adapted primary vertex compatibility cuts are to be applied.
    applyAdaptedPVCuts = cms.bool(True),

    # Impact parameter absolute cuts.
    max_d0 = cms.double(100.),
    max_z0 = cms.double(100.),

    # Cuts on numbers of layers with hits/3D hits/lost hits. 
    minNumberLayers = cms.uint32(4),
    minNumber3DLayers = cms.uint32(4),
    maxNumberLostLayers = cms.uint32(2)
                                
)

