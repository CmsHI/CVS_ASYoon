#!/usr/bin/perl

`./table5b.sh`;

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

        print "-------------------------- \n";


	print "2.36 TeV ---------------- \n";

	$counter++;
	    print "New Eta Bin \n";
	    print "pt  value  error \n";
    }


    if($valuesX[$i] < $xMax){
    $valueY = $valuesY[$i] - $offset;
#    $valueY = `printf "%0.5f" $valueY`;
    print $valuesX[$i], " ",$valueY, "  ", $errorsY[$i], " \n"  ;    

}
}











