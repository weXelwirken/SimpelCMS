<?php

// POST und GET extrahieren
$bid = $_GET["bid"];
$detail = $_GET["detail"];
$editStatus = $_GET["editStatus"];

// ***********************************************************************************************************
// Status aendern ********************************************************************************************
if($bid AND $editStatus)
    {
    // SQL-String bauen
	$sqlString = "UPDATE "._ShopBestellungen." SET Status='".$editStatus."',Geaendert='".datetimemaker(time())."' WHERE ID='".$bid."'";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if(!$ergebnis){echo "Fehler: Der Status konnte in der Datenbank nicht geaendert werden.";}
	if($detail){unset($editStatus);}else{unset($bid);}
    }

// ***********************************************************************************************************
// Uebersicht ************************************************************************************************
if(!$bid)
    {
    ?>

<h3>&Uuml;bersicht Shop</h3>

<br>

<table border="0" cellpadding="3" cellspacing="0" width="480">

<tr>
<td width="50%">

<fieldset>
<legend>Neue Gruppe anlegen</legend>
<div class="kleiner">
Legen Sie hier eine neue Artikelgruppe an.<br><br>
<div align="right"><a href="index.php?modus=SHO&inc=AGN" class="kleiner">mehr...</a></div>
</div>
</fieldset>

</td>
<td width="50%">

<fieldset>
<legend>Neuen Artkel anlegen</legend>
<div class="kleiner">
Legen Sie hier eine neuen Artikel f&uuml;r den Shop an.<br><br>
<div align="right"><a href="index.php?modus=SHO&inc=AAN" class="kleiner">mehr...</a></div>
</div>
</fieldset>

</td>
</tr>

<tr>
<td colspan="2">

<fieldset>
<legend>Bestellungen</legend>

<table border="0" cellspacing="3" cellpadding="3" width="100%">

<tr>
<td style="border-bottom:1px solid #666666;" align="left"><b>Datum</b></td>
<td style="border-bottom:1px solid #666666;" align="left"><b>Kunde</b></td>
<td style="border-bottom:1px solid #666666;" align="center"><b>Umsatz</b></td>
<td style="border-bottom:1px solid #666666;" align="center"><b>Status</b></td>
<td style="border-bottom:1px solid #666666;" align="center"><b>Aktionen</b></td>
</tr>

	<?php
	
	// Vorhandene Bestellungen fuer Ubersicht aus DB holen +++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// SQL-String bauen
	$sqlString = "SELECT b.ID as BID, b.NutzerID as NID, b.Status, b.Erzeugt, b.Geaendert, n.Anrede, n.Vorname, n.Nachname FROM "._ShopBestellungen." b, "._DBuserauth." n WHERE b.NutzerID=n.ID ORDER BY b.Status, b.Erzeugt DESC";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			// Datum vorbereiten
			$datum = dateTimeAusgabe($zeile["Erzeugt"]);
			// Umsatz vorbereiten
            $sqlStringU = "SELECT SUM(Preis*Menge) as Umsatz FROM "._ShopPositionen." WHERE BesID='".$zeile["BID"]."'";
            $ergebnisU = $db -> sql($sqlStringU);
            if($ergebnisU){$umsatz = mysql_fetch_array($ergebnisU);}else{echo "Fehler: Der Umsatz konnte in der Datenbank nicht geaendert werden.";}
            
			// Status vorbereiten
			$statusArray = explode("|", $bestellstatus[$zeile["Status"]]);
			$statusTag = "<div style=\"border:2px solid ".$statusArray[1].";padding:0 3px 0 3px;\"><nobr>".$statusArray[0]."</nobr></div>";
			$editStatus = $zeile["Status"]+1;
			if($editStatus>4){$editStatus=1;}
			
			// Ausgabe
			echo "<tr>
                <td>".$datum["Tag"].".".$datum["Monat"].".".$datum["Jahr"]."</td>
                <td><nobr>".$zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"]."</nobr></td>
                <td align=\"right\">".number_format($umsatz["Umsatz"],2,',','.')." &euro;</td>
                <td align=\"center\">".$statusTag."</td>
                <td align=\"center\"><nobr>
                <a href=\"index.php?modus=SHO&inc=UEB&bid=".$zeile["BID"]."\" style=\"text-decoration:none;\" title=\"Details\"><b class=\"textGruen\">O</b></a>&nbsp;
                <a href=\"index.php?modus=SHO&inc=UEB&bid=".$zeile["BID"]."&editStatus=".$editStatus."\" style=\"text-decoration:none;\" title=\"Status &auml;ndern\"><b class=\"textOrange\">S</b></a>&nbsp;
                <a href=\"index.php?modus=SHO&inc=BLO&id=".$zeile["BID"]."\" style=\"text-decoration:none;\" title=\"L&ouml;schen\"><b class=\"textRot\">X</b></a>
                </nobr></td>
                </tr>";
			}
		mysql_free_result($ergebnis);
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Bestelluebersicht ausgelesen werden!<br>\n";}
	?>
</table>
	
</fieldset>

</td>
</tr>

</table>

    <?php
    }
// /Uebersicht ***********************************************************************************************
// ***********************************************************************************************************

// ***********************************************************************************************************
// Bestellung *********************************************************************************************
if($bid AND !$editStatus)
    {
	// Daten der Bestellung aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT b.ID as BID, b.NutzerID as NID, b.Status, b.Erzeugt, b.Geaendert, n.Anrede, n.Vorname, n.Nachname, n.Strasse, n.PLZ, n.Ort, n.Land, n.Telefon, n.Mobil, n.Mail FROM "._ShopBestellungen." b, "._DBuserauth." n WHERE b.ID='".$bid."' AND b.NutzerID=n.ID LIMIT 1";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	
	// Datum vorbereiten
	$datum = dateTimeAusgabe($zeile["Erzeugt"]);
    // Status vorbereiten
    $statusArray = explode("|", $bestellstatus[$zeile["Status"]]);
    $statusTag = "<div style=\"border:2px solid ".$statusArray[1].";padding:0 3px 0 3px;\"><nobr>".$statusArray[0]."</nobr></div>";
    $editStatus = $zeile["Status"]+1;
    if($editStatus>4){$editStatus=1;}
	?>

<!-- Content Bestellung Details -->

<h5 align="left">Bestellung vom <?php echo $datum["Tag"].".".$datum["Monat"].".".$datum["Jahr"]; ?></h5>
<h3 align="left">F&uuml;r <?php echo $zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"]; ?></h3>
    <?php if($zeile["Untertitel"]){ echo "<b>".$zeile["Untertitel"]."</b><br>\n"; }?>

<p>
<fieldset>
<table border="0" cellpadding="0" cellspacing="3">
<tr><td align="left" valign="top"><b>Aktionen:</b></td><td align="left" valign="top">
	<?php
	// Aktionen
	// Aendern
	echo "&nbsp;&nbsp;&nbsp;";
	// Status
	echo "<a href=\"index.php?modus=SHO&inc=UEB&bid=".$zeile["BID"]."&editStatus=".$editStatus."&detail=x\"><b><span class=\"textGruen\">Status &auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loeschen
	echo "<a href=\"index.php?modus=SHO&inc=BLO&id=".$zeile["BID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Zurueck
	echo "<a href=\"index.php?modus=SHO&inc=UEB\">Zur&uuml;ck zur &Uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<p>
<fieldset><legend><a href="javascript:Show_Stuff('Bes')" style="text-decoration:none;">[<span id="VerOff" style="display:none;">+</span><span id="VerOn">-</span>]</a> Bestellung</legend>
<div id="Bes">
	<?php
    // Daten der Positionen aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._ShopPositionen." WHERE BesID='".$bid."' ORDER BY Erzeugt";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
        {
        echo "<table border=\"0\" cellspacing=\"0\" cellpadding=\"3\" width=\"100%\">
            <tr>
            <td align=\"center\"><b>Pos</b></td>
            <td><b>Artikel</b></td>
            <td align=\"center\"><b>ArtID</b></td>
            <td align=\"center\"><b>Menge</b></td>
            <td align=\"right\"><b>Einzel</b></td>
            <td align=\"right\"><b>Summe</b></td>
            </tr>\n";
            $c = "1";
            
        while($bestellung = mysql_fetch_array($ergebnis))
            {            
            // Ausgabe vorbereiten
            $endpreis = $bestellung["Preis"]*$bestellung["Menge"];
            echo "<tr>
                <td align=\"center\">".$c."</td>
                <td><a href=\"index.php?modus=SHO&inc=AUE&id=".$bestellung["ArtID"]."\">".$bestellung["Name"]."</a></td>
                <td align=\"center\">".$bestellung["ArtID"]."</td>
                <td align=\"center\">".$bestellung["Menge"]."</td>
                <td align=\"right\">".number_format($bestellung["Preis"],2,',','.')." &euro;</td>
                <td align=\"right\">".number_format($endpreis,2,',','.')." &euro;</td>
                </tr>";
            $c++;
            $total = $total+$endpreis;
            }
        echo "<tr><td colspan=\"6\"><hr></td></tr>
            <tr>
            <td colspan=\"5\" align=\"right\"><b>Total:</b></td>
            <td align=\"right\"><b>".number_format($total,2,',','.')." &euro;</b></td></tr>
            </table>\n";
        }
	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
	?>
</div>
</fieldset>
</p>

<p>
<fieldset><legend><a href="javascript:Show_Stuff('Kon')" style="text-decoration:none;">[<span id="VerOff" style="display:none;">+</span><span id="VerOn">-</span>]</a> Rechnungs- &amp; Lieferadresse</legend>
<div id="Kon">
<table width="100%">
<tr>
<td valign="bottom">
	<?php
    echo "<nobr>".$zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"]."</nobr><br>
        <nobr>".$zeile["Strasse"]."</nobr><br>
        <nobr>".$zeile["PLZ"]." ".$zeile["Ort"]."</nobr><br>
        <nobr>".$zeile["Land"]."</nobr><br>\n";
	?>
</td>
<td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
<td valign="bottom" width="100%">
	<?php
    echo "<nobr>Telefon: ".$zeile["Telefon"]."</nobr><br>
        <nobr>Mobil: ".$zeile["Mobil"]."</nobr><br><br>
        <nobr>eMail: <a href=\"mailto:".$zeile["Mail"]."\">".$zeile["Mail"]."</a></nobr><br>\n";
	?>
</td>
<td></td>
<td valign="bottom" align="center">
	<?php
    echo "<a href=\"index.php?modus=NUT&inc=NUE&id=".$zeile["NID"]."\" title=\"Zum Kundenprofil\"><img src=\"../img/shop/scmsIcons_lupe.gif\" width=\"30\" height=\"30\" border=\"0\" alt=\"Zum Kundenprofil\"></a><br>
        <a href=\"index.php?modus=NUT&inc=NUE&id=".$zeile["NID"]."\">Zum Kundenprofil</a>\n";
	?>
</td>
</tr>
</table>
</div>
</fieldset>
</p>

<p>
<fieldset><legend><a href="javascript:Show_Stuff('Sta')" style="text-decoration:none;">[<span id="StaOff" style="display:none;">+</span><span id="StaOn">-</span>]</a> Status</legend>
<div id="Sta">
<table border="0" cellpadding="0" cellspacing="3">

<tr><td align="left" valign="top" width="75"><b>Status:<br></b></td><td align="center" valign="top">
    <?php
    // Status
    echo $statusTag;
    ?>
</td></tr>

<tr><td align="left" valign="top" width="75"><b>Erzeugt:<br>Ge&auml;ndert:<br></b></td><td align="center" valign="top">
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
	echo "&nbsp;&nbsp;&nbsp;";
	// Status
	echo "<a href=\"index.php?modus=SHO&inc=UEB&bid=".$zeile["BID"]."&editStatus=".$editStatus."&detail=x\"><b><span class=\"textGruen\">Status &auml;ndern</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Loeschen
	echo "<a href=\"index.php?modus=SHO&inc=BLO&id=".$zeile["BID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>";
	echo "&nbsp;&nbsp;&nbsp;";
	// Zurueck
	echo "<a href=\"index.php?modus=SHO&inc=UEB\">Zur&uuml;ck zur &Uuml;bersicht</a>";
	?>
</td></tr>
</table>
</fieldset>
</p>

<!-- Content Bestellung Details -->
    <?php
    }
// /Veranstaltung ********************************************************************************************
// ***********************************************************************************************************
?>