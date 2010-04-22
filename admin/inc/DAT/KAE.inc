<?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// POST extrahieren
extract($_POST);

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}

// Daten fur Klasse aus DB holen
// SQL-String bauen
$sqlString = "SELECT * FROM "._KrakeKlassen." WHERE ID='".$id."'";
// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$klasse = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
?>

<!-- Content Klasse andern -->
<table border="0" cellpadding="0" cellspacing="0" width="480">
<tr> <td align="left" valign="top">

<?php 
// Step 0: Eingabe 
//#####################################################################################
if($step==0)
	{
	?>

<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" multiple=" multiple" method="post">

<h3>Klasse &auml;ndern</h3>

<!-- Innere Tabelle Eingabe -->

<p>
<fieldset><legend>Eigenschaften</legend>
<table border="0" cellpadding="3" cellspacing="3">
<tr><td align="left" valign="top"><b>Titel:<br></b></td><td align="left" valign="top"> 
<input type="text" name="titel" size="32" maxlength="64" value="<?php echo stripslashes($klasse["Titel"]); ?>">
</td></tr>
<tr><td align="left" valign="top"><b>Beschreibung:<br></b></td><td align="left" valign="top">
<textarea name="beschreibung" cols="44" rows="5"><?php echo stripslashes(nl2br($klasse["Beschreibung")); ?></textarea>
</td></tr>
</table>
</fieldset>
</p>

<p>
<fieldset><legend>Klassen-Kontakte</legend>
<p align="center">
<a href="#A">A</a>&nbsp;
<a href="#B">B</a>&nbsp;
<a href="#C">C</a>&nbsp;
<a href="#D">D</a>&nbsp;
<a href="#E">E</a>&nbsp;
<a href="#F">F</a>&nbsp;
<a href="#G">G</a>&nbsp;
<a href="#H">H</a>&nbsp;
<a href="#I">I</a>&nbsp;
<a href="#J">J</a>&nbsp;
<a href="#K">K</a>&nbsp;
<a href="#L">L</a>&nbsp;
<a href="#M">M</a>&nbsp;
<a href="#N">N</a>&nbsp;
<a href="#O">O</a>&nbsp;
<a href="#P">P</a>&nbsp;
<a href="#Q">Q</a>&nbsp;
<a href="#R">R</a>&nbsp;
<a href="#S">S</a>&nbsp;
<a href="#T">T</a>&nbsp;
<a href="#U">U</a>&nbsp;
<a href="#V">V</a>&nbsp;
<a href="#W">W</a>&nbsp;
<a href="#X">X</a>&nbsp;
<a href="#Y">Y</a>&nbsp;
<a href="#Z">Z</a>&nbsp;
</p>

<p>
<?php
// Daten fur Kontakt aus DB holen
// SQL-String bauen
$sqlString = "SELECT ID, Anrede, Vorname, Nachname, MailBuero, MailPrivat, Firma, Klassen FROM "._KrakeDatenpool." ORDER BY Nachname, Firma";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis)
	{
	$alphaAkt = "0";
	while($kontakt = mysql_fetch_array($ergebnis))
		{
        // Initialie extrahieren
        $initial = strtoupper(substr($kontakt["Nachname"],0,1));
        if($alphaAkt!=$initial)
            {
            // Fieldset mit Initialie bauen
            if($alphaAkt!="0"){echo"</table>\n</fieldset>\n\n";}
            echo "<fieldset>\n<legend style=\"font-size:20px;\"><a name=\"".$initial."\">".$initial."</a></legend>\n<table border=\"0\" cellpadding=\"3\" cellspacing=\"0\">\n";
            $alphaAkt = $initial;
            }
        // Testen ob Mail voranden
        if(!$kontakt["MailBuero"] AND !$kontakt["MailPrivat"]){$mail = " <i>(keine E-Mail-Adresse)</i>";}
        else{$mail = "";}
		// Testen, ob Klasse ausgewaehlt
		echo "<tr><td>";
		$findmich = "[".$klasse["Titel"]."]";
		$pos = strpos($kontakt["Klassen"], $findmich);
		if($pos !== false){$checked=" checked"; $alt="1";}else{$checked=""; $alt="0";}
		// Testen ob Person oder Firma
		if($kontakt["Vorname"]=="" AND $kontakt["Nachname"]=="")
            {$ausgabe = $kontakt["Firma"];}
        else
            {$ausgabe = $kontakt["Anrede"]." ".$kontakt["Vorname"]." ".$kontakt["Nachname"];}
		echo "<input type=\"checkbox\" name=\"kontakt".$kontakt["ID"]."\" value=\"1\"".$checked."><a href=\"index.php?modus=DAT&inc=KON&id=".$kontakt["ID"]."\" target=\"_blank\">".$ausgabe."</a>".$mail."\n<input type=\"hidden\" name=\"altKontakt".$kontakt["ID"]."\" value=\"".$alt."\"".$checked."></td></tr>";
		// Checked und Alt unchecken
		$checked="";
		$alt="";
		// HAchste ID ermitteln
		if($kontakt["ID"]>$maxKonId){$maxKonId=$kontakt["ID"];}
		}
	mysql_free_result($ergebnis);
	}
else
	{
	echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";
	}
?>
</table>
</fieldset>
</p>

</fieldset>
</p>

<p align="center"><input type="submit" value="Klasse &auml;ndern"></p>

<!-- /Innere Tabelle Eingabe -->
<input type="hidden" name="maxKonId" value="<?php echo $maxKonId; ?>">
<input type="hidden" name="id" value="<?php echo $id; ?>">
<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">
</form>

	<?php
	}
//####################################################################################
// Step 0: Eingabe

// Step 1: Pruefen und speichern
//####################################################################################
if($step==1)
	{
	// Fehlerbehandlung
	$fehlerStr = "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
	// Feldtest
	if($titel=="")
		{$fehler=1; $fehlerStr = $fehlerStr."<li>Es wurde kein Titel angegeben.\n";}
	else
		{
		$sqlString = "SELECT ID FROM "._KrakeKlassen." WHERE Titel='".$titel."'";
		$ergebnis = $db -> sql($sqlString);
		if($ergebnis)
			{
			$test=mysql_fetch_array($ergebnis);
			if(mysql_num_rows($ergebnis)!="0" AND $test["ID"]!=$id)
				{
				$fehler=1; $fehlerStr = $fehlerStr."<li>Der Titel ist schon vergeben.\n";
				}
			}
			else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
		}
	$fehlerStr = $fehlerStr."</ul>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";
	// Fehlerausgabe
	if($fehler!="")
		{
		echo $fehlerStr;
		}

// Speichern
//###################################################################################
	else
		{
		// KlassenKontakte aendern
		
		// TEST AUGABE ##############################################################
		//echo "MaxKonId: ".$maxKonId."<br>\n";
		
		$maxKonId = $maxKonId+1;
		for($c=0;$c<$maxKonId;$c++)
            {
            // Variablen bauen
            $kontakt = "kontakt".$c;
            $altKontakt = "altKontakt".$c;
            
            // TEST AUSGABE ######################################################
            //echo "Kontakt".$c.": ".$$kontakt."<br>\n";
            //echo "AltKontakt".$c.": ".$$altKontakt."<br>\n";
            
            // Neuer Kontakt der Klasse zugeordnen
            if($$kontakt=="1" AND $$altKontakt=="0")
                {
                
                // TEST AUSGABE ######################################################
                //echo "Kontakt Nr. ".$c." zu Klasse HINZUFUEGEN<br>\n";
                
                // Alten KlassenString aus DB holen
                // SQL-String bauen
                $sqlString = "SELECT ID, Klassen FROM "._KrakeDatenpool." WHERE ID='".$c."'";
                // DB abfragen
                $ergebnis = $db -> sql($sqlString);
                // Ergebnis auslesen
                if($ergebnis)
                    {
                    $zeile = mysql_fetch_array($ergebnis);
                    // Neue Klasse in KlassenString einfuegen
                    $klassen = $zeile["Klassen"].chr(10)."[".$titel."]";
                    // Neuer Klassenstring in DB einfuegen
                    // SQL-String bauen
                    $sqlString = "UPDATE "._KrakeDatenpool." SET Klassen='".$klassen."' WHERE ID='".$zeile["ID"]."'";
                    // Neuen Eintrag in DB speichern
                    $ergebnis = $db -> sql($sqlString);
                    // Fehlerbehandlung
                    if(!$ergebnis){echo "<h3 align=\"left\">Fehler!</h3>\nDie Klasse konnte nicht in der Datenbank ge&auml;ndert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
                    }
                // Fehlerbehandlung
                else{echo "<h3 align=\"left\">Fehler!</h3>\nDie Klasse konnte nicht in der Datenbank ge&auml;ndert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
                }
            // Alter Kontakt aus Klasse entfernen
            if($$kontakt=="" AND $$altKontakt=="1")
                {
                
                // TEST AUSGABE ######################################################
                echo "Kontakt Nr. ".$c." aus Klasse ENTFERNEN<br>\n";
                
                // Alten KlassenString aus DB holen
                // SQL-String bauen
                $sqlString = "SELECT ID, Klassen FROM "._KrakeDatenpool." WHERE ID='".$c."'";
                // DB abfragen
                $ergebnis = $db -> sql($sqlString);
                // Ergebnis auslesen
                if($ergebnis)
                    {
                    $zeile = mysql_fetch_array($ergebnis);
                    // Alte Klasse aus KlassenString entfernen
                    $klassenArray = explode(chr(10), $zeile["Klassen"]);
                    for($c0=0;$c0<count($klassenArray);$c0++)
                        {
                        echo "|".$klassenArray[$c0]."|<br>";
                        if($klassenArray[$c0]!="[".$titel."]")
                            {$klassenArrayNeu[] = trim($klassenArray[$c0]);}
                        else
                            {echo "Raus!<br>";}
                        }
                    $klassen = implode(chr(10), $klassenArrayNeu);
                    // Neuer Klassenstring in DB einfuegen
                    // SQL-String bauen
                    $sqlString = "UPDATE "._KrakeDatenpool." SET Klassen='".$klassen."' WHERE ID='".$zeile["ID"]."'";
                    // Neuen Eintrag in DB speichern
                    $ergebnis = $db -> sql($sqlString);
                    // Fehlerbehandlung
                    if(!$ergebnis){echo "<h3 align=\"left\">Fehler!</h3>\nDie Klasse konnte nicht in der Datenbank ge&auml;ndert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
                    }
                // Fehlerbehandlung
                else{echo "<h3 align=\"left\">Fehler!</h3>\nDie Klasse konnte nicht in der Datenbank ge&auml;ndert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
                }
            }
		
		// SQL-String bauen
		$sqlString = "UPDATE "._KrakeKlassen." SET Titel='".addslashes($titel)."',Beschreibung='".addslashes($beschreibung)."' WHERE ID='".$id."'";
		// Neuen Eintrag in DB speichern
		$ergebnis = $db -> sql($sqlString);
		// Fehlerbehandlung
		if($ergebnis){echo "<h3>Klasse ge&auml;ndert</h3>\nDie Klasse wurde erfolgreich in der Datenbank ge&auml;ndert.<br>\n<br>\n<a href=\"index.php?modus=DAT&inc=KLA\">zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=DAT&inc=KLA&id=".$id."\">...zur ge&auml;nderten Klasse</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDie Klasse konnte nicht in der Datenbank ge&auml;ndert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//###################################################################################
// /Step 1: Prufen und speichern
?>
<br><br>
</td>
</tr>
</table>
<!-- Content Klasse andern -->