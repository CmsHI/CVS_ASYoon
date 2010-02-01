


cat ../paper/differential_hap_ham_combined.C | grep gre > greOnly 
#cat ../paper/differential_hab_900.C | grep gre > greOnly 
cat greOnly | sed "s/gre->SetPoint(/Value /g" > greOnly0
cat greOnly0 | sed "s/gre->SetPoint/ /g" > greOnly1
cat greOnly1 | sed "s/(/ /g" > greOnly2
cat greOnly2 | sed "s/)/ /g" > greOnly3
cat greOnly3 | sed "s/,/ /g" > greOnly4
cat greOnly4 | sed "s/;/ /g" > greOnly5
cat greOnly5 | sed "s/TGraphErrors/ /g" > greOnly6
cat greOnly6 | sed "s/Histogram/ValueAndErrorFor A B C D E F/g" > greOnly7

cat greOnly7 | grep Value > valuesDifferential
cat greOnly7 | grep Error > errorsDifferential

cat valuesDifferential | awk '{print $3}' > valuesX
cat valuesDifferential | awk '{print $4}' > valuesY
cat errorsDifferential | awk '{print $4}' > errorsY
 

