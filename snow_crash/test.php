#!/usr/bin/php
<?php
function y($m){
	$m = preg_replace("/\./", " x ", $m);
	$m = preg_replace("/@/", " y", $m);
	return $m;
}
function x($a){
	$a = preg_replace("/(\[x (.*)\])/", "y(\"\\2\")", $a);
	$a = preg_replace("/\[/", "(", $a);
   	$a = preg_replace("/\]/", ")", $a);
	return $a;
}

$input = "[x {${exec(pouet)}}]";
$r = x($input);
print $r;
?>
