<?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Uebersicht
//###############################################################################
// Testen ob ID gesetzt und WHERE-Fall bauen
if($_GET["id"]=="")
	{
	// Aberschrift
	echo "<h3>Alle Klassen</h3>\n<p>";
	?>
<p>
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="100%">
<tr><td align="left" valign="top" width="15%"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Anlegen
	echo "<a href=\"index.php?modus=DAT&inc=KAN\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
	?>	
</td></tr>
</table>
</fieldset>
</p>
	<?php
	// Aufruf Abersicht
	// Daten der Klassen aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._KrakeKlassen." ORDER BY Titel";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			// Anzahl zur Klasse zugeordneter Kontakte berechnen
			// SQL-String bauen
            $sqlStringAnzahl = "SELECT ID FROM "._KrakeDatenpool." WHERE Klassen LIKE '%[".$zeile["Titel"]."]%'";
            // Ergebnis auslesen
            $ergebnisAnzahl = $db -> sql($sqlStringAnzahl);
            if($ergebnisAnzahl){$num = mysql_num_rows($ergebnisAnzahl);}
			
			echo "<p>\n<fieldset>\n<legend style=\"font-size:18px\">".$zeile["Titel"]."<span style=\"font-weight:normal; font-size:14px;\"><i> (".$num." Kontakte)</i></span></legend>\n";
			echo nl2br($zeile["Beschreibung"])."<br>\n";
			echo "<div align=\"right\"><a href=\"index.php?modus=DAT&inc=KLA&id=".$zeile["ID"]."\">Details...</a></div>";
			echo "</fieldset>\n</p>\n";
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	?>
<p>
<fieldset>
<table border="0" cellpadding="3" cellspacing="3" width="100%">
<tr><td align="left" valign="top" width="15%"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Anlegen
	echo "<a href=\"index.php?modus=DAT&inc=KAN\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
	?>	
</td></tr>
</table>
</fieldset>
</p>
	<?php
	}
//###############################################################################
// /Uebersicht

// Details
//###############################################################################
else
	{
	// ID holen
	$id = $_GET["id"];
	
	// WHERE-Fall bauen
	$where = "WHERE ID='".$id."' ";
	
	// Daten der Kategorie aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._KrakeKlassen." ".$where."LIMIT 1";
	?>

<!-- Content Klassen Details -->

<h3 align="left">
	<?php
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	// Aberschrift
	echo "Klasse &raquo;".stripslashes($zeile["Titel"])."&laquo;";
	?>
</h3>

<p>
<fieldset>
<table border="0" cellpadding="3" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Andern
	echo "<a href=\"index.php?modus=DAT&inc=KAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=DAT&inc=KLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Mail
	echo "<a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKla=an&klasse=".$zeile["Titel"]."\"><b><span style=\"color:#0000ff;\">E-Mail an Klasse</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Zuruck
	echo "<a href=\"index.php?modus=DAT&inc=KLA\">Zur &Uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<p>
<fieldset><legend>Klassen-Beschreibung</legend>
	<?php
	// Beschreibung
	echo stripslashes(nl2br($zeile["Beschreibung"]))."<br>\n";
	?>
</fieldset>
</p>

<p>
<fieldset><legend>Klassen-Kontakte</legend>
<table border=\"0\" cellpadding=\"3\" cellspacing=\"0\">
	<?php
	// WHERE-Fall bauen
	$where = "WHERE Klassen LIKE '%[".$zeile["Titel"]."]%'";
	
	// Daten der Kontakte aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._KrakeDatenpool." ".$where." ORDER BY Nachname";

	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		if(mysql_num_rows($ergebnis)==0){echo "<i>(keine Kontakte zugewiesen)</i><br>\n";}
		while($kontakte = mysql_fetch_array($ergebnis))
			{
			// Mail bauen
			if($kontakte["MailBuero"]!="")
				{$mailString="<a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKon=an&kontakt=".$kontakte["MailBuero"]."\" style=\"color:#0000ff;\">".$kontakte["MailBuero"]."</a> <i>(Buro)</i>";}
			else
				{$mailString="<a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKon=an&kontakt=".$kontakte["MailPrivat"]."\" style=\"color:#0000ff;\">".$kontakte["MailPrivat"]."</a> <i>(Privat)</i>";}
			if($kontakte["MailBuero"]=="" AND $kontakte["MailPrivat"]=="")
				{$mailString="<i>keine E-Mail-Adresse</i>";}
			// Ausgabe
			if($kontakte["Vorname"]=="" AND $kontakte["Nachname"]=="")
                {$ausgabe = $kontakte["Firma"];}
            else
                {$ausgabe = $kontakte["Anrede"]." ".$kontakte["Vorname"]." ".$kontakte["Nachname"];}
			echo "<tr>
			<td><li style=\"color:".$modusArrayADMIN[$_GET["modus"]]["Wert"].";\"><a href=\"index.php?modus=DAT&inc=KON&id=".$kontakte["ID"]."\" style=\"color:#000000;\">".$ausgabe."</a></td>
			<td>".$mailString."</td>
			</tr>\n";
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	?>
</table>
</fieldset>
</p>

<p>
<fieldset>
<table border="0" cellpadding="3" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Andern
	echo "<a href=\"index.php?modus=DAT&inc=KAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=DAT&inc=KLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Mail
	echo "<a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKla=an&klasse=".$zeile["ID"]."|".$zeile["Titel"]."\"><b><span style=\"color:#0000ff;\">E-Mail an Klasse</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Zuruck
	echo "<a href=\"index.php?modus=DAT&inc=KLA\">Zur &Uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<!-- Content Klassen Details -->

	<?php
	}
//###############################################################################
// /Details
?>