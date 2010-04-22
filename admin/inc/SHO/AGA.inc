<?php
// POST und GET extrahieren
$name = $_POST["name"];
$beschreibung = $_POST["beschreibung"];
$online = $_POST["online"];
$erzeugt = $_POST["erzeugt"];
$geaendert = $_POST["geaendert"];
$step = $_POST["step"];
if($_POST["modus"]){$modus = $_POST["modus"];}
if($_POST["inc"]){$inc = $_POST["inc"];}
if($_POST["id"]){$id = $_POST["id"];}

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}

// Daten fuer Gruppe aus DB holen
// SQL-String bauen
$sqlString = "SELECT * FROM "._ShopGruppen." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	
?>

<!-- Content Gruppe aendern -->

<table border="0" cellpadding="0" cellspacing="0">

<tr>
<td align="left" valign="top">

<?php
// Step 0: Eingabe
//######################################################################################
if($step==0)
	{
?>

<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">

<!-- Innere Tabelle Eingabe -->

<table border="0" cellpadding="3" cellspacing="3" width="500">

<tr><td align="left"><h3>Artikelgruppe &auml;ndern</h3></td></tr>

<tr><td>

<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">
<a href="index.php?modus=SHO&inc=AGU&id=<?php echo $id; ?>">Gruppenansicht</a>&nbsp;
<a href="index.php?modus=SHO&inc=AGU">&Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->
<br>
<!-- EINSTELLUNGEN ################################################################### -->
<fieldset>
<legend>Einstellungen</legend>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="200"><b>Name:<br></b></td><td align="left" valign="top"><input type="text" name="name" size="25" maxlength="255" value="<?php echo stripslashes($zeile["Name"]); ?>"></td></tr>

<tr><td align="left" valign="top" width="200"><b>Beschreibung:<br></b></td><td align="left" valign="top"><textarea name="beschreibung" cols="40" rows="5"><?php echo stripslashes($zeile["Beschreibung"]); ?></textarea></td></tr>

</table>
</fieldset>
<!-- /EINSTELLUNGEN ################################################################### -->
<br>
<!-- STATUS ################################################################### -->
<fieldset>
<legend>Status</legend>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Online:<br></b></td><td align="left" valign="top"><input type="radio" name="online" value="1" <?php if($zeile["Online"]==1){echo " checked";} ?>>Ja&nbsp;<input type="radio" name="online" value="0" <?php if($zeile["Online"]==0){echo " checked";} ?>>Nein</td></tr>

</table>
</fieldset>
<!-- /STATUS ################################################################### -->
<br>

<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">
<a href="index.php?modus=SHO&inc=AGU&id=<?php echo $id; ?>">Gruppenansicht</a>&nbsp;
<a href="index.php?modus=SHO&inc=AGU">&Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->

</td></tr>

<tr><td><div align="center"><input type="submit" value="Artikelgruppen &auml;ndern"></td></tr>

</table>

<!-- /Innere Tabelle Eingabe -->

<?php
// Anderungs-Datum erzeugen
$geaendert = datetimemaker(time());
?>

<input type="hidden" name="id" value="<?php echo $zeile["ID"]; ?>">
<input type="hidden" name="geaendert" value="<?php echo $geaendert; ?>">
<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">

</form>

<?php
	}
//######################################################################################
// /Step 0: Eingabe

// Step 1: Pruefen und speichern
//######################################################################################
if($step==1)
	{
	// Fehlerbehandlung
	//######################################################################################
	
	$fehlerStr = "<h3 align=\"left\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
		
	// Feldtest
	if(!$name){$fehler=1; $fehlerStr = $fehlerStr."<li>Der Name der Gruppe wurde nicht angegeben.\n";}
	if(!$beschreibung){$fehler=1; $fehlerStr = $fehlerStr."<li>Die Beschreibung der Gruppe wurde nicht angegeben.\n";}
	
	$fehlerStr = $fehlerStr."</ul>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";
	
	// Fehlerausgabe
	if($fehler)
		{
		echo $fehlerStr;
		}
	// Speichern
	//######################################################################################
	else
		{		
		// SQL-String bauen
		$sqlString = "UPDATE "._ShopGruppen." SET Name='".addslashes($name)."',Beschreibung='".addslashes($beschreibung)."',Online='".$online."',Geaendert='".$geaendert."' WHERE ID='".$id."'";
	
		// Neue Veranstaltung in DB speichern
		$ergebnis = $db -> sql($sqlString);
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3 align=\"left\">Artikelgruppe ge&auml;ndert</h3>\nDie Angaben zur Artikelgruppe wurden erfolgreich ge&auml;ndert und in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=SHO&inc=AGU\">zur &Uuml;bersicht...</a>&nbsp;&nbsp;&nbsp;<a href=\"index.php?modus=SHO&inc=AGU&id=".$id."\">zur ge&auml;nderten Gruppe...</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDie Angaben zur Artikelgruppe konnten nicht ge&auml;ndert und in der Datenbank gespeichert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//######################################################################################
// /Step 1: Pruefen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Ordner aendern -->