<?php
// POST und GET extrahieren
$id = $_GET["id"];

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Uebersicht
//###############################################################################
// Testen ob ID gesetzt und WHERE-Fall bauen
if(!$id)
	{
	// Ueberschrift
	echo "<h3>&Uuml;bersicht aller Ordner</h3><br>\n";
    if($ScmsLang)
        {
        foreach($ScmsLangArray as $key => $item)
           {
           echo "<h4><a href=\"javascript:Show_Stuff('".$item."')\" style=\"text-decoration:none;\">[<span id=\"".$item."Off\">+</span><span id=\"".$item."On\" style=\"display:none;\">-</span>]</a> ".$item."</h4>
               <div id=\"".$item."\" style=\"display:none;\">
               <table>\n";
           OrdBaum($mutter, $mutterAlt, $ebene, $key);
           echo "</table>
               </div><br>\n";
           }
        }
    else
        {
        echo "<table>\n";
           OrdBaum($mutter, $mutterAlt, $ebene, "X");
        echo "</table>\n";
        }
	}
//###############################################################################
// /Uebersicht

// Details
//###############################################################################
else
	{	
	// Daten der Kategorie aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBordner." WHERE ID='".$id."' LIMIT 1";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	?>

<!-- Content Ordner Details -->

<table border="0" cellpadding="0" cellspacing="0" width="480">

<tr><td align="left" valign="top">

<!-- Innere Tabelle -->

<table border="0" cellpadding="3" cellspacing="3" width="500">

<tr><td><h3 align="left">
	<?php
	// Ueberschrift
	echo stripslashes($zeile["Name"]);
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
	echo "<a href=\"index.php?modus=ORD&inc=OAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=ORD&inc=OLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";
	?>
<a href="index.php?modus=ORD&inc=OUE">Zur&uuml;ck zur &Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->
<br>
<!-- EINSTELLUNGEN ################################################################### -->
<fieldset>
<legend><a href="javascript:Show_Stuff('Ein')" style="text-decoration:none;">[<span id="EinOff" style="display:none;">+</span><span id="EinOn">-</span>]</a> Einstellungen</legend>
<div id="Ein">
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

<tr><td align="left" valign="top" width="150"><b>Pfad:<br></b></td><td align="left" valign="top" width="300">
	<?php
	// Pfad
	OrdPfad($id, $ordPfad);
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Name:<br></b></td><td align="left" valign="top">
	<?php
	// Name
	echo stripslashes($zeile["Name"]);
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Mutterordner:<br></b></td><td align="left" valign="top">
	<?php
	// Mutter
	// Daten der Mutter-Ordner aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBordner." WHERE ID='".$zeile["Mutter"]."'";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$mutter = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	if($zeile["Mutter"]=="0"){echo "Wurzel";}else{echo $mutter["Name"];}
	?>
</td></tr>

<tr>
<td align="left" valign="top"><b>Position:<br></b></td><td align="left" valign="top">
	<?php
	// Position
	echo $zeile["Position"];
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
	// Ge&auml;ndert
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
	echo "<a href=\"index.php?modus=ORD&inc=OAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=ORD&inc=OLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";
	?>
<a href="index.php?modus=ORD&inc=OUE">Zur&uuml;ck zur &Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->

</td></tr>

</table>

<!-- /Innere Tabelle -->

</td></tr>

</table>

<!-- Content Ordner Details -->

	<?php
	}
//###############################################################################
// /Details
?>