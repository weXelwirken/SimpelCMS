<?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}

// Daten fur Klasse aus DB holen
// SQL-String bauen
$sqlString = "SELECT * FROM "._KrakeKlassen." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
?>

<!-- Content Klasse loeschen -->

<table border="0" cellpadding="0" cellspacing="0">

<tr>
<td align="left" valign="top">

<?php
// Step 0: Eingabe
//################################################################################
if($step==0)
	{
	// Testen, ob Klasse noch Kontakten zugeordnet
	$sqlString = "SELECT ID FROM "._KrakeDatenpool." WHERE Klassen LIKE '%[".$zeile["Titel"]."]%'";
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		if(mysql_num_rows($ergebnis)!="0")
			{echo "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nDie Klasse konnte nicht aus der Datenbank gel&ouml;scht werden, da sie noch Kontakten zugeordnet ist.<br>\nBitte entfernen Sie diese Zuordnungen!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		else
			{
			?>

<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">

<h3 class="textRot">Klasse l&ouml;schen</h3>

Soll die Klasse zu <b>&raquo;<?php echo $zeile["Titel"]; ?>&laquo;</b> wirklich gel&ouml;scht werden?<br>
Falls nicht, geht es hier <a href="javascript:history.back()">zur&uuml;ck zur Detailansicht dieser Klasse</a>.<br><br>

<input type="submit" value="Klasse l&ouml;chen">

<input type="hidden" name="id" value="<?php echo $id; ?>">
<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">

</form>

			<?php
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	}
//################################################################################
// /Step 0: Eingabe

// Step 1: Loschen
//################################################################################
if($step==1)
	{		
	// SQL-String bauen
	$sqlString = "DELETE FROM "._KrakeKlassen." WHERE ID='".$id."'";

	// Eintrag aus DB loschen
	$ergebnis = $db -> sql($sqlString);
	
	// Fehlerbehandlung
	if($ergebnis){echo "<h3 align=\"left\">Klasse gel&ouml;scht</h3>\nDie Klasse wurden erfolgreich aus der Datenbank gel&ouml;scht.<br>\n<br>\n<a href=\"index.php?modus=DAT&inc=KLA\">zur &Uuml;bersicht...</a><br>\n";}
	else{echo "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nDie Klasse konnte nicht aus der Datenbank gel&ouml;scht werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
	}

//################################################################################
// /Step 1: Loschen
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Kontakt loeschen -->