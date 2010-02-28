<?php
// POST und GET extrahieren
$suche = $_POST["suche"];
$ausgabe = $_POST["ausgabe"];
        
$inhalt.= "<p>".$lang_search_searchText1."</p>
    
    <fieldset><legend>".$lang_search_searchLegend.":</legend>
    
    <p>
    <form action=\"".$PHP_SELF."\" method=\"post\">
    <input type=\"text\" name=\"suche\" size=\"37\" value=\"".$suche."\"> <input type=\"submit\" value=\"".$lang_search_searchButton."\">
    <input type=\"hidden\" name=\"ausgabe\" value=\"1\">
    </form>
    </p>
    
    </fieldset>\n";
    

// Ausgabe Suchergebnis ***********************************************
if($ausgabe)
    {
    $inhalt.="<br>
        <fieldset><legend>".$lang_search_resultLegend.":</legend>\n";

    // Such-Sting aufbereiten
	// **********************
    $suchArray = explode(" ", $suche);               
    if(count($suchArray)>1){$suchArray[]=$suche;}

    // SQL-String bauen
	// ****************
	
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Achtung, die Suche enthaelt noch einen Fehler: Sie findet keine
    Inhalte in der Wurzel (Kat 0), da dies der Term "s.Kategorie=k.ID",
    der jedoch benoetigt wird, damit man sich nicht ein komplettes
    Kreuzprodukt der gesamten Suchanfrage ausgibt.
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
    for($c=0;$c<count($suchArray);$c++)
        {
        $like.= "(s.Titel LIKE '%".$suchArray[$c]."%' OR s.Kurztext LIKE '%".$suchArray[$c]."%' OR s.Inhalt LIKE '%".$suchArray[$c]."%')";
		
        if(($c+1)<count($suchArray))
		  {
		   $like.=" OR ";
		  }
        }
    // Auth fuer SQL-String
    if($_SESSION["UserAuth"]){$sqlAuth = " AND (s.Auth BETWEEN '0' AND '1' AND k.Auth BETWEEN '0' AND '1' )";}
    else{$sqlAuth = " AND (s.Auth BETWEEN '-1' AND '0' AND k.Auth BETWEEN '-1' AND '0')";}
    
    $sqlString = "SELECT s.ID,s.Ordner,s.Titel,s.Kurztext,s.Typ,s.Inhalt FROM "._DBdokumente." s, "._DBordner." k WHERE s.Online='1' AND k.Online='1' AND s.Ordner=k.ID AND s.Lang='".$_SESSION["Lang"]."' AND k.Lang='".$_SESSION["Lang"]."' AND ".$like.$sqlAuth;    
    
    
    // Ergebnis auslesen
	// ************************
    $ergebnis = $db -> sql($sqlString);
	
	$treffersum = mysql_num_rows($ergebnis);

    // Treffer
	// ************************
    if($treffersum>0 AND $suche!=" " AND $suche!="")
        {
        $inhalt.= "<p>".$lang_search_resultText1." <b><i>\"".$suche."\"</i></b> ".$lang_search_resultText2." <b>".$treffersum."</b> ".$lang_search_resultText3."</p>\n\n";
        while($zeile = mysql_fetch_array($ergebnis))
            {            
            $inhalt.= "<hr>
                <h5><a href=\"index.php?id=".$zeile["ID"]."&ord=".$zeile["Ordner"]."\" target=\"_top\">".$zeile["Titel"]."</a></h5>
                <span class=\"textKurz\">
                ".$zeile["Kurztext"]."<br>
                </span>
                <div align=\"right\"><a href=\"index.php?id=".$zeile["ID"]."&ord=".$zeile["Ordner"]."\" target=\"_top\">".$lang_search_resultMore."</a></div>\n";           
            }
        }
    else
        {
        $inhalt.= "<p>".$lang_search_noResultText1." <b><i>\"".$suche."\"</i></b> ".$lang_search_noResultText2.".<br> ".$lang_search_noResultText3.".<br></p>\n\n";
        }
    $inhalt.= "</fieldset>\n";
	}
?>