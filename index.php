<?php
// Session starten
session_start();

// Parameter
include("admin/config/settings.php");

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// POST und GET extrahieren
$id = $_GET["id"];
$ord = $_GET["ord"];
if($ord){$_SESSION["ord"] = $ord;}
else{if($ord==="0"){$_SESSION["ord"]="0";}$ord = $_SESSION["ord"];}
$lang = $_GET["lang"];
$userAuthLog = $_POST["userAuthLog"];
$userAuthPass = $_POST["userAuthPass"];
$doUserLogin = $_POST["doUserLogin"];
$doUserLogout = $_POST["doUserLogout"];


// Smarty-Konstruktor ***************************************************************
$smarty = new MySmarty;


// LangSelector bauen *************************************************************
if($ScmsLang)
    {
    // Lang aendern
    if($lang){$_SESSION["Lang"]=$lang;}
    // Selector
    foreach($ScmsLangArray as $key => $item)
        {
        // $_SESSION["Lang"] initialisieren
        if(!$_SESSION["Lang"]){$_SESSION["Lang"]=$key;}
        // Ausgabe
        if($_SESSION["Lang"]==$key){$langAktiv=" style=\"font-weight:bold;text-decoration:none;\"";}else{$langAktiv=" style=\"text-decoration:none;font-size:10px\"";}
        $langSelector.= "&nbsp;<a href=\"index.php?lang=".$key."\"".$langAktiv.">[".$item."]</a>";
        }
    }


// InterfaceLang setzen ***********************************************************************
if($ScmsLang){include($ServerRoot."/admin/lang/".$_SESSION["Lang"].".php");}


// LangBasics aufladen ************************************************************************
$langBasics["footer"] =  $lang_basics_footer;
$langBasics["headline"] =  $lang_basics_headline;
$langBasics["homepage"] =  $lang_basics_homepage;
$langBasics["iframe"] =  $lang_basics_iframe;
$langBasics["more"] =  $lang_basics_more;
$langBasics["navigation"] =  $lang_basics_navigation;
$langBasics["title"] =  $lang_basics_title;


// Testen ob DokID und DokOrd geladen ****************************************************************
if(!$id)
    {
    // SQL-String bauen
    if($ScmsLang){$whereLang = "Lang='".$_SESSION["Lang"]."' AND ";}
    $sqlString = "SELECT ID FROM "._DBdokumente." WHERE ".$whereLang."Online='1' AND Ordner='0' ORDER BY Position ASC LIMIT 1";
    // Ergebnis auslesen
    $ergebnis = $db -> sql($sqlString);
    if($ergebnis){$zeile=mysql_fetch_array($ergebnis); $id=$zeile["ID"];}
    else{echo "Fehler: Es konnte keine DokID ausgelesen werden!<br>\n";}
    }
if(!$ord){$ord="0";}


// UserAuth ********************************************************************************
if($doUserLogin){$userAuthMeldung=UserLogin($userAuthLog, $userAuthPass);}
if($doUserLogout){UserLogout();}


// Navi bauen *************************************************************
$ordPfadArray = explode("|",OrdPfadId($ord, $ordPfad));
$navi = KlappNaviBaum("0", "0", $check, $ordPfadArray);


// Ausgabe-Schleife Pfad ****************************************************
// SQL-String bauen
$sqlString = "SELECT Ordner, Linktext FROM "._DBdokumente." WHERE ID='".$id."' AND Online='1'";
// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis fuer die WoBinIch-Anzeige werden!<br>\n";}
// Leere Ausgabe abfangen
if($zeile)
    {
    // "Wo bin ich?"-Anzeige bauen
    $pfad = WoBinIchLink($zeile["Ordner"], " &raquo; ", $ordPfad);
    if($zeile["Ordner"]!="0"){$pfad.=" &raquo; ";}
    $pfad.= stripslashes($zeile["Linktext"]);
    }
mysql_free_result($ergebnis);


// Ausgabe-Schleife Dokument ****************************************************
// Auth fuer SQL-String
if($_SESSION["UserAuth"]){$sqlAuth = " AND (Auth BETWEEN '0' AND '1')";}
else{$sqlAuth = " AND (Auth BETWEEN '-1' AND '0')";}
// SQL-String bauen
$sqlString = "SELECT * FROM "._DBdokumente." WHERE ID='".$id."' AND Online='1'".$sqlAuth;
// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
// Leere Ausgabe abfangen
if($zeile)
    {
    // Abfangen, ob Ordner des Inhalts auth
    // SQL-String bauen
    $sqlStringOrd = "SELECT ID FROM "._DBordner." WHERE ID='".$zeile["Ordner"]."' AND Auth='1'";
    // Ergebnis auslesen
    $ergebnisOrd = $db -> sql($sqlStringOrd);
    if(!$_SESSION["UserAuth"] AND mysql_num_rows($ergebnisOrd)>"0")
        {
        $inhaltTitel = $lang_content_unavailTitle;
        $inhaltIntern = "<p class=\"text\">".$lang_content_unavailText1."</p><p>".$lang_content_unavailText2."<a href=\"mailto:".$MailAdmin."\">".$lang_content_unavailText3."</a>".$lang_content_unavailText4."</p>\n";
        }
    else
        {
        // Ausgabe
        // Titel
        if($zeile["AnzeigeTitel"]){$inhaltTitel = stripslashes($zeile["Titel"]);}
        // Kurztext
        if($zeile["AnzeigeKurztext"]){$inhaltKurztext = stripslashes($zeile["Kurztext"]);}
        // Intern
        $inhaltIntern = $zeile["Inhalt"];
        // Skript
        if($zeile["Skript"]){include($zeile["Skript"]); $inhaltIntern.= $inhalt;}
        }
    }
else
    {
    $inhaltTitel = $lang_content_unavailTitle;
    $inhaltIntern = "<p class=\"text\">".$lang_content_unavailText1."</p><p>".$lang_content_unavailText2."<a href=\"mailto:".$MailAdmin."\">".$lang_content_unavailText3."</a>".$lang_content_unavailText4."</p>\n";
    }

// Ausgabe-Schleife Verweise ****************************************************
// SQL-String bauen
$sqlString = "SELECT * FROM "._DBdokumente." WHERE ID='".$id."'";
// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
// SCMS-Auth
$verCount = 0; // VerweisCounter auf 0, wenn !$ScmsAuth
if($ScmsAuth)
    {
    // Inhalt UserAuthBox vorbereiten *******************************************
    if($_SESSION["UserAuth"])
        {
        if($userAuthMeldung){$userAuthBox = "<p class=\"textGruen\"><b class=\"klein\">".$userAuthMeldung."</b></p>";}
        $userAuthBox.= "<p class=\"klein\" style=\"margin-top:-2px;\">".$lang_auth_authText1."<b>&raquo;".$_SESSION["UserLogin"]."&laquo;</b><br>
            <div align=\"right\">
            <form action=\"index.php\" method=\"post\">
            <input type=\"hidden\" name=\"doUserLogout\" value=\"1\">
            <input type=\"submit\" value=\"".$lang_auth_buttonLogout."\" class=\"submitUserAuth\">
            </form>
            </div>
            </p>";
        }
    else
        {
        if($userAuthMeldung){$userAuthBox = "<p class=\"textRot\"><b class=\"klein\">".$userAuthMeldung."</b></p>";}
        $userAuthBox.= "<p class=\"klein\" style=\"margin-top:-2px;\">".$lang_auth_authText2."<br></p>
            <form action=\"index.php\" method=\"post\">
            <table>
            <tr><td class=\"kleiner\"><b>".$lang_auth_fieldLogin.":</b></td><td><input type=\"text\" name=\"userAuthLog\" size=\"10\" class=\"inputUserAuth\"></td></tr>
            <tr><td class=\"kleiner\"><b>".$lang_auth_fieldPassword.":</b></td><td><input type=\"password\" name=\"userAuthPass\" size=\"10\" class=\"inputUserAuth\"></td></tr>
            <tr><td colspan=\"2\" align=\"right\">
            <input type=\"hidden\" name=\"doUserLogin\" value=\"1\">
            <input type=\"submit\" value=\"".$lang_auth_buttonLogin."\" class=\"submitUserAuth\">
            </td></tr>
            </table>
            </form>";
        }
    $verweiseArray[0]["verweiseTitel"] = $lang_auth_authTitle;
    $verweiseArray[0]["verweiseText"] = $userAuthBox;
    $verweiseArray[0]["verweiseId"] = "0";
    $verCount = 1; // VerweisCounter auf 1, wenn $ScmsAuth
    }
// Ausgabe
for($c=1;$c<6;$c++)
    {
    $verweisNr="Verweis".$c;
    $zeile[$verweisNr];
    if($zeile[$verweisNr]!="0")
        {
        // SQL-String bauen
        $sqlString = "SELECT * FROM "._DBdokumente." WHERE ID='".$zeile[$verweisNr]."'";
        
        // Ergebnis auslesen
        $ergebnis = $db -> sql($sqlString);
        if($ergebnis){$verweis = mysql_fetch_array($ergebnis);}
        else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}
        
        // Testen, ob Verweis nicht tot oder off
        if($verweis["Linktext"] AND $verweis["Online"]!="0")
            {
            // Testen, ob Verweis oder Ordner des Verweises nicht auth
            // SQL-String bauen
            $sqlStringOrd = "SELECT ID FROM "._DBordner." WHERE ID='".$verweis["Ordner"]."' AND Auth='1'";
            // Ergebnis auslesen
            $ergebnisOrd = $db -> sql($sqlStringOrd);
            if((!$_SESSION["UserAuth"] AND $verweis["Auth"]=="1") OR (!$_SESSION["UserAuth"] AND mysql_num_rows($ergebnisOrd)>"0"))
                {$bla=0;}
            else
                {
                $verweiseArray[$verCount]["verweiseTitel"] = $verweis["Linktext"];
                $verweiseArray[$verCount]["verweiseText"] = $verweis["Kurztext"];
                $verweiseArray[$verCount]["verweiseId"] = $verweis["ID"];
                $verweiseArray[$verCount]["verweiseOrd"] = $verweis["Ordner"];
                $verCount++;
                }
            }
        }
    }


// Ausgabe-Schleife FussNavi *******************************************************
// SQL-String bauen
// SQL-String bauen
if($_SESSION["UserAuth"]){$sqlAuth="";}
else{$sqlAuth=" AND Auth!='1'";}
if($ScmsLang){$sqlLang = " AND Lang='".$_SESSION["Lang"]."'";}
// Ausgabe-Schleife FussNavi
// SQL-String bauen
$sqlString = "SELECT * FROM "._DBordner." WHERE Mutter='0' AND Online='1'".$sqlLang.$sqlAuth;
// Ergebnis auslesen
$ergebnis = $db -> sql($sqlString);
if($ergebnis)
	{
	$c=0;
	while($zeile = mysql_fetch_array($ergebnis))
		{
		$fussArray[$c]["fussId"] = OrdDokEins($zeile["ID"]);
		$fussArray[$c]["fussOrd"] =$zeile["ID"];
		$fussArray[$c]["fussLinktext"] = $zeile["Name"];
		$c++;
		}
	}
else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}


// Smarty-Assign ********************************************************************
$smarty->assign("langBasics",$langBasics);
$smarty->assign("langSelector",$langSelector);
$smarty->assign("css",$CssPfad);
$smarty->assign("js",$JsPfad);
$smarty->assign("meta",$MetaTags);
$smarty->assign("debug",$debug);
$smarty->assign("navi",$navi);
$smarty->assign("pfad",$pfad);
$smarty->assign("inhaltTitel",$inhaltTitel);
$smarty->assign("inhaltKurztext",$inhaltKurztext);
$smarty->assign("inhaltIntern",$inhaltIntern);
$smarty->assign("inhaltExtern",$inhaltExtern);
$smarty->assign("verweiseArray",$verweiseArray);
$smarty->assign("httpRoot",$HttpRoot);
$smarty->assign("fussArray",$fussArray);

// Smarty-Display
$smarty->display($ScmsTpl);


// DB-Verbindung schliessen
mysql_close();
?>