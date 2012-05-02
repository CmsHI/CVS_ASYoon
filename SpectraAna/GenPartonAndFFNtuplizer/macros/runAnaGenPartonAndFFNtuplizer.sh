


save=true

applyQ=true
fractQ=0.3
constQ=30
fractLogQ=0.1
fractLogQ_P2=1

fixedFracLogQ=true # below is not meaningful if it's true
fractLogQ_low=1.5
fractLogQ_hig=2.5

phiDepELoss=false
ellipse_a=7.0
ellipse_b=10.0


# Constant Eloss
fractQ=-1
constQ=10
fractLogQ=-1
fractLogQ_P2=1
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
constQ=20
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
constQ=30
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)


# Constant Fraction
fractQ=0.1
constQ=-1
fractLogQ=-1
fractLogQ_P2=1
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractQ=0.2
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractQ=0.3
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)

# E-dependent Fractional 
fractQ=-1
constQ=-1
fractLogQ=1
fractLogQ_P2=1
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=2
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=3
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)

# E-dependent Fractional details 
fractQ=-1
constQ=-1
fractLogQ=1
fractLogQ_P2=1

fractLogQ=0.2
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=0.4
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=0.6
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=0.8
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=1.2
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=1.4
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=1.6
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=1.8
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=2.2
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=2.4
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=2.6
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=2.8
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=3.0
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)


fractLogQ=0.3
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=0.5
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
fractLogQ=0.7
root -l -q AnaGenPartonAndFFNtuplizer.C+\($save\,$applyQ\,$fractQ\,$constQ\,$fractLogQ\,$fractLogQ_P2\,$fixedFracLogQ\,$fractLogQ_low\,$fractLogQ_hig\,$phiDepELoss\,$ellipse_a\,$ellipse_b\)
