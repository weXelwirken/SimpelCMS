<?php
// POST und GET extrahieren
$lang = $_POST["lang"];
$name = $_POST["name"];
$mutter = $_POST["mutter"];
$position = $_POST["position"];
$auth = $_POST["auth"];
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

// Daten fuer Ordner aus DB holen
// SQL-String bauen
$sqlString = "SELECT * FROM "._DBordner." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	
?>

<!-- Content Ordner aendern -->

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

<tr><td align="left"><h3>Ordner &auml;ndern</h3></td></tr>

<tr><td>

<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">
<a href="index.php?modus=ORD&inc=OUE&id=<?php echo $id; ?>">Ordneransicht</a>&nbsp;
<a href="index.php?modus=ORD&inc=OUE">&Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->
<br>
<!-- EINSTELLUNGEN ################################################################### -->
<fieldset>
<legend>Einstellungen</legend>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<?php
if($ScmsLang)
    {
    ?>
<tr><td align="left" valign="middle" width="75"><b>Sprache:<br></b></td><td align="left" valign="top">
<select name="lang" size="1">
<option value="0">ausw&auml;hlen</option>
    <?php
    foreach($ScmsLangArray as $key => $item)
        {
        if($key==$zeile["Lang"]){$selected=" selected";}else{$selected="";}
        echo "<option value=\"".$key."\"".$selected.">".$item."</option>";
        }
    ?>
</select>
</td></tr>
    <?php
    }
?>

<tr><td align="left" valign="top" width="200"><b>Name:<br></b></td><td align="left" valign="top"><input type="text" name="name" size="25" maxlength="255" value="<?php echo stripslashes($zeile["Name"]); ?>"></td></tr>

<tr><td align="left" valign="top"><b>Mutterordner:<br></b></td><td align="left" valign="top">
<select name="mutter" size="1">
<option value="0">Wurzel</option>
<?php
// OrdnerBaum aus DB holen
OrdPfadBaumOpt($mutter, $mutterAlt, $zeile["Mutter"], $mutterName, $ebene, $id);
?>
</select>
</td></tr>

<tr><td align="left" valign="top"><b>Position:<br></b></td><td align="left" valign="top"><input type="text" name="position" size="4" maxlength="4" value="<?php echo $zeile["Position"]; ?>">
<select size="1">
<option>besetzte Positionen:</option>
<?php
// Schon besetzte Positionen ausgeben
OrdPosBesOpt();
?>
</select></td></tr>

<?php
// $ScmsAuth on?
if($ScmsAuth)
    {
    ?>
<tr><td align="left" valign="middle" colspan="2"><br></td></tr>

<tr><td align="left" valign="top" rowspan="3"><b>Sichtbarkeit &amp; Zugriff:<br></b></td><td align="left" valign="top"><input type="radio" name="auth" value="0"<?php if($zeile["Auth"]=="0"){echo " checked";}if($id=="1"){echo " disabled";}?>><span class="textGruen"><b>Keine Beschr&auml;nkungen</b></span></td></tr>

<tr><td align="left" valign="top"><input type="radio" name="auth" value="-1"<?php if($zeile["Auth"]=="-1"){echo " checked";}if($id=="1"){echo " disabled";}?>><span class="textOrange"><b>Nur unangemeldete Nutzer</b></span></td></tr>

<tr><td align="left" valign="top"><input type="radio" name="auth" value="1"<?php if($zeile["Auth"]=="1"){echo " checked";}if($id=="1"){echo " disabled";}?>><span class="textRot"><b>Nur angemeldete Nutzer</b></span></td></tr>
    <?php
    }
?>

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
<a href="index.php?modus=ORD&inc=OUE&id=<?php echo $id; ?>">Ordneransicht</a>&nbsp;
<a href="index.php?modus=ORD&inc=OUE">&Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->

</td></tr>

<tr><td><div align="center"><input type="submit" value="Ordner &auml;ndern"></td></tr>

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
	if($ScmsLang){if(!$lang){$fehler=1; $fehlerStr = $fehlerStr."<li>Die Sprache wurde nicht ausgew&auml;hlt.\n";}}
	if(!$name){$fehler=1; $fehlerStr = $fehlerStr."<li>Der Name der Kategorie wurde nicht angegeben.\n";}
	
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
		$sqlString = "UPDATE "._DBordner." SET Lang='".$lang."',Name='".addslashes($name)."',Mutter='".$mutter."',Position='".$position."',Auth='".$auth."',Online='".$online."',Geaendert='".$geaendert."' WHERE ID='".$id."'";
	
		// Neue Veranstaltung in DB speichern
		$ergebnis = $db -> sql($sqlString);
		// .htaccess aktualisieren
        if($ModRewrite){UrlRewrite();}
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3 align=\"left\">Ordner ge&auml;ndert</h3>\nDie Angaben zum Ordner wurden erfolgreich ge&auml;ndert und in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=ORD&inc=OUE\">Zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=ORD&inc=OUE&id=".$id."\">...zum ge&auml;nderten Ordner</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDie Angaben zum Ordner konnten nicht ge&auml;ndert und in der Datenbank gespeichert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
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