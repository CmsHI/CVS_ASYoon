#!/usr/bin/perl

`./differential_hap_ham_combined.sh`;

@valuesX = `cat valuesX`;
@valuesY = `cat valuesY`;
@errorsY = `cat errorsY`;

chomp @valuesX;
chomp @valuesY;
chomp @errorsY;

$xMax = 2.;

print "pt  value  error \n";
$counter = 0;
$offset = 0;
for($i = 0; $i < scalar @valuesX; $i++){
  if($valuesX[$i] =~ /B/){
    $counter++;
    if( $counter % 2 == 0){
      printf "Eta %.1f \n", 0.1+$counter*0.1;
      print "pt  value  error \n";
      #$offset = $offset + 3; # for 900 GeV macro
      #$offset = $offset + 4; # for 2.36 TeV
      $offset = $offset + 6; # for 7TeV paper Fig. 2
    }
  }

  if( $counter % 2 == 0){

    if($valuesX[$i] < $xMax && not ($valuesY[$i] =~ /C/)){
      $valueY = $valuesY[$i] - $offset;
      $valueY = `printf "%5.2f" $valueY`;
      $valueYE = `printf "%5.2f" $errorsY[$i]`;
      print $valuesX[$i], " ",$valueY, "  ", $valueYE, " \n"  ;    
    }
  }
}
