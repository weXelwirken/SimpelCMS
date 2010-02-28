<?php
// Session starten
session_start();

// Config
include("config/settings.php");

// DB-Verbindung
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// POST und GET extrahiern
$modus = $_GET["modus"];
$inc = $_GET["inc"];
$id = $_GET["id"];
$userAuthLog = $_POST["userAuthLog"];
$userAuthPass = $_POST["userAuthPass"];
$doUserLogin = $_POST["doUserLogin"];
$doUserLogout = $_GET["doUserLogout"];

// UserAuth
if($doUserLogin){$userAuthMeldung=UserLogin($userAuthLog, $userAuthPass);}
if($doUserLogout){UserLogout();}

// Parameter testen
if($modus == ""){$modus="HOM";}
if($inc == ""){$inc="SDA";}

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
          "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title><?php echo $lang_basics_adminTitle; ?></title>
<?php
// CSS & JS
include("inc/css_js.inc");

if($GalSlimboxAdmin)
    {
    // Slimbox laden
    echo "\n
    <!-- Slimbox einbinden -->
    <script type=\"text/javascript\" src=\"".$HttpRoot.$GalSrc."/mootools.js\"></script>
    <script type=\"text/javascript\" src=\"".$HttpRoot.$GalSrc."/slimbox.js\"></script>
    <link rel=\"stylesheet\" href=\"".$HttpRoot.$GalSrc."/slimbox.css\" type=\"text/css\" media=\"screen\" />
    <!-- /Slimbox einbinden -->\n\n";
    }

?>
</head>

<body>

<center>
<?php
/*
// Debug
echo $_SESSION["UserAuth"]."<br>";
*/

if(!$_SESSION["UserAuth"] OR !$_SESSION["UserRolle"]>"0")
    {
    // Fix fuer User ohne Adminrechte
    if($userAuthMeldung=="Nutzer angemeldet<br>\n"){$userAuthMeldung="Login inkorrekt";}
    // AuthBox
    echo "<table height=\"100%\"><tr><td valign=top>
        <fieldset style=\"margin-top:200px\">
        <legend>SCMS-Adminbereich</legend>
        <p style=\"margin-top:-2px;\">Hier k&ouml;nnen Sie sich an den Admin-Bereich anmelden.<br></p>";
    if($userAuthMeldung){echo "<center><p class=\"textRot\"><b>".$userAuthMeldung."</b></p></center>";}
    echo "<form action=\"index.php\" method=\"post\">
        <center>
        <table>
        <tr><td><b>Login:</b></td><td><input type=\"text\" name=\"userAuthLog\" size=\"25\" class=\"inputUserAuth\"></td></tr>
        <tr><td><b>Passwort:</b></td><td><input type=\"password\" name=\"userAuthPass\" size=\"25\" class=\"inputUserAuth\"></td></tr>
        <tr><td colspan=\"2\" align=\"right\">
        <input type=\"hidden\" name=\"doUserLogin\" value=\"1\">
        <input type=\"submit\" value=\"Anmelden\" class=\"submitUserAuth\">
        </td></tr>
        </table>
        </center>
        </form>
        </fieldset>
        </td></tr></table>";
    }
else
    {
    // AdminBereich
    ?>
<table border="0" cellpadding="0" cellspacing="0" width="700">

<tr>
<td colspan="2" align="left">

<table width="100%">
<tr><td>
<h3>
    <?php
    // Titel
    echo $lang_basics_adminHeadline;
    ?>
</h3>

</td>

<td align="right" valign="bottom" class="klein">
Sie sind angemeldet als: <b><i>"<?php echo $_SESSION["UserLogin"]; ?>"</i></b><br>
Ihre Nutzerrolle ist: <b><i>"<?php echo $RollenArray[$_SESSION["UserRolle"]]; ?>"</i></b><br>
</td>

</tr>

</table>
</td>
</tr>

<tr>
<td colspan="2" background="img/fauna.jpg">
    <?php
    // Kopfzeile
    include("inc/adminKopf.inc");
    ?>
</td>
</tr>

<tr><td colspan="2">&nbsp;<br></td></tr>

<tr>
<td align="left" valign="top">
    <?php
    // Navigation
    include("inc/adminNavi.inc");
    ?>							
</td>
<td align="right" valign="top">
    <?php
    // Content
    include("inc/adminInhalt.inc");
    ?>
</td>
</tr>

<tr>
<td colspan="2">
    <?php
    // Fuszeile
    include("inc/adminFuss.inc");
    ?>
</td>
</tr>

</table>
    <?php
    }
?>
</center>

</body>

</html>