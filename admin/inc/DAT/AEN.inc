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
$neu = $_POST["neu"];
$erzeugt = $_POST["erzeugt"];
$geaendert = $_POST["geaendert"];
$modus = $_POST["modus"];
$inc = $_POST["inc"];
$step = $_POST["step"];

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}

// Daten fuer Kontakt aus DB holen
// SQL-String bauen
$sqlString = "SELECT * FROM "._KrakeDatenpool." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
?>

<!-- Content Konatkt &auml;ndern -->

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

<h3>Kontakt &auml;ndern</h3>

<!-- Innere Tabelle Eingabe -->

<p>
<fieldset>
<table border="0" cellpadding="3" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Zurueck
	echo "<a href=\"javascript:history.back()\">Zur&uuml;ck zur Kontakt&uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<p>
<fieldset><legend>Pers&ouml;nliche Daten</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Anrede:<br></b></td><td align="left" valign="top">
<select name="anrede" size="1">
<option value="0"<?php if($zeile["Anrede"]=="0"){echo " selected";}?>>----</option>
<option<?php if($zeile["Anrede"]=="Frau"){echo " selected";}?>>Frau</option>
<option<?php if($zeile["Anrede"]=="Herr"){echo " selected";}?>>Herr</option>
</select>
</td></tr>

<tr><td align="left" valign="top"><b>Titel:<br></b></td><td align="left" valign="top">
<input type="text" name="titel" size="15" maxlength="64" value="<?php echo $zeile["Titel"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Vorname:<br></b></td><td align="left" valign="top">
<input type="text" name="vorname" size="32" maxlength="64" value="<?php echo $zeile["Vorname"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Nachname:<br></b></td><td align="left" valign="top">
<input type="text" name="nachname" size="32" maxlength="64" value="<?php echo $zeile["Nachname"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Spitzname:<br></b></td><td align="left" valign="top">
<input type="text" name="spitzname" size="32" maxlength="64" value="<?php echo $zeile["Spitzname"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Firma/Organisation:<br></b></td><td align="left" valign="top">
<input type="text" name="firma" size="32" maxlength="64" value="<?php echo $zeile["Firma"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Position:<br></b></td><td align="left" valign="top">
<input type="text" name="position" size="32" maxlength="64" value="<?php echo $zeile["Position"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><br><i>Anschrift gesch&auml;ftlich:<br></i></td><td align="left" valign="top">
&nbsp
</td></tr>

<tr><td align="left" valign="top"><b>Strasse &amp; Nummer:<br></b></td><td align="left" valign="top">
<input type="text" name="bueroStrasse" size="32" maxlength="64" value="<?php echo $zeile["BueroStrasse"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>PLZ &amp; Ort:<br></b></td><td align="left" valign="top">
<input type="text" name="bueroPlz" size="5" maxlength="10" value="<?php echo $zeile["BueroPLZ"]; ?>">
<input type="text" name="bueroOrt" size="25" maxlength="64" value="<?php echo $zeile["BueroOrt"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Bundesland:<br></b></td><td align="left" valign="top">
<input type="text" name="bueroBundesland" size="32" maxlength="64" value="<?php echo $zeile["BueroBundesland"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Land:<br></b></td><td align="left" valign="top">
<input type="text" name="bueroLand" size="32" maxlength="64" value="<?php echo $zeile["BueroLand"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><br><i>Anschrift privat:<br></i></td><td align="left" valign="top">
&nbsp
</td></tr>

<tr><td align="left" valign="top"><b>Strasse &amp; Nummer:<br></b></td><td align="left" valign="top">
<input type="text" name="privatStrasse" size="32" maxlength="64" value="<?php echo $zeile["PrivatStrasse"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>PLZ &amp; Ort:<br></b></td><td align="left" valign="top">
<input type="text" name="privatPlz" size="5" maxlength="10" value="<?php echo $zeile["PrivatPLZ"]; ?>">
<input type="text" name="privatOrt" size="25" maxlength="64" value="<?php echo $zeile["PrivatOrt"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Bundesland:<br></b></td><td align="left" valign="top">
<input type="text" name="privatBundesland" size="32" maxlength="64" value="<?php echo $zeile["PrivatBundesland"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Land:<br></b></td><td align="left" valign="top">
<input type="text" name="privatLand" size="32" maxlength="64" value="<?php echo $zeile["PrivatLand"]; ?>">
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>weitere Kontaktdaten</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top" width="140"><b>Telefon, gesch&auml;ftlich:<br></b></td><td align="left" valign="top">
<input type="text" name="teleBuero" size="25" maxlength="64" value="<?php echo $zeile["TeleBuero"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Telefon, privat:<br></b></td><td align="left" valign="top">
<input type="text" name="telePrivat" size="25" maxlength="64" value="<?php echo $zeile["TelePrivat"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Fax:<br></b></td><td align="left" valign="top">
<input type="text" name="teleFax" size="25" maxlength="64" value="<?php echo $zeile["TeleFax"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Mobil:<br></b></td><td align="left" valign="top">
<input type="text" name="teleMobil" size="25" maxlength="64" value="<?php echo $zeile["TeleMobil"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>eMail, gesch&auml;ftlich:<br></b></td><td align="left" valign="top">
<input type="text" name="mailBuero" size="25" maxlength="64" value="<?php echo $zeile["MailBuero"]; ?>">
<nobr><input type="radio" name="mailStandard" value="MailBuero"<?php if($zeile["MailStandard"]=="MailBuero"){echo " checked";}; ?>>Standard</nobr>
</td></tr>

<tr><td align="left" valign="top"><b>eMail, privat:<br></b></td><td align="left" valign="top">
<input type="text" name="mailPrivat" size="25" maxlength="64" value="<?php echo $zeile["MailPrivat"]; ?>">
<nobr><input type="radio" name="mailStandard" value="MailPrivat"<?php if($zeile["MailStandard"]=="MailPrivat"){echo " checked";}; ?>>Standard</nobr>
</td></tr>

<tr><td align="left" valign="top"><b>Website:<br></b></td><td align="left" valign="top">
<input type="text" name="netz" size="25" maxlength="64" value="<?php if($zeile["Netz"]){echo $zeile["Netz"];}else{echo "http://";} ?>">
</td></tr>
</table>
</fieldset>
</p>

<p>
<fieldset><legend>Weitere Angaben</legend>
<table border="0" cellpadding="3" cellspacing="3">

<?php
// Geburt vorbereiten
$datum = explode(" ",$zeile["Geburt"]);
$datum = explode("-",$datum[0]);
?>

<tr><td align="left" valign="top"><b>Geburtsdatum:<br></b></td><td align="left" valign="top">
<select name="geburtTag" size="1">
<option value="00">--</option>
<?php
// GeburtTag bauen
for($c=1;$c<32;$c++)
	{
	if($c<10){$a="0".$c;}else{$a=$c;}
	if($datum[2]==$c){$selected=" selected";}
	echo "<option".$selected.">".$a."</option>";
	$selected="";
	}
?>
</select> .
<select name="geburtMonat" size="1">
<option value="00">--</option>
<?php
// GeburtMonat bauen
for($c=1;$c<13;$c++)
	{
	if($c<10){$a="0".$c;}else{$a=$c;}
	if($datum[1]==$c){$selected=" selected";}
	echo "<option".$selected.">".$a."</option>";
	$selected="";
	}
?>
</select> .
<select name="geburtJahr" size="1">
<option value="0000">----</option>
<?php
// GeburtJahr bauen
$datumJ = getdate(time());
$stop = $datumJ["year"]-120;
for($c=$datumJ["year"];$c>$stop;$c--)
	{
	if($datum[0]==$c){$selected=" selected";}
	echo "<option".$selected.">".$c."</option>";
	$selected="";
	}
?>
</select>
</td></tr>

<tr><td align="left" valign="top"><b>SkypeID:<br></b></td><td align="left" valign="top">
<input type="text" name="skypeId" size="25" maxlength="64" value="<?php echo $zeile["SkypeID"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>ICQ:<br></b></td><td align="left" valign="top">
<input type="text" name="icq" size="25" maxlength="64" value="<?php echo $zeile["ICQ"]; ?>">
</td></tr>

</table>
</fieldset>
</p>



<p>
<fieldset><legend>Bankverbindung</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Kontoinhaber:<br></b></td><td align="left" valign="top">
<input type="text" name="kontoInhaber" size="25" maxlength="64" value="<?php echo $zeile["KontoInhaber"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Geldinstitut:<br></b></td><td align="left" valign="top">
<input type="text" name="kontoBank" size="25" maxlength="64" value="<?php echo $zeile["KontoBank"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Kontonummer:<br></b></td><td align="left" valign="top">
<input type="text" name="kontoNummer" size="25" maxlength="64" value="<?php echo $zeile["KontoNummer"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>BLZ:<br></b></td><td align="left" valign="top">
<input type="text" name="kontoBlz" size="25" maxlength="64" value="<?php echo $zeile["KontoBLZ"]; ?>">
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Klassen & Notizen</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Klassen:<br></b></td><td align="left" valign="top">
<textarea name="klassen" cols="44" rows="12"><?php echo stripslashes($zeile["Klassen"]); ?></textarea>
<i class="kleiner"><b class="textRot">Achtung:</b> Nur EINE Klassen pro Zeile eingeklammert in "[" &amp; "]"!</i>
</td></tr>

<tr><td align="left" valign="top"><b>Notizen:<br></b></td><td align="left" valign="top">
<textarea name="notizen" cols="44" rows="20"><?php echo stripslashes($zeile["Notizen"]); ?></textarea>
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Status</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Neu:<br></b></td><td align="left" valign="top">
<input type="radio" name="neu" value="1"<?php if($zeile["Neu"]=="1"){echo " checked";} ?>>Ja&nbsp;&nbsp;&nbsp;<input type="radio" name="neu" value="0"<?php if($zeile["Neu"]=="0"){echo " checked";} ?>>Nein<br>
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset>
<table border="0" cellpadding="3" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Zurueck
	echo "<a href=\"javascript:history.back()\">Zur&uuml;ck zur Kontakt&uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<p align="center"><input type="submit" value="Kontakt &auml;ndern"></p>

<!-- /Innere Tabelle Eingabe -->

<?php
// Datum erzeugen
$geaendert = datetimemaker(time());
?>

<input type="hidden" name="id" value="<?php echo $id; ?>">
<input type="hidden" name="erzeugt" value="<?php echo $zeile["Erzeugt"]; ?>">
<input type="hidden" name="geaendert" value="<?php echo $geaendert; ?>">
<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">

</form>

<?php
	}
//######################################################################################
// /Step 0: Eingabe

// Step 1: Pr&uuml;fen und speichern
//######################################################################################
if($step==1)
	{
	// Fehlerbehandlung
	//######################################################################################
	
		$fehlerStr = "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
	
	// Feldtest
	if($mailBuero!="")
		{
		$mailAt = explode("@", $mailBuero);
		if(count($mailAt)!="2"){$fehler=1; $fehlerStr.="<li>Die B&uuml;ro-E-Mail-Adresse ist nicht korrekt\n";}
		else{
			$mailPunkt = explode(".", $mailAt[1]);
			if(count($mailPunkt)<"2"){$fehler=1; $fehlerStr.="<li>Die B&uuml;ro-E-Mail-Adresse ist nicht korrekt\n";}
			}
		}
	if($mailPrivat!="")
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
		$sqlString = "UPDATE "._KrakeDatenpool." SET Neu='".$neu."',Anrede='".$anrede."',Titel='".$titel."',Vorname='".$vorname."',Nachname='".$nachname."',Spitzname='".$spitzname."',Firma='".$firma."',BueroStrasse='".$bueroStrasse."',BueroPLZ='".$bueroPlz."',BueroOrt='".$bueroOrt."',BueroBundesland='".$bueroBundesland."',BueroLand='".$bueroLand."',PrivatStrasse='".$privatStrasse."',PrivatPLZ='".$privatPlz."',PrivatOrt='".$privatOrt."',PrivatBundesland='".$privatBundesland."',PrivatLand='".$privatLand."',TeleBuero='".$teleBuero."',TelePrivat='".$telePrivat."',TeleFax='".$teleFax."',TeleMobil='".$teleMobil."',MailBuero='".$mailBuero."',MailPrivat='".$mailPrivat."',MailStandard='".$mailStandard."',Netz='".$netz."',Geburt='".$geburt."',SkypeID='".$skypeId."',ICQ='".$icq."',KontoInhaber='".$kontoInhaber."',KontoBank='".$kontoBank."',KontoNummer='".$kontoNummer."',KontoBLZ='".$kontoBlz."',Klassen='".$klassen."',Notizen='".$notizen."',Erzeugt='".$erzeugt."',Geaendert='".$geaendert."' WHERE ID='".$id."'";
	
		// Neuen Eintrag in DB speichern
		$ergebnis = $db -> sql($sqlString);
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3>Kontakt ge&auml;ndert</h3>\nDer Kontakt wurde erfolgreich in der Datenbank ge&auml;ndert.<br>\n<br>\n<a href=\"index.php?modus=DAT&inc=KON\">zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=DAT&inc=KON&id=".$id."\">...zum ge&auml;nderten Kontakt</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDer Kontakt konnte nicht in der Datenbank ge&auml;ndert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//######################################################################################
// /Step 1: Pruefen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Kontakt &auml;ndern -->