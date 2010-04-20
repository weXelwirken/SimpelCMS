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
?>

<!-- Content Nutzer anlegen -->

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

<h3>Nutzer neu anlegen</h3>

<!-- Innere Tabelle Eingabe -->

<p>
<fieldset><legend>Pers&ouml;nliche Daten</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top" width="140"><b>Anrede:<br></b></td><td align="left" valign="top">
<select name="anrede" size="1">
<option>Frau</option>
<option>Herr</option>
</select>
</td></tr>

<tr><td align="left" valign="top"><b>Vorname:<br></b></td><td align="left" valign="top">
<input type="text" name="vorname" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Nachname:<br></b></td><td align="left" valign="top">
<input type="text" name="nachname" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Strasse &amp; Nummer:<br></b></td><td align="left" valign="top">
<input type="text" name="strasse" size="32" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>PLZ &amp; Ort:<br></b></td><td align="left" valign="top">
<input type="text" name="plz" size="5" maxlength="10">
<input type="text" name="ort" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Land:<br></b></td><td align="left" valign="top">
<input type="text" name="land" size="32" maxlength="64">
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Weitere Kontaktdaten</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top" width="140"><b>Telefon:<br></b></td><td align="left" valign="top">
<input type="text" name="telefon" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Mobil:<br></b></td><td align="left" valign="top">
<input type="text" name="mobil" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>eMail:<br></b></td><td align="left" valign="top">
<input type="text" name="mail" size="25" maxlength="64">
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Notizen</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Notizen:<br></b></td><td align="left" valign="top">
<textarea name="notizen" cols="44" rows="20"></textarea>
</td></tr>

</table>
</fieldset>
</p>

<p>
<fieldset><legend>Login, Passwort &amp; Status</legend>
<table border="0" cellpadding="3" cellspacing="3">

<tr><td align="left" valign="top"><b>Login:<br></b></td><td align="left" valign="top">
<input type="text" name="login" size="25" maxlength="64">
</td></tr>

<tr><td align="left" valign="top"><b>Passwort:<br></b></td><td align="left" valign="top">
<input type="text" name="passwort" size="25" maxlength="64" value="<?php echo MakePW("10"); ?>">
</td></tr>

<tr><td align="left" valign="top"><b>Gesperrt:<br></b></td><td align="left" valign="top">
<input type="radio" name="gesperrt" value="1" id="gesperrtJa"><label for="gesperrtJa">Ja</label>&nbsp;&nbsp;&nbsp;
<input type="radio" name="gesperrt" value="0" checked id="gesperrtNein"><label for="gesperrtNein">Nein</label>
</td></tr>

<tr><td align="left" valign="top"><b>Rolle:<br></b></td><td align="left" valign="top">
<select size="1" name="rolle">
<option value="x">Bitte w&auml;hlen</option>
<?php
foreach($RollenArray as $key => $item)
    {
    echo "<option value=\"".$key."\"".$selected.">".$item."</option>\n";
    }
?>
</select>
</td></tr>

</table>
</fieldset>
</p>

<p align="center"><input type="submit" value="Nutzer anlegen"></p>

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
    if(!$passwort){$fehler=1; $fehlerStr.="<li>Es wurde kein Passwort angegeben\n";}
    if($login==$passwort){$fehler=1; $fehlerStr.="<li>Login und Passwort m&uuml;ssen verschieden sein\n";}
    if(strlen($passwort)<6){$fehler=1; $fehlerStr.="<li>Das Passwort mu&szlig; mindestens 6 Zeichen lang sein\n";}
    if($rolle=="x"){$fehler=1; $fehlerStr.="<li>Es wurde keine Rolle angegeben\n";}
    // Testen, ob Login noch frei
    $sqlString = "SELECT ID FROM "._DBuserauth." WHERE Login='".$login."'";
    $ergebnis = $db -> sql($sqlString);
    if($ergebnis){$num=mysql_num_rows($ergebnis);}
    if($num>0){$fehler=1; $fehlerStr.="<li>Es ist schon ein Login mit dem gleichen Namen vorhanden\n";}
		
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
		$passwort = md5($passwort);
		
		// SQL-String bauen
		$sqlString = "INSERT INTO "._DBuserauth." (Anrede,Vorname,Nachname,Strasse,PLZ,Ort,Land,Telefon,Mobil,Mail,Notizen,Login,Passwort,Gesperrt,Rolle,Erzeugt,Geaendert) VALUES ('".$anrede."','".addslashes($vorname)."','".addslashes($nachname)."','".addslashes($strasse)."','".$plz."','".addslashes($ort)."','".$land."','".$telefon."','".$mobil."','".$mail."','".addslashes($notizen)."','".$login."','".$passwort."','".$gesperrt."','".$rolle."','".$erzeugt."','".$geaendert."')";
	
		// Neuen Eintrag in DB speichern
		$ergebnis = $db -> sql($sqlString);
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3>Neuer Nutzer angelegt</h3>\nDer neue Nutzer wurde erfolgreich in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=NUT&inc=NUE\">zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=NUT&inc=NAN\">...weiteren Nutzer anlegen<br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDer Nutzer konnte nicht in der Datenbank gespeichert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//######################################################################################
// /Step 1: Prufen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Nutzer anlegen -->