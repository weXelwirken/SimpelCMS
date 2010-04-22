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
$sqlString = "SELECT * FROM "._ShopArtikel." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
?>

<!-- Content Artikel loeschen -->

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
<h3>Artikel l&ouml;schen</h3>

Soll der Artikel <b>&raquo;<?php echo $zeile["Name"]; ?>&laquo;</b> wirklich gel&ouml;scht werden?<br>
Falls nicht, geht es hier <a href="javascript:history.back()">zur&uuml;ck zur Detailansicht des Artikels</a>.<br><br>

<input type="submit" value="Artikel l&ouml;schen">
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
	$sqlString = "SELECT ID FROM "._ShopPositionen." WHERE ArtID='".$id."'";

	// DB auslesen
	$ergebnis = $db -> sql($sqlString);

	// Fehlerbehandlung
	if(mysql_fetch_array($ergebnis)){echo "<h3 align=\"center\">Fehler!</h3>\nDie Angaben zum Artikel konnten nicht aus der Datenbank gel&ouml;scht werden.<br>\nDieser Artikel ist noch mit einem oder mehreren Bestellungen verkn&uuml;pft.<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
	else
        {
        // SQL-String bauen
        $sqlString = "DELETE FROM "._ShopArtikel." WHERE ID='".$id."'";
    
        // Eintrag aus DB loschen
        $ergebnis = $db -> sql($sqlString);
        
        // Bild loeschen
        if($bild){unlink($ServerRoot.$ShopBildPfad."/".$bild);}
        
        // Fehlerbehandlung
        if($ergebnis){echo "<h3 align=\"left\">Artikel gel&ouml;scht</h3>\nDer Artikel wurden erfolgreich aus der Datenbank gel&ouml;scht.<br>\n<br>\n<a href=\"index.php?modus=SHO&inc=AUE\">zur &Uuml;bersicht...</a><br>\n";}
        else{echo "<h3 align=\"left\" class=\"textRot\">Fehler!</h3>\nDer Artikel konnte nicht aus der Datenbank gel&ouml;scht werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
        }
	}

//################################################################################
// /Step 1: Loeschen
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Gruppe loeschen -->