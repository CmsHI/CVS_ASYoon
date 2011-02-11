printf "HICorePhysics - "
grep '^TrigReport.*1    4.*hltJets' CMSSW_*.stdout | awk '{print $4}' | addfloats.py
for Selection in hltJets noBSChalo hfNegFilter3 primaryVertexFilter hltPixelClusterShapeFilter hitrackAna; do
  printf "$Selection - "
  grep '^TrigReport.*1    4.*'$Selection CMSSW_*.stdout | awk '{print $5}' | addfloats.py
done
