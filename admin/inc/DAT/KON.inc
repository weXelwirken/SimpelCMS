<?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Ubersicht
//###############################################################################
// Testen ob ID gesetzt und WHERE-Fall bauen
if($_GET["id"]=="")
	{
	// Uberschrift
	echo "<h3>Alle Kontakte</h3>\n<p>";
	?>
<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3" width="100%">
<tr><td align="left" valign="top" width="15%"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Anlegen
	echo "<a href=\"index.php?modus=DAT&inc=ANL\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
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
	$sqlString = "SELECT ID, Anrede, Vorname, Nachname, Firma, MailBuero, MailPrivat FROM "._KrakeDatenpool." WHERE Nachname!='' ORDER BY Nachname,Firma";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		$alphaAkt = "0";
		
		// Kontakte in DB?
		if(mysql_num_rows($ergebnis)=="0")
            {
            echo "Es sind keine Kontakte in der Datenbank vorhanden.";
            }
        else
            {
            while($zeile = mysql_fetch_array($ergebnis))
                {
                // Initialie extrahieren
                $initial = strtoupper(substr($zeile["Nachname"],0,1));
                if($alphaAkt!=$initial)
                    {
                    // Fieldset mit Initialie bauen
                    if($alphaAkt!="0"){echo"</table>\n</fieldset>\n\n";}
                    echo "<fieldset>\n<legend style=\"font-size:20px;\"><a name=\"".$initial."\">".$initial."</a></legend>\n<table border=\"0\" cellpadding=\"3\" cellspacing=\"0\">\n";
                    $alphaAkt = $initial;
                    }
                // Mail bauen
                if($zeile["MailBuero"]!="")
                    {$mailString="<a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKon=an&kontakt=".$zeile["MailBuero"]."\" style=\"color:#0000ff;\">".$zeile["MailBuero"]."</a> <i class=\"kleiner\">(gesch&auml;ftlich)</i>";}
                else
                    {$mailString="<a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKon=an&kontakt=".$zeile["MailPrivat"]."\" style=\"color:#0000ff;\">".$zeile["MailPrivat"]."</a> <i class=\"kleiner\">(privat)</i>";}
                if($zeile["MailBuero"]=="" AND $zeile["MailPrivat"]=="")
                    {$mailString="<i>keine E-Mail-Adresse</i>";}
                // Ausgabe
                if($zeile["Vorname"]=="" AND $zeile["Nachname"]=="")
                    {$ausgabe = $zeile["Firma"];}
                else
                    {$ausgabe = $zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"];}
                echo "<tr>
                <td width=\"\"><nobr><li style=\"color:".$modusArrayADMIN[$_GET["modus"]]["Wert"].";\"><a href=\"index.php?modus=DAT&inc=KON&id=".$zeile["ID"]."\" style=\"color:#000000;\">".$ausgabe."</a></nobr></td>
                <td width=\"\">".$mailString."</td>
                </tr>\n";
                }
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
	echo "<a href=\"index.php?modus=DAT&inc=ANL\"><b><span class=\"textGruen\">Neu anlegen</span></b></a>";
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
	$sqlString = "SELECT * FROM "._KrakeDatenpool." ".$where."LIMIT 1";
	?>

<!-- Content Kontakt Details -->

<h3 align="left">
	<?php
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	// Uberschrift
	if($zeile["Vorname"]=="" AND $zeile["Nachname"]=="")
        {$ausgabe = $zeile["Firma"];}
    else
        {$ausgabe = $zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"];}
	echo "Kontakt <nobr>&raquo;".$ausgabe."&laquo;</nobr>";
	?>
</h3>

<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Andern
	echo "&nbsp;&nbsp;&nbsp;";
	echo "<a href=\"index.php?modus=DAT&inc=AEN&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=DAT&inc=LOE&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Zuruck
	echo "<a href=\"index.php?modus=DAT&inc=KON\">Zur&uuml;ck zur Kontakt&uuml;bersicht</a>";
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
    if($zeile["Titel"]){$persDaten.= $zeile["Titel"]." ";}
    $persDaten.= $zeile["Vorname"]." ".$zeile["Nachname"]."</b>";
    if($zeile["Spitzname"]){$persDaten.= " <i>\"".$zeile["Spitzname"]."\"</i>";}
    $persDaten.= "<br>\n";
    if($zeile["Firma"])
        {
        $persDaten.= $zeile["Firma"];
        if($zeile["Position"]){$persDaten.= " (".$zeile["Position"].")";}
        $persDaten.= "<br>\n";
        }
    $persDaten.= "<br>\n";
    $persDaten.= "<table>\n";
    if($zeile["BueroStrasse"] OR $zeile["BueroPLZ"] OR $zeile["BueroOrt"])
        {
        $persDaten.= "<tr><td><i>gesch&auml;ftlich:</i></td><td>".$zeile["BueroStrasse"].", ";
        $persDaten.= $zeile["BueroPLZ"]." ".$zeile["BueroOrt"];
        if($zeile["BueroBundesland"]){$persDaten.= " (".$zeile["BueroBundesland"].")";}
        $persDaten.= ", ".$zeile["BueroLand"]."</td></tr>\n";
        }
    if($zeile["PrivatStrasse"] OR $zeile["PrivatPLZ"] OR $zeile["PrivatOrt"])
        {
        $persDaten.= "<tr><td><i>privat:</i></td><td>".$zeile["PrivatStrasse"].", ";
        $persDaten.= $zeile["PrivatPLZ"]." ".$zeile["PrivatOrt"];
        if($zeile["PrivatBundesland"]){$persDaten.= " (".$zeile["PrivatBundesland"].")";}
        $persDaten.= ", ".$zeile["PrivatLand"]."</td></tr>\n";
        }
    $persDaten.= "</table>\n";
    echo $persDaten;
	?>
</div>
</fieldset>
</p>

<p>
<fieldset><legend><a href="javascript:Show_Stuff('Kon')" style="text-decoration:none;">[<span id="KonOff">+</span><span id="KonOn" style="display:none;">-</span>]</a> weitere Kontaktdaten</legend>
<div id="Kon" style="display:none;">
	<?php
    // Kontaktdaten
    $konDaten = "<table border=\"0\" cellpadding=\"0\" cellspacing=\"3\">";
    // Telefon
    if($zeile["TeleBuero"]!="" OR $zeile["TelePrivat"]!="")
        {
        if($zeile["TeleBuero"]!=""){$telebuero = "<td>".$zeile["TeleBuero"]." <i>(gesch&auml;ftlich)</i><br></td>";}
        if($zeile["TelePrivat"]!=""){$teleprivat = "<td>".$zeile["TelePrivat"]." <i>(privat)</i><br></td>";}
        $konDaten.= "<tr><td><b>Telefon:</b><br></td>".$telebuero.$teleprivat."</tr>";
        }
    // Fax
    if($zeile["TeleFax"]!=""){$konDaten.= "<tr><td><b>Fax:</b><br></td><td>".$zeile["TeleFax"]."<br></td></tr>";}
    // Mobil
    if($zeile["TeleMobil"]!=""){$konDaten.= "<tr><td><b>Mobil:</b><br></td><td>".$zeile["TeleMobil"]."<br></td></tr>";}
    // Mail
    if($zeile["MailBuero"]!="" OR $zeile["MailPrivat"]!="")
        {
        // MailStandard
        if($zeile["MailStandard"]=="MailBuero"){$standardBuero="[S]";$standardPrivat="";}else{$standardBuero="";$standardPrivat="[S]";}
        if($zeile["MailBuero"]!=""){$mailbuero = "<td><a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKon=an&kontakt=".$zeile["MailBuero"]."\" style=\"color:#0000ff;\">".$zeile["MailBuero"]."</a> <i>(gesch&auml;ftlich)</i>".$standardBuero."<br></td>";}
        if($zeile["MailPrivat"]!=""){$mailprivat = "<td><a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKon=an&kontakt=".$zeile["MailPrivat"]."\" style=\"color:#0000ff;\">".$zeile["MailPrivat"]."</a> <i>(privat)</i>".$standardPrivat."<br></td>";}
        $konDaten.= "<tr><td><b>eMail:</b><br></td>".$mailbuero.$mailprivat."</tr>";
        }
    // Netz
    if($zeile["Netz"]!=""){$konDaten.= "<tr><td><b>Netz:</b><br></td><td><a href=\"".$zeile["Netz"]."\" style=\"color:#0000ff;\" target=\"_blank\">".$zeile["Netz"]."</a><br></td></tr>";}
    $konDaten.= "</table>";
    echo $konDaten;
	?>
</div>
</fieldset>
</p>

	<?php
	// Weitere Angaben
	if($zeile["Geburt"]!="0000-00-00 00:00:00" OR $zeile["SkypeID"] OR $zeile["ICQ"])
		{
		?>
<p>
<fieldset><legend><a href="javascript:Show_Stuff('Wei')" style="text-decoration:none;">[<span id="WeiOff">+</span><span id="WeiOn" style="display:none;">-</span>]</a> Weitere Angaben</legend>
<div id="Wei" style="display:none;">
<table border="0" cellpadding="0" cellspacing="3">
		<?php
        // Geburt
        if($zeile["Geburt"]!="0000-00-00 00:00:00")
            {
            ?>
<tr><td align="left" valign="top"><b>Geburtsdatum:<br></b></td><td align="left" valign="top">
            <?php
            // Geburt
            $datum = explode(" ",$zeile["Geburt"]);
            $datum = explode("-",$datum[0]);
            echo $datum[2].".".$datum[1].".".$datum[0];
            ?>
</td></tr>
            <?php
            }
        // SkypeID
        if($zeile["SkypeID"])
            {
            ?>
<tr><td align="left" valign="top"><b>SkypeID:<br></b></td><td align="left" valign="top">
            <?php
            // SkypeID
            echo $zeile["SkypeID"]
            ?>
</td></tr>
            <?php
            }
        // ICQ
        if($zeile["ICQ"])
            {
            ?>
<tr><td align="left" valign="top"><b>ICQ:<br></b></td><td align="left" valign="top">
            <?php
            // ICQ
            echo $zeile["ICQ"]
            ?>
</td></tr>
            <?php
            }
        ?>
</table>
</div>
</fieldset>
</p>
		<?php
		}
	
	// Bankverbindung
	if($zeile["KontoInhaber"]!="" OR $zeile["KontoBank"]!="" OR $zeile["KontoNummer"]!="" OR $zeile["KontoBLZ"]!="")
		{
		?>
<p>
<fieldset><legend><a href="javascript:Show_Stuff('Ban')" style="text-decoration:none;">[<span id="BanOff">+</span><span id="BanOn" style="display:none;">-</span>]</a> Bankverbindung</legend>
<div id="Ban" style="display:none;">
<table border="0" cellpadding="0" cellspacing="3">
		<?php
		// KontoInhaber
		if($zeile["KontoInhaber"]!="")
			{
			?>
<tr><td align="left" valign="top"><b>Kontoinhaber:<br></b></td><td align="left" valign="top">
			<?php
			// KontoInhaber
			echo $zeile["KontoInhaber"];
			?>
</td></tr>
			<?php
			}
			
		// KontoBank
		if($zeile["KontoBank"]!="")
			{
			?>
<tr><td align="left" valign="top"><b>Geldinstitut:<br></b></td><td align="left" valign="top">
			<?php
			// KontoBank
			echo $zeile["KontoBank"];
			?>
</td></tr>
			<?php
			}
			
		// KontoNummer
		if($zeile["KontoNummer"]!="")
			{
			?>
<tr><td align="left" valign="top"><b>Kontonummer:<br></b></td><td align="left" valign="top">
			<?php
			// KontoNummer
			echo $zeile["KontoNummer"];
			?>
</td></tr>
			<?php
			}
			
		// KontoBLZ
		if($zeile["KontoBLZ"]!="")
			{
			?>
<tr><td align="left" valign="top"><b>BLZ:<br></b></td><td align="left" valign="top">
			<?php
			// KontoBLZ
			echo $zeile["KontoBLZ"];
			?>
</td></tr>
			<?php
			}
		?>
</table>
</div>
</fieldset>
</p>
		<?php
		}

	// Klassen & Notizen
	if($zeile["Klassen"]!="" OR $zeile["Notizen"]!="")
		{
		?>
<p>
<fieldset><legend><a href="javascript:Show_Stuff('Kn')" style="text-decoration:none;">[<span id="KnOff">+</span><span id="KnOn" style="display:none;">-</span>]</a> Klassen &amp; Notizen</legend>
<div id="Kn" style="display:none;">
<table border="0" cellpadding="0" cellspacing="3" width="100%">
		<?php
		// Klassen
		if($zeile["Klassen"]!="")
			{
			?>
<tr><td align="left" valign="top"><b>Klassen:<br></b></td><td align="left" valign="top">
			<?php
			// Klassen
			echo stripslashes(nl2br($zeile["Klassen"]));
			?>
</td></tr>
			<?php
			}
	
		// Notizen
		if($zeile["Notizen"]!="")
			{
			?>
<tr><td align="left" valign="top"><b>Notizen:<br></b></td><td align="left" valign="top" bgcolor="#ffffff" width="385" style="padding:3px; border:1px solid #7799aa;">
			<?php
			// Notizen
			echo stripslashes(nl2br($zeile["Notizen"]));
			?>
</td></tr>
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
<fieldset><legend><a href="javascript:Show_Stuff('Sta')" style="text-decoration:none;">[<span id="StaOff">+</span><span id="StaOn" style="display:none;">-</span>]</a> Status</legend>
<div id="Sta" style="display:none;">
<table border="0" cellpadding="0" cellspacing="3">

	<?php
	// Neu
	if($zeile["Neu"]!="")
		{
		?>
<tr><td align="left" valign="top" width="75"><b>Neu:<br></b></td><td align="left" valign="top">
		<?php
		// Neu
		if($zeile["Neu"]=="1")
		  {
		  echo "Ja<br>\n";
		  }
        else
		  {
		  echo "Nein<br>\n";
		  }
		?>
</td></tr>
		<?php
		}
	?>

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
	// Andern
	echo "&nbsp;&nbsp;&nbsp;";
	echo "<a href=\"index.php?modus=DAT&inc=AEN&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loschen
	echo "<a href=\"index.php?modus=DAT&inc=LOE&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Zuruck
	echo "<a href=\"index.php?modus=DAT&inc=KON\">Zur&uuml;ck zur Kontakt&uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<!-- Content Konatkt Details -->

	<?php
	}
//###############################################################################
// /Details
?>