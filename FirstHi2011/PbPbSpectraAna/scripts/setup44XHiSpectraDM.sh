

# first check out spectra ana ara
cvs co UserCode/ASYoon/FirstHi2011/PbPbSpectraAna/scripts/setup44XHiSpectra.sh
cp UserCode/ASYoon/FirstHi2011/PbPbSpectraAna/scripts/setup44XHiSpectra.sh .
. setup44XHiSpectra.sh

# needed for DM reconstruction
# note: to run on 2010 DM (produced in 41X?), old CommonFunctions_cff.py is needed
cvs co -d SimGeneral/DataMixingModule UserCode/yetkin/SimGeneral/DataMixingModule
cvs co -r hi44X_01 -d  MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer # this is needed for above
rm MitHig/PixelTrackletAnalyzer/src/SimTrackAnalyzer.cc
rm CmsHi/Analysis2010/python/CommonFunctions_cff.py
cvs co -r 1.32 UserCode/CmsHi/Analysis2010/python/CommonFunctions_cff.py
cp UserCode/CmsHi/Analysis2010/python/CommonFunctions_cff.py CmsHi/Analysis2010/python/
