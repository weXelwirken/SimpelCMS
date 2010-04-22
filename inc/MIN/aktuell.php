<?php
//####################################################################################################################

// SCMS MiniKal-Skript "Aktuell" (Frontend)
// """"""""""""""""""""""""""""""""""""""""
// Version 0001, Stand 24.03.2009

// INHALT:
// """""""
// UEBERSICHT:          Alle Eintraege nach Datum absteigend sortiert
// DETAILS:             Detailansicht eines Eintrags

//####################################################################################################################


// POST und GET extrahieren
$eid = $_GET["eid"];

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);


//####################################################################################################################
// Uebersicht
//####################################################################################################################
if(!$eid)
	{	
	// Aufruf Uebersicht
	// Daten des Eintrags aus DB holen
	// Datum vorbereiten
	$jetzt = datetimemaker(time());
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._MiniKal." WHERE Datum>'".$jetzt."' AND Online='1' ORDER BY Datum";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
        {
        while($zeile = mysql_fetch_array($ergebnis))
            {
            // Datum vorbereiten
            $datArray = dateTimeAusgabe($zeile["Datum"]);
            $out.= "<b>&bull;</b> <i>".$datArray["Tag"].".".$datArray["Monat"].".".$datArray["Jahr"]."</i>: <b>&raquo;<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;eid=".$zeile["ID"]."\"><span".$off.">".stripslashes($zeile["Titel"])."</span></a>&laquo;</b> (".stripslashes($zeile["Ort"]).")<br>\n";
            }
        }
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Uebersicht ausgelesen werden!<br>\n";}
	
	// Ueberschrift
	$inhalt.= "<p>
	   ".$out."
	   </p>\n";
	}
//####################################################################################################################
// /Uebersicht
//####################################################################################################################



//####################################################################################################################
// Details
//####################################################################################################################
if($eid)
	{	
    // Aufruf Details
	// Daten des Eintrags aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._MiniKal." WHERE ID='".$eid."' AND Online='1' LIMIT 1";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
        {
        $zeile = mysql_fetch_array($ergebnis);
        // Datum vorbereiten
        $datArray = dateTimeAusgabe($zeile["Datum"]);
        $inhalt = $zeile["Beschreibung"];
        }
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Details ausgelesen werden!<br>\n";}
	
	// Ueberschrift
	$inhalt.= "<p>
	   ".$out."
	   </p>\n";
	}
//####################################################################################################################
// /Details
//####################################################################################################################
?>