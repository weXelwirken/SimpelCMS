<?php

/*******************************************

SCMS Zeit-Funktionen
""""""""""""""""""""

Die Datei beinhaltet Skripte, die besondere
Funkionaltitäten für die Datums- und Zeitbe-
handlung erzeugen.

Copyleft by weXelwirken 2009
********************************************/

// echo "<!-- Zeit-Funktionen einbinden -->\n";

//================================================================================================
// DateTimeMaker

function datetimemaker($time)
	{
	return date("Y-m-d H:i:s" , $time);
	}

//================================================================================================
// DateTimeAusgabe ($ausgabe[])

function dateTimeAusgabe($dateTime)
	{
	// Zerlegen
	$explode = explode(" ", $dateTime);
	$explodeDate = explode("-", $explode[0]);
	$explodeTime = explode(":", $explode[1]);
	// Ausgabe bauen
	$ausgabe["Jahr"] = $explodeDate[0];
	$ausgabe["Monat"] = $explodeDate[1];
	$ausgabe["Tag"] = $explodeDate[2];
	$ausgabe["Stunde"] = $explodeTime[0];
	$ausgabe["Minute"] = $explodeTime[1];
	$ausgabe["Sekunde"] = $explodeTime[1];
	return $ausgabe;
	}

//================================================================================================
// DateTimeAusgabe1 (xx. - xx.xx.xxxx)

function datetimeausgabe1($datetimeVon, $datetimeBis)
	{
	// Von zerlegen
	$explodeVon = explode(" ", $datetimeVon);
	$explodeVonDate = explode("-", $explodeVon[0]);
	//$explodeVonTime = explode(":", $explodeVon[1]);
	// Bis zerlegen
	$explodeBis = explode(" ", $datetimeBis);
	$explodeBisDate = explode("-", $explodeBis[0]);
	//$explodeBisTime = explode(":", $explodeBis[1]);
	// Ausgabe bauen
	$ausgabe = $explodeVonDate[2].".".$explodeVonDate[1].". - ".$explodeBisDate[2].".".$explodeBisDate[1].".".$explodeBisDate[0];
	return $ausgabe;
	}

?>