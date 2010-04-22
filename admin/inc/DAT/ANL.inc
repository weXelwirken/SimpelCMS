<?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// POST und GET extrahieren
$anrede = $_POST["anrede"];
$titel = $_POST["titel"];
$vorname = $_POST["vorname"];
$nachname = $_POST["nachname"];
$spitzname = $_POST["spitzname"];
$firma = $_POST["firma"];
$position = $_POST["position"];
$bueroStrasse = $_POST["bueroStrasse"];
$bueroPlz = $_POST["bueroPlz"];
$bueroOrt = $_POST["bueroOrt"];
$bueroBundesland = $_POST["bueroBundesland"];
$bueroLand = $_POST["bueroLand"];
$privatStrasse = $_POST["privatStrasse"];
$privatPlz = $_POST["privatPlz"];
$privatOrt = $_POST["privatOrt"];
$privatBundesland = $_POST["privatBundesland"];
$privatLand = $_POST["privatLand"];
$teleBuero = $_POST["teleBuero"];
$telePrivat = $_POST["telePrivat"];
$teleFax = $_POST["teleFax"];
$teleMobil = $_POST["teleMobil"];
$mailBuero = $_POST["mailBuero"];
$mailPrivat = $_POST["mailPrivat"];
$mailStandard = $_POST["mailStandard"];
$netz = $_POST["netz"];
$geburtTag = $_POST["geburtTag"];
$geburtMonat = $_POST["geburtMonat"];
$geburtJahr = $_POST["geburtJahr"];
$skypeId = $_POST["skypeId"];
$icq = $_POST["icq"];
$kontoInhaber = $_POST["kontoInhaber"];
$kontoBank = $_POST["kontoBank"];
$kontoNummer = $_POST["kontoNummer"];
$kontoBlz = $_POST["kontoBlz"];
$klassen = $_POST["klassen"];
$notizen = $_POST["notizen"];
$erzeugt = $_POST["erzeugt"];
$geaendert = $_POST["geaendert"];
$modus = $_POST["modus"];
$inc = $_POST["inc"];
$step = $_POST["step"];

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}
?>

<!-- Content Kontakt anlegen -->

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

<h3>Kontakt neu anlegen</h3>

<!-- Innere Tabelle Eingabe -->

<p>
<fieldset><legend>Pers&ouml;nliche Daten</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top" width="140"><b>Anrede:<br></b></td><td align="left" valign="top">
<select name="anrede" size="1">
<option value="0">----</option>
<option>Frau</option>
<option>Herr</option>
</select>
</td></tr>

<tr><td align="left" valign="top"><b>Titel:<br></b></td><td align="left" valign="top">
<input type="text" name="titel" size="15" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Vorname:<br></b></td><td align="left" valign="top">
<input type="text" name="vorname" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Nachname:<br></b></td><td align="left" valign="top">
<input type="text" name="nachname" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Spitzname:<br></b></td><td align="left" valign="top">
<input type="text" name="spitzname" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Firma/Organisation:<br></b></td><td align="left" valign="top">
<input type="text" name="firma" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Position:<br></b></td><td align="left" valign="top">
<input type="text" name="position" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><i>Anschrift gesch&auml;ftlich:<br></i></td><td align="left" valign="top">
&nbsp
</td></tr>

<tr><td align="left" valign="top"><b>Strasse &amp; Nummer:<br></b></td><td align="left" valign="top">
<input type="text" name="bueroStrasse" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>PLZ &amp; Ort:<br></b></td><td align="left" valign="top">
<input type="text" name="bueroPlz" size="5" maxlength="10">
<input type="text" name="bueroOrt" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Bundesland:<br></b></td><td align="left" valign="top">
<input type="text" name="bueroBundesland" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Land:<br></b></td><td align="left" valign="top">
<input type="text" name="bueroLand" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><i>Anschrift privat:<br></i></td><td align="left" valign="top">
&nbsp
</td></tr>

<tr><td align="left" valign="top"><b>Strasse &amp; Nummer:<br></b></td><td align="left" valign="top">
<input type="text" name="privatStrasse" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>PLZ &amp; Ort:<br></b></td><td align="left" valign="top">
<input type="text" name="privatPlz" size="5" maxlength="10">
<input type="text" name="privatOrt" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Bundesland:<br></b></td><td align="left" valign="top">
<input type="text" name="privatBundesland" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Land:<br></b></td><td align="left" valign="top">
<input type="text" name="privatLand" size="32" maxlength="64">
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Weitere Kontaktdaten</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top" width="140"><b>Telefon, gesch&auml;ftlich:<br></b></td><td align="left" valign="top">
<input type="text" name="teleBuero" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Telefon, privat:<br></b></td><td align="left" valign="top">
<input type="text" name="telePrivat" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Fax:<br></b></td><td align="left" valign="top">
<input type="text" name="teleFax" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Mobil:<br></b></td><td align="left" valign="top">
<input type="text" name="teleMobil" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>eMail, gesch&auml;ftlich:<br></b></td><td align="left" valign="top">
<input type="text" name="mailBuero" size="25" maxlength="64">
<nobr><input type="radio" name="mailStandard" value="MailBuero" checked>Standard</nobr>
</td></tr>

<tr><td align="left" valign="top"><b>eMail, privat:<br></b></td><td align="left" valign="top">
<input type="text" name="mailPrivat" size="25" maxlength="64">
<nobr><input type="radio" name="mailStandard" value="MailPrivat">Standard</nobr>
</td></tr>

<tr><td align="left" valign="top"><b>Website:<br></b></td><td align="left" valign="top">
<input type="text" name="netz" size="25" maxlength="64" value="http://">
</td></tr>
</table>
</fieldset>
</p>

<p>
<fieldset><legend>Weitere Angaben</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top" width="140"><b>Geburtsdatum:<br></b></td><td align="left" valign="top">
<select name="geburtTag" size="1">
<option value="00">--</option>
<?php
// GeburtTag bauen
for($c=1;$c<32;$c++)
	{
	if($c<10){$a="0".$c;}else{$a=$c;}
	echo "<option>".$a."</option>";
	}
?>
</select>.
<select name="geburtMonat" size="1">
<option value="00">--</option>
<?php
// GeburtMonat bauen
for($c=1;$c<13;$c++)
	{
	if($c<10){$a="0".$c;}else{$a=$c;}
	echo "<option>".$a."</option>";
	}
?>
</select>.
<select name="geburtJahr" size="1">
<option value="0000">----</option>
<?php
// GeburtJahr bauen
$datum = getdate(time());
$stop = $datum["year"]-120;
for($c=$datum["year"];$c>$stop;$c--)
	{
	echo "<option>".$c."</option>";
	}
?>
</select>
</td></tr>

<tr><td align="left" valign="top"><b>SkypeID:<br></b></td><td align="left" valign="top">
<input type="text" name="skypeId" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>ICQ:<br></b></td><td align="left" valign="top">
<input type="text" name="icq" size="25" maxlength="64">
</td></tr>

</table>
</fieldset>
</p>



<p>
<fieldset><legend>Bankverbindung</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top" width="140"><b>Kontoinhaber:<br></b></td><td align="left" valign="top">
<input type="text" name="kontoInhaber" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Geldinstitut:<br></b></td><td align="left" valign="top">
<input type="text" name="kontoBank" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Kontonummer:<br></b></td><td align="left" valign="top">
<input type="text" name="kontoNummer" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>BLZ:<br></b></td><td align="left" valign="top">
<input type="text" name="kontoBlz" size="25" maxlength="64">
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Klassen & Notizen</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Klassen:<br></b></td><td align="left" valign="top">
<textarea name="klassen" cols="44" rows="12"></textarea>
<i class="kleiner"><b class="textRot">Achtung:</b> Nur EINE Klassen pro Zeile eingeklammert in "[" &amp; "]"!</i>
</td></tr>

<tr><td align="left" valign="top"><b>Notizen:<br></b></td><td align="left" valign="top">
<textarea name="notizen" cols="44" rows="20"></textarea>
</td></tr>
</table>
</fieldset>
</p>

<p align="center"><input type="submit" value="Kontakt anlegen"></p>

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

// Step 1: Prufen und speichern
//######################################################################################
if($step==1)
	{
	// Fehlerbehandlung
	//######################################################################################
	
	$fehlerStr = "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
	
	// Feldtest
	if($mailBuero)
		{
		$mailAt = explode("@", $mailBuero);
		if(count($mailAt)!="2"){$fehler=1; $fehlerStr.="<li>Die B&uuml;ro-E-Mail-Adresse ist nicht korrekt\n";}
		else{
			$mailPunkt = explode(".", $mailAt[1]);
			if(count($mailPunkt)<"2"){$fehler=1; $fehlerStr.="<li>Die B&uuml;ro-E-Mail-Adresse ist nicht korrekt\n";}
			}
		}
	if($mailPrivat)
		{
		$mailAt = explode("@", $mailPrivat);
		if(count($mailAt)!="2"){$fehler=1; $fehlerStr.="<li>Die Privat-E-Mail-Adresse ist nicht korrekt\n";}
		else{
			$mailPunkt = explode(".", $mailAt[1]);
			if(count($mailPunkt)<"2"){$fehler=1; $fehlerStr.="<li>Die Privat-E-Mail-Adresse ist nicht korrekt\n";}
			}
		}
    if(($vorname OR $nachname) AND !$anrede){$fehler=1; $fehlerStr.="<li>Es wurde keine Anrede ausgew&auml;hlt\n";}
    if(!$vorname AND !$nachname AND !$firma){$fehler=1; $fehlerStr.="<li>Bitte Vor- &amp; Nachname oder einen Firmennamen angeben\n";}
		
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
		// Sonderzeichen maskieren
		$notizen = addslashes($notizen);
		$klassen = addslashes($klassen);
		
		// Feld wirklich leeren, wenn leer
		if($netz=="http://"){$netz="";}
		if($anrede=="0"){$anrede="";}
		
		// Geburt zusammenbauen
		$geburt = $geburtJahr."-".$geburtMonat."-".$geburtTag." 00:00:00";
		
		// SQL-String bauen
		$sqlString = "INSERT INTO "._KrakeDatenpool." (Anrede,Titel,Vorname,Nachname,Spitzname,Firma,Position,BueroStrasse,BueroPLZ,BueroOrt,BueroBundesland,BueroLand,PrivatStrasse,PrivatPLZ,PrivatOrt,PrivatBundesland,PrivatLand,TeleBuero,TelePrivat,TeleFax,TeleMobil,MailBuero,MailPrivat,MailStandard,Netz,Geburt,SkypeID,ICQ,KontoInhaber,KontoBank,KontoNummer,KontoBLZ,Klassen,Notizen,Erzeugt,Geaendert) VALUES ('".$anrede."','".$titel."','".$vorname."','".$nachname."','".$spitzname."','".$firma."','".$position."','".$bueroStrasse."','".$bueroPlz."','".$bueroOrt."','".$bueroBundesland."','".$bueroLand."','".$privatStrasse."','".$privatPlz."','".$privatOrt."','".$privatBundesland."','".$privatLand."','".$teleBuero."','".$telePrivat."','".$teleFax."','".$teleMobil."','".$mailBuero."','".$mailPrivat."','".$mailStandard."','".$netz."','".$geburt."','".$skypeId."','".$icq."','".$kontoInhaber."','".$kontoBank."','".$kontoNummer."','".$kontoBlz."','".$klassen."','".$notizen."','".$erzeugt."','".$geaendert."')";
	
		// Neuen Eintrag in DB speichern
		$ergebnis = $db -> sql($sqlString);
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3>Neuer Kontakt angelegt</h3>\nDer neue Kontakt wurde erfolgreich in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=DAT&inc=KON\">zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=DAT&inc=ANL\">...weiteren Kontakt anlegen<br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDer Kontakt konnte nicht in der Datenbank gespeichert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//######################################################################################
// /Step 1: Prufen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Kontakt anlegen -->