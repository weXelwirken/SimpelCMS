<?php

// POST und GET extrahieren

$step = $_POST["step"];

if($_POST["id"]){$id = $_POST["id"];}

if($_POST["modus"]){$modus = $_POST["modus"];}

if($_POST["inc"]){$inc = $_POST["inc"];}



// DB-Verbindung

$db = new db($dbHost,$dbUser,$dbPasswort);

$db -> select_db($dbDatenbank);



// Testen ob Arbeitsschritt gesetzt

if(!$step){$step=0;}



// Daten fuer Seite aus DB holen

// SQL-String bauen

$sqlString = "SELECT * FROM "._MiniKal." WHERE ID='".$id."'";



// Ergebnis auslesen

$ergebnis = $db -> sql($sqlString);

if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}

else{echo "Fehler: Es konnte kein Ergebnis fuer den Eintrag ausgelesen werden!<br>\n";}

	

?>



<!-- Content Eintrag loeschen -->



<table border="0" cellpadding="0" cellspacing="0" width="480">



<tr>

<td align="left" valign="top">



<?php

// Step 0: Eingabe

//######################################################################################

if(!$step)

	{

	// Datum vorbereiten

    $datArray = dateTimeAusgabe($zeile["Datum"]);

    ?>

<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">



<div align="left">

<h3>Eintrag l&ouml;schen</h3>



Soll der Eintrag <b>&raquo;<?php echo $zeile["Titel"]; ?>&laquo;</b> (<?php echo $datArray["Tag"].".".$datArray["Monat"].".".$datArray["Jahr"]." in ".$zeile["Ort"]; ?>) wirklich gel&ouml;scht werden?<br>

Falls nicht, geht es hier <a href="javascript:history.back()">zur&uuml;ck zur Eintragsansicht</a>.<br><br>



<input type="submit" value="Eintrag l&ouml;schen">

</div>



<input type="hidden" name="id" value="<?php echo $id; ?>">

<input type="hidden" name="modus" value="<?php echo $modus; ?>">

<input type="hidden" name="inc" value="<?php echo $inc; ?>">

<input type="hidden" name="step" value="1">



</form>

    <?php

	}

//######################################################################################

// /Step 0: Eingabe



// Step 1: Loeschen

//######################################################################################

if($step)

	{

    // SQL-String bauen

    $sqlString = "DELETE FROM "._MiniKal." WHERE ID='".$id."'";



    // Veranstaltung aus DB l&ouml;schen

    $ergebnis = $db -> sql($sqlString);

    

    // Fehlerbehandlung

    if($ergebnis){echo "<h3 align=\"left\">Eintrag gel&ouml;scht</h3>\nDer EIntrag wurde erfolgreich aus der Datenbank gel&ouml;scht.<br>\n<br>\n<a href=\"index.php?modus=MIN&inc=MUE\">...zur &Uuml;bersicht</a><br>\n";}

    else{echo "<h3 align=\"left\">Fehler!</h3>\nDer EIntrag konnte nicht aus der Datenbank gel&ouml;scht werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}

	}

//######################################################################################

// /Step 1: Loeschen

?>



<br><br>



</td>

</tr>



</table>



<!-- Content Eintrag loeschen -->