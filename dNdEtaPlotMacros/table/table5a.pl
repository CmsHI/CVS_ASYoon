#!/usr/bin/perl

`./table5a.sh`;

@valuesX = `cat valuesX`;
@valuesY = `cat valuesY`;
@errorsY = `cat errorsY`;

chomp @valuesX;
chomp @valuesY;
chomp @errorsY;

print "pt  value  error \n";
$counter = 0;
$offset = 0;
for($i = 1; $i < scalar @valuesX; $i++){
    
    if($valuesX[$i] =~ /B/){
	$counter++;
	if( $counter % 2 == 0){
	    print "New Eta Bin \n";
	    print "pt  value  error \n";
	    $offset = $offset + 4;
	}
    }
    
    $valueY = $valuesY[$i] - $offset;
    $valueY = `printf "%0.5f" $valueY`;
    print $valuesX[$i], " ",$valueY, "  ", $errorsY[$i], " \n"  ;    
}











