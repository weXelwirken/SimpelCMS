<?php
// POST und GET extrahieren
$step = $_POST["step"];
$lang = $_POST["lang"];
$ordner = $_POST["ordner"];
$titel = $_POST["titel"];
$linktext = $_POST["linktext"];
$kurztext = $_POST["kurztext"];
$typ = $_POST["typ"];
$quelle = $_POST["quelle"];
$skript = $_POST["skript"];
$inhalt = $_POST["inhalt"];
$position = $_POST["position"];
$anzeigeTitel = $_POST["anzeigeTitel"];
$anzeigeLinktext = $_POST["anzeigeLinktext"];
$anzeigeKurztext = $_POST["anzeigeKurztext"];
$auth = $_POST["auth"];
$verweis1 = $_POST["verweis1"];
$verweis2 = $_POST["verweis2"];
$verweis3 = $_POST["verweis3"];
$verweis4 = $_POST["verweis4"];
$verweis5 = $_POST["verweis5"];
$online = $_POST["online"];
if($_POST["id"]){$id = $_POST["id"];}
if($_POST["erzeugt"]){$erzeugt = $_POST["erzeugt"];}
if($_POST["geaendert"]){$geaendert = $_POST["geaendert"];}
if($_POST["modus"]){$modus = $_POST["modus"];}
if($_POST["inc"]){$inc = $_POST["inc"];}

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}
?>

<!-- Content Dokument anlegen -->

<table border="0" cellpadding="0" cellspacing="0">

<tr>
<td align="left" valign="top">

<?php
// Step 0: Eingabe
//######################################################################################
if($step==0)
	{
?>

<form name="formular" action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">

<!-- Innere Tabelle Eingabe -->

<table border="0" cellpadding="3" cellspacing="3" width="500">

<tr><td align="left"><h3>Neues Dokument anlegen</h3></td></tr>

<tr><td>

<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top"><a href="index.php?modus=DOK&inc=DUE">Zur&uuml;ck zur &Uuml;bersicht</a></td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->
<br>
<!-- ALLGEMEIN ################################################################### -->
<fieldset>
<legend>Allgemein</legend>
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
    echo "<option value=\"".$key."\">".$item."</option>";
    }
?>
</select>
</td></tr>
    <?php
    }
?>

<tr><td align="left" valign="middle" width="75"><b>Ordner:<br></b></td><td align="left" valign="top">
<select name="ordner" size="1">
<option value="0">Wurzel</option>
<?php
DokOrdOpt($mutter, $mutterAlt, $mutterAkt, $mutterName, $ebene, $id);
?>
</select>
</td></tr>

<tr><td align="left" valign="middle"><b>Titel:<br></b></td><td align="left" valign="top"><input type="text" name="titel" size="40" maxlength="255"></td></tr>

<tr><td align="left" valign="middle"><b>Linktext:<br></b></td><td align="left" valign="top"><input type="text" name="linktext" size="25" maxlength="255"></td></tr>

<?php
if($ScmsVerweise)
{
?>
<tr><td align="left" valign="top" width="75"><b>Kurztext:<br></b></td><td align="left" valign="top"><textarea name="kurztext" cols="50" rows="5"></textarea></td></tr>
<?php
}
?>

</table>
</fieldset>
<!-- /ALLGEMEIN ################################################################### -->
<br>
<!-- DETAILS ################################################################### -->

<fieldset>
<legend>Details</legend>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top"><b>Seiteninhalt:<br></b></td><td align="left" valign="top"><textarea name="inhalt" cols="50" rows="25" class="mceEditor"></textarea></td></tr>

<tr><td align="left" valign="top" width="75"><b><nobr>Skript Quelle:</nobr><br></b></td><td align="left" valign="top"><input type="text" name="skript" size="40" maxlength="255"></td></tr>
</td></tr>

</table>
</fieldset>
<!-- /DETAILS ################################################################### -->
<br>
<!-- EINSTELLUNGEN ################################################################### -->
<fieldset>
<legend>Einstellungen</legend>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="200"><b>Position:<br></b></td><td align="left" valign="top"><input type="text" name="position" size="3" maxlength="4"></td></tr>

<tr><td align="left" valign="top"><b>Anzeige des Titels:<br></b></td><td align="left" valign="top"><input type="radio" name="anzeigeTitel" id="anzeigeTitelJa" value="1" checked><label for="anzeigeTitelJa">Ja</label>&nbsp;<input type="radio" name="anzeigeTitel" id="anzeigeTitelNein" value="0"><label for="anzeigeTitelNein">Nein</label></td></tr>

<tr><td align="left" valign="top"><b>Anzeige des Linktext:<br></b></td><td align="left" valign="top"><input type="radio" name="anzeigeLinktext" id="anzeigeLinktextJa" value="1" checked><label for="anzeigeLinktextJa">Ja</label>&nbsp;<input type="radio" name="anzeigeLinktext" id="anzeigeLinktextNein" value="0"><label for="anzeigeLinktextNein">Nein</label></td></tr>

<?php
if($ScmsVerweise)
{
?>
<tr><td align="left" valign="top"><b>Anzeige des Kurztext:<br></b></td><td align="left" valign="top"><input type="radio" name="anzeigeKurztext" id="anzeigeKurztextJa" value="1" checked><label for="anzeigeKurztextJa">Ja</label>&nbsp;<input type="radio" name="anzeigeKurztext" id="anzeigeKurztextNein" value="0"><label for="anzeigeKurztextNein">Nein</label></td></tr>
<?php
}
?>

<?php
// $ScmsAuth on?
if($ScmsAuth)
    {
    ?>
<tr><td align="left" valign="middle" colspan="2"><br></td></tr>

<tr><td align="left" valign="top"><b>Sichtbarkeit &amp; Zugriff:<br></b></td><td align="left" valign="top"><input type="radio" name="auth" id="auth1" value="0" checked><span class="textGruen"><b><label for="auth1">Keine Beschr&auml;nkungen</label></b></span></td></tr>

<tr><td align="left" valign="top">&nbsp;<br></td><td align="left" valign="top"><input type="radio" name="auth" id="auth2" value="-1"><span class="textOrange"><b><label for="auth2">Nur unangemeldete Nutzer</label></b></span></td></tr>

<tr><td align="left" valign="top">&nbsp;<br></td><td align="left" valign="top"><input type="radio" name="auth" id="auth3" value="1"><span class="textRot"><b><label for="auth3">Nur angemeldete Nutzer</label></b></span></td></tr>
    <?php
    }
?>
</table>
<?php
if($ScmsVerweise)
{
?>
	<table border="0" cellpadding="3" cellspacing="3" width="450">
	
	<tr><td align="left" valign="middle" width="75"><b><nobr>Verweis 1:</nobr><br></b></td><td align="left" valign="top">
	<select name="verweis1" size="1">
	<option value="0">---Kein Verweis---</option>
	<?php
	VerweisDok($verweisAkt);
	?>
	</select>
	</td></tr>
	
	<tr><td align="left" valign="middle"><b><nobr>Verweis 2:</nobr><br></b></td><td align="left" valign="top">
	<select name="verweis2" size="1">
	<option value="0">---Kein Verweis---</option>
	<?php
	VerweisDok($verweisAkt);
	?>
	</select>
	</td></tr>
	
	<tr><td align="left" valign="middle"><b><nobr>Verweis 3:</nobr><br></b></td><td align="left" valign="top">
	<select name="verweis3" size="1">
	<option value="0">---Kein Verweis---</option>
	<?php
	VerweisDok($verweisAkt);
	?>
	</select>
	</td></tr>
	
	<tr><td align="left" valign="middle"><b><nobr>Verweis 4:</nobr><br></b></td><td align="left" valign="top">
	<select name="verweis4" size="1">
	<option value="0">---Kein Verweis---</option>
	<?php
	VerweisDok($verweisAkt);
	?>
	</select>
	</td></tr>
	
	<tr><td align="left" valign="middle"><b><nobr>Verweis 5:</nobr><br></b></td><td align="left" valign="top">
	<select name="verweis5" size="1">
	<option value="0">---Kein Verweis---</option>
	<?php
	VerweisDok($verweisAkt);
	?>
	</select>
	</td></tr>
	
	</table>
    <?php
    }
?>
</fieldset>
<!-- /EINSTELLUNGEN ################################################################### -->
<br>
<!-- STATUS ################################################################### -->
<fieldset>
<legend>Status</legend>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Online:<br></b></td><td align="left" valign="top"><input type="radio" name="online" id="onlineJa" value="1" checked><label for="onlineJa">Ja</label>&nbsp;<input type="radio" name="online" id="onlineNein" value="0"><label for="onlineNein">Nein</label></td></tr>

</table>
</fieldset>
<!-- /STATUS ################################################################### -->
<br>
<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top"><a href="index.php?modus=DOK&inc=DUE">Zur&uuml;ck zur &Uuml;bersicht</a></td></tr>

</table>

</fieldset>
<!-- /AKTIONEN ################################################################### -->

</td></tr>

<tr><td align="center"><input type="submit" value="Neues Dokument anlegen"></td></tr>

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

	
	$fehlerStr = "<h3 align=\"left\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
		
	// Feldtest
	if($ScmsLang){if(!$lang){$fehler=1; $fehlerStr = $fehlerStr."<li>Die Sprache wurde nicht ausgew&auml;hlt.\n";}}
	if(!$titel){$fehler=1; $fehlerStr = $fehlerStr."<li>Der Titel des Dokuments wurde nicht angegeben.\n";}
	if(!$linktext){$fehler=1; $fehlerStr = $fehlerStr."<li>Der Linktext des Dokuments wurde nicht angegeben.\n";}
	if($ScmsVerweise){if(!$kurztext){$fehler=1; $fehlerStr = $fehlerStr."<li>Der Kurztext des Dokuments wurde nicht angegeben.\n";}}
	
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
		// Vorbereiten
		if($skript){$typ="skript";}else{$typ="intern";}
		
		// SQL-String bauen
		$sqlString = "INSERT INTO "._DBdokumente." (Lang,Ordner,Titel,Linktext,Kurztext,Typ,Quelle,Skript,Inhalt,Position,AnzeigeTitel,AnzeigeLinktext,AnzeigeKurztext,Auth,Verweis1,Verweis2,Verweis3,Verweis4,Verweis5,Online,Erzeugt,Geaendert) VALUES ('".$lang."','".$ordner."','".addslashes($titel)."','".addslashes($linktext)."','".addslashes($kurztext)."','".$typ."','".$quelle."','".$skript."','".$inhalt."','".$position."','".$anzeigeTitel."','".$anzeigeLinktext."','".$anzeigeKurztext."','".$auth."','".$verweis1."','".$verweis2."','".$verweis3."','".$verweis4."','".$verweis5."','".$online."','".$erzeugt."','".$geaendert."')";
	
		// Neue Veranstaltung in DB speichern
		$ergebnis = $db -> sql($sqlString);
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3 align=\"left\">Neues Dokument angelegt</h3>\nDie Angaben zum Dokument wurden erfolgreich in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=DOK&inc=DUE\">Zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=DOK&inc=DUE&id=".mysql_insert_id()."\">...zum angelegten Dokument</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDie Angaben zum Dokument konnten nicht in der Datenbank gespeichert werden.<br>\nBitte versuch es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//######################################################################################
// /Step 1: Pruefen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Dokument anlegen -->