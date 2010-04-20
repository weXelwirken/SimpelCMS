<!-- Kopfzeile -->

<table border="0" cellpadding="0" cellspacing="0" width="700">

<tr>
<td><img src="<?php echo $OneGif; ?>" width="1" height="125" border="0" alt="spacer"></td>
<td align="left" valign="bottom">

<div style="margin:0px 0px 10px 10px;">
<span class="kopfnav"><a href="index.php?doUserLogout=1" style="color:#ff0000">Logout</a></span>
</div>

</td>
<td align="right" valign="bottom">

<!-- Menu bar. -->

<div class="menuBar"
><a class="menuButton"
    href="index.php?modus=HOM&inc=SDA"
    onclick="return buttonClick(event, 'Home_Menu');"
    onmouseover="buttonMouseover(event, 'Home_Menu');"
>Home</a
><a class="menuButton"
    href=""
    onclick="return buttonClick(event, 'SimpleCMS_Menu');"
    onmouseover="buttonMouseover(event, 'SimpleCMS_Menu');"
>SimpelCMS</a
><a class="menuButton" style="color:#FF9900;"
    href=""
    onclick="return buttonClick(event, 'SCMS_Module_Menu');"
    onmouseover="buttonMouseover(event, 'SCMS_Module_Menu');"
>SCMS Module</a
></div>

<!-- Main menus. -->
<div id="SimpleCMS_Menu" class="menu">
<?php
foreach($modusArrayADMIN as $feld)
	{
	// Berechtigung testen
	if($_SESSION["UserRolle"]>=$feld["Rolle"])
	   {
	   if($feld["Wert"]=="#7799aa")
            {	       
            // Ausgabe
            echo "<a class=\"menuItem\" href=\"index.php?modus=".$feld["Kurz"]."&inc=".key($modusArrayADMIN[$feld["Kurz"]]["Inc"])."\" style=\"color:".$feld["Wert"].";\">".$feld["Titel"]."</a>\n";
            unset($feld);
            }
	   }
	}
?>
</div>

<div id="SCMS_Module_Menu" class="menu">
<?php
foreach($modusArrayADMIN as $feld)
	{
	// Berechtigung testen
	if($_SESSION["UserRolle"]>=$feld["Rolle"])
	   {
	   if($feld["Wert"]=="#FF9900")
            {	       
            // Ausgabe
            echo "<a class=\"menuItem\" href=\"index.php?modus=".$feld["Kurz"]."&inc=".key($modusArrayADMIN[$feld["Kurz"]]["Inc"])."\" style=\"color:".$feld["Wert"].";\">".$feld["Titel"]."</a>\n";
            unset($feld);
            }
	   }
	}
?>
</div>

</td>
</tr>

</table>

<!-- Kopfzeile -->