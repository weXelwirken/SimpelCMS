<?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// DB-Verbindung Dokument
$dbDokument = new db($dbHost,$dbUser,$dbPasswort);
$dbDokument -> select_db($dbDatenbank);

// Uebersicht
//###############################################################################
// Testen ob ID gesetzt und WHERE-Fall bauen
if($id=="")
	{
	// Ueberschrift
	echo "<h3>&Uuml;bersicht aller Dokumente</h3><br>\n";

	// Aufruf DokOrdBaum
	if($ScmsLang)
        {
        foreach($ScmsLangArray as $key => $item)
           {
           echo "<h4><a href=\"javascript:Show_Stuff('".$item."')\" style=\"text-decoration:none;\">[<span id=\"".$item."Off\">+</span><span id=\"".$item."On\" style=\"display:none;\">-</span>]</a> ".$item."</h4>
               <div id=\"".$item."\" style=\"display:none;\">
               <table>\n";
           AdminDokOrdBaum($mutter, $mutterAlt, $ebene, $check, $key);
           echo "</table>
               </div><br>\n";
           }
        }
    else
        {
        echo "<table>\n";
           AdminDokOrdBaum($mutter, $mutterAlt, $ebene, $check, "X");
        echo "</table>\n";
        }
	}
//###############################################################################
// /Ubersicht

// Details
//###############################################################################
else
	{
	$where = "WHERE ID='".$id."' ";
	
	// Daten des Ordners aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBdokumente." ".$where."LIMIT 1";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	?>

<!-- Content Dokument Details -->

<table border="0" cellpadding="0" cellspacing="0" width="500">

<tr><td align="left" valign="top">

<!-- Innere Tabelle -->

<table border="0" cellpadding="3" cellspacing="3">

<tr><td><h3 align="left">
	<?php
	// Uberschrift
	echo $zeile["Titel"];
	?>
</h3></td></tr>

<tr><td>

<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">
    <?php
	// Aktionen
	// Andern
	echo "<a href=\"index.php?modus=DOK&inc=DAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=DOK&inc=DLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";
	?>
<a href="index.php?modus=DOK&inc=DUE">Zur&uuml;ck zur &Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->
<br>
<!-- ALLGEMEIN ################################################################### -->
<fieldset>
<legend><a href="javascript:Show_Stuff('All')" style="text-decoration:none;">[<span id="AllOff" style="display:none;">+</span><span id="AllOn">-</span>]</a> Allgemein</legend>
<div id="All">
<table border="0" cellpadding="3" cellspacing="3" width="450">

    <?php
    if($ScmsLang)
        {
        ?>
<tr><td align="left" valign="middle"><b>Sprache:<br></b></td><td align="left" valign="top">
        <?php
        // Sprache
        echo $ScmsLangArray[$zeile["Lang"]];
        ?>
</td></tr>
        <?php
        }
    ?>

<tr><td align="left" valign="middle" width="75"><b>Ordner:<br></b></td><td align="left" valign="top">
	<?php
	// Ordner
	OrdPfad($zeile["Ordner"], $ordPfad);
	?>
</td></tr>

<tr><td align="left" valign="middle"><b>Titel:<br></b></td><td align="left" valign="top">
	<?php
	// Titel
	echo stripslashes($zeile["Titel"]);
	?>
</td></tr>

<tr><td align="left" valign="middle"><b>Linktext:<br></b></td><td align="left" valign="top">
	<?php
	// Linktext
	echo stripslashes($zeile["Linktext"]);
	?>
</td></tr>

<?php
if($ScmsVerweise)
{
?>
<tr><td align="left" valign="top" width="75"><b>Kurztext:<br></b></td><td align="left" valign="top">
	<?php
	// Kurztext
	echo stripslashes($zeile["Kurztext"]);
	?>
</td></tr>
<?php
}
?>

<tr><td align="left" valign="top" width="75"><b><nobr>Link zum Dokument:</nobr><br></b></td><td align="left" valign="top" class="anzeigeBox">
	<?php
	// Link zum Dokument
	echo "index.php?id=".$zeile["ID"]."&amp;amp;ord=".$zeile["Ordner"]."\n";
	?>
</td></tr>

</table>
</div>
</fieldset>
<!-- /ALLGEMEIN ################################################################### -->
<br>
<!-- DETAILS ################################################################### -->
<fieldset>
<legend><a href="javascript:Show_Stuff('Det')" style="text-decoration:none;">[<span id="DetOff">+</span><span id="DetOn" style="display:none;">-</span>]</a> Details</legend>
<div id="Det" style="display:none;">
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Dokumententyp:<br></b></td><td align="left" valign="top">
	<?php
	// Dokumententyp
	echo $zeile["Typ"];
	?>
</td></tr>
    
    <?php
    // Check, ob intern
    if($zeile["Typ"]=="intern")
        {
        ?>
<tr><td align="left" valign="top"><b>Inhalt:<br></b></td><td align="left" valign="top" class="anzeigeBox">
        <?php
        // Inhalt
        echo stripslashes($zeile["Inhalt"]);
        ?>
</td></tr>
        <?php
        }
        
    // Check, ob extern
    if($zeile["Typ"]=="extern")
        {
        ?>
<tr><td align="left" valign="top"><b>Quelle:<br></b></td><td align="left" valign="top">
        <?php
        // Quelle
        echo $zeile["Quelle"];
        ?>
</td></tr>
        <?php
        }
    ?>

</table>
</div>
</fieldset>
<!-- /DETAILS ################################################################### -->
<br>
<!-- EINSTELLUNGEN ################################################################### -->
<fieldset>
<legend><a href="javascript:Show_Stuff('Ein')" style="text-decoration:none;">[<span id="EinOff">+</span><span id="EinOn" style="display:none;">-</span>]</a> Einstellungen</legend>
<div id="Ein" style="display:none;">
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="200"><b>Position:<br></b></td><td align="left" valign="top">
	<?php
	// Position
	echo $zeile["Position"];
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Anzeige des Titels:<br></b></td><td align="left" valign="top">
	<?php
	// AnzeigeTitel
	if($zeile["AnzeigeTitel"]==1){echo "<span class=\"textGruen\"><b>Ja</b></span>";}else{echo "<span class=\"textRot\"><b>Nein</b></span>";}
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Anzeige des Linktext:<br></b></td><td align="left" valign="top">
	<?php
	// AnzeigeLinktext
	if($zeile["AnzeigeLinktext"]==1){echo "<span class=\"textGruen\"><b>Ja</b></span>";}else{echo "<span class=\"textRot\"><b>Nein</b></span>";}
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Anzeige des Kurztext:<br></b></td><td align="left" valign="top">
	<?php
	// AnzeigeKurztext
	if($zeile["AnzeigeKurztext"]==1){echo "<span class=\"textGruen\"><b>Ja</b></span>";}else{echo "<span class=\"textRot\"><b>Nein</b></span>";}
	?>
</td></tr>

    <?php
    // $ScmsAuth on?
    if($ScmsAuth)
        {
        ?>
<tr><td align="left" valign="top"><b>Sichbarkeit &amp; Zugriff:<br></b></td><td align="left" valign="top">
        <?php
        // Auth
        if($zeile["Auth"]=="-1"){echo "<span class=\"textOrange\"><b>Nur unangemeldete Nutzer</b></span>";}
        if($zeile["Auth"]=="0"){echo "<span class=\"textGruen\"><b>Keine Beschr&auml;nkungen</b></span>";}
        if($zeile["Auth"]=="1"){echo "<span class=\"textRot\"><b>Nur angemeldete Nutzer</b></span>";}
        ?>
</td></tr>
        <?php
        }
    ?>

</table>
<?php
if($ScmsVerweise)
{
?>
	<table border="0" cellpadding="3" cellspacing="3" width="450">
	
	<tr><td align="left" valign="middle" colspan="2"><br></td></tr>
	
		<?php
		// Verweise auslesen
		for($c=1;$c<6;$c++)
			{        
			$verweisNr="Verweis".$c;
			// Daten der Kategorie aus DB holen
			// SQL-String bauen
			$sqlString = "SELECT Titel FROM "._DBdokumente." WHERE ID='".$zeile[$verweisNr]."'";
			// Ergebnis auslesen
			$ergebnis = $db -> sql($sqlString);
			if($ergebnis){$verweis = mysql_fetch_array($ergebnis);}
			else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
			?>
	
	<tr>
	<td align="left" valign="top" width="75"><b><nobr>Verweis <?php echo $c; ?>:</nobr><br></b></td><td align="left" valign="top">
			<?php
			// Verweis
			if($zeile[$verweisNr]!="0"){echo $verweis["Titel"]."<br>\n";}
			else{echo "---Kein Verweis---<br>\n";}
			?>
	</td></tr>
	
		<?php
			}
		?>
	
	</table>
<?php
}
?>
</div>
</fieldset>
<!-- /EINSTELLUNGEN ################################################################### -->
<br>
<!-- STATUS ################################################################### -->
<fieldset>
<legend><a href="javascript:Show_Stuff('Sta')" style="text-decoration:none;">[<span id="StaOff">+</span><span id="StaOn" style="display:none;">-</span>]</a> Status</legend>
<div id="Sta" style="display:none;">
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Online:<br></b></td><td align="left" valign="top">
	<?php
	// Online
	if($zeile["Online"]==1){echo "<span class=\"textGruen\"><b>Ja</b></span>";}else{echo "<span class=\"textRot\"><b>Nein</b></span>";}
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Erzeugt:<br>Ge&auml;ndert:<br></b></td><td align="left" valign="top">
	<?php
	// Erzeugt
	echo $zeile["Erzeugt"] . "<br>\n";
	// Geandert
	echo $zeile["Geaendert"];
	?>
</td></tr>

</table>
</div>
</fieldset>
<!-- /STATUS ################################################################### -->
<br>
<!-- AKTIONEN ################################################################### -->
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="450">

<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">
    <?php
	// Aktionen
	// Andern
	echo "<a href=\"index.php?modus=DOK&inc=DAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loeschen
	echo "<a href=\"index.php?modus=DOK&inc=DLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";
	?>
<a href="index.php?modus=DOK&inc=DUE">Zur&uuml;ck zur &Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->

</td></tr>

</table>

<!-- /Innere Tabelle -->

</td></tr>

</table>

<!-- Content Dokument Details -->

	<?php
	}
//###############################################################################
// /Details
?>