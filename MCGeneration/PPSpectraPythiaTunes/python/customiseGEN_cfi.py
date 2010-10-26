import FWCore.ParameterSet.Config as cms



def getPy6ProcParameters(genTypePtHatRange):
    para = {
        # NSD (beyon pt>5~10 GeV/c, it's safe to say NSD = MB, but below, it's not)
        'NSD_0_to_5':['MSEL=1','CKIN(3)=0','CKIN(4)=5'], 
        'NSD_5_to_10':['MSEL=1','CKIN(3)=5','CKIN(4)=10'],
        'NSD_10_to_20':['MSEL=1','CKIN(3)=10','CKIN(4)=20'],
        'NSD_0_to_15':['MSEL=1','CKIN(3)=0','CKIN(4)=15'],
        'NSD_15_to_20':['MSEL=1','CKIN(3)=15','CKIN(4)=20'],
        'NSD_20_to_30':['MSEL=1','CKIN(3)=20','CKIN(4)=30'],
        'NSD_30_to_50':['MSEL=1','CKIN(3)=30','CKIN(4)=50'],
        'NSD_50_to_80':['MSEL=1','CKIN(3)=50','CKIN(4)=80'],
        'NSD_80_to_inf':['MSEL=1','CKIN(3)=80'],
        'NSD_80_to_120':['MSEL=1','CKIN(3)=80','CKIN(4)=120'],
        'NSD_120_to_170':['MSEL=1','CKIN(3)=120','CKIN(4)=170'],
        'NSD_170_to_230':['MSEL=1','CKIN(3)=170','CKIN(4)=230'],
        'NSD_230_to_300':['MSEL=1','CKIN(3)=230','CKIN(4)=300'],
        'NSD_300_to_380':['MSEL=1','CKIN(3)=300','CKIN(4)=380'],
        'NSD_380_to_470':['MSEL=1','CKIN(3)=380','CKIN(4)=470'],
        'NSD_470_to_inf':['MSEL=1','CKIN(3)=470'],
        # explicit NSD
        'ENSD_0_to_5':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=0','CKIN(4)=5'],
        'ENSD_5_to_10':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=5','CKIN(4)=10'],
        'ENSD_10_to_20':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=10','CKIN(4)=20'],
        'ENSD_0_to_15':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=0','CKIN(4)=15'],
        'ENSD_15_to_20':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=15','CKIN(4)=20'],
        'ENSD_20_to_30':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=20','CKIN(4)=30'],
        'ENSD_30_to_50':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=30','CKIN(4)=50'],
        'ENSD_50_to_80':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=50','CKIN(4)=80'],
        'ENSD_80_to_inf':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=80'],
        'ENSD_80_to_120':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=80','CKIN(4)=120'],
        'ENSD_120_to_170':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=120','CKIN(4)=170'],
        'ENSD_170_to_230':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=170','CKIN(4)=230'],
        'ENSD_230_to_300':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=230','CKIN(4)=300'],
        'ENSD_300_to_380':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=300','CKIN(4)=380'],
        'ENSD_380_to_470':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=380','CKIN(4)=470'],
        'ENSD_470_to_inf':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=470'],
        # MB
        'MB_0_to_5':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(92)=1','MSUB(93)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=0','CKIN(4)=5'],
        'MB_0_to_10':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(92)=1','MSUB(93)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=0','CKIN(4)=10'],
        'MB_0_to_15':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(92)=1','MSUB(93)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=0','CKIN(4)=15'],
        'MB_0_to_20':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(92)=1','MSUB(93)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=0','CKIN(4)=20'],
        'MB_0_to_25':['MSEL=0','MSUB(11)=1','MSUB(12)=1','MSUB(13)=1','MSUB(28)=1','MSUB(53)=1','MSUB(68)=1','MSUB(92)=1','MSUB(93)=1','MSUB(94)=1','MSUB(95)=1','CKIN(3)=0','CKIN(4)=25']
        }
    print "PYTHIA process parameters: ",para[genTypePtHatRange]
    return para[genTypePtHatRange]


def updatePy6ProcParameters(gen,genTypePtHatRange,sqrtS):
    print "Center-of-mass energy: ",sqrtS
    gen.PythiaParameters.processParameters = getPy6ProcParameters(genTypePtHatRange)
    gen.comEnergy = sqrtS


