<?php
// POST und GET extrahieren
$step = $_POST["step"];
$bild = $_POST["bild"];
if($_POST["id"]){$id = $_POST["id"];}
if($_POST["modus"]){$modus = $_POST["modus"];}
if($_POST["inc"]){$inc = $_POST["inc"];}

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}

// Daten fuer Artikel aus DB holen
// SQL-String bauen
$sqlString = "SELECT b.ID as BID, b.NutzerID as NID, b.Status, b.Erzeugt, b.Geaendert, n.Anrede, n.Vorname, n.Nachname FROM "._ShopBestellungen." b, "._DBuserauth." n WHERE b.ID='".$id."' AND b.NutzerID=n.ID LIMIT 1";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

// Datum vorbereiten
$datum = dateTimeAusgabe($zeile["Erzeugt"]);
// Status vorbereiten
$statusArray = explode("|", $bestellstatus[$zeile["Status"]]);
$statusTag = "<span style=\"border:2px solid ".$statusArray[1].";padding:0 3px 0 3px;\"><nobr>".$statusArray[0]."</nobr></span>";
$editStatus = $zeile["Status"]+1;
if($editStatus>4){$editStatus=1;}
?>

<!-- Content Bestellung loeschen -->

<table border="0" cellpadding="0" cellspacing="0">

<tr>
<td align="left" valign="top">

<?php
// Step 0: Eingabe
//################################################################################
if($step==0)
	{
	?>

<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">

<div align="left">
<h3>Bestellung l&ouml;schen</h3>

Soll die Bestellung vom <b><i><?php echo $datum["Tag"].".".$datum["Monat"].".".$datum["Jahr"]; ?></i></b> f&uuml;r <b><i><?php echo $zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"]; ?></i></b> mit dem Status <?php echo $statusTag; ?> wirklich gel&ouml;scht werden?<br><br>
Falls nicht, geht es hier <a href="javascript:history.back()">zur&uuml;ck zur Detailansicht der Bestellung</a>.<br><br>

<input type="submit" value="Bestellung l&ouml;schen">
</div>

<input type="hidden" name="id" value="<?php echo $id; ?>">
<input type="hidden" name="bild" value="<?php echo $zeile["Bild"]; ?>">
<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">

</form>

	<?php
	}
//################################################################################
// /Step 0: Eingabe

// Step 1: Loeschen
//################################################################################
if($step==1)
	{	
    // SQL-String bauen
    $sqlString = "DELETE FROM "._ShopBestellungen." WHERE ID='".$id."'";
    // Eintrag aus DB loschen
    $ergebnis = $db -> sql($sqlString);
    
    // SQL-String bauen
    $sqlString = "DELETE FROM "._ShopPositionen." WHERE BesID='".$id."'";
    // Eintrag aus DB loschen
    $ergebnis = $db -> sql($sqlString);
    
    // Fehlerbehandlung
    if($ergebnis){echo "<h3 align=\"left\">Bestellung gel&ouml;scht</h3>\nDie Bestellung wurden erfolgreich aus der Datenbank gel&ouml;scht.<br>\n<br>\n<a href=\"index.php?modus=SHO&inc=UEB\">zur &Uuml;bersicht...</a><br>\n";}
    else{echo "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nDie Bestellung konnte nicht aus der Datenbank gel&ouml;scht werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
    }


//################################################################################
// /Step 1: Loeschen
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Bestellung loeschen -->