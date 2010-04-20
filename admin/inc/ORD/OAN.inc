<?php
// POST und GET extrahieren
$lang = $_POST["lang"];
if($lang){$_SESSION["OAN"]["lang"] = $lang;}
$name = $_POST["name"];
if($name){$_SESSION["OAN"]["name"] = $name;}
$mutter = $_POST["mutter"];
if($mutter){$_SESSION["OAN"]["mutter"] = $mutter;}
$position = $_POST["position"];
if($position){$_SESSION["OAN"]["position"] = $position;}
$auth = $_POST["auth"];
if($auth){$_SESSION["OAN"]["auth"] = $auth;}
$online = $_POST["online"];
if($online==="1"){$_SESSION["DAN"]["online"] = $_POST["online"];}
if($online==="0"){$_SESSION["DAN"]["online"] = $_POST["online"];}
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
?>

<!-- Content Ordner anlegen -->

<table border="0" cellpadding="0" cellspacing="0" width="480">

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

<table border="0" cellpadding="3" cellspacing="3" width="100%">

<tr><td align="left"><h3>Neuen Ordner anlegen</h3></td></tr>

<tr><td>

<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">
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
    if($_SESSION["OAN"]["lang"]==$key){$selected=" selected";}else{$selected="";}
    echo "<option value=\"".$key."\"".$selected.">".$item."</option>";
    }
?>
</select>
</td></tr>
    <?php
    }
?>

<tr><td align="left" valign="top" width="200"><b>Name:<br></b></td><td align="left" valign="top"><input type="text" name="name" size="25" maxlength="255" value="<?php echo $_SESSION["OAN"]["name"]; ?>"></td></tr>

<tr><td align="left" valign="top"><b>Mutterordner:<br></b></td><td align="left" valign="top">
<select name="mutter" size="1">
<option value="0">Wurzel</option>
<?php
// Ordner aus DB holen
OrdPfadBaumOpt($mutter, $mutterAlt, $mutterAkt, $mutterName, $ebene, $id);
?>
</select>
</td></tr>

<tr><td align="left" valign="top"><b>Position:<br></b></td><td align="left" valign="top"><input type="text" name="position" size="4" maxlength="4" value="<?php echo $_SESSION["OAN"]["position"]; ?>">
<select size="1">
<option>besetzte Positionen:</option>
<?php
// Schon besetzte Positionen ausgeben
OrdPosBesOpt();
?>
</select>
</td></tr>

<?php
// $ScmsAuth on?
if($ScmsAuth)
    {
    ?>
<tr><td align="left" valign="middle" colspan="2"><br></td></tr>

<tr><td align="left" valign="top" rowspan="3"><b>Sichtbarkeit &amp; Zugriff:<br></b></td><td align="left" valign="top"><input type="radio" name="auth" value="0"<?php if($_SESSION["OAN"]["auth"]==="0" OR !$_SESSION["OAN"]["auth"]){echo " checked";} ?>><span class="textGruen"><b>Keine Beschr&auml;nkungen</b></span></td></tr>

<tr><td align="left" valign="top"><input type="radio" name="auth" value="-1"<?php if($_SESSION["OAN"]["auth"]=="-1"){echo " checked";} ?>><span class="textOrange"><b>Nur unangemeldete Nutzer</b></span></td></tr>

<tr><td align="left" valign="top"><input type="radio" name="auth" value="1"<?php if($_SESSION["OAN"]["auth"]=="1"){echo " checked";} ?>><span class="textRot"><b>Nur angemeldete Nutzer</b></span></td></tr>
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

<tr><td align="left" valign="top" width="75"><b>Online:<br></b></td><td align="left" valign="top"><input type="radio" name="online" value="1"<?php if($_SESSION["DAN"]["online"]){echo " checked";} ?>>Ja&nbsp;<input type="radio" name="online" value="0"<?php if(!$_SESSION["DAN"]["online"]){echo " checked";} ?>>Nein</td></tr>

</table>
</fieldset>
<!-- /STATUS ################################################################### -->
<br>

<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">
<a href="index.php?modus=ORD&inc=OUE">&Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->

</td></tr>

<tr><td align="center"><input type="submit" value="Neuen Ordner anlegen"></td></tr>

</table>

<!-- /Innere Tabelle Eingabe -->

<?php
// Datum erzeugen
$erzeugt = datetimemaker(time());
$geaendert = $erzeugt;
?>

<input type="hidden" name="erzeugt" value="<?php echo $erzeugt; ?>">
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
	$typ = $typNeu;
	
	$fehlerStr = "<h3 align=\"left\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
		
	// Feldtest
	if($ScmsLang){if(!$lang){$fehler=1; $fehlerStr = $fehlerStr."<li>Die Sprache wurde nicht ausgew&auml;hlt.\n";}}
	if($name==""){$fehler=1; $fehlerStr = $fehlerStr."<li>Der Name des Ordners wurde nicht angegeben.\n";}
	
	$fehlerStr = $fehlerStr."</ul>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";
	
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
		$sqlString = "INSERT INTO "._DBordner." (Lang,Name,Mutter,Position,Auth,Online,Erzeugt,Geaendert) VALUES ('".$lang."','".addslashes($name)."','".$mutter."','".$position."','".$auth."','".$online."','".$erzeugt."','".$geaendert."')";
	
		// Neuen Ordner in DB speichern
		$ergebnis = $db -> sql($sqlString);
		// .htaccess aktualisieren
        if($ModRewrite){UrlRewrite();}
        // Vorbelegungen loeschen
        $_SESSION["OAN"] = false;
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3 align=\"left\">Neuer Ordner angelegt</h3>\nDie Angaben zum Ordner wurden erfolgreich in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=ORD&inc=OUE\">Zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=ORD&inc=OUE&id=".mysql_insert_id()."\">...zum angelegten Ordner</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDie Angaben zum Ordner konnten nicht in der Datenbank gespeichert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//######################################################################################
// /Step 1: Pruefen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Ordner anlegen -->