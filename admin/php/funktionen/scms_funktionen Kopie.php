<?php

/*******************************************

SCMS-Funktionen
"""""""""""""""

Die Datei beinhaltet Skripte, die besondere
Funkionaltitaeten fur SimpelCMS v08/15 erzeugen.

Copyleft by weXelwirken 2009
********************************************/

// echo "<!-- SCMS-Funktionen einbinden -->\n";

//===============================================================================
// AdminDokOrd
// """""""""""
// Beschreibung: Gibt fur die Admin-Ansicht fur einen vorgegebenen Ordner alle zugeordenten Dokumente mit deren Status aus (On/Off, Position, Sprache).
// Verwendung:	./admin/php/funktionen/scms_funktionen.php -> AdminDokumentenOrdBaum()

function AdminDokOrd($ordner, $ebene, $lang)
	{
	// Globals
	global $ScmsLang, $db;
	
	// SeitenDaten aus DB holen
	// Lang vorbereiten
	if($ScmsLang){$sqlLang="Lang='".$lang."' AND ";}
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBdokumente." WHERE ".$sqlLang."Ordner='".$ordner."' ORDER BY Position";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			// On/Offline vorbereiten
			if($zeile["Online"]=="1"){$onOff="Gruen";}else{$onOff="Rot";}
			// AnzeigeLinktext vorbereiten
			if($zeile["AnzeigeLinktext"]=="0"){$link=" <span style=\"color:#FF9900; text-decoration:line-through;\">Linktext</span>";}else{$link="";}
			// Auth vorbereiten
			if($zeile["Auth"]=="-1"){$authColor=" style=\"color:#FF9900\"";}
			if($zeile["Auth"]=="0"){$authColor="";}
			if($zeile["Auth"]=="1"){$authColor=" style=\"color:#FF0000\"";}
			// Lang vorbereiten
			if($ScmsLang){$langAnzeige="|<i><b>".$zeile["Lang"]."</b></i>";}
            
            echo "<tr><td>".$ebene."&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src=\"img/scmsIcons_dok_".$zeile["Typ"].".gif\" width=\"25\" border=\"0\" alt=\"".$zeile["Typ"]."\" align=\"absmiddle\">&nbsp;<a href=\"index.php?modus=DOK&inc=DUE&id=".$zeile["ID"]."\"".$authColor.">".stripslashes($zeile["Linktext"])."</a></td><td><span class=\"text".$onOff."\">[".$zeile["Position"].$langAnzeige."]</span>".$link."<br></td></tr>\n";
            }

		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion AdminDokOrd ausgelesen werden!<br>\n";}
	}

//===============================================================================
// AdminDokOrdBaum
// """""""""""""""
// Beschreibung: Gibt fur die Admin-Ansicht alle Dokumente im Ordner-Baum mit zugehorigem Status aus (On/Off, Position)
// Verwendung:	.admin/inc/DOK/DUE.inc

function AdminDokOrdBaum($mutter, $mutterAlt, $ebene, $check, $lang)
	{
	// Globals
	global $ScmsLang, $db;
	
	// Parameter initialisieren
	if($mutter==""){$mutter=0;}
	if($mutterAlt==""){$mutterAlt=0;}
	
	// Dokumente in Wurzel ausgeben
	if($check==""){AdminDokOrd("0", $ebene, $lang); $check=1;}
	
	// OrdnerDaten aus DB holen
	// Lang vorbereiten
	if($ScmsLang){$sqlLang="Lang='".$lang."' AND ";}
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBordner." WHERE ".$sqlLang."Mutter='".$mutter."' ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($mutter!=$mutterAlt){$ebene=$ebene."&nbsp;&nbsp;&nbsp;";}
			$mutterAlt = $mutter;
			// Auth vorbereiten
			if($zeile["Auth"]=="-1"){$authColor=" style=\"color:#FF9900\"";}
			if($zeile["Auth"]=="0"){$authColor="";}
			if($zeile["Auth"]=="1"){$authColor=" style=\"color:#FF0000\"";}
			echo "<tr><td colspan=\"2\" style=\"padding-top:10px;\">".$ebene."&nbsp;<img src=\"img/scmsIcons_ord.gif\" width=\"30\" border=\"0\" alt=\"Ordner\" align=\"absmiddle\">&nbsp;<b".$authColor." style=\"line-height:23px;font-size:14px\">".stripslashes($zeile["Name"])."</b><br></td></tr>\n";
			AdminDokOrd($zeile["ID"], $ebene, $lang);
			AdminDokOrdBaum($zeile["ID"], $mutterAlt, $ebene, $check, $lang);
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion AdminDokOrdBaum ausgelesen werden!<br>\n";}
	}

//===============================================================================
// DokOrd
// """"""
// Beschreibung: Gibt alle Dokumente eines Ordners aus. Ueber den Flag $online=1 koennen alle im Modus offline befindlichen Dokumente ausgeblendet werden.
// Verwendung:  ./admin/php/funktionen/scms-funktionen.inc => DokOrdBaum()

function DokOrd($ordner, $ebene, $online, $userAuth)
	{
	// Globals
	global $ScmsLang, $db;
	
	// DokumentenDaten aus DB holen
	// SQL-String bauen
	if($online=="1"){$ifOnline = " AND Online='1'";}
	if($userAuth){if(!$_SESSION["UserAuth"]){$ifAuth = " AND (Auth BETWEEN '-1' AND '0')";}else{$ifAuth = " AND (Auth BETWEEN '0' AND '1')";}}
	if($ScmsLang){$ifLang = " AND Lang='".$_SESSION["Lang"]."'";}
    $sqlString = "SELECT * FROM "._DBdokumente." WHERE AnzeigeLinktext='1' AND Ordner='".$ordner."'".$ifOnline.$ifAuth.$ifLang." ORDER BY Position";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			$out.= $ebene."<b>&bull;</b>&nbsp;<a href=\"index.php?id=".$zeile["ID"]."\">".stripslashes($zeile["Linktext"])."</a><br>\n";
			}
		}
	else{$out = "Fehler: Es konnte kein Ergebnis fuer die Funktion DokOrd ausgelesen werden!<br>\n";}
	return $out;
	}

//===============================================================================
// DokOrdBaum
// """"""""""
// Beschreibung: Gibt den vollstaendigen Baum des CMS-Inhalts mit entsprechenden Einrueckungen aus. Ueber den Flag $online=1 koennen alle im Modus offline befindliche Seiten ausgeblendet werden.
// Verwendung:  ./inc/sitemap.php

function DokOrdBaum($mutter, $mutterAlt, $dbSeite, $ebene, $check, $online, $userAuth)
	{
	// Globals
	global $ScmsLang, $db;
	
	// Parameter initialisieren
	if($mutter==""){$mutter=0;}
	if($mutterAlt==""){$mutterAlt=0;}
	
	// Dokumente in Wurzel ausgeben
	if($check==""){$out.= DokOrd("0", $ebene, $online, $userAuth); $check=1;}
	
	// KategorieDaten aus DB holen
	// SQL-String bauen
	if($online=="1"){$ifOnline = " AND Online='1'";}
	if($userAuth){if(!$_SESSION["UserAuth"]){$ifAuth = " AND (Auth BETWEEN '-1' AND '0')";}else{$ifAuth = " AND (Auth BETWEEN '0' AND '1')";}}
	if($ScmsLang){$ifLang = " AND Lang='".$_SESSION["Lang"]."'";}
	$sqlString = "SELECT * FROM "._DBordner." WHERE Mutter='".$mutter."'".$ifOnline.$ifAuth.$ifLang." ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($mutter!=$mutterAlt){$ebene=$ebene."&nbsp;&nbsp;&nbsp;";}
			$mutterAlt = $mutter;
			$out.= "<br>".$ebene."<b>".stripslashes($zeile["Name"])."</b><br>\n";
			$out.= DokOrd($zeile["ID"], $ebene, $online, $userAuth);
			$out.= DokOrdBaum($zeile["ID"], $mutterAlt, $dbSeite, $ebene, $check, $online, $userAuth);
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion DokOrdBaum ausgelesen werden!<br>\n";}
	return $out;
	}

//===============================================================================
// DokOrdOpt
// Beschreibung: Liefert den vorhandenen Ordnerbaum als <option>-Liste
// Verwendung:  ./admin/inc/DOK/DAN.inc
//              ./admin/inc/DOK/DAE.inc

function DokOrdOpt($mutter, $mutterAlt, $mutterAkt, $mutterName, $ebene, $id)
	{
	//Globals
	global $ScmsLang, $db, $_SESSION;
	
	// Parameter initialisieren
	if($mutter==""){$mutter=0;}
	if($mutterAlt==""){$mutterAlt=0;}
	
	// OrdnerDaten aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBordner." WHERE Mutter='".$mutter."' ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($mutter!=$mutterAlt){$ebene=$ebene.$mutterName." / ";}
			$mutterAlt = $mutter;
			if($mutterAkt==$zeile["ID"]){$selected=" selected";}else{if($_SESSION["DAN"]["ordner"]==$zeile["ID"]){$selected=" selected";}else{$selected="";}}
			if($ScmsLang){$langOut=" [".$zeile["Lang"]."]";}
			echo "<option value=\"".$zeile["ID"]."\"".$selected.">".$ebene.stripslashes($zeile["Name"]).$langOut."</option>\n";
			OrdPfadBaumOpt($zeile["ID"], $mutterAlt, $mutterAkt, $zeile["Name"], $ebene, $id);
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion DokOrdOpt ausgelesen werden!<br>\n";}
	}

//===============================================================================
// KlappNaviDok
// """"""""""""
// Beschreibung: Gibt den vollstaendigen Baum des CMS-Inhalts mit entsprechenden Einrueckungen und Klappmechanismus aus.
// Verwendung:  ./admin/php/funktionen/scms-funktionen.inc => KlappNaviBaum()

function KlappNaviDok($ordner)
	{
	// Globals
	global $ScmsLang, $ScmsAuth, $db, $ModRewrite;
	
	// DokumentenDaten aus DB holen
	// SQL-String bauen
	if($ScmsAuth){if(!$_SESSION["UserAuth"]){$ifAuth = " AND (Auth BETWEEN '-1' AND '0')";}else{$ifAuth = " AND (Auth BETWEEN '0' AND '1')";}}
	if($ScmsLang){$ifLang = " AND Lang='".$_SESSION["Lang"]."'";}
    $sqlString = "SELECT * FROM "._DBdokumente." WHERE AnzeigeLinktext='1' AND Ordner='".$ordner."' AND Online='1'".$ifLang.$ifAuth." ORDER BY Position";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			// mod_Rewrite?
			if($ModRewrite){$link=LinkRewrite($zeile["ID"]);}
			else{$link="index.php?id=".$zeile["ID"]."&amp;ord=".$ordner;}
			
			$out.= "<b>&bull;</b>&nbsp;<a href=\"".$link."\" class=\"naviItem\">".stripslashes($zeile["Linktext"])."</a><br>\n";
			}
		}
	else{$out = "Fehler: Es konnte kein Ergebnis fuer die Funktion KlappNaviDok ausgelesen werden!<br>\n";}
	return $out;
	}

//===============================================================================
// KlappNaviBaum
// """""""""""""
// Beschreibung: Gibt den vollstaendigen Baum des CMS-Inhalts mit entsprechenden Einrueckungen aus. Ueber den Flag $online=1 koennen alle im Modus offline befindlichen Dokumente ausgeblendet werden.
// Verwendung:  ./index.php

function KlappNaviBaum($mutter, $mutterAlt, $check, $ordPfadArray)
	{
	// Globals
	global $ScmsLang, $ScmsAuth, $db;
	
	// Parameter initialisieren
	if(!$mutter){$mutter="0";}
	if(!$mutterAlt){$mutterAlt="0";}
	
	// Seiten in Wurzel ausgeben
	if(!$check){$out.= "<div class=\"naviPos\">\n".KlappNaviDok("0")."\n</div>"; $check=1;}
	
	// OrdnerDaten aus DB holen
	// SQL-String bauen
	if($ScmsAuth){if(!$_SESSION["UserAuth"]){$ifAuth = " AND (Auth BETWEEN '-1' AND '0')";}else{$ifAuth = " AND (Auth BETWEEN '0' AND '1')";}}
	if($ScmsLang){$ifLang = " AND Lang='".$_SESSION["Lang"]."'";}
	$sqlString = "SELECT * FROM "._DBordner." WHERE Mutter='".$mutter."' AND Online='1'".$ifAuth.$ifLang." ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			// Hoechste ID des Ordners auslesen
            // SQL-String bauen
            if($ScmsAuth){if(!$_SESSION["UserAuth"]){$ifAuth = " AND (Auth BETWEEN '-1' AND '0')";}else{$ifAuth = " AND (Auth BETWEEN '0' AND '1')";}}
            if($ScmsLang){$ifLang = " AND Lang='".$_SESSION["Lang"]."'";}
            $sqlStringDokId = "SELECT ID FROM "._DBdokumente." WHERE Ordner='".$zeile["ID"]."' AND Online='1'".$ifLang.$ifAuth." ORDER BY Position ASC LIMIT 1";
            // Ergebnis auslesen
            $ergebnisDokId = $db -> sql($sqlStringDokId);
            $dokId = mysql_fetch_array($ergebnisDokId);
			
			// Mutter auf alt setzen
			$mutterAlt = $mutter;
			// Display laden
			if(in_array($zeile["ID"],$ordPfadArray)){$display="blockXXXXX";}else{$display="none";}
			$out.= "<div class=\"naviPos\"><a href=\"index.php?id=".$dokId["ID"]."&amp;ord=".$zeile["ID"]."\" class=\"naviOrd\">".stripslashes($zeile["Name"])."</a><br>\n";
			$out.= "<span style=\"display:".$display.";\">\n";
			$out.= KlappNaviDok($zeile["ID"]);
			$out.= KlappNaviBaum($zeile["ID"], $mutterAlt,$check, $ordPfadArray);
			$out.= "</span>\n</div>\n";
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion KlappNaviBaum ausgelesen werden!<br>\n";}
	return $out;
	}
	
//===============================================================================
// LinkRewrite
// """"""""""
// Beschreibung: Gibt fuer einen gegeben ID dden Rewrite-Pafd zurueck
// Verwendung:	./admin/php/funktionen/scms-funktionen.inc => KlappNaviDok()
//				./admin/inc/DOK/DUE.inc

function LinkRewrite($id)
	{
	// Globals
	global $db, $ModRewrite, $Suffix, $ServerRoot, $ServerRootPath;
	
    // Dokumentenbaum auslesen ******************************
    // SQL-String bauen
    $sqlString = "SELECT ID, Ordner, Linktext FROM "._DBdokumente." WHERE ID='".$id."'";
    // Ergebnis auslesen
    $ergebnis = $db -> sql($sqlString);
    if($ergebnis)
        {
        $zeile = mysql_fetch_array($ergebnis);
        // Rewrite-Pfad erzeugen ******************************
        $pfad = WoBinIch($zeile["Ordner"], "_", $ordPfad);              // Pfad erzeugen
        if($zeile["Ordner"]!="0"){$pfad.="_";}                          // Trenner einbauen
        $rohpfad = $pfad.stripslashes($zeile["Linktext"]);              // Rohpfad erzeugen
        $rohpfad = Umlaute($rohpfad);                                   // Umlaute ersetzen
        $rohpfad = strip_tags($rohpfad);                                // Sonderzeichen in HTML wandeln
        $rohpfad = str_replace("'", "", $rohpfad);                      // Anfuehrungstriche ersetzen
        $rohpfad = str_replace("\"", "", $rohpfad);                     // Anfuehrungstriche ersetzen
        $rohpfad = str_replace(" ", "_", $rohpfad);                     // Leerzeichen ersetzen
        $rohpfad = str_replace("__", "_", $rohpfad);                    // doppelte Unterstriche ersetzen
        if($ModRewrite=="2"){$rohpfad=$rohpfad."_".$zeile["ID"]."";}    // ID anfuegen
        $rohpfad = $rohpfad.$Suffix;                                    // Suffix anfuegen
        $rewritePfad.= $rohpfad;                                        // RewirtePfad uebergeben
        }
    else{echo "Fehler: Es konnte kein Ergebnis fuer den RewritePfad ausgelesen werden!<br>\n";}
    mysql_free_result($ergebnis);
    
    return $rewritePfad;
	}


//===============================================================================
// MakePW
// """"""
// Beschreibung: Erzeugt ein sicheres Paswswort mit vorgegebener Länge
// Verwendung:	./admin/inc/NUT/NAN.inc

function MakePW($length)
	{
    $dummy	= array_merge(range('0', '9'), range('a', 'z'), range('A', 'Z'), array('#','&','@','$','_','%','?','+'));
 
		// shuffle array
		mt_srand((double)microtime()*1000000);
		
		for ($i = 1; $i <= (count($dummy)*2); $i++)
		{
			$swap		= mt_rand(0,count($dummy)-1);
			$tmp		= $dummy[$swap];
			$dummy[$swap]	= $dummy[0];
			$dummy[0]	= $tmp;
		}
 
		// get password
		return substr(implode('',$dummy),0,$length);
	}

//===============================================================================
// OrdBaum
// """""""
// Beschreibung: Gibt alle Ordner entsprechend ihrer Ebene als eingerueckte Baumstruktur aus. Hinter jedem Ordner-Namen erscheint der Status (on/offline?, Position, Sprache).
// Verwendung:	./admin/inc/ORD/OUE.inc

function OrdBaum($mutter, $mutterAlt, $ebene, $lang)
	{
	// Globals
	global $ScmsLang, $ScmsLangArray, $db; 
	
	// Parameter initialisieren
	if($mutter==""){$mutter=0;}
	if($mutterAlt==""){$mutterAlt=0;}
	
	// KategorieDaten aus DB holen
	// Lang vorbereiten
	if($ScmsLang){$sqlLang="Lang='".$lang."' AND ";}
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBordner." WHERE ".$sqlLang."Mutter='".$mutter."' ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($mutter!=$mutterAlt){$ebene=$ebene."&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";}
			$mutterAlt = $mutter;
			// On/Offline vorbereiten
			if($zeile["Online"]=="1"){$onOff="Gruen";}else{$onOff="Rot";}
			// Auth vorbereiten
			if($zeile["Auth"]=="-1"){$authColor=" style=\"color:#FF9900\"";}
			if($zeile["Auth"]=="0"){$authColor="";}
			if($zeile["Auth"]=="1"){$authColor=" style=\"color:#FF0000\"";}
			// Positions-Angabe vorbereiten
			while("4">strlen($zeile["Position"])){$zeile["Position"]="0".$zeile["Position"];}
			// Lang vorbereiten
			if($ScmsLang){$langAnzeige="|<i><b>".$zeile["Lang"]."</b></i>";}
			
			echo "<tr><td>".$ebene."&nbsp;<img src=\"img/scmsIcons_ord.gif\" width=\"25\" border=\"0\" alt=\"Ordner\" align=\"absmiddle\">&nbsp;<a href=\"index.php?modus=ORD&inc=OUE&id=".$zeile["ID"]."\"".$authColor."><b>".stripslashes($zeile["Name"])."</b></a></td><td><span class=\"text".$onOff."\" style=\"line-height:20px;\">[".$zeile["Position"].$langAnzeige."]</span><br></td></tr>\n";
			OrdBaum($zeile["ID"], $mutterAlt, $ebene, $zeile["Lang"]);
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion OrdBaum ausgelesen werden!<br>\n";}
	}

//===============================================================================
// OrdDokEins
// Beschreibung: Gibt die ID des nach seiner Positions-Nummer ersten Dokuments eines Ordners aus
// Verwendung:  ./index.php

function OrdDokEins($ordId)
	{
	// Globals
	global $db;
		
	// OrdnerDaten aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBdokumente." WHERE Ordner='".$ordId."' ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			return $zeile["ID"];
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion OrdDokEins ausgelesen werden!<br>\n";}
	}

//===============================================================================
// OrdPfad
// Beschreibung: Gibt den vollstaendigen Pfad eines Ordners aus.
// Verwendung:	./admin/inc/ORD/OUE.inc

function OrdPfad($id, $ordPfad)
	{
	// Globals
	global $db;
	
	if($id!="0")
		{
		// OrdnerDaten aus DB holen
		// SQL-String bauen
		$sqlString = "SELECT * FROM "._DBordner." WHERE ID='".$id."'";
		
		// Ergebnis auslesen
		$ergebnis = $db -> sql($sqlString);
		
		if($ergebnis)
			{
			$zeile = mysql_fetch_array($ergebnis);
			if($zeile["Mutter"]!="0")
				{
				$ordPfad = " / ".$zeile["Name"].$ordPfad;
				ordPfad($zeile["Mutter"], $ordPfad);
				}
			else
				{
				echo $ordPfad = $zeile["Name"].$ordPfad;
				}
			}
		else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion OrdPfad ausgelesen werden!<br>\n";}
		}
	else
		{
		echo "Wurzel";
		}
	}
	
//===============================================================================
// OrdPfadBaum
// Beschreibung: Gibt den vollstaendigen Ordnerbaum aus.
// Verwendung:	???

function OrdPfadBaum($mutter, $mutterAlt, $mutterName, $ebene)
	{
	// Globals
	global $db;
	
	// Parameter initialisieren
	if($mutter==""){$mutter=0;}
	if($mutterAlt==""){$mutterAlt=0;}
	
	// KategorieDaten aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBordner." WHERE Mutter='".$mutter."' ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($mutter!=$mutterAlt){$ebene=$ebene.$mutterName." / ";}
			$mutterAlt = $mutter;
			echo $ebene."<a href=\"index.php?modus=OAT&inc=OUE&id=".$zeile["ID"]."\">".$zeile["Name"]."</a><br>\n";
			OrdPfadBaum($zeile["ID"], $mutterAlt, $zeile["Name"], $ebene);
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion OrdPfadBaum ausgelesen werden!<br>\n";}
	}
	
//===============================================================================
// OrdPfadBaumOpt
// Beschreibung: Liefert den vorhandenen Ordnerbaum als <option>-Liste
// Verwendung:  ./admin/php/funktionen/scms_funktionen.php -> DokOrdOpt()
//              ./admin/inc/OAT/OAN.inc
//              ./admin/inc/OAT/OAE.inc

function OrdPfadBaumOpt($mutter, $mutterAlt, $mutterAkt, $mutterName, $ebene, $id)
	{
	// Globals
	global $ScmsLang, $db, $_SESSION;
	
	// Parameter initialisieren
	if($mutter==""){$mutter=0;}
	if($mutterAlt==""){$mutterAlt=0;}
	
	// KategorieDaten aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._DBordner." WHERE Mutter='".$mutter."' ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($id!=$zeile["ID"]){
			if($mutter!=$mutterAlt){$ebene=$ebene.$mutterName." / ";}
			$mutterAlt = $mutter;
			if($mutterAkt==$zeile["ID"]){$selected=" selected";}else{if($_SESSION["OAN"]["mutter"]==$zeile["ID"]){$selected=" selected";}else{$selected="";}}
			if($ScmsLang){$langOut=" [".$zeile["Lang"]."]";}
			echo "<option value=\"".$zeile["ID"]."\"".$selected.">".$ebene.$zeile["Name"].$langOut."</option>\n";
			OrdPfadBaumOpt($zeile["ID"], $mutterAlt, $mutterAkt, $zeile["Name"], $ebene, $id);}
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion OrdPfadBaumOpt ausgelesen werden!<br>\n";}
	}

//===============================================================================
// OrdPfadId
// Beschreibung: Gibt den vollstaendigen Pfad eines Ordners als Kette von IDs aus.
// Verwendung:	./admin/php/funktionen/scms-funktionen.inc => KlappNaviBaum()
	
function OrdPfadId($id, $ordPfad)
	{
	// Globals
	global $db;
	
	if($id!="0")
		{
		// OrdnerDaten aus DB holen
		// SQL-String bauen
		$sqlString = "SELECT * FROM "._DBordner." WHERE ID='".$id."'";
		
		// Ergebnis auslesen
		$ergebnis = $db -> sql($sqlString);
		
		if($ergebnis)
			{
			$zeile = mysql_fetch_array($ergebnis);
			if($zeile["Mutter"]!="0")
				{
				$ordPfad = "|".$zeile["ID"].$ordPfad;
				$ordPfad = OrdPfadId($zeile["Mutter"], $ordPfad);
				}
			else
				{
				$ordPfad = $zeile["ID"].$ordPfad;
				}
			}
		else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion OrdPfadId ausgelesen werden!<br>\n";}
		}
	else
		{
		$ordPfad = "0";
		}
    return $ordPfad;
	}
	
//===============================================================================
// OrdPosBesOpt
// """"""""""""
// Beschreibung: Gibt alle schon besetzten Positionen von Ordner im Ordnerbaum in einem Rollfenster aus.
// Verwendung:	./admin/inc/ORD/OAN.inc
//				./admin/inc/ORD/OAE.inc

function OrdPosBesOpt()
	{
	// Globals
	global $db;
	
	// OrdnerDaten aus DB holen
	// SQL-String bauen
	echo $sqlString = "SELECT Position FROM "._DBordner." ORDER BY Position";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			echo "<option>".$zeile["Position"]."</option>\n";
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion OrdPosBesOpt ausgelesen werden!<br>\n";}
	}

//===============================================================================
// Umlaute
// """""""
// Beschreibung: Setzt Umaute in z.B. 'ue' um
// Verwendung:	./admin/php/funktionen/scms_funktionen.php -> UrlRewrite()

function umlaute($text)
    {
    $search  = array ('Ä', 'Ö', 'Ü', 'ä', 'ö', 'ü', 'ß', '?');
    $replace = array ('Ae', 'Oe', 'Ue', 'ae', 'oe', 'ue', 'ss', '');
    $str  = str_replace($search, $replace, $text);
    return $str;
    }
	
//===============================================================================
// UrlRewrite
// """"""""""
// Beschreibung: Bildet den SCMS-Dokumentenbaum als mod_rewrite-Regeln ab und schreibt eine .htaccess-Datei
// Verwendung:	./admin/inc/ORD/OAN.inc
//				./admin/inc/ORD/OAE.inc
//				./admin/inc/ORD/OLO.inc
//				./admin/inc/DOK/DAN.inc
//				./admin/inc/DOK/DAE.inc
//				./admin/inc/DOK/DLO.inc
//				./admin/inc/EIN/EUE.inc

function UrlRewrite()
	{	
	// Globals
	global $db, $ModRewrite, $Suffix, $ServerRoot, $ServerRootPath;
	
    // Dokumentenbaum auslesen ******************************
    // SQL-String bauen
    $sqlString = "SELECT ID, Ordner, Linktext FROM "._DBdokumente." WHERE Online='1'";
    // Ergebnis auslesen
    $ergebnis = $db -> sql($sqlString);
    if($ergebnis)
        {
        while($zeile = mysql_fetch_array($ergebnis))
            {
            // Rewrite-Regeln erzeugen ******************************
            $pfad = WoBinIch($zeile["Ordner"], "_", $ordPfad);              // Pfad erzeugen
            if($zeile["Ordner"]!="0"){$pfad.="_";}                          // Trenner einbauen
            $rohpfad = $pfad.stripslashes($zeile["Linktext"]);              // Rohpfad erzeugen
            $rohpfad = Umlaute($rohpfad);                                   // Umlaute ersetzen
            $rohpfad = strip_tags($rohpfad);                                // Sonderzeichen in HTML wandeln
            $rohpfad = str_replace("'", "", $rohpfad);                      // Anfuehrungstriche ersetzen
            $rohpfad = str_replace("\"", "", $rohpfad);                     // Anfuehrungstriche ersetzen
            $rohpfad = str_replace(" ", "_", $rohpfad);                     // Leerzeichen ersetzen
            $rohpfad = str_replace("__", "_", $rohpfad);                    // doppelte Unterstriche ersetzen
            if($ModRewrite=="2"){$rohpfad=$rohpfad."_".$zeile["ID"]."";}    // ID anfuegen
            $rohpfad = $rohpfad.$Suffix;                                    // Suffix anfuegen
            $rewriteRegeln.= "RewriteRule ".$rohpfad." index.php?id=".$zeile["ID"]."&amp;ord=".$zeile["Ordner"]."\n";                                       // RewirteRegel anlegen
            }
        }
    else{echo "Fehler: Es konnte kein Ergebnis fuer den RewritePfad ausgelesen werden!<br>\n";}
    mysql_free_result($ergebnis);
    
    // .htaccess-Datei schreiben ****************************
    // Dateikopf
    $inhalt = "RewriteEngine on\nOptions FollowSymLinks\nRewriteBase ".$ServerRootPath."\n\n";
    // RewriteRules
    $inhalt.= $rewriteRegeln;
    
    // Datei schreiben **********
    $pfad = $ServerRoot."/.htaccess";
    // Sichergehen, dass die Datei existiert und beschreibbar ist
    if (is_writable($pfad))
        {
        if(!$handle = fopen($pfad, "w"))
            {
            print "Kann die Datei $pfad nicht &ouml;ffnen";
            exit;
            }
        
        // Schreibe $somecontent in die geoeffnete Datei.
        if(!fwrite($handle, $inhalt))
            {
            print "Kann in die Datei $pfad nicht schreiben";
            exit;
            }        
        fclose($handle);
        }
    else
        {
        print "Die Datei $pfad ist nicht schreibbar";
        }
    // Debug: return $inhalt;
	}

//===============================================================================
// UserLogin
// """""""""
// Beschreibung: Testet, ob ein Nutzer gueltig ist und setzt $_SESSION["UserAuth"] = true und schreibt Nutzerdaten in $_SESSION
// Verwendung:  ./index.php
//              ./admin/index.php
//              ./extern/RBP/rbp.php

function UserLogin($log, $pass)
	{
	// Globals
	global $db;
	
	// Parameter-Test
	if(!$log){$fehler.="Bitte Login eingeben<br>\n";}
	if(!$pass){$fehler.="Bitte Passwort eingeben<br>\n";}
	if($fehler){return $fehler;}
	else
        {
        // Nutzerdaten aus DB holen
        // SQL-String bauen
        $sqlString = "SELECT * FROM "._DBuserauth." WHERE Login='".$log."' AND Passwort='".md5($pass)."' LIMIT 1";
        
        // Ergebnis auslesen
        $ergebnis = $db -> sql($sqlString);
        
        if($ergebnis)
            {
            if(mysql_num_rows($ergebnis)=="1")
                {
                $user = mysql_fetch_array($ergebnis);
                if(!$user["Gesperrt"])
                    {
                    // Logindaten
                    $_SESSION["UserAuth"] = true;
                    $_SESSION["UserId"] = $user["ID"];
                    $_SESSION["UserLogin"] = $user["Login"];
                    $_SESSION["UserPass"] = $user["Passwort"];
                    $_SESSION["UserRolle"] = $user["Rolle"];
                    // Kontaktdaten
                    $_SESSION["UserAnrede"] = $user["Anrede"];
                    $_SESSION["UserVorname"] = $user["Vorname"];
                    $_SESSION["UserNachname"] = $user["Nachname"];
                    $_SESSION["UserStrasse"] = $user["Strasse"];
                    $_SESSION["UserPLZ"] = $user["PLZ"];
                    $_SESSION["UserOrt"] = $user["Ort"];
                    $_SESSION["UserLand"] = $user["Land"];
                    $_SESSION["UserTelefon"] = $user["Telefon"];
                    $_SESSION["UserMobil"] = $user["Mobil"];
                    $_SESSION["UserMail"] = $user["Mail"];
                    $_SESSION["UserTelefon"] = $user["Telefon"];
                    return "Nutzer angemeldet<br>\n";
                    }
                else
                    {
                    return "Nutzer gesperrt<br>\n";
                    }
                }
            else
                {
                $_SESSION["UserAuth"] = false;
                return "Login inkorrekt<br>\n";
                }
            }
        else{return "DB-Fehler: Es konnten kein Ergebnis fuer die Funktion UserLogin ausgelesen werden.<br>\n";}
        }
	}

//===============================================================================
// UserLogout
// """"""""""
// Beschreibung: Setzt $_SESSION["UserAuth"] = false
// Verwendung:  ./index.php
//              ./admin/index.php
//              ./extern/RBP/rbp.php

function UserLogout()
	{
	$_SESSION["UserAuth"] = false;
	}

//===============================================================================
// VerweisDok
// Beschreibung: Liefert alle Dokumente als <option>-Liste fuer die Verweisfunktion.
// Verwendung:  ./admin/inc/DOK/DAN.inc
//              ./admin/inc/DOK/DAE.inc

function VerweisDok($verweisAkt)
	{
	// Globals
	global $db;
	
	// OrdnerDaten aus DB holen
	// SQL-String bauen
	echo $sqlString = "SELECT * FROM "._DBdokumente." ORDER BY Titel";
	
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($verweisAkt==$zeile["ID"]){$selected=" selected";}else{$selected="";}
			echo "<option value=\"".$zeile["ID"]."\"".$selected.">".$zeile["Titel"]."</option>\n";
			}
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion ausgelesen werden!<br>\n";}
	}

//===============================================================================
// WoBinIch
// """"""""
// Beschreibung: Gibt einen WoBinIch-Pfad aus.
// Verwendung:  ./admin/php/funktionen/scms-funktionen.inc => KlappNaviDok()
//              ./admin/php/funktionen/scms-funktionen.inc => LinkRewrite()

function WoBinIch($id, $trenner, $ordPfad)
	{
	// Globals
	global $db;
	
	if($id!="0")
		{
		// OrdnerDaten aus DB holen
		// SQL-String bauen
		$sqlString = "SELECT * FROM "._DBordner." WHERE ID='".$id."' AND Online='1'";
		
		// Ergebnis auslesen
		$ergebnis = $db -> sql($sqlString);
		
		if($ergebnis)
			{
			$zeile = mysql_fetch_array($ergebnis);
			if($zeile["Mutter"]!="0")
				{
				$ordPfad = $trenner.stripslashes($zeile["Name"]).$ordPfad;
				return WoBinIch($zeile["Mutter"], $trenner, $ordPfad);
				}
			else
				{
				$ordPfad = stripslashes($zeile["Name"]).$ordPfad;
				return $ordPfad;
				}
			}
		else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion WoBinIch ausgelesen werden!<br>\n";}
		}
	}

//===============================================================================
// WoBinIchLink
// """"""""""""
// Beschreibung: Gibt einen klickbaren WoBinIch-Pfad aus.
// Verwendung:  .index.php

function WoBinIchLink($id, $trenner, $ordPfad)
	{
	// Globals
	global $db, $MailAdmin, $HttpRoot;
	
	if($id!="0")
		{
		// OrdnerDaten aus DB holen
		// SQL-String bauen
		$sqlString = "SELECT o.*, d.ID as DID FROM "._DBordner." o, "._DBdokumente." d WHERE o.ID='".$id."' AND o.Online='1' AND d.Ordner=o.ID ORDER BY d.Position LIMIT 1";
		
		// Ergebnis auslesen
		$ergebnis = $db -> sql($sqlString);
		
		if($ergebnis)
			{
			// Sicherung gegen Endlosschleife, falls eine Ordner im Pfad kein Dokument enthaelt
			if(!mysql_num_rows($ergebnis))
                {
                exit("ACHTUNG: Ein Ordner der Website enth&auml;lt kein Dokument.<br>Bitte informieren Sie den Administrator (<a href=\"mailto:".$MailAdmin."\">".$MailAdmin."</a>) dieser Site per eMail.<br><br>Zur&uuml;ck zur <a href=\"".$HttpRoot."\">Startseite...</a><br>");
                }
			
			$zeile = mysql_fetch_array($ergebnis);
			
			// Pfad klickbar
            if($ModRewrite){$link=LinkRewrite($zeile["DID"]);}
			else{$link="index.php?id=".$zeile["DID"]."&amp;ord=".$zeile["ID"];}
			
            // Ausgabe	
			if($zeile["Mutter"]!="0")
				{
				$ordPfad = $trenner."<a href=\"".$link."\">".stripslashes($zeile["Name"])."</a>".$ordPfad;
				return WoBinIchLink($zeile["Mutter"], $trenner, $ordPfad);
				}
			else
				{
				$ordPfad = "<a href=\"".$link."\">".stripslashes($zeile["Name"])."</a>".$ordPfad;
				return $ordPfad;
				}
			}
		else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion WoBinIchLink ausgelesen werden!<br>\n";}
		}
	}

?>