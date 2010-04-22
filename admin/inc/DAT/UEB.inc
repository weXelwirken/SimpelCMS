<h3>&Uuml;bersicht Datenkrake</h3>

<br>

<table border="0" cellpadding="3" cellspacing="0" width="475">

<tr>
<td width="100%" colspan="2">
<!-- Neu -->
<fieldset>
<legend>Neu</legend>
<p>
<?php

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Aufruf Ubersicht
// Daten der Kategorie aus DB holen
// SQL-String bauen
$sqlString = "SELECT ID, Anrede, Vorname, Nachname, MailBuero, MailPrivat FROM "._KrakeDatenpool." WHERE Neu='1' ORDER BY Nachname";
// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis)
    {
    // Wenn keinen neuen Eintraege...
    $anzErg = mysql_num_rows($ergebnis);
    if($anzErg<"1")
        {
        echo "<li style=\"color:".$modusArrayADMIN[$_GET["modus"]]["Wert"].";\"><span class=\"text\">Zur Zeit gibt es keine neuen Eintr&auml;ge im Datenpool.</span><br>\n";
        }
    // Neue Daten auslesen
    else
        {
        if($anzErg<2){$ergText="neuen Eintrag";}else{$ergText="neue Eintr&auml;ge";}
        echo "<p>Zur Zeit gibt es <b>".$anzErg." ".$ergText."</b> im Datenpool:<br></p>\n";
        $c=0;
        echo "<table>\n";
        while($zeile = mysql_fetch_array($ergebnis))
            {
            // Ausgabe
            if($c<5 OR $show=="1")
                {
                // Mail bauen
                if($zeile["MailBuero"]!="")
                    {$mailString="<a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKon=an&kontakt=".$zeile["MailBuero"]."\" style=\"color:#0000ff;\">".$zeile["MailBuero"]."</a> <i>(B&uuml;ro)</i>";}
                else
                    {$mailString="<a href=\"index.php?modus=DAT&inc=MAI&sendeOptionKon=an&kontakt=".$zeile["MailPrivat"]."\" style=\"color:#0000ff;\">".$zeile["MailPrivat"]."</a> <i>(Privat)</i>";}
                if($zeile["MailBuero"]=="" AND $zeile["MailPrivat"]=="")
                    {$mailString="<i>keine E-Mail-Adresse</i>";}
                
                echo "<tr>
                <td width=\"\"><nobr><li style=\"color:".$modusArrayADMIN[$_GET["modus"]]["Wert"].";\"><a href=\"index.php?modus=DAT&inc=KON&id=".$zeile["ID"]."\" style=\"color:#000000;\">".$zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"]."</a></nobr></td>
                <td width=\"\">".$mailString."</td>
                </tr>\n";
                }
            $c++;
            }
        echo "</table>\n";
        if($show!="1" AND $c>4)
            {echo "<p align=right><a href=\"index.php?modus=DAT&inc=UEB&show=1\">Alle neuen Eintr&auml;ge anzeigen...</a></p>";} 
        }
    }
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
?>
</p>
</fieldset>
<!-- /Neu -->
</td>
</tr>

<tr>
<td width="50%">
<!-- Kontakte -->
<fieldset>
<legend>Kontakte</legend>
<p>
<a href="index.php?modus=DAT&inc=KON"><img src="img/module/krake/krake_kontakt.gif" width="50" height="50" border="0" alt="Konatkte" title="Kontakte" align="left"></a>
Alle gespeicherten Kontakte von A bis Z.<br><br>
<div align="right"><a href="index.php?modus=DAT&inc=KON">mehr...</a></div><br>
</p>
</fieldset>
<!-- /Kontakte -->
</td>
<td width="50%">
<!-- E-Mail -->
<fieldset>
<legend>E-Mail</legend>
<p>
<a href="index.php?modus=DAT&inc=MAI"><img src="img/module/krake/krake_mail.gif" width="50" height="50" border="0" alt="E-Mail" title="E-Mail" align="left"></a>
E-Mails an Einzelkontakte oder Kontaktklassen versenden.<br>
<div align="right"><a href="index.php?modus=DAT&inc=MAI">mehr...</a></div><br>
</p>
</fieldset>
<!-- /E-Mail -->
</td>
</tr>

<tr>
<td width="50%">
<!-- Klassen -->
<fieldset>
<legend>Klassen</legend>
<p>
<a href="index.php?modus=DAT&inc=KLA"><img src="img/module/krake/krake_klassen.gif" width="50" height="50" border="0" alt="Klassen" title="Klassen" align="left"></a>
Klassen von Kontakten anlegen, &auml;ndern und verwalten.<br>
<div align="right"><a href="index.php?modus=DAT&inc=KLA">mehr...</a></div><br>
</p>
</fieldset>
<!-- /Klassen -->
</td>
<td width="50%">
<!-- Import -->
<fieldset>
<legend>Import &amp; Export</legend>
<p>
<a href="index.php?modus=DAT&inc=IMP"><img src="img/module/krake/krake_import.gif" width="50" height="50" border="0" alt="Import &amp; Export" title="Import &amp; Export" align="left"></a>
Gro&szlig;e Mengen von Kontaktdaten per Datei im- oder exportieren.<br>
<div align="right"><a href="index.php?modus=DAT&inc=IMP">mehr...</a></div><br>
</p>
</fieldset>
<!-- /Import -->
</td>
</tr>

<tr>
<td width="100%" colspan="2">
<!-- Dubletten -->
<fieldset>
<legend>Dubletten-Suche</legend>
<p>
<a href="index.php?modus=DAT&inc=DUB"><img src="img/module/krake/krake_dubletten.gif" width="50" height="50" border="0" alt="Dubletten-Suche" title="Dubletten-Suche" align="left"></a>Diese Funktion durchsucht den Datenpool nach potentiellen Dubletten und zeigt sie an.<br>
<div align="right"><a href="index.php?modus=DAT&inc=DUB">mehr...</a></div><br>
</p>
</fieldset>
<!-- /Dubletten -->
</td>
</tr>

</table>