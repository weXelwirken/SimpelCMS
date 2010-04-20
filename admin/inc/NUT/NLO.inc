<?php
// POST und GET extrahieren
$step = $_POST["step"];
if($_POST["id"]){$id = $_POST["id"];}
if($_POST["modus"]){$modus = $_POST["modus"];}
if($_POST["inc"]){$inc = $_POST["inc"];}

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Testen ob Arbeitsschritt gesetzt
if($step==""){$step = 0;}

// Daten fuer Nutzer aus DB holen
// SQL-String bauen
$sqlString = "SELECT Login,Anrede,Vorname,Nachname FROM "._DBuserauth." WHERE ID='".$id."'";

// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

// Testen, ob min. ein Admin vorhanden
$sqlStringA = "SELECT ID FROM "._DBuserauth." WHERE Rolle='3' AND ID!='".$id."'";
$ergebnisA = $db -> sql($sqlStringA);
if($ergebnisA){$num=mysql_num_rows($ergebnisA);}
	
?>

<!-- Content Nutzer loeschen -->

<table border="0" cellpadding="0" cellspacing="0" width="480">

<tr>
<td align="left" valign="top">

<?php
// Step 0: Eingabe
//######################################################################################
if($step==0)
	{
	if($num<1)
        {
        ?>
<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">

<div align="left">
<h3 class="textRot">Achtung</h3>

Der Nutzer <b>&raquo;<?php echo $zeile["Login"]."&laquo; <i>(".$zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"].")</i>"; ?></b> kann nicht gel&ouml;scht werden, da sonst kein Nutzer mit Administrations-Rechten mehr vorhanden ist.<br>
Bitte vergeben Sie an einen anderen Nutzer die entsprechenden Rechte, wenn Sie den ngew&auml;hlten Nutzer l&ouml;schen wollen.<br><br>
<a href="javascript:history.back()">zur&uuml;ck zur &Uuml;bersicht</a><br>
</div>
        <?php
        }
    else
        {
        ?>
<form action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">

<div align="left">
<h3>Nutzer l&ouml;schen</h3>

Soll der Nutzer <b>&raquo;<?php echo $zeile["Login"]."&laquo; <i>(".$zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"].")</i>"; ?></b> wirklich gel&ouml;scht werden?<br>
Falls nicht, geht es hier <a href="javascript:history.back()">zur&uuml;ck zur &Uuml;bersicht</a>.<br><br>

<input type="submit" value="Nutzer l&ouml;schen">
</div>

<input type="hidden" name="id" value="<?php echo $id; ?>">
<input type="hidden" name="modus" value="<?php echo $modus; ?>">
<input type="hidden" name="inc" value="<?php echo $inc; ?>">
<input type="hidden" name="step" value="1">

</form>
        <?php
        }
	}
//######################################################################################
// /Step 0: Eingabe

// Step 1: L&ouml;schen
//######################################################################################
if($step==1)
	{
    // SQL-String bauen
    $sqlString = "DELETE FROM "._DBuserauth." WHERE ID='".$id."'";

    // Veranstaltung aus DB l&ouml;schen
    $ergebnis = $db -> sql($sqlString);
    
    // Fehlerbehandlung
    if($ergebnis){echo "<h3 align=\"left\">Nutzer gel&ouml;scht</h3>\nDer Nutzer wurde erfolgreich aus der Datenbank gel&ouml;scht.<br>\n<br>\n<a href=\"index.php?modus=NUT&inc=NUE\">zur &Uuml;bersicht...</a><br>\n";}
    else{echo "<h3 align=\"left\">Fehler!</h3>\nDer Nutzer konnte nicht aus der Datenbank gel&ouml;scht werden.<br>\nBitte versuch es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}
	}
//######################################################################################
// /Step 1: Pruefen und speichern
?>

<br><br>

</td>
</tr>

</table>

<!-- Content Nutzer loeschen -->