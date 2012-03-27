import FWCore.ParameterSet.Config as cms


def enableMinPtHatCut(process,genTypePtHatRange):
    if genTypePtHatRange=='NSD_0_to_5':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(5.0)
    if genTypePtHatRange=='NSD_0_to_10':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(10.0)
    if genTypePtHatRange=='NSD_0_to_15':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(15.0)
    if genTypePtHatRange=='NSD_0_to_20':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(20.0)
    if genTypePtHatRange=='ENSD_0_to_5':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(5.0)
    if genTypePtHatRange=='ENSD_0_to_10':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(10.0)
    if genTypePtHatRange=='ENSD_0_to_15':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(15.0)
    if genTypePtHatRange=='ENSD_0_to_20':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(20.0)
    if genTypePtHatRange=='ENSD_0_to_30':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(30.0)
    if genTypePtHatRange=='MB_0_to_5':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(5.0)
    if genTypePtHatRange=='MB_0_to_10':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(10.0)
    if genTypePtHatRange=='MB_0_to_15':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(15.0)
    if genTypePtHatRange=='MB_0_to_20':
        print "Min pT_hat cut enable"
        process.genSpectAna.pthatCut=cms.untracked.double(20.0)
    return process


# Check this values for various tunes!
def getPy6ProcXsection(genTypePtHatRange):
    para = {
        'NSD_0_to_5':4.130E+01,
        'NSD_5_to_10':1.155E+01,
        'NSD_10_to_20':9.073E-01,
        'NSD_0_to_10':4.130E+01,
        'NSD_0_to_15':4.130E+01,
        'NSD_0_to_20':4.130E+01,
        'NSD_15_to_20':1.373E-01,
        'NSD_20_to_30':4.903E-02,
        'NSD_30_to_50':9.366E-03,
        'NSD_50_to_80':9.071E-04,
        'NSD_80_to_inf':9.925E-05,
        'NSD_80_to_120':8.951E-05,
        'NSD_120_to_170':9.929E-06,
        'NSD_170_to_230':1.324E-06,
        'NSD_230_to_300':1.906E-07,
        'NSD_300_to_380':2.960E-08,
        'NSD_380_to_470':4.469E-09,
        'NSD_380_to_inf':5.208E-09,
        'NSD_470_to_inf':7.241E-10,
        'NSD_470_to_600':6.861E-10,
        'NSD_600_to_800':4.503E-11,
        'NSD_800_to_1100':4.844E-13,
        'NSD_1100_to_inf':3.175E-17
        }
    print 'PYTHIA process xsection = %s mb' % para[genTypePtHatRange]
    return para[genTypePtHatRange]
         
