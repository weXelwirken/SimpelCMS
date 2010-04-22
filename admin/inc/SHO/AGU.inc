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
	echo "<h3>&Uuml;bersicht aller Artikelgruppen</h3><br>\n";

?>
<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3" width="100%">
<tr><td align="left" valign="top" width="15%"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Anlegen
	echo "<a href=\"index.php?modus=SHO&inc=AGN\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
	?>	
</td></tr>
<tr><td colspan="2">
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
</td></tr>
</table>
</fieldset>
</p>
	<?php
	// Aufruf Uebersicht
	// Daten der Gruppe aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._ShopGruppen." ORDER BY Name";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		$alphaAkt = "0";
		while($zeile = mysql_fetch_array($ergebnis))
			{
			// Initialie extrahieren
			$initial = strtoupper(substr($zeile["Name"],0,1));
			if($alphaAkt!=$initial)
				{
				// Fieldset mit Initialie bauen
				if($alphaAkt!="0"){echo"</table>\n</fieldset>\n\n";}
				echo "<fieldset>\n<legend style=\"font-size:20px;\"><a name=\"".$initial."\">".$initial."</a></legend>\n<table border=\"0\" cellpadding=\"3\" cellspacing=\"0\" width=\"100%\">\n";
				$alphaAkt = $initial;
				}
            // On/Off bauen
            if($zeile["Online"]){$onOffString="";}else{$onOffString="offline";}
			// Ausgabe
			echo "<tr>
			<td width=\"47%\"><nobr><li style=\"color:".$modusArrayADMIN[$_GET["modus"]]["Wert"].";\"><a href=\"index.php?modus=SHO&inc=AGU&id=".$zeile["ID"]."\" style=\"color:#000000;\">".$zeile["Name"]."</a></td><td><span class=\"textRot\"><b>".$onOffString."</b></span></td>
			</tr>\n";
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Artikelgruppen-Uebersicht ausgelesen werden!<br>\n";}
	
	echo "</table>\n</fieldset>\n\n</p>\n";
	?>
<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3" width="100%">
<tr><td colspan="2">
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
</td></tr>
<tr><td align="left" valign="top" width="15%"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Anlegen
	echo "<a href=\"index.php?modus=SHO&inc=AGN\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
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
	// Daten der Gruppen aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._ShopGruppen." WHERE ID='".$id."' LIMIT 1";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die GruppenDetails ausgelesen werden!<br>\n";}
	?>

<!-- Content Gruppen Details -->

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
	echo "<a href=\"index.php?modus=SHO&inc=AGA&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=SHO&inc=AGL&id=".$zeile["ID"]."&name=".$zeile["Name"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";
	?>
<a href="index.php?modus=SHO&inc=AGU">Zur&uuml;ck zur &Uuml;bersicht</a>
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
	echo "<a href=\"index.php?modus=SHO&inc=AGA&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=SHO&inc=AGL&id=".$zeile["ID"]."&name=".$zeile["Name"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";
	?>
<a href="index.php?modus=SHO&inc=AGU">Zur&uuml;ck zur &Uuml;bersicht</a>
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