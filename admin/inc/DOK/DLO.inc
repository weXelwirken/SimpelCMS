<?php
// POST und GET extrahieren
$step = $_POST["step"];
$idLetzte = $_POST["idLetzte"];
if($_POST["id"]){$id = $_POST["id"];}
if($_POST["modus"]){$modus = $_POST["modus"];}
if($_POST["inc"]){$inc = $_POST["inc"];}

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Testen ob Arbeitsschritt gesetzt
if(!$step){$step=0;}

// Daten fuer Seite aus DB holen
// SQL-String bauen
$sqlString = "SELECT * FROM "._DBdokumente." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

// Daten fuer letzte Seite in Wurzel aus DB holen
// SQL-String bauen
$sqlString = "SELECT ID FROM "._DBdokumente." WHERE Ordner='0' ORDER BY Position ASC";
// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis)
    {
    if(mysql_num_rows($ergebnis)==1)
        {
        $zeileLetzte=mysql_fetch_array($ergebnis);
        $idLetzte=$zeileLetzte["ID"];
        }
    }
else{echo "Fehler: Es konnte keine DokID ausgelesen werden!<br>\n";}
	
?>

<!-- Content Dokument loeschen -->

<table border="0" cellpadding="0" cellspacing="0" width="480">

<tr>
<td align="left" valign="top">

<?php
// Step 0: Eingabe
//######################################################################################
if($step==0)
	{
	if($id!=$idLetzte)
		{
		?>

<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">

<div align="left">
<h3>Dokument l&ouml;schen</h3>

Soll das Dokument <b>&raquo;<?php echo $zeile["Linktext"]." - ".$zeile["Titel"]; ?>&laquo;</b> wirklich gel&ouml;scht werden?<br>
Falls nicht, geht es hier <a href="javascript:history.back()">zur&uuml;ck zur Dokumentenansicht</a>.<br><br>

<input type="submit" value="Dokument l&ouml;schen">
</div>

<input type="hidden" name="id" value="<?php echo $id; ?>">
<input type="hidden" name="idLetzte" value="<?php echo $idLetzte; ?>">
<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">

</form>

		<?php
		}
	else
		{
		?>
<div align="left">
<h3>Achtung!</h3>

Dieses Dokument darf nicht gel&ouml;scht werden, da es sich um das letzte Dokument im der Wurzel-Ordner handelt!<br>
<a href="javascript:history.back()">zur&uuml;ck zur &Uuml;bersicht</a>.<br><br>

</div>
		<?php
		}
	}
//######################################################################################
// /Step 0: Eingabe

// Step 1: Loeschen
//######################################################################################
if($step==1)
	{
	if($id!=$idLetzte)
		{
		// SQL-String bauen
		$sqlString = "DELETE FROM "._DBdokumente." WHERE ID='".$id."'";
	
		// Veranstaltung aus DB l&ouml;schen
		$ergebnis = $db -> sql($sqlString);
		
		// Fehlerbehandlung
		if($ergebnis){echo "<h3 align=\"left\">Dokument gel&ouml;scht</h3>\nDas Dokument wurde erfolgreich aus der Datenbank gel&ouml;scht.<br>\n<br>\n<a href=\"index.php?modus=DOK&inc=DUE\">Zur &Uuml;bersicht...</a><br>\n";}
		else{echo "<h3 align=\"left\">Fehler!</h3>\nDas Dokument konnte nicht aus der Datenbank gel&ouml;scht werden.<br>\nBitte versuch es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
		}
	else
		{
		?>
<div align="left">
<h3>Achtung!</h3>

Dieses Dokument darf nicht gel&ouml;scht werden, da es sich um das letzte Dokument im der Wurzel-Ordner handelt!<br>
<a href="javascript:history.back()">zur&uuml;ck zur &Uuml;bersicht</a>.<br><br>

</div>
		<?php
		}
	}
//######################################################################################
// /Step 1: Loeschen
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Dokument loeschen -->