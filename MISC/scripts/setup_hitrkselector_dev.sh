
cvs co -r V00-25-06 RecoTracker/FinalTrackSelectors 

cvs co UserCode/ASYoon/MISC/tracking
mv UserCode/ASYoon/MISC/tracking/AnalyticalTrackSelector.cc RecoTracker/FinalTrackSelectors/src
mv UserCode/ASYoon/MISC/tracking/MultiTrackSelector.* RecoTracker/FinalTrackSelectors/src
mv UserCode/ASYoon/MISC/tracking/select*.py RecoTracker/FinalTrackSelectors/python
mv UserCode/ASYoon/MISC/tracking/multiTrackSelector_cfi.py RecoTracker/FinalTrackSelectors/python
