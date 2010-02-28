<?php
// POST und GET extrahieren
$step = $_POST["step"];
if($_POST["id"]){$id = $_POST["id"];}
if($_POST["modus"]){$modus = $_POST["modus"];}
if($_POST["inc"]){$inc = $_POST["inc"];}
if($_POST["trotzdem"]){$trotzdem = $_POST["trotzdem"];}

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}
?>

<!-- Content Ordner loeschen -->

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
<h3>Ordner l&ouml;schen</h3>

Soll der Ordner <b>&raquo;<?php OrdPfad($id, $ordPfad); ?>&laquo;</b> wirklich gel&ouml;scht werden?<br>
Falls nicht, geht es hier <a href="javascript:history.back()">zur&uuml;ck zur Detailansicht des Ordners</a>.<br><br>

<input type="submit" value="Ordner l&ouml;schen">
</div>

<input type="hidden" name="id" value="<?php echo $id; ?>">
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
	// Fehlerbehandlung
	
	// Testen, ob Ordner noch Doumente enthaelt
	// SQL-String bauen
	$sqlString = "SELECT ID FROM "._DBdokumente." WHERE Ordner='".$id."'";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if(mysql_fetch_array($ergebnis)){$fehler = "<li>Der Ordner konnte nicht aus der Datenbank gel&ouml;scht werden, da ihm noch Dokumente zugeordnet sind. Klicken Sie hier, wenn Sie den <span class=\"textRot\">Ordner trotzdem inklusive aller Inhalte l&ouml;schen</span> wollen.\n<input type=\"hidden\" name=\"id\" value=\"".$id."\">\n<input type=\"hidden\" name=\"modus\" value=\"".$modus."\">\n<input type=\"hidden\" name=\"inc\" value=\"".$inc."\">\n<input type=\"hidden\" name=\"step\" value=\"1\">\n<input type=\"hidden\" name=\"trotzdem\" value=\"1\">\n<p><input type=\"submit\" value=\"Ordner trotzdem l&ouml;schen\"></p>\n";}
	
	// Testen, ob Ordner noch Unterordner enthaelt
	// SQL-String bauen
	$sqlString = "SELECT ID FROM "._DBordner." WHERE Mutter='".$id."'";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if(mysql_fetch_array($ergebnis)){$fehler = "<li>Der Ordner konnte nicht aus der Datenbank gel&ouml;scht werden, da er noch Unterordner enth&auml;lt. Bitte l&ouml;schen Sie zuerst alle Unterordner.\n";}
	
	if($trotzdem=="1"){unset($fehler);}
	
	if($fehler!="")
		{
		echo "<h3 align=\"left\">Fehler!</h3>
		  <form action=\"".$PHP_SELF."\" enctype=\"multipart/form-data\" method=\"post\">
		  <ul>\n".$fehler."</ul>
		  </form>
		  <a href=\"index.php?id=".$id."&modus=ORD&inc=OUE&id=".$id."\">zur&uuml;ck...</a><br>\n";
		}
	else
		{		
		// SQL-String bauen
		$sqlString = "DELETE FROM "._DBordner." WHERE ID='".$id."'";
		// Ordner aus DB loeschen
		$ergebnis = $db -> sql($sqlString);
		
		if($trotzdem=="1")
            {	
            // SQL-String bauen
            $sqlString = "DELETE FROM "._DBdokumente." WHERE Ordner='".$id."'";
            // Dokumente aus DB loeschen
            $ergebnis = $db -> sql($sqlString);
            }
        
        // .htaccess aktualisieren
        if($ModRewrite){UrlRewrite();}
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3 align=\"left\">Ordner gel&ouml;scht</h3>\nDer Ordner wurden erfolgreich aus der Datenbank gel&ouml;scht.<br>\n<br>\n<a href=\"index.php?modus=ORD&inc=OUE\">Zur &Uuml;bersicht...</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDer Ordner konnte nicht aus der Datenbank gel&ouml;scht werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	}
//################################################################################
// /Step 1: Pruefen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Ordner loeschen -->