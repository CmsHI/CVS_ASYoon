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
        'NSD_0_to_5':2.878E+01, # 4.130E+01-(1.155E+01+9.073E-01+....)
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
        'NSD_470_to_570':6.365E-10,
        'NSD_570_to_670':7.524E-11,
        'NSD_670_to_800':9.318E-12,
        'NSD_800_to_930':4.723E-13,
        'NSD_930_to_1000':1.296E-14,
        'NSD_930_to_inf':1.446E-14,
        'NSD_1000_to_1100':1.536E-15,
        'NSD_1100_to_1200':3.136E-17,
        'NSD_1200_to_inf':1.405E-19
        }
    print 'PYTHIA process xsection = %s mb' % para[genTypePtHatRange]
    return para[genTypePtHatRange]
         

# This is for 200 GeV 

def getPy6ProcXsection200GeV(genTypePtHatRange):
    para = {
      'NSD_0_to_5':2.747E+01, # 2.764E+01-()
      'NSD_5_to_10':1.626E-01,
      'NSD_10_to_20':4.477E-03,
      'NSD_20_to_30':5.572E-05,
      'NSD_30_to_50':2.297E-06,
      'NSD_50_to_80':6.899E-09,
      'NSD_80_to_120':4.538E-14
      }
    print 'PYTHIA process xsection = %s mb' % para[genTypePtHatRange]
    return para[genTypePtHatRange]
    
