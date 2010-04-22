<?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// POST extrahieren
$step = $_POST["step"];

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}

// Daten fur Klasse aus DB holen
// SQL-String bauen
$sqlString = "SELECT * FROM "._KrakeDatenpool." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
?>

<!-- Content Kontakt loschen -->

<table border="0" cellpadding="0" cellspacing="0">

<tr>
<td align="left" valign="top">

<?php
// Step 0: Eingabe
//################################################################################
if($step==0)
	{
	?>

<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">

<h3 class="textRot">Kontakt l&ouml;schen</h3>

Soll der Kontakt zu <b>&raquo;<?php echo $zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"]; ?>&laquo;</b> wirklich gel&ouml;scht werden?<br>
Falls nicht, geht es hier <a href="javascript:history.back()">zur&uuml;ck zur Detailansicht dieses Kontakts</a>.<br><br>

<input type="submit" value="Kontakt l&ouml;schen">

<input type="hidden" name="id" value="<?php echo $id; ?>">
<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">

</form>

    <?php
	}
//################################################################################
// /Step 0: Eingabe

// Step 1: Loschen
//################################################################################
if($step==1)
	{		
	// SQL-String bauen
	$sqlString = "DELETE FROM "._KrakeDatenpool." WHERE ID='".$id."'";

	// Eintrag aus DB loschen
	$ergebnis = $db -> sql($sqlString);
	
	// Fehlerbehandlung
	if($ergebnis){echo "<h3 align=\"left\">Kontakt gel&ouml;scht</h3>\nDer Kontakt wurden erfolgreich aus der Datenbank gel&ouml;scht.<br>\n<br>\n<a href=\"index.php?modus=DAT&inc=KON\">zur &Uuml;bersicht...</a><br>\n";}
	else{echo "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nDer Kontakt konnte nicht aus der Datenbank gel&ouml;scht werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
	}

//################################################################################
// /Step 1: Loschen
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Kontakt loschen -->