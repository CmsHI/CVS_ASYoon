import FWCore.ParameterSet.Config as cms

pythiaUESettingsBlock = cms.PSet(
    pythiaUESettings = cms.vstring(

    ####
    #'MSTU(21)=1     ! Check on possible errors during program execution',
    #'MSTJ(22)=2     ! Decay those unstable particles',
    #'PARJ(71)=10.   ! for which ctau  10 mm',
    #'MSTP(2)=1      ! which order running alphaS',
    #'MSTP(33)=0     ! no K factors in hard cross sections',
    #'MSTP(51)=7     ! structure function chosen (internal PDF CTEQ5L)',
    #'MSTP(52)=1     ! work with internal PDF',
    #'MSTP(81)=1    ! multiple parton interactions 1 is Pythia default',
    #'MSTP(82)=4    ! Defines the multi-parton model',
    #'PARP(82)=1.8  ! pt cutoff for multiparton interactions',
    #'PARP(83)=0.5  ! Multiple interactions: matter distrbn parameter',
    #'PARP(84)=0.5  ! Multiple interactions: matter distribution parameter',
    #'PARP(85)=0.33 ! gluon prod. mechanism in MI',
    #'PARP(86)=0.66 ! gluon prod. mechanism in MI',
    #'PARP(89)=1000 ! sqrts for which PARP82 is set',
    #'PARP(90)=0.16 ! Multiple interactions: rescaling power',
    #'PARP(62)=1.0  !',
    #'PARP(64)=1.0  !',
    #'PARP(67)=1.0  ! amount of initial-state radiation',
    #'MSTP(91)=1    !',
    #'PARP(91)=1    ! kt distribution',
    #'PARP(93)=5.0  !'
    #####

    #####
    #'MSTJ(11)=3     ! Choice of the fragmentation function', 
    #'MSTJ(22)=2     ! Decay those unstable particles', 
    #'PARJ(71)=10 .  ! for which ctau  10 mm', 
    #'MSTP(2)=1      ! which order running alphaS', 
    #'MSTP(33)=0     ! no K factors in hard cross sections', 
    #'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)',
    #'MSTP(52)=2     ! work with LHAPDF',
    #'MSTU(21)=1     ! Check on possible errors during program execution', 
    #####

    #####
    #'MSTU(21)=1     ! Check on possible errors during program execution',
    #'MSTJ(22)=2     ! Decay those unstable particles',
    #'PARJ(71)=10.   ! for which ctau  10 mm',
    #'MSTP(2)=1      ! which order running alphaS',
    #'MSTP(33)=0     ! no K factors in hard cross sections',
    #'MSTP(51)=7     ! structure function chosen (internal PDF CTEQ5L)',
    #'MSTP(52)=1     ! work with internal PDF',
    #####


    )
)
