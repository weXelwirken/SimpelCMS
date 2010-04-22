<?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// POST extrahieren
$titel = $_POST["titel"];
$beschreibung = $_POST["beschreibung"];
$step = $_POST["step"];

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}
?>

<!-- Content Klasse anlegen -->

<table border="0" cellpadding="0" cellspacing="0" width="480">

<tr>
<td align="left" valign="top">

<?php
// Step 0: Eingabe
//######################################################################################
if($step==0)
	{
?>

<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" multiple=" multiple" method="post">

<h3>Klasse neu anlegen</h3>

<!-- Innere Tabelle Eingabe -->

<p>
<fieldset><legend>Eigenschaften</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Titel:<br></b></td><td align="left" valign="top">
<input type="text" name="titel" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Beschreibung:<br></b></td><td align="left" valign="top">
<textarea name="beschreibung" cols="44" rows="5"></textarea>
</td></tr>
</table>
</fieldset>
</p>

<p align="center"><input type="submit" value="Klasse anlegen"></p>

<!-- /Innere Tabelle Eingabe -->

<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">

</form>

<?php
	}
//######################################################################################
// /Step 0: Eingabe

// Step 1: Prufen und speichern
//######################################################################################
if($step==1)
	{
	// Fehlerbehandlung
	//######################################################################################
	
	$fehlerStr = "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
	
	// Feldtest
	if($titel==""){$fehler=1; $fehlerStr = $fehlerStr."<li>Es wurde kein Titel angegeben.\n";}
	else
		{
		$sqlString = "SELECT * FROM "._KrakeKlassen." WHERE Titel='".$titel."'";
		$ergebnis = $db -> sql($sqlString);
		if($ergebnis)
			{
			if(mysql_num_rows($ergebnis)!="0")
				{$fehler=1; $fehlerStr = $fehlerStr."<li>Der Titel ist schon vergeben.\n";}
			}
		else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
		}
		
	$fehlerStr = $fehlerStr."</ul>\n<a href=\"javascript:history.back()\">zuruck...</a><br>\n";
	
	// Fehlerausgabe
	if($fehler!="")
		{
		echo $fehlerStr;
		}
	// Speichern
	//######################################################################################
	else
		{
		// SQL-String bauen
		$sqlString = "INSERT INTO "._KrakeKlassen." (Titel,Beschreibung) VALUES ('".addslashes($titel)."','".addslashes($beschreibung)."')";
	
		// Neuen Eintrag in DB speichern
		$ergebnis = $db -> sql($sqlString);
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3>Neue Klasse angelegt</h3>\nDie neue Klasse wurde erfolgreich in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=DAT&inc=KLA\">zur &Uuml;bersicht...</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDie Klasse konnte nicht in der Datenbank gespeichert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//######################################################################################
// /Step 1: Prufen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Klasse anlegen -->