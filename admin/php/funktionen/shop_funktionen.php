<?php

/*******************************************
Shop-Funktionen
"""""""""""""""

Die Datei beinhaltet Skripte, die besondere
Funkionaltitaeten fuer das Shop-Modul des
SimpelCMS v08/15 erzeugen.

Copyleft by weXelwirken 2009
********************************************/

// echo "<!-- Shop-Funktionen einbinden -->\n";

//===============================================================================
// GruppenOpt
// """"""""""
// Beschreibung: Gibt alle vorhanden Artikelgruppen als <option>-Liste aus
// Verwendung:	./admin/inc/SHO/AAN.inc

function GruppenOpt($id)
	{
	// Globals
	global $db;
	
	// Gruppen aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT * FROM "._ShopGruppen." ORDER BY Name";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		while($zeile = mysql_fetch_array($ergebnis))
			{
			// On/Offline vorbereiten
			if($zeile["Online"]){$onOff="";}else{$onOff=" (offline)";}
			// Selected vorbereiten
			if($id==$zeile["ID"]){$selected=" selected";}else{$selected="";}
			// Ausgabe
			echo "<option value=\"".$zeile["ID"]."\"".$selected.">".$zeile["Name"].$onOff."</option>\n";
            }
		}
	else{echo "Fehler: Es konnte kein Ergebnis fuer die Funktion GruppenOpt ausgelesen werden!<br>\n";}
	}

//===============================================================================
// MiniKorb
// """"""""
// Beschreibung: Gibt einen Mini-Warenkorb aus
// Verwendung:	./inc/shop.php

function MiniKorb()
	{
	// Globals
	global $id, $ord, $shop;
	
    $out.= "<fieldset>
        <legend><i>Schon eingekauft</i></legend>
        <table border=\"0\" cellspacing=\"0\" cellpadding=\"3\" width=\"100%\">\n";
       
    foreach($_SESSION["Shop"] as $key => $item)
        {
        // Ausgabe vorbereiten
        $endpreis = $item["Preis"]*$item["Menge"];
        $out.= "<tr>
            <td align=\"right\" class=\"klein nobr\">".$item["Menge"]."x</td>
            <td class=\"klein nobr\"><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;artId=".$key."\">".$item["Name"]."</a></td>
            <td align=\"right\" class=\"klein nobr\">".number_format($endpreis,2,',','.')." &euro;</td>
            </tr>";
        $total = $total+$endpreis;  
        }
        
    $out.= "<tr>
        <td colspan=\"3\" align=\"right\" class=\"klein nobr\" style=\"border-top:1px solid #7799aa;padding-bottom:5px\">
        <div style=\"width:65px; float:left; opacity:0; filter:alpha(opacity=0); background-color:#CBF400;\" id=\"shopAdd\" />&nbsp;</div>&nbsp;
        <b>Total: ".number_format($total,2,',','.')." &euro;</b>
        </td></tr>
        <tr>
        <td colspan=\"2\" align=\"left\" class=\"klein nobr\"><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;shop=x\">&laquo; Einkauf ansehen</a></td>
        <td align=\"right\" class=\"klein nobr\"><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;kasse=x\">Zur Kasse &raquo;</a></td>
        </tr>
        </table>
        </fieldset>\n";
    
    return $out;
	}

//===============================================================================
// ShopNavi
// """"""""
// Beschreibung: Gibt den Inhalt des Shops als Navigator aus
// Verwendung:  ./inc/shop.php

function ShopNavi()
	{
	// Globals
	global $db, $id, $ord;
	
	// Daten der Gruppe und des Artikel aus DB holen
	// SQL-String bauen
	$sqlString = "SELECT a.ID, a.Name, a.Preis, a.Online as ArtikelOn, g.Name as Gruppe, g.Online as GruppeOn FROM "._ShopArtikel." a, "._ShopGruppen." g WHERE a.Gruppe=g.ID AND a.Online='1' AND g.Online='1' ORDER BY g.Name, a.Name";
	// Ergebnis auslesen
	$ergebnis = $db -> sql($sqlString);
	if($ergebnis)
		{
		$out.= "<div style=\"margin-bottom:5px;\"><b>Artikel-&Uuml;bersicht:</b><br></div>\n";
		$shopGruppe = "0";
		while($zeile = mysql_fetch_array($ergebnis))
			{
			if($shopGruppe!=$zeile["Gruppe"])
				{
				// Ueberschrift mit Gruppen bauen
				if($shopGruppe!="0"){$out.="</div>\n";}
				$out.= "<a href=\"javascript:Show_Stuff('ArtGr".$zeile["ID"]."')\" class=\"naviOrd\">".$zeile["Gruppe"]."</a><br>
				    <div id=\"ArtGr".$zeile["ID"]."\" style=\"display:none;\">\n";
				$shopGruppe = $zeile["Gruppe"];
				}
			// Ausgabe
			$out.= "<b>&bull;</b>&nbsp;<a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;artId=".$zeile["ID"]."\" class=\"naviItem\">".$zeile["Name"]."</a><br>\n";
			}
    	$out.= "</div>\n";
    	$out.= "<div style=\"margin-top:5px;\"><a href=\"index.php?id=".$id."&amp;ord=".$ord."&amp;bestellungen=1\">Bisherige Bestellungen</a><br></div>\n";
		}
	else{$out.= "Fehler: Es konnte kein Ergebnis fuer die ShopNavi ausgelesen werden!<br>\n";}
	return $out;
	}

?>