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
	echo "<h3>&Uuml;bersicht aller Artikel</h3><br>\n";

?>
<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3" width="100%">
<tr><td align="left" valign="top" width="20%"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Anlegen
	echo "<a href=\"index.php?modus=SHO&inc=AAN\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
	?>	
</td></tr>
<tr><td colspan="2">
	<?php
	// Aufruf Uebersicht
	// Daten der Gruppe aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT a.ID, a.Name, a.Preis, a.Online as ArtikelOn, g.Name as Gruppe, g.Online as GruppeOn FROM "._ShopArtikel." a, "._ShopGruppen." g WHERE a.Gruppe=g.ID ORDER BY g.Name, a.Name";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		$alphaAkt = "0";
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($alphaAkt!=$zeile["Gruppe"])
				{
				// On/Off Gruppe bauen
                if($zeile["GruppeOn"]){$onOffString="";}else{$onOffString=" (offline)";}
				// Fieldset mit Gruppen bauen
				if($alphaAkt!="0"){echo"</table>\n</fieldset>\n\n";}
				echo "<br><fieldset>\n<legend style=\"font-size:16px;\">".$zeile["Gruppe"]."<span class=\"textRot\" style=\"font-size:10px;\"><b>".$onOffString."</b></span></legend>\n<table border=\"0\" cellpadding=\"3\" cellspacing=\"0\" width=\"100%\">\n";
				$alphaAkt = $zeile["Gruppe"];
				}
            // On/Off Artikel bauen
            if($zeile["ArtikelOn"]){$onOffString="";}else{$onOffString="offline";}
			// Ausgabe
			echo "<tr>
			<td width=\"50%\"><nobr><li style=\"color:".$modusArrayADMIN[$_GET["modus"]]["Wert"].";\"><a href=\"index.php?modus=SHO&inc=AUE&id=".$zeile["ID"]."\" style=\"color:#000000;\">".$zeile["Name"]."</a></td><td align=\"right\">".number_format($zeile["Preis"],2,',','')." &euro;</td><td width=\"20%\"><span class=\"textRot\"><b>".$onOffString."</b></span></td>
			</tr>\n";
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Artikel-Uebersicht ausgelesen werden!<br>\n";}
	
	echo "</table>\n</fieldset>\n\n</p>\n";
	?>
</td></tr>
<tr><td align="left" valign="top" width="20%"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Anlegen
	echo "<a href=\"index.php?modus=SHO&inc=AAN\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
	?>	
</td></tr>
</table>
</fieldset>
</p>
	<?php
	}
//###############################################################################
// /Uebersicht

// Details
//###############################################################################
else
	{	
	// Daten des Artikels aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT a.ID, a.Name, a.Beschreibung, a.Preis, a.Bild, a.Online, a.Erzeugt, a.Geaendert, g.Name as GruppenName FROM "._ShopArtikel." a, "._ShopGruppen." g WHERE a.ID='".$id."' AND a.Gruppe=g.ID LIMIT 1";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die ArtikelDetails ausgelesen werden!<br>\n";}
	?>

<!-- Content Artikel Details -->

<table border="0" cellpadding="0" cellspacing="0" width="480">

<tr><td align="left" valign="top">

<!-- Innere Tabelle -->

<table border="0" cellpadding="3" cellspacing="3" width="500">

<tr><td><h3 align="left">
	<?php
	// Ueberschrift
	echo $zeile["Name"];
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
	echo "<a href=\"index.php?modus=SHO&inc=AAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=SHO&inc=ALO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";
	?>
<a href="index.php?modus=SHO&inc=AUE">Zur&uuml;ck zur &Uuml;bersicht</a>
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

<tr><td align="left" valign="top"><b>Artikelgruppe:<br></b></td><td align="left" valign="top">
	<?php
	// Artikelgruppe
	echo $zeile["GruppenName"];
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Name:<br></b></td><td align="left" valign="top">
	<?php
	// Name
	echo $zeile["Name"];
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Beschreibung:<br></b></td><td align="left" valign="top">
	<?php
	// Beschreibung
	echo nl2br($zeile["Beschreibung"]);
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Preis:<br></b></td><td align="left" valign="top">
	<?php
	// Preis
	echo number_format($zeile["Preis"],2,',','')." &euro";
	?>
</td></tr>

<tr><td align="left" valign="top"><b>Foto:<br></b></td><td align="left" valign="top">
	<?php
	// Bild
	if($zeile["Bild"]){echo "<img src=\"..".$ShopBildPfad."/".$zeile["Bild"]."\" width=\"150px\" alt=\"".$zeile["Name"]."\" border=\"0\">";}
    else{echo "Bitte Bild einf&uuml;gen";}
	?>
</td></tr>

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
	echo "<a href=\"index.php?modus=SHO&inc=AAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=SHO&inc=ALO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";
	?>
<a href="index.php?modus=SHO&inc=AUE">Zur&uuml;ck zur &Uuml;bersicht</a>
</td></tr>

</table>
</fieldset>
<!-- /AKTIONEN ################################################################### -->

</td></tr>

</table>

<!-- /Innere Tabelle -->

</td></tr>

</table>

<!-- Content Gruppen Details -->

	<?php
	}
//###############################################################################
// /Details
?>