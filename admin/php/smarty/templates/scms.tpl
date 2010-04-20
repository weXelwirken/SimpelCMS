<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
          "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>{$inhaltTitel} - {$langBasics.title}</title>
<!-- CSS & JS -->
<link href="{$css}" rel="stylesheet">
<link rel="stylesheet" href="admin/jscripts/slimbox/css/slimbox.css" type="text/css" media="screen">
<script src="{$js}" type="text/javascript"></script>
<script type="text/javascript" src="admin/jscripts/slimbox/js/mootools.js"></script>
<script type="text/javascript" src="admin/jscripts/slimbox/js/slimbox.js"></script>
<!-- /CSS & JS -->
<!-- MetaTags -->
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<link rel="shortcut icon" href="admin/img/scmsIcons_scms.ico">
{$meta}
<!-- /MetaTags -->
</head>

<body>

<!-- WZ ToolTip muss dirkt hinter dem Body-Tag und nich im Head eingebunden sein (siehe ToolTip-Doku)! -->
<script type="text/javascript" src="admin/jscripts/wz_tooltip/wz_tooltip.js"></script> 
<script type="text/javascript" src="admin/jscripts/wz_tooltip/tip_balloon.js"></script>

<center>
{if $debug != ""}
<fieldset>
<legend>Debug:</legend>
{$debug}
</fieldset>
{/if}

<table border="0" cellpadding="0" cellspacing="0" width="800">

<tr>
<td width="175"><img src="img/one.gif" width="175" height="1" alt="spacer"></td>
<td width="10"><img src="img/one.gif" width="10" height="1" alt="spacer"></td>
<td width="430"><img src="img/one.gif" width="430" height="1" alt="spacer"></td>
<td width="10"><img src="img/one.gif" width="10" height="1" alt="spacer"></td>
<td width="175"><img src="img/one.gif" width="175" height="1" alt="spacer"></td>
</tr>

<tr>
<td colspan="5" align="left"><h1>{$langBasics.headline}</h1></td>
</tr>

<tr>
<td colspan="5" id="header">
<table border="0" cellpadding="0" cellspacing="0" width="800">
<tr>
<td><img src="img/one.gif" width="1" height="125" alt="spacer"></td>
<td align="right" valign="bottom"><div style="margin:0px 5px 5px 0px;">{$langSelector}</div></td>
</tr>
</table></td>
</tr>

<tr>
<td colspan="5"><img src="img/one.gif" width="800" height="10" alt="spacer"></td>
</tr>

<tr>
<td valign="top">
<!-- Navigation -->
<div style="padding:10px; background-color:#ffffff;">{$navi}</div>
<!-- Navigation -->
<!-- ShopNavi -->
{if $shopNavi != ""}
<div style="margin-top:10px; padding:10px; background-color:#ffffff;">{$shopNavi}</div>
{/if}
<!-- ShopNavi -->
</td>
<td><img src="img/one.gif" width="10" height="1" alt="spacer"></td>
<td valign="top">
<!-- Pfad -->
<div style="padding:10px 0px 10px 0px;">{$pfad}</div>
<!-- Pfad -->

<!-- Inhalt -->
{if $inhaltTitel != ""}
<h1>{$inhaltTitel}</h1>
{/if}
{if $inhaltKurztext != ""}
<p class="textKurz">{$inhaltKurztext}</p>
{/if}
{if $inhaltIntern != ""}
{$inhaltIntern}
{else}
<iframe src="{$inhaltExtern}" width="100%" height="400" name="extern" scrolling="auto" frameborder="0">
  <p>Ihr Browser kann leider keine eingebetteten Frames anzeigen:
  Sie k&ouml;nnen die eingebettete Seite &uuml;ber den folgenden Verweis
  aufrufen: <a href="{$inhaltExtern}">{$inhaltExtern}</a></p>
</iframe>
{/if}
<!-- /Inhalt -->
</td>
<td><img src="img/one.gif" width="10" height="1" alt="spacer"></td>
<td valign="top">
<!-- Verweise -->
{section name=verweiseItem loop=$verweiseArray}
<fieldset>
<legend><i>{$verweiseArray[verweiseItem].verweiseTitel}</i></legend>
<div align="left" class="klein">{$verweiseArray[verweiseItem].verweiseText}</div>
{if $verweiseArray[verweiseItem].verweiseId != "0"}
<div align="right" style="margin-bottom:0px" class="klein"><a href="index.php?id={$verweiseArray[verweiseItem].verweiseId}&amp;ord={$verweiseArray[verweiseItem].verweiseOrd}">{$langBasics.more}</a><br></div>
{/if}
</fieldset>
{sectionelse}
&nbsp;<br><!-- Kein Verweis -->
{/section}
<!-- /Verweise -->
<!-- MiniKorb -->
{if $miniKorb != ""}
{$miniKorb}
{/if}
<!-- MiniKorb -->
</td>
</tr>

<tr>
<td colspan="5"><img src="img/one.gif" width="800" height="10" alt="spacer"></td>
</tr>

<tr>
<td><img src="img/one.gif" width="1" height="1" alt="spacer"></td>
<td><img src="img/one.gif" width="1" height="1" alt="spacer"></td>
<td bgcolor="#7799aa"><img src="img/one.gif" width="1" height="1" alt="spacer"></td>
<td><img src="img/one.gif" width="1" height="1" alt="spacer"></td>
<td><img src="img/one.gif" width="1" height="1" alt="spacer"></td>
</tr>

<tr>
<td colspan="5"><img src="img/one.gif" width="800" height="5" alt="spacer"></td>
</tr>

<tr>
<td colspan="5" align="center">
<!-- Fuss -->
<table border="0" cellpadding="0" cellspacing="0">
<tr>
<td align="center" valign="bottom" class="kleiner">
<a href="{$httpRoot}/index.php">{$langBasics.homepage}</a>
{section name=fussItem loop=$fussArray}
&nbsp;&nbsp;&nbsp;<a href="{$httpRoot}/index.php?id={$fussArray[fussItem].fussId}&amp;ord={$fussArray[fussItem].fussOrd}">{$fussArray[fussItem].fussLinktext}</a>
{sectionelse}
&nbsp;<br><!-- Kein Fuss -->
{/section}
<br><br>
{$langBasics.footer}<br>
</td>
</tr>
</table>
<!-- /Fuss -->
</td>
</tr>

</table>

</center>

</body>

</html>