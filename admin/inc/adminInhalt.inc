<table border="0" cellpadding="0" cellspacing="0">

<tr>
<td><img src="<?php echo $OneGif; ?>" width="24" height="1" border="0" alt=""></td>
<td><img src="<?php echo $OneGif; ?>" width="475" height="1" border="0" alt=""></td>
<td><img src="<?php echo $OneGif; ?>" width="1" height="1" border="0" alt=""></td>
</tr>

<tr>
<td><img src="<?php echo $OneGif; ?>" width="24" height="1" border="0" alt=""></td>
<td align="left" valign="top" class="text">

<!-- Inhalt -->
<?php
// Berechtigung testen
if($_SESSION["UserRolle"]>=$modusArrayADMIN[$modus]["Inc"][$inc]["Rolle"]){$incPfad = "inc/".$modus."/".$inc.".inc";}
else{$incPfad = "inc/HOM/ROL.inc";}
// Inhalts-Inc einbinden
include($incPfad);
?>
<!-- /Inhalt -->

</td>
<td><img src="<?php echo $OneGif; ?>" width="1" height="1" border="0" alt=""></td>
</tr>

<tr>

</tr>

</table>