<?php /* Smarty version 2.6.18, created on 2009-01-27 04:35:30
         compiled from _vorlageExtern.tpl */ ?>
<html>
<head>
<title><?php echo $this->_tpl_vars['titel']; ?>
</title>
<!-- CSS & JS -->
<link href="<?php echo $this->_tpl_vars['css']; ?>
" rel="stylesheet">
<script src="<?php echo $this->_tpl_vars['js']; ?>
" type="text/javascript"></script>
<!-- /CSS & JS -->
</head>

<body bgcolor="#ffffff" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">

<?php if ($this->_tpl_vars['debug'] != ""): ?>
<fieldset>
<legend>Debug:</legend>
<?php echo $this->_tpl_vars['debug']; ?>

</fieldset>
<?php endif; ?>

<!-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ -->

<center>
<table border="0" cellspacing="0" cellpadding="0" width="100%">

<tr>
<td>
<?php echo $this->_tpl_vars['inhalt']; ?>

</td>
</tr>

</table>
</center>


<!-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ -->

</body>

</html>