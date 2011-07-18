import FWCore.ParameterSet.Config as cms


#loose
hiTracksWithLooseQuality = cms.EDProducer("AnalyticalTrackSelector",
         src = cms.InputTag("hiGlobalPrimTracks"),
         keepAllTracks = cms.bool(True), ## if set to true tracks failing this filter are kept in the output
         beamspot = cms.InputTag("offlineBeamSpot"),

         # vertex selection                                          
         vertices = cms.InputTag("hiSelectedVertex"),
         vtxNumber = cms.int32(0),
         vertexCut = cms.string('ndof>=0&((chi2==0.0)|(chi2prob(chi2,ndof)>=0.01))'),

         #untracked bool copyTrajectories = true // when doing retracking before
         copyTrajectories = cms.untracked.bool(True),
         copyExtras = cms.untracked.bool(True), ## set to false on AOD
         qualityBit = cms.string('loose'), ## set to '' or comment out if you don't want to set the bit

         # parameters for cutting on pterror/pt and number of valid hits
         min_relpterr = cms.double(0.06),
         min_nhits = cms.uint32(10),
                                          
         # parameters for adapted optimal cuts on chi2 and primary vertex compatibility
         chi2n_par = cms.double(0.4), # already applied in hiSelectedTracks
         res_par = cms.vdouble(99999., 99999.),
         d0_par1 = cms.vdouble(99999., 0.0),
         dz_par1 = cms.vdouble(99999., 0.0),
         d0_par2 = cms.vdouble(999.0, 0.0),
         dz_par2 = cms.vdouble(999.0, 0.0),

         # Boolean indicating if adapted primary vertex compatibility cuts are to be applied.
         applyAdaptedPVCuts = cms.bool(True),
                                          
         # Impact parameter absolute cuts.
         max_d0 = cms.double(1000),
         max_z0 = cms.double(1000),
         nSigmaZ = cms.double(3.),
                                          
         # Cuts on numbers of layers with hits/3D hits/lost hits.
         minNumberLayers = cms.uint32(7),
         minNumber3DLayers = cms.uint32(3),
         maxNumberLostLayers = cms.uint32(99999),

         # Absolute cuts in case of no PV. If yes, please define also max_d0NoPV and max_z0NoPV
         applyAbsCutsIfNoPV = cms.bool(False)
)

#tight
hiTracksWithTightQuality = hiTracksWithLooseQuality.clone(
    src = cms.InputTag("hiTracksWithLooseQuality"),
    qualityBit = cms.string('tight'),
    min_nhits = cms.uint32(12),
    d0_par2 = cms.vdouble(999.0, 0.0),
    dz_par2 = cms.vdouble(999.0, 0.0)
)

#highPurity
hiSelectedTracks = hiTracksWithLooseQuality.clone(
    src = cms.InputTag("hiTracksWithTightQuality"),
    qualityBit = cms.string('highPurity'),
    min_nhits = cms.uint32(13),
    chi2n_par = cms.double(0.15), 
    d0_par2 = cms.vdouble(999.0, 0.0),
    dz_par2 = cms.vdouble(999.0, 0.0)
)

#example filters (it will produce a separate track collection)
hiGoodTightTracks = cms.EDProducer("QualityFilter",
      TrackQuality = cms.string('highPurity'),
      recTracks = cms.InputTag("hiSelectedTracks")
)


#complete sequence
hiTracksWithQuality = cms.Sequence(hiTracksWithLooseQuality
                                   * hiTracksWithTightQuality
                                   * hiSelectedTracks)

