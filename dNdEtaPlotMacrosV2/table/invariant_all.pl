#!/usr/bin/perl

`./invariant_all.sh`;

@valuesX = `cat valuesX`;
@valuesY = `cat valuesY`;
@errorsY = `cat errorsY`;

chomp @valuesX;
chomp @valuesY;
chomp @errorsY;

$xMax = 4.;


print "900 GeV ---------------- \n";
print "pt  value  error \n";
$counter = 0;
$offset = 0;
for($i = 0; $i < scalar @valuesX; $i++){
  if($valuesX[$i] =~ /B/){
    if ( $counter  == 0) { print "2.36 TeV ---------------- \n"; }
    if ( $counter  == 1) { print "7 TeV ---------------- \n"; }
    $counter++;
    #print "New Eta Bin \n";
    print "pt  value  error \n";
  }


  if($counter>1) { $xMax=6.; }
  if($valuesX[$i] < $xMax && not ($valuesY[$i] =~ /C/)){
    $valueY = $valuesY[$i] - $offset;
    $valueY = `printf "%0.2e" $valueY`;
    $valueYE = `printf "%0.1e" $errorsY[$i]`;
    print $valuesX[$i], " ",$valueY, "  ", $valueYE, " \n"  ;    

  }
}











