<?php
// POST und GET extrahieren
$step = $_POST["step"];
$anrede = $_POST["anrede"];
$vorname = $_POST["vorname"];
$nachname = $_POST["nachname"];
$strasse = $_POST["strasse"];
$plz = $_POST["plz"];
$ort = $_POST["ort"];
$land = $_POST["land"];
$telefon = $_POST["telefon"];
$mobil = $_POST["mobil"];
$mail = $_POST["mail"];
$notizen = $_POST["notizen"];
$login = $_POST["login"];
$passwort = $_POST["passwort"];
$gesperrt = $_POST["gesperrt"];
$rolle = $_POST["rolle"];
$rolleAlt = $_POST["rolleAlt"];
$erzeugt = $_POST["erzeugt"];
if($_POST["id"]){$id = $_POST["id"];}
if($_POST["geaendert"]){$geaendert = $_POST["geaendert"];}
if($_POST["modus"]){$modus = $_POST["modus"];}
if($_POST["inc"]){$inc = $_POST["inc"];}


// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}

// Daten fuer Kontakt aus DB holen
// SQL-String bauen
$sqlString = "SELECT * FROM "._DBuserauth." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
?>

<!-- Content Nutzer aendern -->

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

<h3>Nutzer &auml;ndern</h3>

<!-- Innere Tabelle Eingabe -->

<p>
<fieldset>
<table border="0" cellpadding="3" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Zurueck
	echo "<a href=\"javascript:history.back()\">Zur&uuml;ck zur Nutzer&uuml;bersicht</a>";
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
<option<?php if($zeile["Anrede"]=="Frau"){echo " selected";}?>>Frau</option>
<option<?php if($zeile["Anrede"]=="Herr"){echo " selected";}?>>Herr</option>
</select>
</td></tr>

<tr><td align="left" valign="top"><b>Vorname:<br></b></td><td align="left" valign="top">
<input type="text" name="vorname" size="32" maxlength="64" value="<?php echo $zeile["Vorname"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Nachname:<br></b></td><td align="left" valign="top">
<input type="text" name="nachname" size="32" maxlength="64" value="<?php echo $zeile["Nachname"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Strasse &amp; Nummer:<br></b></td><td align="left" valign="top">
<input type="text" name="strasse" size="32" maxlength="64" value="<?php echo $zeile["Strasse"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>PLZ &amp; Ort:<br></b></td><td align="left" valign="top">
<input type="text" name="plz" size="5" maxlength="10" value="<?php echo $zeile["PLZ"]; ?>">
<input type="text" name="ort" size="25" maxlength="64" value="<?php echo $zeile["Ort"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Land:<br></b></td><td align="left" valign="top">
<input type="text" name="land" size="32" maxlength="64" value="<?php echo $zeile["Land"]; ?>">
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>weitere Kontaktdaten</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top" width="140"><b>Telefon:<br></b></td><td align="left" valign="top">
<input type="text" name="telefon" size="25" maxlength="64" value="x<?php echo $zeile["Telefon"]; ?>x">
</td></tr>

<tr><td align="left" valign="top"><b>Mobil:<br></b></td><td align="left" valign="top">
<input type="text" name="mobil" size="25" maxlength="64" value="<?php echo $zeile["Mobil"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>eMail:<br></b></td><td align="left" valign="top">
<input type="text" name="mail" size="25" maxlength="64" value="<?php echo $zeile["Mail"]; ?>">
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Notizen</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Notizen:<br></b></td><td align="left" valign="top">
<textarea name="notizen" cols="44" rows="20"><?php echo $zeile["Notizen"]; ?></textarea>
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Login, Passwort &amp; Status</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Login:<br></b></td><td align="left" valign="top">
<input type="text" name="login" size="25" maxlength="64" value="<?php echo $zeile["Login"]; ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Passwort:<br></b></td><td align="left" valign="top">
<input type="password" name="passwort" size="25" maxlength="64"><br><span class="kleiner"><i><b><span class="textRot">Achtung:</span></b> Nur ausf&uuml;llen, wenn das aktuelle Passwort ge&auml;ndert werden soll!</i></span>
</td></tr>

<tr><td align="left" valign="top"><b>Gesperrt:<br></b></td><td align="left" valign="top">
<input type="radio" name="gesperrt" value="1" id="gesperrtJa"<?php if($zeile["Gesperrt"]=="1"){echo " checked";} ?>><label for="gesperrtJa">Ja</label>&nbsp;&nbsp;&nbsp;<input type="radio" name="gesperrt" value="0" id="gesperrtNein"<?php if($zeile["Gesperrt"]=="0"){echo " checked";} ?>><label for="gesperrtNein">Nein</label><br>
</td></tr>

<tr><td align="left" valign="top"><b>Rolle:<br></b></td><td align="left" valign="top">
<select size="1" name="rolle">
<?php
foreach($RollenArray as $key => $item)
    {
    if($key==$zeile["Rolle"]){$selected=" selected";}else{$selected="";}
    echo "<option value=\"".$key."\"".$selected.">".$item."</option>\n";
    }
?>
</select>
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
	echo "<a href=\"javascript:history.back()\">Zur&uuml;ck zur Nutzer&uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<p align="center"><input type="submit" value="Nutzer &auml;ndern"></p>

<!-- /Innere Tabelle Eingabe -->

<?php
// Datum erzeugen
$geaendert = datetimemaker(time());
?>

<input type="hidden" name="rolleAlt" value="<?php echo $zeile["Rolle"]; ?>">
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

// Step 1: Pruefen und speichern
//######################################################################################
if($step==1)
	{
	// Fehlerbehandlung
	//######################################################################################
	
		$fehlerStr = "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
	
	// Feldtest
	if($mail!="")
		{
		$mailAt = explode("@", $mail);
		if(count($mailAt)!="2"){$fehler=1; $fehlerStr.="<li>Die eMail-Adresse ist nicht korrekt\n";}
		else{
			$mailPunkt = explode(".", $mailAt[1]);
			if(count($mailPunkt)<"2"){$fehler=1; $fehlerStr.="<li>Die eMail-Adresse ist nicht korrekt\n";}
			}
		}
    if(!$login){$fehler=1; $fehlerStr.="<li>Es wurde kein Login angegeben\n";}
    if($login==$passwort){$fehler=1; $fehlerStr.="<li>Login und Passwort m&uuml;ssen verschieden sein\n";}
    if($passwort AND strlen($passwort)<6){$fehler=1; $fehlerStr.="<li>Das Passwort mu&szlig; mindestens 6 Zeichen lang sein\n";}
    // Testen, ob Login noch frei
    $sqlString = "SELECT ID FROM "._DBuserauth." WHERE Login='".$login."' AND ID!='".$id."'";
    $ergebnis = $db -> sql($sqlString);
    if($ergebnis){$num=mysql_num_rows($ergebnis);}
    if($num>0){$fehler=1; $fehlerStr.="<li>Es ist schon ein Login mit dem gleichen Namen vorhanden\n";}
    // Testen, ob min. ein Admin vorhanden
	if($rolle<"3" AND $rolleAlt=="3")
        {
        $sqlString = "SELECT ID FROM "._DBuserauth." WHERE Rolle='3' AND ID!='".$id."'";
        $ergebnis = $db -> sql($sqlString);
        if($ergebnis){$num=mysql_num_rows($ergebnis);}
        if($num<1){$fehler=1; $fehlerStr.="<li>Wenn Sie diese &Auml;nderung durchf&uuml;hren, gibt es keinen Nutzer mit Administrations-Rechten mehr\n";}
        }
        
		
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
		
		// Passwort codieren
		if($passwort){$passwort = ",Passwort='".md5($passwort)."'";}
		else{$passwort = "";}
		
		// SQL-String bauen
		$sqlString = "UPDATE "._DBuserauth." SET Anrede='".$anrede."',Vorname='".addslashes($vorname)."',Nachname='".addslashes($nachname)."',Strasse='".addslashes($strasse)."',PLZ='".$plz."',Ort='".addslashes($ort)."',Land='".$land."',Telefon='".$telefon."',Mobil='".$mobil."',Mail='".$mail."',Notizen='".addslashes($notizen)."',Login='".$login."'".$passwort.",Gesperrt='".$gesperrt."',Rolle='".$rolle."',Erzeugt='".$erzeugt."',Geaendert='".$geaendert."' WHERE ID='".$id."'";
	
		// Neuen Eintrag in DB speichern
		$ergebnis = $db -> sql($sqlString);
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3>Nutzer ge&auml;ndert</h3>\nDer Nutzer wurde erfolgreich in der Datenbank ge&auml;ndert.<br>\n<br>\n<a href=\"index.php?modus=NUT&inc=NUE\">zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=NUT&inc=NUE&id=".$id."\">...zum ge&auml;nderten Nutzer</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDer Nutzer konnte nicht in der Datenbank ge&auml;ndert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//######################################################################################
// /Step 1: Pruefen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Nutzer aendern -->