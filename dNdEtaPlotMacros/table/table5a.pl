#!/usr/bin/perl

`./table5a.sh`;

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
	    $offset = $offset + 4; # for 2.36 TeV
	}
    }

    if( $counter % 2 == 0){

    if($valuesX[$i] < $xMax){
    $valueY = $valuesY[$i] - $offset;
    $valueY = `printf "%5.3e" $valueY`;
    $valueY = `printf "%5.3f" $valueY`;
    $valueYE = `printf "%5.3f" $errorsY[$i]`;
    print $valuesX[$i], " ",$valueY, "  ", $valueYE, " \n"  ;    
}
}
}











