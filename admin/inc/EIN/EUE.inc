    <?php
// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// DB-Verbindung Seite
$dbSeite = new db($dbHost,$dbUser,$dbPasswort);
$dbSeite -> select_db($dbDatenbank);

// Pfad
$pfad = "config/userSettings.php";
// User-Settings einlesen
include($pfad);

// POST und GET
$bearbeiten = $_GET["bearbeiten"];
if(!$bearbeiten){$bearbeiten = $_POST["bearbeiten"];}
$speichern = $_POST["speichern"];
if($_POST["SiteTitle"]){$SiteTitle = $_POST["SiteTitle"];}
if($_POST["SiteHeadline"]){$SiteHeadline = $_POST["SiteHeadline"];}
if($_POST["SiteFooter"]){$SiteFooter = $_POST["SiteFooter"];}
if($_POST["MailInfo"]){$MailInfo = $_POST["MailInfo"];}
if($_POST["MailAdmin"]){$MailAdmin = $_POST["MailAdmin"];}
if($_POST["MetaTags"]){$MetaTags = $_POST["MetaTags"];}
if($_POST["ModRewrite"]==="0" OR $_POST["ModRewrite"]){$ModRewrite = $_POST["ModRewrite"];}
if($_POST["Suffix"]){$Suffix = $_POST["Suffix"];}

// Uebersicht
//###############################################################################
if(!$bearbeiten)
	{
	?>
<table border="0" cellpadding="0" cellspacing="0" width="500">
<tr><td align="left" valign="top">
	<?php
	
	// Ueberschrift
	echo "<h3>Einstellungen</h3>
	   <p>Von dieser &Uuml;bersicht aus kann das Verhalten verschiedene Bereiche der Site gesteuert werden.</p>
	   <p><a href=\"index.php?modus=EIN&inc=EUE&bearbeiten=1\">Einstellungen bearbeiten</a></p>
	   <hr>
	   <h4><a href=\"javascript:Show_Stuff('St')\" style=\"text-decoration:none;\">[<span id=\"StOff\">+</span><span id=\"StOn\" style=\"display:none;\">-</span>]</a> SiteTitle</h4>
	   <div id=\"St\" style=\"display:none;\">
	   <p>Hier kann festgelegt werden, was als Site-Bezeichnung im Kopf des Browserfensters erscheinen soll.</p>
	   <p>SiteTitle: <span class=\"userSettings\">".$SiteTitle."</span></p>
	   </div>
	   <hr>
	   <h4><a href=\"javascript:Show_Stuff('Sh')\" style=\"text-decoration:none;\">[<span id=\"ShOff\">+</span><span id=\"ShOn\" style=\"display:none;\">-</span>]</a> SiteHeadline</h4>
	   <div id=\"Sh\" style=\"display:none;\">
	   <p>Hier kann festgelegt werden, welcher Text im Grafikheader angezeigt werden soll.</p>
	   <p>SiteHeadline: <span class=\"userSettings\">".$SiteHeadline."</span></p>
	   </div>
	   <hr>
	   <h4><a href=\"javascript:Show_Stuff('Sf')\" style=\"text-decoration:none;\">[<span id=\"SfOff\">+</span><span id=\"SfOn\" style=\"display:none;\">-</span>]</a> SiteFooter</h4>
	   <div id=\"Sf\" style=\"display:none;\">
	   <p>Hier kann festgelegt werden, welcher Text im Fu&szlig;bereich der Site angezeigt werden soll.</p>
	   <p>SiteFooter: <div class=\"userSettings\">".nl2br($SiteFooter)."</div></p>
	   </div>
	   <hr>
	   <h4><a href=\"javascript:Show_Stuff('Ma')\" style=\"text-decoration:none;\">[<span id=\"MaOff\">+</span><span id=\"MaOn\" style=\"display:none;\">-</span>]</a> Mail-Adressen</h4>
	   <div id=\"Ma\" style=\"display:none;\">
	   <p>In diesem Abschnitt kann festgelegt werden, wie die Adressen f&uuml;r den jeweiligen Zweck lauten</p>
	   <p>MailInfo: <span class=\"userSettings\">".$MailInfo."</span> (Allgemeine Information)</span></p>
	   <p>MailAdmin: <span class=\"userSettings\">".$MailInfo."</span> (Adresse des Webmasters)</span></p>
	   </div>
	   <hr>
	   <h4><a href=\"javascript:Show_Stuff('Mt')\" style=\"text-decoration:none;\">[<span id=\"MtOff\">+</span><span id=\"MtOn\" style=\"display:none;\">-</span>]</a> MetaTags</h4>
	   <div id=\"Mt\" style=\"display:none;\">
	   <p>Hier k&ouml;nnen Meta-Angaben zum Inhalt der Site gemacht werden.</p>
	   <p>MetaTags: <div class=\"userSettings\">".stripslashes(nl2br($MetaTags))."</div></p>
	   </div>
	   <hr>
	   <h4><a href=\"javascript:Show_Stuff('Mr')\" style=\"text-decoration:none;\">[<span id=\"MrOff\">+</span><span id=\"MrOn\" style=\"display:none;\">-</span>]</a> ModRewrite</h4>
	   <div id=\"Mr\" style=\"display:none;\">
	   <p>Hier k&ouml;nnen Sie s.g. \"sprechende URLs\" aktivieren. Statt aus kryptischen Parameter-Werten besteht der URL so aus les- und merkbaren Linktexten.</p>
	   <p>mod_rewrite: <span class=\"userSettings\">";
    if(!$ModRewrite){echo "deaktiviert";}
    if($ModRewrite=="1"){echo "aktiviert";}
    if($ModRewrite=="2"){echo "aktiviert (mit ID)";}
    echo "</span></p>
        <p>Dateiendung: <span class=\"userSettings\">".$Suffix."</span></p>
	   </div>
	   <hr>
	   <p><a href=\"index.php?modus=EIN&inc=EUE&bearbeiten=1\">Einstellungen bearbeiten</a></p>\n";
	
	?>
</td></tr>
</table>
	<?php
	}
//###############################################################################
// /Ubersicht

// Barbeiten
//###############################################################################
else
	{
	?>
<table border="0" cellpadding="0" cellspacing="0" width="500">
<tr><td align="left" valign="top">
	<?php
	
	// Ueberschrift
	echo "<h3>Einstellungen bearbeiten</h3>\n";

    // Bearbeiten ***************************************************************    	
	if(!$speichern)
        {
        echo "<form action=\"".$PHP_SELF."\" method=\"post\">
            <p>Bitte tragen Sie in alle Felder passende Werte ein.</p>
            <hr>
            <h4><a href=\"javascript:Show_Stuff('St')\" style=\"text-decoration:none;\">[<span id=\"StOff\">+</span><span id=\"StOn\" style=\"display:none;\">-</span>]</a> SiteTitle</h4>
            <div id=\"St\" style=\"display:none;\">
            <p>Hier kann festgelegt werden, was als Site-Bezeichnung im Kopf des Browserfensters erscheinen soll.</p>
            <p>SiteTitle: <input type=\"text\" name=\"SiteTitle\" value=\"".stripslashes($SiteTitle)."\" size=\"50\" maxlength=\"255\"></p>
            </div>
            <hr>
            <h4><a href=\"javascript:Show_Stuff('Sh')\" style=\"text-decoration:none;\">[<span id=\"ShOff\">+</span><span id=\"ShOn\" style=\"display:none;\">-</span>]</a> SiteHeadline</h4>
            <div id=\"Sh\" style=\"display:none;\">
            <p>Hier kann festgelegt werden, welcher Text im Grafikheader angezeigt werden soll.</p>
            <p>SiteHeadline: <input type=\"text\" name=\"SiteHeadline\" value=\"".stripslashes($SiteHeadline)."\" size=\"50\" maxlength=\"255\"></p>
            </div>
            <hr>
            <h4><a href=\"javascript:Show_Stuff('Sf')\" style=\"text-decoration:none;\">[<span id=\"SfOff\">+</span><span id=\"SfOn\" style=\"display:none;\">-</span>]</a> SiteFooter</h4>
            <div id=\"Sf\" style=\"display:none;\">
            <p>Hier kann festgelegt werden, welcher Text im Fu&szlig;bereich der Site angezeigt werden soll.</p>
            <p>SiteFooter:<br><textarea name=\"SiteFooter\" cols=\"60\" rows=\"7\">".stripslashes($SiteFooter)."</textarea></p>
            </div>
            <hr>
            <h4><a href=\"javascript:Show_Stuff('Ma')\" style=\"text-decoration:none;\">[<span id=\"MaOff\">+</span><span id=\"MaOn\" style=\"display:none;\">-</span>]</a> MailAdressen</h4>
            <div id=\"Ma\" style=\"display:none;\">
            <p>In diesem Abschnitt kann festgelegt werden, wie die Adressen f&uuml;r den jeweiligen Zweck lauten</p>
            <p>MailInfo: <input type=\"text\" name=\"MailInfo\" value=\"".$MailInfo."\" size=\"30\" maxlength=\"255\"> (Allgemeine Information)</p>
            <p>MailAdmin: <input type=\"text\" name=\"MailAdmin\" value=\"".$MailAdmin."\" size=\"30\" maxlength=\"255\"> (Adresse des Webmasters)</p>
            </div>
            <hr>
            <h4><a href=\"javascript:Show_Stuff('Mt')\" style=\"text-decoration:none;\">[<span id=\"MtOff\">+</span><span id=\"MtOn\" style=\"display:none;\">-</span>]</a> MetaTags</h4>
            <div id=\"Mt\" style=\"display:none;\">
            <p>Hier k&ouml;nnen Meta-Angaben zum Inhalt der Site gemacht werden.</p>
            <p>MetaTags:<br><textarea name=\"MetaTags\" cols=\"60\" rows=\"12\">".stripslashes($MetaTags)."</textarea></p>
            </div>
            <hr>
            <h4><a href=\"javascript:Show_Stuff('Mr')\" style=\"text-decoration:none;\">[<span id=\"MrOff\">+</span><span id=\"MrOn\" style=\"display:none;\">-</span>]</a> ModRewrite</h4>
            <div id=\"Mr\" style=\"display:none;\">
            <p>Hier k&ouml;nnen Sie s.g. \"sprechende URLs\" aktivieren. Statt aus kryptischen Parameter-Werten besteht der URL so aus les- und merkbaren Linktexten.</p>
            <p><b>mod_rewrite:</b> ";
            
        echo "<input type=\"radio\" name=\"ModRewrite\" value=\"0\"";
        if(!$ModRewrite){echo " checked";}
        echo ">deaktiviert&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
            
        echo "<input type=\"radio\" name=\"ModRewrite\" value=\"1\"";
        if($ModRewrite=="1"){echo " checked";}
        echo ">aktiviert&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"; 
            
        echo "<input type=\"radio\" name=\"ModRewrite\" value=\"2\"";
        if($ModRewrite=="2"){echo " checked";}
        echo ">aktiviert (mit ID)";     
            
        echo "</p>
        <p>Dateiendung: <input type=\"text\" name=\"Suffix\" value=\"".$Suffix."\"></p>
            </div>
            <hr>
            <p align=center>
            <input type=\"hidden\" name=\"berabeiten\" value=\"1\">
            <input type=\"hidden\" name=\"speichern\" value=\"1\">
            <input type=\"submit\" value=\"Einstellungen speichern\">
            </p>
            </form>\n";
        }
    // Speichern ****************************************************************
    else
        {
        $fehlerStr = "<h4 align=\"left\">Fehler!</h4>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";
		
        // Feldtest
        if(!$SiteTitle){$fehler=1; $fehlerStr = $fehlerStr."<li>SiteTitle ist nicht gesetzt.\n";}
        if(!$SiteHeadline){$fehler=1; $fehlerStr = $fehlerStr."<li>SiteHeadline ist nicht gesetzt.\n";}
        if(!$SiteFooter){$fehler=1; $fehlerStr = $fehlerStr."<li>SiteFooter ist nicht gesetzt.\n";}
        if(!$MailInfo){$fehler=1; $fehlerStr = $fehlerStr."<li>MailInfo ist nicht gesetzt.\n";}
        if(!$MailAdmin){$fehler=1; $fehlerStr = $fehlerStr."<li>MailAdmin ist nicht gesetzt.\n";}
        if(!$MetaTags){$fehler=1; $fehlerStr = $fehlerStr."<li>MetaTags sind nicht gesetzt.\n";}
        
        $fehlerStr = $fehlerStr."</ul>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";
        
        // Fehlerausgabe
        if($fehler!="")
            {
            echo $fehlerStr;
            }
        // Wenn Feldtest ohne Fehler **********
        else
            {
            // Datei vorbereiten **********
            // Dateikopf
            $inhalt = "<?php\n// UserSettings-Datei vom SCMS\n// \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\n// Hier tut keiner was, der keine Ahnung hat!\n// sonst:\n// ALLES KAPUTT!!!\n// dann:\n// FRATZENGEBALLER!!!!\n// *grrr*\n\n";
            
            // SiteTitle
            $inhalt.= "// SiteTitle\n\$SiteTitle = \"".addslashes($SiteTitle)."\";\n\n";
            // SiteHeadline
            $inhalt.= "// SiteHeadline\n\$SiteHeadline = \"".addslashes($SiteHeadline)."\";\n\n";
            // SiteFooter
            $inhalt.= "// SiteFooter\n\$SiteFooter = \"".addslashes($SiteFooter)."\";\n\n";
            // Mail
            $inhalt.= "// Mail\n\$MailInfo = \"".$MailInfo."\";\n\$MailAdmin = \"".$MailAdmin."\";\n\n";
            // MetaTags
            $inhalt.= "// MetaTags\n\$MetaTags = \"".addslashes($MetaTags)."\";\n\n";
            // ModRewrite
            $inhalt.= "// ModRewrite\n\$ModRewrite = \"".$ModRewrite."\";\n\n";
            // Suffix
            $inhalt.= "// Suffix\n\$Suffix = \"".$Suffix."\";\n\n";
            
            // Dateifuss
            $inhalt.= "?>\n";
            
            // Datei schreiben **********
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
                
                echo "<p>Die Einstellungen wurden erfolgreich aktualisiert geschrieben</p>
                    <p><a href=\"index.php?modus=EIN&inc=EUE\">zur&uuml;ck zur &Uuml;bersicht</a></p>\n";
                
                fclose($handle);
            
                }
            else
                {
                print "Die Datei $pfad ist nicht schreibbar";
                }
            
            // .htaccess aktualisieren
            if($ModRewrite){UrlRewrite();}
            }
        }
	?>
</td></tr>
</table>
	<?php
	}
//###############################################################################
// /Barbeiten
?>