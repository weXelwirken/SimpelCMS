<div style="padding:5px 5px 5px 5px; background-color:#ffffff; min-height:300px; width:175px;">
<h4><?php echo $modusArrayADMIN[$modus]["Titel"]; ?></h4>

<p>
<!-- Text -->
<ul style="color:<?php echo $modusArrayADMIN[$modus]["Wert"]; ?>;">
<?php
// Ausgabeschleife Navi
$li = "<li style=\"margin-top:10px; margin-left:-10px\">";
foreach($modusArrayADMIN[$modus]["Inc"] as $key => $item)
	{
	// Berechtigung testen
	if($_SESSION["UserRolle"]>=$item["Rolle"] AND $item["Name"])
	   {
        echo $li."<a href=\"index.php?modus=".$modus."&inc=".$key."\">".$item["Name"]."</a>\n";
        }
	}
?>
</ul>
<!-- /Text -->

<!-- AdminInhalte -->

<?php
// Admin-Tools einbinden
if($modus=="HOM" AND $_SESSION["UserRolle"]=="3")
	{
	echo "<br><h4 align=\"center\">".$lang_basics_adminTools."</h4>\n";
	echo "<ul style=\"color:".$modusArrayADMIN[$modus]["Wert"]."\">\n";
	echo $li."<a href=\"".$PmaPfad."\" target=\"_blank\">".$lang_basics_adminPMA."</a>\n";
	echo "</ul>\n";
	}
?>

<!-- /AdminInhalte -->
<?php
// Krake
if($modus=="DAT")
	{
	echo "<div style=\"margin:120px 0px 15px 15px;\"><img src=\"img/module/krake/krake_krake.gif\" alt=\"Die Datenkrake\"></div>\n";
	}
?>
</p>

</div>