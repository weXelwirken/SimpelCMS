<?php
// POST und GET extrahieren

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Ubersicht
//###############################################################################
// Testen ob ID gesetzt
if($_GET["id"]=="")
	{
	// Ueberschrift
	echo "<h3>Alle Nutzer</h3>\n<p>";
	?>
<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3" width="100%">
<tr><td align="left" valign="top" width="15%"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Anlegen
	echo "<a href=\"index.php?modus=NUT&inc=NAN\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
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
	// Aufruf Ubersicht
	// Daten der Kategorie aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBuserauth." ORDER BY Login";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		$alphaAkt = "0";
		while($zeile = mysql_fetch_array($ergebnis))
			{
			// Initialie extrahieren
			$initial = strtoupper(substr($zeile["Login"],0,1));
			if($alphaAkt!=$initial)
				{
				// Fieldset mit Initialie bauen
				if($alphaAkt!="0"){echo"</table>\n</fieldset>\n\n";}
				echo "<fieldset>\n<legend style=\"font-size:20px;\"><a name=\"".$initial."\">".$initial."</a></legend>\n<table border=\"0\" cellpadding=\"3\" cellspacing=\"0\" width=\"100%\">\n";
				$alphaAkt = $initial;
				}
			// Mail bauen				
			if($zeile["Mail"])
                {$mailString="<a href=\"mailto:".$zeile["Mail"]."\" style=\"color:#0000ff;\">".$zeile["Mail"]."</a>";}
			else
				{$mailString="<i>keine E-Mail-Adresse</i>";}
            // Rolle bauen
            if($zeile["Rolle"]){$rollenString=$RollenArray[$zeile["Rolle"]];}else{$rollenString="";}
            // Sperrzeichen bauen
            if($zeile["Gesperrt"]){$sperrString="&bull;";}else{$sperrString="";}
			// Ausgabe
			echo "<tr>
			<td width=\"47%\"><nobr><li style=\"color:".$modusArrayADMIN[$_GET["modus"]]["Wert"].";\"><a href=\"index.php?modus=NUT&inc=NUE&id=".$zeile["ID"]."\" style=\"color:#000000;\">".$zeile["Login"]."</a> <span style=\"color:#666666;\"><i>(".$zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"].")</i></span></nobr></td>
			<td width=\"42%\">".$mailString."</td>
			<td width=\"15%\" align=\"right\"><span class=\"textRot\">".$rollenString."</span><span class=\"textOrange\"><b>".$sperrString."</b></span></td>
			</tr>\n";
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	
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
	echo "<a href=\"index.php?modus=NUT&inc=NAN\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
	?>	
</td></tr>
</table>
</fieldset>
</p>
	<?php
	}
//###############################################################################
// /Ubersicht

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
	$sqlString = "SELECT * FROM "._DBuserauth." ".$where."LIMIT 1";
	?>

<!-- Content Nutzer Details -->

<h3 align="left">
	<?php
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	// Uberschrift
	echo "<nobr>&raquo;".$zeile["Login"]."&laquo; <i>(".$zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"].")</i></nobr>";
	?>
</h3>

<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Aendern
	echo "&nbsp;&nbsp;";
	echo "<a href=\"index.php?modus=NUT&inc=NAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loeschen
	echo "<a href=\"index.php?modus=NUT&inc=NLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Zurueck
	echo "<a href=\"index.php?modus=NUT&inc=NUE\">Zur&uuml;ck zur Nutzer&uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<fieldset><legend><a href="javascript:Show_Stuff('Per')" style="text-decoration:none;">[<span id="PerOff" style="display:none;">+</span><span id="PerOn">-</span>]</a> Pers&ouml;nliche Daten</legend>
<div id="Per">
	<?php
    // Personliche Daten
    $persDaten = "<b>".$zeile["Anrede"]." ";
    $persDaten.= $zeile["Vorname"]." ".$zeile["Nachname"]."</b><br>\n";
    $persDaten.= $zeile["Strasse"]." ".$zeile["Hausnummer"]."<br>\n";
    $persDaten.= $zeile["PLZ"]." ".$zeile["Ort"]."<br>\n";
    $persDaten.= $zeile["Land"]."\n<br>";
    echo $persDaten;
	?>
</div>
</fieldset>

<p>
<fieldset><legend><a href="javascript:Show_Stuff('Kon')" style="text-decoration:none;">[<span id="KonOff">+</span><span id="KonOn" style="display:none;">-</span>]</a> weitere Kontaktdaten</legend>
<div id="Kon" style="display:none;">
	<?php
    // Kontaktdaten
    $konDaten = "<table border=\"0\" cellpadding=\"0\" cellspacing=\"3\">";
    // Telefon
    if($zeile["Telefon"]!=""){$konDaten.= "<tr><td><b>Telefon:</b><br></td><td>".$zeile["Telefon"]."</tr>";}
    // Mobil
    if($zeile["Mobil"]!=""){$konDaten.= "<tr><td><b>Mobil:</b><br></td><td>".$zeile["Mobil"]."<br></td></tr>";}
    // Mail
    if($zeile["Mail"]!=""){$konDaten.= "<tr><td><b>eMail:</b><br></td><td><a href=\"mailto:".$zeile["Mail"]."\" style=\"color:#0000ff;\">".$zeile["Mail"]."</a><br></td></tr>";}
    $konDaten.= "</table>";
    echo $konDaten;
	?>
</div>
</fieldset>
</p>

    <?php
	// Notizen
	if($zeile["Notizen"])
		{
		?>
<p>
<fieldset><legend><a href="javascript:Show_Stuff('Not')" style="text-decoration:none;">[<span id="NotOff">+</span><span id="NotOn" style="display:none;">-</span>]</a> Notizen</legend>
<div id="Not" style="display:none;">
<table border="0" cellpadding="2" cellspacing="3" width="100%">
		<?php	
		// Notizen
		if($zeile["Notizen"]!="")
			{
			?>
<tr><td align="left" valign="top"><b>Notizen:<br></b></td><td align="left" valign="top" bgcolor="#eeeeee" width="100%"><i>
			<?php
			// Notizen
			echo nl2br($zeile["Notizen"]);
			?>
</i></td></tr>
			<?php
			}
		?>
</table>
</div>
</fieldset>
</p>
		<?php
		}
	?>

<p>
<fieldset><legend><a href="javascript:Show_Stuff('Lps')" style="text-decoration:none;">[<span id="LpsOff">+</span><span id="LpsOn" style="display:none;">-</span>]</a> Login, Passwort &amp; Status</legend>
<div id="Lps" style="display:none;">
<table border="0" cellpadding="0" cellspacing="5">

<tr><td align="left" valign="top" width="75"><b>Login:<br></b></td><td align="left" valign="top">
    <?php
    // Login
    echo $zeile["Login"];
    ?>
</td></tr>
<tr><td align="left" valign="top" width="75"><b>Passwort:<br></b></td><td align="left" valign="top">
    <?php
    // Passwort
    echo $zeile["Passwort"];
    ?>
 <i>(MD5-Hash)</i></td></tr>
<tr><td align="left" valign="top" width="75"><b>Gesperrt:<br></b></td><td align="left" valign="top">
    <?php
    // Gesperrt
    if($zeile["Gesperrt"]=="1"){echo "<span class=\"textOrange\"><b>Ja</b><span><br>\n";}
    else{echo "<span class=\"textGruen\"><b>Nein</b><span><br>\n";}
    ?>
</td></tr>
<tr><td align="left" valign="top" width="75"><b>Rolle:<br></b></td><td align="left" valign="top">
    <?php
    // Rolle
    echo $RollenArray[$zeile["Rolle"]];
    ?>
</td></tr>
<tr><td>&nbsp;<br><td><td>&nbsp;<br><td></tr>
<tr><td align="left" valign="top" width="75"><b>Erzeugt:<br>Ge&auml;ndert:<br></b></td><td align="left" valign="top">
	<?php
	// Erzeugt
	echo $zeile["Erzeugt"] . "<br>\n";
	// Geandert
	echo $zeile["Geaendert"];
	?>
<br></td></tr>
</table>
</div>
</fieldset>
</p>

<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Aendern
	echo "&nbsp;&nbsp;";
	echo "<a href=\"index.php?modus=NUT&inc=NAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loeschen
	echo "<a href=\"index.php?modus=NUT&inc=NLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Zurueck
	echo "<a href=\"index.php?modus=NUT&inc=NUE\">Zur&uuml;ck zur Nutzer&uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<!-- Content Nutzer Details -->

	<?php
	}
//###############################################################################
// /Details
?>