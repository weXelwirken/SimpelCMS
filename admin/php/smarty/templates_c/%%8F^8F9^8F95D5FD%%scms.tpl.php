<?php /* Smarty version 2.6.18, created on 2009-07-14 09:12:44
         compiled from scms.tpl */ ?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
          "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title><?php echo $this->_tpl_vars['inhaltTitel']; ?>
 - <?php echo $this->_tpl_vars['langBasics']['title']; ?>
</title>
<!-- CSS & JS -->
<link href="<?php echo $this->_tpl_vars['css']; ?>
" rel="stylesheet">
<link rel="stylesheet" href="admin/jscripts/slimbox/css/slimbox.css" type="text/css" media="screen">
<script src="<?php echo $this->_tpl_vars['js']; ?>
" type="text/javascript"></script>
<script type="text/javascript" src="admin/jscripts/slimbox/js/mootools.js"></script>
<script type="text/javascript" src="admin/jscripts/slimbox/js/slimbox.js"></script>
<!-- /CSS & JS -->
<!-- MetaTags -->
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<link rel="shortcut icon" href="admin/img/scmsIcons_scms.ico">
<?php echo $this->_tpl_vars['meta']; ?>

<!-- /MetaTags -->
</head>

<body>

<!-- WZ ToolTip muss dirkt hinter dem Body-Tag und nich im Head eingebunden sein (siehe ToolTip-Doku)! -->
<script type="text/javascript" src="admin/jscripts/wz_tooltip/wz_tooltip.js"></script> 
<script type="text/javascript" src="admin/jscripts/wz_tooltip/tip_balloon.js"></script>

<center>
<?php if ($this->_tpl_vars['debug'] != ""): ?>
<fieldset>
<legend>Debug:</legend>
<?php echo $this->_tpl_vars['debug']; ?>

</fieldset>
<?php endif; ?>

<table border="0" cellpadding="0" cellspacing="0" width="800">

<tr>
<td width="175"><img src="img/one.gif" width="175" height="1" alt="spacer"></td>
<td width="10"><img src="img/one.gif" width="10" height="1" alt="spacer"></td>
<td width="430"><img src="img/one.gif" width="430" height="1" alt="spacer"></td>
<td width="10"><img src="img/one.gif" width="10" height="1" alt="spacer"></td>
<td width="175"><img src="img/one.gif" width="175" height="1" alt="spacer"></td>
</tr>

<tr>
<td colspan="5" align="left"><h1><?php echo $this->_tpl_vars['langBasics']['headline']; ?>
</h1></td>
</tr>

<tr>
<td colspan="5" id="header">
<table border="0" cellpadding="0" cellspacing="0" width="800">
<tr>
<td><img src="img/one.gif" width="1" height="125" alt="spacer"></td>
<td align="right" valign="bottom"><div style="margin:0px 5px 5px 0px;"><?php echo $this->_tpl_vars['langSelector']; ?>
</div></td>
</tr>
</table></td>
</tr>

<tr>
<td colspan="5"><img src="img/one.gif" width="800" height="10" alt="spacer"></td>
</tr>

<tr>
<td valign="top">
<!-- Navigation -->
<div style="padding:10px; background-color:#ffffff;"><?php echo $this->_tpl_vars['navi']; ?>
</div>
<!-- Navigation -->
<!-- ShopNavi -->
<?php if ($this->_tpl_vars['shopNavi'] != ""): ?>
<div style="margin-top:10px; padding:10px; background-color:#ffffff;"><?php echo $this->_tpl_vars['shopNavi']; ?>
</div>
<?php endif; ?>
<!-- ShopNavi -->
</td>
<td><img src="img/one.gif" width="10" height="1" alt="spacer"></td>
<td valign="top">
<!-- Pfad -->
<div style="padding:10px 0px 10px 0px;"><?php echo $this->_tpl_vars['pfad']; ?>
</div>
<!-- Pfad -->

<!-- Inhalt -->
<?php if ($this->_tpl_vars['inhaltTitel'] != ""): ?>
<h1><?php echo $this->_tpl_vars['inhaltTitel']; ?>
</h1>
<?php endif; ?>
<?php if ($this->_tpl_vars['inhaltKurztext'] != ""): ?>
<p class="textKurz"><?php echo $this->_tpl_vars['inhaltKurztext']; ?>
</p>
<?php endif; ?>
<?php if ($this->_tpl_vars['inhaltIntern'] != ""): ?>
<?php echo $this->_tpl_vars['inhaltIntern']; ?>

<?php else: ?>
<iframe src="<?php echo $this->_tpl_vars['inhaltExtern']; ?>
" width="100%" height="400" name="extern" scrolling="auto" frameborder="0">
  <p>Ihr Browser kann leider keine eingebetteten Frames anzeigen:
  Sie k&ouml;nnen die eingebettete Seite &uuml;ber den folgenden Verweis
  aufrufen: <a href="<?php echo $this->_tpl_vars['inhaltExtern']; ?>
"><?php echo $this->_tpl_vars['inhaltExtern']; ?>
</a></p>
</iframe>
<?php endif; ?>
<!-- /Inhalt -->
</td>
<td><img src="img/one.gif" width="10" height="1" alt="spacer"></td>
<td valign="top">
<!-- Verweise -->
<?php unset($this->_sections['verweiseItem']);
$this->_sections['verweiseItem']['name'] = 'verweiseItem';
$this->_sections['verweiseItem']['loop'] = is_array($_loop=$this->_tpl_vars['verweiseArray']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
$this->_sections['verweiseItem']['show'] = true;
$this->_sections['verweiseItem']['max'] = $this->_sections['verweiseItem']['loop'];
$this->_sections['verweiseItem']['step'] = 1;
$this->_sections['verweiseItem']['start'] = $this->_sections['verweiseItem']['step'] > 0 ? 0 : $this->_sections['verweiseItem']['loop']-1;
if ($this->_sections['verweiseItem']['show']) {
    $this->_sections['verweiseItem']['total'] = $this->_sections['verweiseItem']['loop'];
    if ($this->_sections['verweiseItem']['total'] == 0)
        $this->_sections['verweiseItem']['show'] = false;
} else
    $this->_sections['verweiseItem']['total'] = 0;
if ($this->_sections['verweiseItem']['show']):

            for ($this->_sections['verweiseItem']['index'] = $this->_sections['verweiseItem']['start'], $this->_sections['verweiseItem']['iteration'] = 1;
                 $this->_sections['verweiseItem']['iteration'] <= $this->_sections['verweiseItem']['total'];
                 $this->_sections['verweiseItem']['index'] += $this->_sections['verweiseItem']['step'], $this->_sections['verweiseItem']['iteration']++):
$this->_sections['verweiseItem']['rownum'] = $this->_sections['verweiseItem']['iteration'];
$this->_sections['verweiseItem']['index_prev'] = $this->_sections['verweiseItem']['index'] - $this->_sections['verweiseItem']['step'];
$this->_sections['verweiseItem']['index_next'] = $this->_sections['verweiseItem']['index'] + $this->_sections['verweiseItem']['step'];
$this->_sections['verweiseItem']['first']      = ($this->_sections['verweiseItem']['iteration'] == 1);
$this->_sections['verweiseItem']['last']       = ($this->_sections['verweiseItem']['iteration'] == $this->_sections['verweiseItem']['total']);
?>
<fieldset>
<legend><i><?php echo $this->_tpl_vars['verweiseArray'][$this->_sections['verweiseItem']['index']]['verweiseTitel']; ?>
</i></legend>
<div align="left" class="klein"><?php echo $this->_tpl_vars['verweiseArray'][$this->_sections['verweiseItem']['index']]['verweiseText']; ?>
</div>
<?php if ($this->_tpl_vars['verweiseArray'][$this->_sections['verweiseItem']['index']]['verweiseId'] != '0'): ?>
<div align="right" style="margin-bottom:0px" class="klein"><a href="index.php?id=<?php echo $this->_tpl_vars['verweiseArray'][$this->_sections['verweiseItem']['index']]['verweiseId']; ?>
&amp;ord=<?php echo $this->_tpl_vars['verweiseArray'][$this->_sections['verweiseItem']['index']]['verweiseOrd']; ?>
"><?php echo $this->_tpl_vars['langBasics']['more']; ?>
</a><br></div>
<?php endif; ?>
</fieldset>
<?php endfor; else: ?>
&nbsp;<br><!-- Kein Verweis -->
<?php endif; ?>
<!-- /Verweise -->
<!-- MiniKorb -->
<?php if ($this->_tpl_vars['miniKorb'] != ""): ?>
<?php echo $this->_tpl_vars['miniKorb']; ?>

<?php endif; ?>
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
<a href="<?php echo $this->_tpl_vars['httpRoot']; ?>
/index.php"><?php echo $this->_tpl_vars['langBasics']['homepage']; ?>
</a>
<?php unset($this->_sections['fussItem']);
$this->_sections['fussItem']['name'] = 'fussItem';
$this->_sections['fussItem']['loop'] = is_array($_loop=$this->_tpl_vars['fussArray']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
$this->_sections['fussItem']['show'] = true;
$this->_sections['fussItem']['max'] = $this->_sections['fussItem']['loop'];
$this->_sections['fussItem']['step'] = 1;
$this->_sections['fussItem']['start'] = $this->_sections['fussItem']['step'] > 0 ? 0 : $this->_sections['fussItem']['loop']-1;
if ($this->_sections['fussItem']['show']) {
    $this->_sections['fussItem']['total'] = $this->_sections['fussItem']['loop'];
    if ($this->_sections['fussItem']['total'] == 0)
        $this->_sections['fussItem']['show'] = false;
} else
    $this->_sections['fussItem']['total'] = 0;
if ($this->_sections['fussItem']['show']):

            for ($this->_sections['fussItem']['index'] = $this->_sections['fussItem']['start'], $this->_sections['fussItem']['iteration'] = 1;
                 $this->_sections['fussItem']['iteration'] <= $this->_sections['fussItem']['total'];
                 $this->_sections['fussItem']['index'] += $this->_sections['fussItem']['step'], $this->_sections['fussItem']['iteration']++):
$this->_sections['fussItem']['rownum'] = $this->_sections['fussItem']['iteration'];
$this->_sections['fussItem']['index_prev'] = $this->_sections['fussItem']['index'] - $this->_sections['fussItem']['step'];
$this->_sections['fussItem']['index_next'] = $this->_sections['fussItem']['index'] + $this->_sections['fussItem']['step'];
$this->_sections['fussItem']['first']      = ($this->_sections['fussItem']['iteration'] == 1);
$this->_sections['fussItem']['last']       = ($this->_sections['fussItem']['iteration'] == $this->_sections['fussItem']['total']);
?>
&nbsp;&nbsp;&nbsp;<a href="<?php echo $this->_tpl_vars['httpRoot']; ?>
/index.php?id=<?php echo $this->_tpl_vars['fussArray'][$this->_sections['fussItem']['index']]['fussId']; ?>
&amp;ord=<?php echo $this->_tpl_vars['fussArray'][$this->_sections['fussItem']['index']]['fussOrd']; ?>
"><?php echo $this->_tpl_vars['fussArray'][$this->_sections['fussItem']['index']]['fussLinktext']; ?>
</a>
<?php endfor; else: ?>
&nbsp;<br><!-- Kein Fuss -->
<?php endif; ?>
<br><br>
<?php echo $this->_tpl_vars['langBasics']['footer']; ?>
<br>
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