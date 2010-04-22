<?php

// DB-Verbindung

$db = new db($dbHost,$dbUser,$dbPasswort);

$db -> select_db($dbDatenbank);



// POST und GET extrahieren

$klasse = $_POST["klasse"];

$sendeOptionKla = $_POST["sendeOptionKla"];

$an = $_POST["an"];

$cc = $_POST["cc"];

$bcc = $_POST["bcc"];

$klassenTitel = $_POST["klassenTitel"];

$kontakt = $_POST["kontakt"];

$sendeOptionKon = $_POST["sendeOptionKon"];

$mailAnAlle = $_POST["mailAnAlle"];

$betreff = $_POST["betreff"];

$text = $_POST["text"];

$step = $_POST["step"];

$von = $_POST["von"];



// Testen ob Arbeitsschritt gesetzt

if($step==""){$step = 0;}



?>



<!-- Content Mail schreiben -->



<table border="0" cellpadding="0" cellspacing="0" width="480">



<tr>

<td align="left" valign="top">



<?php

// Step 0: Eingabe

//######################################################################################

if($step==0)

	{

	// Klasse hinzufuegen

	if($klasse=="0" OR $klasse=="")

		{echo "";}

	else

		{

		// Daten fuer Kontakte nach Klassen aus DB holen

		// SQL-String bauen

		$sqlString = "SELECT MailBuero, MailPrivat, MailStandard FROM "._KrakeDatenpool." WHERE Klassen LIKE '%[".$klasse."]%'";

		// Ergebnis auslesen

		$ergebnis = $db -> sql($sqlString);

		if($ergebnis)

			{

			while($klassenMail = mysql_fetch_array($ergebnis))

				{

				if($klassenMail["MailBuero"] AND $klassenMail["MailStandard"]=="MailBuero")

					{$mailAdressen.= $klassenMail["MailBuero"].", ";}

				if(!$klassenMail["MailBuero"] AND $klassenMail["MailStandard"]=="MailBuero" AND $klassenMail["MailPrivat"])

					{$mailAdressen.= $klassenMail["MailPrivat"].", ";}

				if($klassenMail["MailPrivat"] AND $klassenMail["MailStandard"]=="MailPrivat")

					{$mailAdressen.= $klassenMail["MailPrivat"].", ";}

				if(!$klassenMail["MailPrivat"] AND $klassenMail["MailStandard"]=="MailPrivat" AND $klassenMail["MailBuero"])

					{$mailAdressen.= $klassenMail["MailBuero"].", ";}

				}

			mysql_free_result($ergebnis);

			}

		else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

		

		// Titel der ausgewaehlten Klasse speichern

		if($klassenTitel){$klassenTitel.=", ".$klasseIdTitel[1];}

		else{$klassenTitel=$klasseIdTitel[1];}		

		

		// Sendeoptionen auswerten

		if($sendeOptionKla=="an")

			{

			if(substr($mailAdressen,strlen($mailAdressen)-2)==", ")

				{

				if($an){$an.=", ".substr($mailAdressen,0,strlen($mailAdressen)-2);}

				else{$an.=substr($mailAdressen,0,strlen($mailAdressen)-2);}

				}

			}

		if($sendeOptionKla=="cc")

			{

			if(substr($mailAdressen,strlen($mailAdressen)-2)==", ")

				{

				if($cc){$cc.=", ".substr($mailAdressen,0,strlen($mailAdressen)-2);}

				else{$cc.=substr($mailAdressen,0,strlen($mailAdressen)-2);}

				}

			}

		if($sendeOptionKla=="bcc")

			{

			if(substr($mailAdressen,strlen($mailAdressen)-2)==", ")

				{

				if($bcc){$bcc.=", ".substr($mailAdressen,0,strlen($mailAdressen)-2);}

				else{$bcc.=substr($mailAdressen,0,strlen($mailAdressen)-2);}

				}

			}

		}

		

	// Kontakt hinzufuegen

	if($kontakt=="0" OR $kontakt=="")

		{echo "";}

	else

		{		

		// Sendeoptionen auswerten

		if($sendeOptionKon=="an")

			{

			if($an){$an.=", ".$kontakt;}

			else{$an.=$kontakt;}

			}

		if($sendeOptionKon=="cc")

			{

			if($cc){$cc.=", ".$kontakt;}

			else{$cc.=$kontakt;}

			}

		if($sendeOptionKon=="bcc")

			{

			if($bcc){$bcc.=", ".$kontakt;}

			else{$bcc.=$kontakt;}

			}

		}

	?>



<h3>eMail verfassen</h3>



<!-- Innere Tabelle Eingabe -->



<p>

<fieldset><legend>Klassen & Kontakte hinzuf&uuml;gen</legend>

<table border="0" cellpadding="0" cellspacing="3" width="100%">



<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" multiple=" multiple" method="post">



<tr>

<td align="left" valign="middle" width="15%"><b>Klasse:<br></b></td>

<td align="left" valign="middle" width="85%" colspan="2">



<select name="klasse" size="1">

<option value="0">Klasse ausw&auml;hlen</option>



	<?php

	

	// Daten fuer Klasse aus DB holen

	// SQL-String bauen

	$sqlString = "SELECT ID, Titel FROM "._KrakeKlassen." ORDER BY Titel";

	// Ergebnis auslesen

	$ergebnis = $db -> sql($sqlString);

	if($ergebnis)

		{

		while($klassenDb = mysql_fetch_array($ergebnis))

			{

			echo "<option value=\"".$klassenDb["Titel"]."\">".$klassenDb["Titel"]."</option>";

			}

		mysql_free_result($ergebnis);

		}

	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

	

	?>



</select>



</td></tr>



<tr>

<td width="15%">&nbsp;<br></td>

<td valign="middle" width="80%" align="center" class="kleiner">

Sendeoptionen:

<input type="radio" name="sendeOptionKla" value="an" checked>AN

<input type="radio" name="sendeOptionKla" value="cc">CC

<input type="radio" name="sendeOptionKla" value="bcc">BCC

</td>

<td align="left" valign="middle" width="5%" align="right"><input type="submit" value="+"></td>

</tr>



<tr><td colspan="4">

	<?php

	if($klassenTitel)

		{

		echo "<span class=\"kleiner\"><b>Schon eingef&uuml;gte Klassen:</b> ".$klassenTitel."</span><br>\n";

		}

	?>

<img scr="img/one.gif" width="1" height="5" alt=""><br></td></tr>

<tr><td colspan="4" bgcolor="<?php echo $modusArrayADMIN[$_GET["modus"]]["Wert"]; ?>"><img scr="img/one.gif" width="100%" height="1" alt=""><br></td></tr>

<tr><td colspan="4"><img scr="img/one.gif" width="1" height="5" alt=""><br></td></tr>



<input type="hidden" name="an" value="<?php echo $an; ?>">

<input type="hidden" name="cc" value="<?php echo $cc; ?>">

<input type="hidden" name="bcc" value="<?php echo $bcc; ?>">

<input type="hidden" name="klassenTitel" value="<?php echo $klassenTitel; ?>">



</form>



<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" multiple=" multiple" method="post">



<tr>

<td align="left" valign="middle" width="10%"><b>Kontakt:<br></b></td>

<td align="left" valign="middle" width="50%" colspan="2">



<select name="kontakt" size="1">

<option value="0">Kontakt ausw&auml;hlen</option>



	<?php

	

	// Daten fuer Kontakte aus DB holen

	// SQL-String bauen

	$sqlString = "SELECT ID, Vorname, Nachname, MailBuero, MailPrivat FROM "._KrakeDatenpool." ORDER BY Nachname";

	// Ergebnis auslesen

	$ergebnis = $db -> sql($sqlString);

	if($ergebnis)

		{

		while($kontakteDb = mysql_fetch_array($ergebnis))

			{

			if($kontakteDb["MailBuero"])

				{echo "<option value=\"".$kontakteDb["MailBuero"]."\">".$kontakteDb["Nachname"].", ".$kontakteDb["Vorname"]." (".$kontakteDb["MailBuero"].")[B]</option>";}

			if($kontakteDb["MailPrivat"])

				{echo "<option value=\"".$kontakteDb["MailPrivat"]."\">".$kontakteDb["Nachname"].", ".$kontakteDb["Vorname"]." (".$kontakteDb["MailPrivat"].")[P]</option>";}

			

			}

		mysql_free_result($ergebnis);

		}

	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

	

	?>



</select>



</td>

</tr>



<tr>

<td width="15%">&nbsp;<br></td>

<td valign="middle" width="80%" align="center" class="kleiner">

Sendeoptionen:

<input type="radio" name="sendeOptionKon" value="an" checked>AN

<input type="radio" name="sendeOptionKon" value="cc">CC

<input type="radio" name="sendeOptionKon" value="bcc">BCC

</td>

<td align="left" valign="middle" width="5%" align="right"><input type="submit" value="+"></td>

</tr>



</table>

</fieldset>

</p>



<input type="hidden" name="von" value="<?php echo $von; ?>">

<input type="hidden" name="an" value="<?php echo $an; ?>">

<input type="hidden" name="cc" value="<?php echo $cc; ?>">

<input type="hidden" name="bcc" value="<?php echo $bcc; ?>">



</form>



<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" multiple=" multiple" method="post">



<p>

<fieldset><legend>eMail verfassen</legend>

<table border="0" cellpadding="3" cellspacing="3">



<tr><td align="left" valign="top"><b>VON*:<br></b></td><td align="left" valign="top">

<input type="text" name="von" size="59" maxlength="128" value="<?php echo $betreff; ?>"><span class="klein">*optional (ohne Eintrag wird von <?php echo $MailInfo; ?> gesendet)</span>

</td></tr>

<tr><td align="left" valign="top"><b>AN:<br></b></td><td align="left" valign="top">

<textarea name="an" cols="44" rows="2"><?php echo $an; ?></textarea><br>

<!-- <input type="checkbox" name="mailAnAlle" value="1">

<span class="klein"><i><b class="textRot">Mail an ALLE:</b></i> eMail wird an <b>alle</b> Kontakte in der Datenkrake gesendet!</span> -->

</td></tr>

<tr><td align="left" valign="top"><b>CC:<br></b></td><td align="left" valign="top">

<textarea name="cc" cols="44" rows="2"><?php echo $cc; ?></textarea>

</td></tr>

<tr><td align="left" valign="top"><b>BCC:<br></b></td><td align="left" valign="top">

<textarea name="bcc" cols="44" rows="2"><?php echo $bcc; ?></textarea>

</td></tr>



<tr><td align="left" valign="top"><b>Betreff:<br></b></td><td align="left" valign="top">

<input type="text" name="betreff" size="51" maxlength="128" value="<?php echo $betreff; ?>">

</td></tr>



<tr><td align="left" valign="top"><b>Text:<br></b></td><td align="left" valign="top">

<textarea name="text" cols="44" rows="15"><?php echo $text; ?></textarea>

</td></tr>



</table>

</fieldset>

</p>



<p align="center"><input type="submit" value="E-Mail-Vorschau"></p>



<!-- /Innere Tabelle Eingabe -->



<input type="hidden" name="step" value="1">



</form>



<?php

	}

//######################################################################################

// /Step 0: Eingabe



// Step 1: Pruefen und Vorschau

//######################################################################################

if($step==1)

	{

    $text = addslashes($text);

	// Fehlerbehandlung

	//######################################################################################

	

	$fehlerStr = "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";

	

	// Feldtest

	if($an=="" AND $cc=="" AND $bcc=="" AND $mailAnAlle==""){$fehler=1; $fehlerStr = $fehlerStr."<li>Bitte geben Sie mindestens eine E-Mail-Adresse an!\n";}

	if($betreff==""){$fehler=1; $fehlerStr = $fehlerStr."<li>Bitte geben Sie einen Betreff f&uuml;r die E-Mail an!\n";}

	if($text==""){$fehler=1; $fehlerStr = $fehlerStr."<li>Bitte geben Sie einen Text f&uuml;r die E-Mail an!\n";}

			

	$fehlerStr = $fehlerStr."</ul>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";

	

	// Fehlerausgabe

	if($fehler!="")

		{

		echo $fehlerStr;

		}



	// Vorschau

	//######################################################################################

	else

		{

		// Felder vorbereiten

		 if($mailAnAlle){$an.="&nbsp;<b class=\"textRot\">ALLE!</b>";} 

		 if(!$von){$von=$MailInfo;}

		?>

		

<h3>E-Mail-Vorschau</h3>



<p>

<fieldset><legend>Empf&auml;nger</legend>

<table border="0" cellpadding="3" cellspacing="3">



<tr><td align="left" valign="top"><b>VON:<br></b></td><td align="left" valign="top">

<?php echo $von; ?><br>

</td></tr>

<tr><td align="left" valign="top"><b>AN:<br></b></td><td align="left" valign="top">

<?php echo $an; ?><br>

</td></tr>

<tr><td align="left" valign="top"><b>CC:<br></b></td><td align="left" valign="top">

<?php echo $cc; ?><br>

</td></tr>

<tr><td align="left" valign="top"><b>BCC:<br></b></td><td align="left" valign="top">

<?php echo $bcc; ?><br>

</td></tr>



</table>

</fieldset>

</p>



<p>

<fieldset><legend>Nachricht</legend>

<table border="0" cellpadding="3" cellspacing="3">



<tr><td align="left" valign="top"><b>Betreff:<br></b></td><td align="left" valign="top"><?php echo $betreff; ?><br></td></tr>



<tr><td align="left" valign="top"><b>Text:<br></b></td><td align="left" valign="top"><?php echo nl2br($text); ?></td></tr>



</table>

</fieldset>

</p>



<p>

Wenn Sie diese E-Mail so, wie Sie sie hier sehen versenden m&ouml;chten, dann klicken Sie auf den Butten <b><i>"E-Mail senden"</i></b>.<br>

Wenn Sie noch &Auml;nderungen vornehmen wollen, dann k&ouml;nnen Sie hier <a href="javascript:history.back()">zum Eingabeformular zur&uuml;ck gelangen</a>.<br>

</p>



<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" multiple=" multiple" method="post">



<p align="center"><input type="submit" value="E-Mail senden"></p>



<input type="hidden" name="von" value="<?php echo $von; ?>">

<input type="hidden" name="an" value="<?php echo $an; ?>">

<input type="hidden" name="cc" value="<?php echo $cc; ?>">

<input type="hidden" name="bcc" value="<?php echo $bcc; ?>">

<input type="hidden" name="mailAnAlle" value="<?php echo $mailAnAlle; ?>">

<input type="hidden" name="betreff" value="<?php echo $betreff; ?>">

<input type="hidden" name="text" value="<?php echo $text; ?>">



<input type="hidden" name="step" value="2">



</form>



		<?php

		}

	}

//######################################################################################

// /Step 1: Pruefen und Vorschau



// Step 2: Senden

//######################################################################################

	

if($step==2)

	{

	// Mail an ALLE

	if($mailAnAlle)

	   {

	   // Daten fuer Mail an ALLE aus DB holen

		// SQL-String bauen

		$sqlString = "SELECT MailBuero, MailPrivat FROM "._KrakeDatenpool." WHERE MailPrivat!='' OR MailBuero!=''";

		// Ergebnis auslesen

		$ergebnis = $db -> sql($sqlString);

		if($ergebnis)

			{

			while($alleMail = mysql_fetch_array($ergebnis))

				{

				if($alleMail["MailBuero"])

					{$alleMailAdressen.= $alleMail["MailBuero"].", ";}

				if($alleMail["MailPrivat"])

					{$alleMailAdressen.= $alleMail["MailPrivat"].", ";}

				}

			mysql_free_result($ergebnis);

			}

		else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

	   }

	

	// Empfaenger zusammenfuegen

	$empfaenger = $an.", ".$cc.", ".$bcc.", ".$alleMailAdressen;

	// Empfaenger in Array zerlegen

	$anArray = explode(", ", $empfaenger);

	// Doppelte Eintraege entfernen

	$anArray = array_unique($anArray);

	// Summe der zusenden Mails bestimmen

	$summe = count($anArray)-1;

	

	$fehler = 0;

	echo "<h3 align=\"left\">E-Mail senden</h3>\n<p>\n";

	

	// Mailer-Schleife

	for($c=0;$c<count($anArray);$c++)

        {

        if($anArray[$c]!="")

            {

            // Header

            $header .= "From: ".$von."\r\n";

            //$header .= 'Cc: info@wexelwirken.net' . "\r\n";

            //$header .= 'Bcc: info@wexelwirken.net' . "\r\n";

            

            // "x von y"-Zaehler laden

            $c1 = $c+1;

            

            if(mail($anArray[$c], $betreff, $text, $header))

            // Fehlerbehandlung

                {

                // Ausgabe Erfolg

                echo $c1." von ".$summe.": <span class=\"textGruen\">Mail an <b>".$anArray[$c]."</b> erfolgreich gesendet.</span><br>\n";

                }

            else

                {

                // Ausgabe Misserfolg

                echo $c1." von ".$summe.": <span class=\"textRot\">Mail an <b>".$anArray[$c]."</b> nicht gesendet.</span><br>\n";

                $fehler = $fehler + 1;

                }

            }

        }

    echo "</p>\n";

    // Fehlerbehandlung

    if($fehler=="0"){echo "<h3>eMail gesendet</h3>\nDie eMail wurde erfolgreich gesendet.<br>\n<br>\n<a href=\"index.php?modus=DAT&inc=UEB\">zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=DAT&inc=MAI\">...noch eine eMail senden</a><br>\n";}

    else{echo "<h3 align=\"left\">Fehler!</h3>\nDie eMail konnte nicht oder nur teilweise gesendet werden (siehe Liste!).<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}

	}

//*****************************************************************************





//######################################################################################

// /Step 2: Senden

?>



<br><br>



</td>

</tr>



</table>



<!-- Content Mail schreiben -->