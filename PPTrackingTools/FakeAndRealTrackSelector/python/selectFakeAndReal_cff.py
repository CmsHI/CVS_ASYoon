import FWCore.ParameterSet.Config as cms

import PPTrackingTools.FakeAndRealTrackSelector.selectFakeAndReal_cfi

selectReal = PPTrackingTools.FakeAndRealTrackSelector.selectFakeAndReal_cfi.selectFakeAndReal.clone(
    src = 'generalTracks',
    selectFake = False,
    #keepAllTracks = False,
    #copyExtras = False,
    #copyTrajectories = False,
    #chi2n_par = 0.2,
    #res_par = ( 0.003, 0.001 ),
    #minNumberLayers = 5,
    #maxNumberLostLayers = 0,
    #minNumber3DLayers = 2,
    #d0_par1 = ( 1.4, 4.0 ),
    #dz_par1 = ( 1.3, 4.0 ),
    #d0_par2 = ( 1.4, 4.0 ),
    #dz_par2 = ( 1.3, 4.0 )
)

selectFake = PPTrackingTools.FakeAndRealTrackSelector.selectFakeAndReal_cfi.selectFakeAndReal.clone(
        src = 'generalTracks',
        selectFake = True
        #keepAllTracks = False,
        #copyExtras = False,
        #copyTrajectories = False,
        #chi2n_par = 0.2,
        #res_par = ( 0.003, 0.001 ),
        #minNumberLayers = 5,
        #maxNumberLostLayers = 0,
        #minNumber3DLayers = 2,
        #d0_par1 = ( 1.4, 4.0 ),
        #dz_par1 = ( 1.3, 4.0 ),
        #d0_par2 = ( 1.4, 4.0 ),
        #dz_par2 = ( 1.3, 4.0 )
)

selectRealLoose = PPTrackingTools.FakeAndRealTrackSelector.selectFakeAndReal_cfi.selectFakeAndReal.clone(
        src = 'generalTracks',
        selectFake = False,
        qualityString = 'loose'
)

selectFakeLoose = PPTrackingTools.FakeAndRealTrackSelector.selectFakeAndReal_cfi.selectFakeAndReal.clone(
    src = 'generalTracks',
    selectFake = True,
    qualityString ='loose'
)


selectFakeAndReal = cms.Sequence(selectReal+selectFake)
selectFakeAndRealLoose = cms.Sequence(selectRealLoose+selectFakeLoose)
