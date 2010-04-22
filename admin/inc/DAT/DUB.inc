<h3>Dubletten-Suche</h3>

<p>
<?php

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Aufruf Ubersicht
// Daten aus DB holen
// SQL-String bauen
$sqlString = "SELECT ID, Anrede, Vorname, Nachname, MailBuero, MailPrivat FROM "._KrakeDatenpool." ORDER BY ID";
// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis)
    {
    $c0=0;
    while($zeile = mysql_fetch_array($ergebnis))
        {
        // Array befuellen
        $pool[$c0]["ID"] = $zeile["ID"];
        $pool[$c0]["Anrede"] = $zeile["Anrede"];
        $pool[$c0]["Vorname"] = $zeile["Vorname"];
        $pool[$c0]["Nachname"] = $zeile["Nachname"];
        $pool[$c0]["MailBuero"] = $zeile["MailBuero"];
        $pool[$c0]["MailPrivat"] = $zeile["MailPrivat"];
        $c0++;
        }
    $ausgabeKopf.= "<p>Im Datenpool sind folgende Dubletten vorhanden:</p>\n";
    //echo "Array geladen mit ".$c0." Datens&auml;tzen!<br>\n====<br>\n";
    
    // Tabellenkopf
    $ausgabeKopf.= "<table cellpadding=3>
        <tr>
        <td bgcolor=\"#cccccc\" align=\"center\">Name</td>
        <td bgcolor=\"#cccccc\" align=\"center\">eMail</td>
        <td bgcolor=\"#cccccc\" align=\"center\">Datum</td>
        <tr>";
    // Hintergrundfarbe fuer Zeilen
    $bgCount = "0";
    $bgcolor["0"] = "#ffffff";
    $bgcolor["1"] = "#eeeeee";
    
    // Daten vergleichen
    for($c1=0;$c1<$c0;$c1++)
        {
        $doppelt[] = $pool[$c1]["ID"];
        //echo "***<br>Durchlauf c1:".$c1."<br>\n";
        for($c2=0;$c2<$c0;$c2++)
            {
            if($pool[$c1]["Vorname"]==$pool[$c2]["Vorname"] AND $pool[$c1]["Nachname"]==$pool[$c2]["Nachname"] AND ($pool[$c1]["MailBuero"]==$pool[$c2]["MailBuero"] OR $pool[$c1]["MailBuero"]==$pool[$c2]["MailPrivat"] OR $pool[$c1]["MailPrivat"]==$pool[$c2]["MailBuero"] OR $pool[$c1]["MailPrivat"]==$pool[$c2]["MailPrivat"]))
                {
                // Als doppelt erkannte speichern
                $doppelt[] = $pool[$c2]["ID"];
                $doppeltPool[] = $c2;
                /*echo "Durchlauf c2:".$c2."<br>\n";
                echo $pool[$c2]["ID"]." ".$pool[$c2]["Vorname"]." ".$pool[$c2]["Nachname"]."<br>\n";
                echo "Count von doppelt:".count($doppelt)."<br>\n";*/
                }
            }
        // Doppelte ausgeben
        if(count($doppelt)>2 AND count($doppelt)<20)
            {
            // Daten aus DB holen
            // SQL-String bauen
            for($c=0;$c<count($doppelt);$c++)
                {
                $where.= "ID='".$doppelt[$c]."'";
                if($c<(count($doppelt)-1)){$where.=" OR ";}
                }
            $sqlString = "SELECT * FROM "._KrakeDatenpool." WHERE ".$where;
            unset($where);
            // Ergebnis auslesen
            $ergebnis = $db -> sql($sqlString);
            if($ergebnis)
                {
                // Testen, ob Ergebnis vorhanden
                if(mysql_num_rows($ergebnis))
                    {
                    while($zeile = mysql_fetch_array($ergebnis))
                        {
                        // Mail bauen
                        if($zeile["MailBuero"]!="")
                            {$mailString="<span style=\"color:#0000ff;\">".$zeile["MailBuero"]."</span> <i>(B&uuml;ro)</i>";}
                        else
                            {$mailString="<span style=\"color:#0000ff;\">".$zeile["MailPrivat"]."</span> <i>(Privat)</i>";}
                        if($zeile["MailBuero"]=="" AND $zeile["MailPrivat"]=="")
                            {$mailString="<i>keine E-Mail-Adresse</i>";}
                        // Hintergrundfarbe vorbereiten
                        $cVar = $bgCount % 2;
                        // Ausgabe
                        $ausgabeInhalt.= "<tr>
                        <td bgcolor=\"".$bgcolor[$cVar]."\"><nobr><a href=\"index.php?modus=DAT&inc=KON&id=".$zeile["ID"]."\" style=\"color:#000000;\" target=\"_blank\">".$zeile["Anrede"]." ".$zeile["Vorname"]." ".$zeile["Nachname"]."</a></nobr></td>
                        <td bgcolor=\"".$bgcolor[$cVar]."\"><nobr>".$mailString."</nobr></td>
                        <td bgcolor=\"".$bgcolor[$cVar]."\" class=klein><nobr>".$zeile["Geaendert"]."</nobr></td>
                        </tr>\n";
                        $bgCount++;
                        }
                    $ausgabeInhalt.= "<tr><td colspan=4><hr></td></tr>";
                    }
                }    
            }
        // Doppelte aus SuchArray loeschen
        for($x=0;$x<count($doppeltPool);$x++)
            {
            unset($pool[$doppeltPool[$x]]);
            }
        unset($doppeltPool);
        unset($doppelt);
        }
    $ausgabeFuss.= "</table>\n";
    }
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

// Ausgabe **********************************************
if($ausgabeInhalt){echo $ausgabeKopf.$ausgabeInhalt.$ausgabeFuss;}
else{echo "<p>Zur Zeit sind keine Dubletten in der Datenkrake vorhanden.<br></p><p><a href=\"index.php?modus=DAT&inc=UEB\">Zur&uuml;ck zur &Uuml;bersicht...</p>\n";}


?>
</p>