<table border="0" cellpadding="0" cellspacing="0" width="700">

<tr>
<td rowspan="2"><img src="<?php echo $OneGif; ?>" width="1" height="100" border="0" alt=""></td>
<td><img src="<?php echo $OneGif; ?>" width="698" height="25" border="0" alt=""></td>
<td rowspan="2"><img src="<?php echo $OneGif; ?>" width="1" height="100" border="0" alt=""></td>
</tr>

<tr>
<td align="center" valign="bottom" class="kleiner">

<?php
// Ausgabe-Schleife
foreach($modusArrayADMIN as $feld)
	{
	// Nutzer ausblenden, wenn !ScmsAuth
	if($feld["Kurz"]=="NUT" AND !$ScmsAuth){break;}
	// Ausgabe
	echo "&nbsp;\n<!-- ".$feld["Farbe"]." -->\n<nobr>\n";
	echo "<b><a href=\"index.php?modus=".$feld["Kurz"]."&inc=".$modusArrayADMIN[$feld["Kurz"]]["Link"]["0"]["Inc"]."\" style=\"color:".$feld["Wert"].";\"><span class=\"kleiner\" style=\"color:".$feld["Wert"].";\">".$feld["Titel"]."</span></a></b>\n";
	echo "<!-- /".$feld["Farbe"]." -->\n</nobr>\n";
	}
?>
<br><br>
<?php echo $lang_basics_adminFooter; ?><br>
</td>
</tr>

</table>
<br><br>