<?php
//####################################################################################################################

// SCMS Shop-Skript (Frontend)
// """""""""""""""""""""""""""
// Version 0001, Stand 23.01.2009

// INHALT:
// """""""
// UEBERSICHT:          Alle Artikel nach Artikelgruppen sortiert
// EINKAUF:             Uebersicht aller schon eingekauften Artikel
// DETAILS:             Detailansicht eines Artikels
// KASSE:               Zusammenfassung des Einkaufs und Bestaetigung der Bestellung
// SENDEN:              Speichern der Bestellung und senden der Bestellbestaetigung
// BESTELLUNGEN:        Liste aller bisherigen Bestellungen eines Kunden
// SHOPNAVI & MINIKORB: Vorbereitung der ShopNavi und des MiniKorbs fuer das Smarty-Template

//####################################################################################################################


// POST und GET extrahieren
$artId = $_GET["artId"];
$shop = $_GET["shop"];
$del = $_GET["del"];
$minus = $_GET["minus"];
$plus = $_GET["plus"];
$kasse = $_GET["kasse"];
$senden = $_GET["senden"];
$bestellungen = $_GET["bestellungen"];

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);


//####################################################################################################################
// Uebersicht
//####################################################################################################################
if(!$artId AND !$shop AND !$kasse AND !$senden AND !$bestellungen)
	{
	$inhalt.= "<!-- AKTIONEN ################################################################### -->
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
        <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;bestellungen=1\">Bisherige Bestellungen</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";
    if($_SESSION["Shop"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x\">Einkauf ansehen</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
    $inhalt.= "</td></tr>
        </table>
        <!-- /AKTIONEN ################################################################### -->\n";
	
	// Aufruf Uebersicht
	// Daten der Gruppe und des Artikel aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT a.ID, a.Name, a.Preis, a.Online as ArtikelOn, g.Name as Gruppe, g.Online as GruppeOn FROM "._ShopArtikel." a, "._ShopGruppen." g WHERE a.Gruppe=g.ID AND a.Online='1' AND g.Online='1' ORDER BY g.Name, a.Name";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		$alphaAkt = "0";
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($alphaAkt!=$zeile["Gruppe"])
				{
				// Fieldset mit Gruppen bauen
				if($alphaAkt!="0"){$inhalt.="</table>\n</fieldset>\n\n";}
				$inhalt.= "<fieldset>\n<legend style=\"font-size:16px;\">".$zeile["Gruppe"]."</legend>\n<table border=\"0\" cellpadding=\"3\" cellspacing=\"0\" width=\"100%\">\n";
				$alphaAkt = $zeile["Gruppe"];
				}
			// Ausgabe
			$inhalt.= "<tr>
			<td width=\"50%\"><b>&bull;</b>&nbsp;<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;artId=".$zeile["ID"]."\" style=\"color:#000000;\">".$zeile["Name"]."</a></td><td align=\"right\">".number_format($zeile["Preis"],2,',','.')." &euro;</td>
			</tr>\n";
			}
		}
	else{$inhalt.= "Fehler: Es konnte kein Ergebnis fuer die Artikel-Uebersicht ausgelesen werden!<br>\n";}
	
	$inhalt.= "</table>\n</fieldset>\n";

	$inhalt.= "<!-- AKTIONEN ################################################################### -->
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
        <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;bestellungen=1\">Bisherige Bestellungen</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";
    if($_SESSION["Shop"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x\">Einkauf ansehen</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
    $inhalt.= "</td></tr>
        </table>
        <!-- /AKTIONEN ################################################################### -->\n";
	}
//####################################################################################################################
// /Uebersicht
//####################################################################################################################



//####################################################################################################################
// Einkauf
//####################################################################################################################
if($shop)
	{
	$ueberschrift = "Bisheriger Einkauf";
	
	// Einkauf hinzufuegen *************************************
	if($shop!="x")
        {
        // Daten der Gruppe und des Artikel aus DB holen
        // SQL-String bauen
        $sqlString = "SELECT * FROM "._ShopArtikel." WHERE ID='".$shop."' LIMIT 1";
        // Ergebnis auslesen
        $ergebnis = $db -> sql($sqlString);
        if($ergebnis)
            {
            $zeile = mysql_fetch_array($ergebnis);
            }
        else
            {
            echo "Fehler: Es konnte kein Ergebnis fuer den Einkauf ausgelesen werden.";
            }
        $_SESSION["Shop"][$shop]["Name"] = $zeile["Name"];
        $_SESSION["Shop"][$shop]["Menge"]++;
        $_SESSION["Shop"][$shop]["Preis"] = $zeile["Preis"];
        
        $ueberschrift = "Artikel hinzugef&uuml;gt";
        if(!$plus){$aktion = "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;artId=".$zeile["ID"]."\">Zur&uuml;ck zum Artikel</a>";}
        }    
    
    // Menge verringern
    if($minus)
        {
        $_SESSION["Shop"][$minus]["Menge"]--;
        // Artikel entfernen, wenn Menge < 1
        if($_SESSION["Shop"][$minus]["Menge"]<1){$del=$minus;}
        }
    
    // Artikel entfernen
    if($del){unset($_SESSION["Shop"][$del]);}

	// Anzeige MaxiKorb
	if($MaxiKorbShow OR $shop=="x" OR $plus)
        {
        // Ausgabe *************************************************
        $inhalt.= "<h4 style=\"margin:5px 0px 10px 0px;\">".$ueberschrift."</h4>
            <!-- AKTIONEN ################################################################### -->
            <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
        
            <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
            <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";
        if($_SESSION["Shop"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;kasse=x\">Zur Kasse</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
        $inhalt.= $aktion."</td></tr>
            </table>
            <!-- /AKTIONEN ################################################################### -->
            
            <!-- EINKAUF ################################################################### -->
            <fieldset>
            <legend>Schon eingekauft</legend>
            <table border=\"0\" cellspacing=\"0\" cellpadding=\"3\" width=\"100%\">
            <tr>
            <td align=\"center\"><b>Pos</b></td>
            <td><b>Artikel</b></td>
            <td align=\"center\"><b>Menge</b></td>
            <td align=\"right\"><b>Einzel</b></td>
            <td align=\"right\"><b>Summe</b></td>
            <td align=\"center\"><b></b></td>
            </tr>\n";
        
        $c = "1";
        if($_SESSION["Shop"]) // Fehler abfangen bei Session Timeout
            {
            foreach($_SESSION["Shop"] as $key => $item)
                {
                // Ausgabe vorbereiten
                $endpreis = $item["Preis"]*$item["Menge"];
                $inhalt.= "<tr>
                    <td align=\"center\">".$c."</td>
                    <td><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;artId=".$key."\">".$item["Name"]."</a></td>
                    <td align=\"center\"><b><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x&amp;minus=".$key."\" title=\"Menge verringern\" style=\"text-decoration:none;font-size:14px;\"><span class=\"textRot\">-</span></a></b>&nbsp;".$item["Menge"]."&nbsp;<b><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=".$key."&amp;plus=1\" title=\"Menge verg&ouml;&szlig;ern\" style=\"text-decoration:none;font-size:14px;\"><span class=\"textGruen\">+</span></a></b></td>
                    <td align=\"right\">".number_format($item["Preis"],2,',','.')." &euro;</td>
                    <td align=\"right\">".number_format($endpreis,2,',','.')." &euro;</td>
                    <td align=\"center\"><b><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x&amp;del=".$key."\" title=\"Artikel l&ouml;schen\" style=\"text-decoration:none;\"><span class=\"textRot\">X</span></a></b></td>
                    </tr>";
                $c++;
                $total = $total+$endpreis;  
                }
            }
            
        $inhalt.= "<tr><td colspan=\"5\"><hr></td></tr>
            <tr>
            <td colspan=\"4\" align=\"right\"><b>Total:</b></td>
            <td align=\"right\"><b>".number_format($total,2,',','.')." &euro;</b></td></tr>
            <td align=\"center\"><b></b></td>
            </table>\n";
        if($_SESSION["Shop"]){$inhalt.= "<div style=\"float:right\" align=\"center\">
            <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;kasse=x\"><img src=\"".$HttpRoot.$ShopBildPfad."/scmsIcons_checkout.gif\" width=\"40px\" alt=\"Zur Kasse\" border=\"0\" title=\"Zur Kasse\" align=\"absmiddle\"></a>
            <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;kasse=x\">Zur Kasse...</a>
            </div>\n";}
        $inhalt.= "</fieldset>
            <!-- /EINKAUF ################################################################### -->
            
            <!-- AKTIONEN ################################################################### -->
            <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
            <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
            <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";
        if($_SESSION["Shop"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;kasse=x\">Zur Kasse</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
        $inhalt.= $aktion."</td></tr>
            </table>
            <!-- /AKTIONEN ################################################################### -->\n";
        }
    else
        {
        $artId = $shop; // Zurueck zur Artikel-Ansicht, wenn $MaxiKorbShow == false
        }
	}
//####################################################################################################################
// /Einkauf
//####################################################################################################################



//####################################################################################################################
// Details
//####################################################################################################################
if($artId)
	{	
	// Daten des Artikels aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT a.ID, a.Name, a.Beschreibung, a.Preis, a.Bild, a.Online, a.Erzeugt, a.Geaendert, g.Name as GruppenName FROM "._ShopArtikel." a, "._ShopGruppen." g WHERE a.ID='".$artId."' AND a.Online='1' AND a.Gruppe=g.ID LIMIT 1";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
	   {
	   // Testen, ob es einen Artikel gibt
	   if(mysql_num_rows($ergebnis))
	       {
	       $zeile = mysql_fetch_array($ergebnis);
            // Bild vorbereiten
            if($zeile["Bild"])
                {
                $bildgroesse = getimagesize($ServerRoot.$ShopBildPfad."/".$zeile["Bild"]);
                $daeumling["0"] = 150-20;
                $daeumling["1"] = ($bildgroesse["1"]/($bildgroesse["0"]/150))-20;
                
                $bildTag = "<div style=\"position:relative; z-index:0; width:".$bildgroesse["0"]."; height:".$bildgroesse["1"]."; float:left;\">
                    <div style=\"position:absolute; top:".$daeumling["1"]."px; left:".$daeumling["0"]."px; z-index:200;\">
                    <a href=\"".$HttpRoot.$ShopBildPfad."/".$zeile["Bild"]."\" onclick=\"window.open('".$HttpRoot.$ShopBildPfad."/".$zeile["Bild"]."','','toolbar=no,menubar=no,status=no,width=".$bildgroesse["0"].",height=".$bildgroesse["1"]."');return false;\" title=\"Klicken zum Vergr&ouml;&szlig;ern\"><img src=\"".$HttpRoot.$ShopBildPfad."/scmsIcons_lupe.gif\" width=\"20px\" alt=\"Klicken zum Vergr&ouml;&szlig;ern\" border=\"0\"></a>
                    </div>
                    </div>
                    
                    <a href=\"".$HttpRoot.$ShopBildPfad."/".$zeile["Bild"]."\" onclick=\"window.open('".$HttpRoot.$ShopBildPfad."/".$zeile["Bild"]."','','toolbar=no,menubar=no,status=no,width=".$bildgroesse["0"].",height=".$bildgroesse["1"]."');return false;\" title=\"Klicken zum Vergr&ouml;&szlig;ern\"><img src=\"".$HttpRoot.$ShopBildPfad."/".$zeile["Bild"]."\" width=\"150px\" alt=\"".$zeile["Name"]."\" border=\"0\" class=\"left\"></a>
                
                    ";
                }
            else{$bildTag = "";}
            
            $inhalt.= "<h5>".$zeile["GruppenName"].":</h5>
                <h4 style=\"margin:5px 0px 10px 0px;\">&raquo;".$zeile["Name"]."&laquo;</h4>
                <!-- AKTIONEN ################################################################### -->
                <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
        
                <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
                <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";
            if($_SESSION["Shop"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x\">Einkauf ansehen</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
            $inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=".$artId."\" onClick=\"opacity('shopAdd', 100, 0, 400)\">Artikel einkaufen</a>&nbsp;&nbsp;&nbsp;&nbsp;
                </td></tr>
                </table>
                <!-- /AKTIONEN ################################################################### -->
                
                <!-- ARTIKEL ################################################################### -->
                <fieldset>
                <legend>Beschreibung</legend>
                <div style=\"float:right;\" align=\"center\">
                <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=".$artId."\" onClick=\"opacity('shopAdd', 100, 0, 400)\"><img src=\"".$HttpRoot.$ShopBildPfad."/scmsIcons_shop.gif\" width=\"60px\" alt=\"Einkauf\" border=\"0\" title=\"".$zeile["Name"]." einkaufen\"></a>
                <h3>".number_format($zeile["Preis"],2,',','.')." &euro</h3>
                </div>
                ".$bildTag.nl2br(stripslashes($zeile["Beschreibung"]))."
                </fieldset>
                <!-- /ARTIKEL ################################################################### -->
                
                <!-- AKTIONEN ################################################################### -->
                <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
                <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
                <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";
            if($_SESSION["Shop"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x\">Einkauf ansehen</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
            $inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=".$artId."\" onClick=\"opacity('shopAdd', 100, 0, 400)\">Artikel einkaufen</a>&nbsp;&nbsp;&nbsp;&nbsp;
                </td></tr>
                </table>
                <!-- /AKTIONEN ################################################################### -->\n";
	       }
	   // Artikel nicht vorhanden
	   else{$inhalt.= "<h3>Artikel nicht vorhanden</h3>
	       <p>Leider ist keine Artikel mit dieser ArtID in unserem Shop vorhanden.</p>
	       <p><a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&laquo; zur&uuml;ck zur &Uuml;bersicht</a></p>";}
	   }
	else{$inhalt.= "Fehler: Es konnte kein Ergebnis fuer die ArtikelDetails ausgelesen werden!<br>\n";}
	}
//####################################################################################################################
// /Details
//####################################################################################################################



//####################################################################################################################
// Kasse
//####################################################################################################################
if($kasse)
	{	
	// Ausgabe *************************************************
    $inhalt.= "<h4 style=\"margin:5px 0px 10px 0px;\">Kasse</h4>
        <!-- AKTIONEN ################################################################### -->
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">

        <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";
    if($_SESSION["Shop"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x\">Einkauf anpassen</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
    if($_SESSION["UserAuth"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;senden=x\">Bestellung senden</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
    $inhalt.= "</td></tr>
        </table>
        <!-- /AKTIONEN ################################################################### -->
        
        <!-- KASSE ################################################################### -->\n";
    // Kassenansicht *******************************************
    if($_SESSION["UserAuth"])
        {
        $inhalt.= "<fieldset>
            <legend>Zusammenfassung</legend>
                    
            <h5>Einkauf:</h5>
            
            <p>
            <table border=\"0\" cellspacing=\"0\" cellpadding=\"3\" width=\"100%\">
            <tr>
            <td align=\"center\"><b>Pos</b></td>
            <td><b>Artikel</b></td>
            <td align=\"center\"><b>Menge</b></td>
            <td align=\"right\"><b>Einzel</b></td>
            <td align=\"right\"><b>Summe</b></td>
            </tr>\n";
        
        $c = "1";    
        foreach($_SESSION["Shop"] as $key => $item)
            {
            // Ausgabe vorbereiten
            $endpreis = $item["Preis"]*$item["Menge"];
            $inhalt.= "<tr>
                <td align=\"center\">".$c."</td>
                <td>".$item["Name"]."</td>
                <td align=\"center\">".$item["Menge"]."</td>
                <td align=\"right\">".number_format($item["Preis"],2,',','.')." &euro;</td>
                <td align=\"right\">".number_format($endpreis,2,',','.')." &euro;</td>
                </tr>";
            $c++;
            $total = $total+$endpreis;  
            }
            
        $inhalt.= "<tr><td colspan=\"5\"><hr></td></tr>
            <tr>
            <td colspan=\"4\" align=\"right\"><b>Total:</b></td>
            <td align=\"right\"><b>".number_format($total,2,',','.')." &euro;</b></td></tr>
            </table>
            </p>
            
            <h5>Rechnungs- &amp; Lieferadresse:</h5>
            
            <div style=\"float:right\" align=\"center\">
            <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;senden=x\"><img src=\"".$HttpRoot.$ShopBildPfad."/scmsIcons_checkout.gif\" width=\"60px\" alt=\"Bestellung senden\" border=\"0\" title=\"Bestellung senden\"></a><br>
            <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;senden=x\">Bestellung senden</a>
            </div>
            
            <p style=\"float:left\">
            ".$_SESSION["UserAnrede"]." ".$_SESSION["UserVorname"]." ".$_SESSION["UserNachname"]."<br>
            ".$_SESSION["UserStrasse"]."<br>
            ".$_SESSION["UserPLZ"]." ".$_SESSION["UserOrt"]."<br>
            ".$_SESSION["UserMail"]."
            </p>        
            </fieldset>\n";
        }
    // Nicht angemeldet ****************************************
    else
        {
        $inhalt.= "<fieldset>
            <legend>Bitte anmelden!</legend>
            Sie sind zur Zeit an der Website nicht angemeldet. Bitte authentifizieren Sie sich mit Ihrem Login und Passwort und gehen Sie dann wieder zur Kasse des Shops.<br>
            <br>
            Sollten Sie noch keine Zugangsdaten besitzen, dann schreiben Sie uns eine Mail an <a href=\"mailto:".$MailInfo."\">".$MailInfo."</a>.
            </fieldset>\n";
        }
    $inhalt.= "<!-- /KASSE ################################################################### -->
        
        <!-- AKTIONEN ################################################################### -->
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
        <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";
    if($_SESSION["Shop"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x\">Einkauf anpassen</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
    if($_SESSION["UserAuth"]){$inhalt.= "<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;senden=x\">Bestellung senden</a>&nbsp;&nbsp;&nbsp;&nbsp;\n";}
    $inhalt.= "</td></tr>
        </table>
        <!-- /AKTIONEN ################################################################### -->\n";
	}
//####################################################################################################################
// /Kasse
//####################################################################################################################



//####################################################################################################################
// Senden
//####################################################################################################################
if($senden AND $_SESSION["Shop"] AND $_SESSION["UserAuth"])
	{
	// Ausgabe *************************************************
    $inhalt.= "<h4 style=\"margin:5px 0px 10px 0px;\">Bestellung versandt</h4>
        <!-- AKTIONEN ################################################################### -->
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
        <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;
        </td></tr>
        </table>
        <!-- /AKTIONEN ################################################################### -->
        
        <!-- BESTELLUNG ################################################################### -->\n";
    // Bestellung senden *******************************************
    
    // Bestellung in DB schreiben
    // SQL-String bauen
    $sqlString = "INSERT INTO "._ShopBestellungen." (NutzerID,Status,Erzeugt,Geaendert) VALUES ('".$_SESSION["UserId"]."','1','".datetimemaker(time())."','".datetimemaker(time())."')";
    // In DB einfuegen
    $ergebnis = $db -> sql($sqlString);
    // BID auslesen
    if($ergebnis){$bid = mysql_insert_id();}
    else{$fehler.="<li>Die Bestellung konnte nicht in die Datenbank geschrieben werden.";}
    
    // Position in DB schreiben
    foreach($_SESSION["Shop"] as $key => $item)
        {
        // SQL-String bauen
        $sqlString = "INSERT INTO "._ShopPositionen." (BesID,ArtID,Name,Menge,Preis,Erzeugt,Geaendert) VALUES ('".$bid."','".$key."','".$item["Name"]."','".$item["Menge"]."','".$item["Preis"]."','".datetimemaker(time())."','".datetimemaker(time())."')";
        // In DB einfuegen
        $ergebnis = $db -> sql($sqlString);
        // PID auslesen
        if($ergebnis){$pid = mysql_insert_id();}
        else{$fehler.="<li>Die Position ".$key." konnte nicht in die Datenbank geschrieben werden.";}
        }
    
    // Mail mit Bestellbestaetigung
    $to = $_SESSION["UserMail"];
    // Debug: $to = "info@wexelwirken.de";
    $subject = "Ihre Bestellung im SimpelCMS Demo-Shop";
    $message = "Hallo ".$_SESSION["UserAnrede"]." ".$_SESSION["UserNachname"].",<br>\r\n<br>\r\n";
    $message.= "Vielen Dank f&uuml;r Ihre Bestellung in unserem Online-Shop.<br>\r\n<br>\r\n";
    // Bestellung
    $message.= "<h3>Ihre Einkauf</h3><p>
            <table border=\"0\" cellspacing=\"0\" cellpadding=\"3\" width=\"100%\">
            <tr>
            <td align=\"center\"><b>Pos</b></td>
            <td><b>Artikel</b></td>
            <td align=\"center\"><b>ArtID</b></td>
            <td align=\"center\"><b>Menge</b></td>
            <td align=\"right\"><b>Einzel</b></td>
            <td align=\"right\"><b>Summe</b></td>
            </tr>\r\n";
        
        $c = "1";    
        foreach($_SESSION["Shop"] as $key => $item)
            {
            // Ausgabe vorbereiten
            $endpreis = $item["Preis"]*$item["Menge"];
            $message.= "<tr>
                <td align=\"center\">".$c."</td>
                <td>".$item["Name"]."</td>
                <td align=\"center\">".$key."</td>
                <td align=\"center\">".$item["Menge"]."</td>
                <td align=\"right\">".number_format($item["Preis"],2,',','.')." &euro;</td>
                <td align=\"right\">".number_format($endpreis,2,',','.')." &euro;</td>
                </tr>\r\n";
            $c++;
            $total = $total+$endpreis;  
            }
            
        $message.= "<tr><td colspan=\"6\"><hr></td></tr>
            <tr>
            <td colspan=\"5\" align=\"right\"><b>Total:</b></td>
            <td align=\"right\"><b>".number_format($total,2,',','.')." &euro;</b></td></tr>
            </table>
            </p>
            <h3>Ihre Rechnungs- &amp; Lieferadresse:</h3>
            
            <p>
            ".$_SESSION["UserAnrede"]." ".$_SESSION["UserVorname"]." ".$_SESSION["UserNachname"]."<br>
            ".$_SESSION["UserStrasse"]."<br>
            ".$_SESSION["UserPLZ"]." ".$_SESSION["UserOrt"]."<br>
            ".$_SESSION["UserMail"]."
            </p><br>\r\n";
    
    $message.= "Die bestellten Artikel werden in den n&auml;chsten Tagen an Sie ausgeliefert. Falls Sie Fragen haben, dann schreiben Sie uns eine Mail an <a href=\"mailto:".$MailInfo."\">".$MailInfo."</a>.<br>\r\n<br>\r\n";
    $message.= "Mit freundlichen Gr&uuml;&szlig;en,<br>\r\n";
    $message.= "Ihr SimpelCMS Demo-Shop<br>\r\n";
    
    // "Content-type"-Header.
    $headers  = "MIME-Version: 1.0\r\n";
    $headers .= "Content-type: text/html; charset=utf-8\r\n";

    // zusaetzliche Header
    $headers .= "From: ".$MailInfo." <".$MailInfo.">\r\n";
    $headers .= "CC: ".$MailInfo." <".$MailInfo.">\r\n";

    // Verschicken der Mail
    if(!mail($to, $subject, $message, $headers)){$fehler.="<li>Die Bestellbest&auml;tigung konnte nicht per eMail versandt werden.";}
    
    
    if(!$fehler)
        {
        // Erfolgsmeldung
        $inhalt.= "<fieldset>
            <legend>Bestellung gesendet</legend>
            Ihre Bestellung wurde <b>erfolgreich</b> an uns weitergeleitet. Es wurde eine Bestellbest&auml;tigung an Ihre Mailadresse (".$_SESSION["UserMail"].") versandt. In wenigen Tagen werden die bestellten Artikel an Sie ausgeliefert.<br>
            <br>
            Vielen Dank f&uuml;r Ihre Bestellung! 
            </fieldset>\n";
        // Shop-Session loeschen
        unset($_SESSION["Shop"]);
        }
    // Fehler ****************************************
    else
        {
        $inhalt.= "<fieldset>
            <legend>Fehler!</legend>
            Es ist ein technischer Fehler aufgetreten:<br>
            <ul>
            ".$fehler."
            </ul>
            Daher konnte Ihre Bestellung nicht an uns versandt werden. Bitte versuchen Sie es erneut.<br>
            <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;senden=x\"><img src=\"".$HttpRoot.$ShopBildPfad."/scmsIcons_checkout.gif\" width=\"40px\" alt=\"Bestellung erneut senden...\" border=\"0\" title=\"Bestellung erneut senden...\" align=\"absmiddle\"></a>
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;senden=x\">Bestellung erneut senden...</a>
            <br><br>
            Sollte dieser Fehler erneut auftreten, dann schreiben Sie uns eine Mail an <a href=\"mailto:".$MailInfo."\">".$MailInfo."</a>.
            </fieldset>\n";
        }
    $inhalt.= "<!-- /BESTELLUNG ################################################################### -->
        
        <!-- AKTIONEN ################################################################### -->
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">
        <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;
        </td></tr>
        </table>
        <!-- /AKTIONEN ################################################################### -->\n";
	}
//####################################################################################################################
// /Senden
//####################################################################################################################



//####################################################################################################################
// Bestellungen
//####################################################################################################################
if($bestellungen)
	{
	$inhalt.= "<!-- AKTIONEN ################################################################### -->
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">

        <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;
        </td></tr>
        </table>
        <!-- /AKTIONEN ################################################################### -->\n";
	
    // Bisherige Bestellungen
    if($_SESSION["UserAuth"])
        {
        $inhalt.="<fieldset>
            <legend>Bisherige Bestellungen</legend>\n";
        
        // Vorhandene Bestellungen fuer Nutzer aus DB holen +++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // SQL-String bauen
        $sqlString = "SELECT b.ID as BID, b.NutzerID as NID, b.Status, b.Erzeugt, b.Geaendert, n.Anrede, n.Vorname, n.Nachname FROM "._ShopBestellungen." b, "._DBuserauth." n WHERE b.NutzerID=n.ID AND b.NutzerID=".$_SESSION["UserId"]." ORDER BY b.Status, b.Erzeugt DESC";
        
        // Ergebnis auslesen
        $ergebnis = $db -> sql($sqlString);
        
        if($ergebnis)
            {
            if(mysql_num_rows($ergebnis))
                {
                $inhalt.="<p style=\"margin:0px 5px 5px 5px;\">Hier eine &Uuml;bersicht all Ihrer bisherigen Bestellungen bei uns. Wenn Sie m&ouml;chten, k&ouml;nnen Sie diese erneut Ihrem aktuellen Warenkorb hinzuf&uuml;gen.</p>
                    
                    <table border=\"0\" cellspacing=\"0\" cellpadding=\"3\" width=\"100%\">
                    
                    <tr>
                    <td style=\"border-bottom:1px solid #666666;\" align=\"left\"><b>Datum</b></td>
                    <td style=\"border-bottom:1px solid #666666;\" align=\"left\"><b>Arikel</b></td>
                    <td style=\"border-bottom:1px solid #666666;\" align=\"center\"><b>Summe</b></td>
                    <td style=\"border-bottom:1px solid #666666;\" align=\"center\"><b>Status</b></td>
                    <td style=\"border-bottom:1px solid #666666;\" align=\"center\"><b>Aktionen</b></td>
                    </tr>";
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
                    
                    // Ausgabe Bestellung
                    $inhalt.= "<tr>
                        <td>".$datum["Tag"].".".$datum["Monat"].".".$datum["Jahr"]."</td>
                        <td class=\"nobr\">Liste der Artikel:</td>
                        <td align=\"right\"><b>".number_format($umsatz["Umsatz"],2,',','.')." &euro;</b></td>
                        <td align=\"center\">".$statusTag."</td>
                        <td align=\"center\" class=\"nobr\">erneut</td>
                        </tr>";
    
                    // Daten der Positionen aus DB holen
                    // SQL-String bauen
                    $sqlStringP = "SELECT * FROM "._ShopPositionen." WHERE BesID='".$zeile["BID"]."' ORDER BY Erzeugt";
                    
                    // Ergebnis auslesen
                    $ergebnisP = $db -> sql($sqlStringP);
                    if($ergebnisP)
                        {                        
                        while($bestellung = mysql_fetch_array($ergebnisP))
                            {            
                            // Ausgabe Positionen
                            $endpreis = $bestellung["Preis"]*$bestellung["Menge"];
                            
                            $inhalt.= "<tr>
                                <td class=\"nobr klein\">&nbsp;</td>
                                <td class=\"nobr klein\">".$bestellung["Menge"]."x <a href=\"index.php?id=64&amp;ord=45&amp;artId=".$bestellung["ArtID"]."\">".$bestellung["Name"]."</a></td>
                                <td align=\"right\" class=\"nobr klein\">".number_format($endpreis,2,',','.')." &euro;</td>
                                <td align=\"center\" class=\"nobr klein\">&nbsp;</td>
                                <td align=\"center\" class=\"nobr klein\"><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=".$bestellung["ArtID"]."&amp;shop=".$bestellung["ArtID"]."\" onClick=\"opacity('shopAdd', 100, 0, 400)\">bestellen</a></td>
                                </tr>\n";
                            }
                        $inhalt.= "<tr><td style=\"border-top:1px solid #7799aa;\" colspan=\"6\" class=\"nobr kleiner\">&nbsp;</td></tr>";
                        }
                    else{echo "Fehler: Es konnte kein Ergebnis fuer die Positionen ausgelesen werden!<br>\n";}
                    mysql_free_result($ergebnisP);
                    }
                    $inhalt.= "</table>\n";
                }
            // Keine Bestellungen vorhanden
            else
                {
                $inhalt.= "<p style=\"margin:0px 5px 5px 5px;\">Es sind keine bisherigen Bestellungen gespeichert.</p>\n";
                }
            }
        else{$inhalt.= "Fehler: Es konnte kein Ergebnis fuer die Bestelluebersicht ausgelesen werden!<br>\n";}
        mysql_free_result($ergebnis);

        $inhalt.= "</fieldset>\n";
        }
    // Nutzer nicht angemeldet
    else
        {
        $inhalt.="<h4>Bitte anmelden</h4>
            <p>Bitte melden Sie sich mit Ihren Zugangsdaten an, um Ihr bisherigen Bestellungen anzusehen.</p>";
        }

	$inhalt.= "<!-- AKTIONEN ################################################################### -->
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"3\" width=\"100%\" class=\"aktionen\">

        <tr><td align=\"left\" valign=\"top\" width=\"75\"><b>Aktionen:</b></td><td align=\"left\" valign=\"top\">
        <a href=\"index.php?id=".$id."&amp;ord=".$ord."\">&Uuml;bersicht</a>&nbsp;&nbsp;&nbsp;&nbsp;
        </td></tr>
        </table>
        <!-- /AKTIONEN ################################################################### -->\n";
	}
//####################################################################################################################
// /Bestellungen
//####################################################################################################################

//####################################################################################################################
// ShopNavi & MiniKorb
//####################################################################################################################

// ShopNavi bauen
if($ShopNaviShow)
    {
    if($ShopId==$id){$shopNavi = ShopNavi();}
    $smarty->assign("shopNavi",$shopNavi);
    }
    
// MiniKorb bauen
if($MiniKorbShow)
    {
    if($_SESSION["Shop"]){$miniKorb = MiniKorb();}
    $smarty->assign("miniKorb",$miniKorb);
    }

//####################################################################################################################
// /ShopNavi & MiniKorb
//####################################################################################################################
?>