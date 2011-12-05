
cvs co UserCode/yinglu/MC_Production/Dijet
cvs co UserCode/davidlw/MCProduction/python
cvs co UserCode/ASYoon/MCGeneration/QCDEmbedding
mv UserCode/ASYoon/MCGeneration .

## GenProduction
cvs co Configuration/GenProduction/python/customiseCaloDigisNZS.py
cp UserCode/davidlw/MCProduction/python/*.py Configuration/GenProduction/python/

## Generator 
cvs co Configuration/Generator/python/PyquenDefaultSettings_cff.py 
cvs co Configuration/Generator/python/PythiaUEZ2Settings_cfi.py 
cvs co Configuration/Generator/python/PythiaUESettings_cfi.py
cp UserCode/davidlw/MCProduction/python/PyquenTuneZ2Settings*.* Configuration/Generator/python/