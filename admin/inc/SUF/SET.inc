<?php
//pfad zu den eigenen sufu settings
$pfad = "inc/SUF/sufu_settings.php";

//POST und GET
$wastun = $_POST['wastun'];
$min_word = $_POST['min_word'];
//nur kleinbuchstb schreiben
$word_ausn = $_POST['word_ausn'];

$prio_multi_ganzer_string = $_POST['ganz_str_multi']; 
$prio_multi_wort_alleine = $_POST['ganz_word_multi'];
$such_ausgb_eigen = str_replace(array("<?php", "?>"), array("",""), $_POST['such_ausgb_eigen']);
$such_ausgb = $_POST['such_ausgb'];





if($wastun == 'einst_spei') {
	$einstellungen  = ' <?php $sufu_min_wordl = "'.$min_word.'"; ';
	$einstellungen .= '$sufu_word_ausn = "'.$word_ausn.'"; ';
	$einstellungen .= '$prio_multi_ganzer_string = "'.$prio_multi_ganzer_string.'"; ';
	$einstellungen .= '$such_ausgb_eigen = \''.$such_ausgb_eigen.'\'; ';
	$einstellungen .= '$such_ausgb = "'.$such_ausgb.'"; ';
	$einstellungen .= '$prio_multi_wort_alleine = "'.$prio_multi_wort_alleine.'"; ?>';

	if (is_writable($pfad)) {
	    if(!$handle = fopen($pfad, "w"))
	        {
	        print "Kann die Datei ".$pfad." nicht &ouml;ffnen";
	        exit;
	        }
	    
	    // Schreibe $somecontent in die geoeffnete Datei.
	    if(!fwrite($handle, $einstellungen))
	        {
	        print "Kann in die Datei ".$pfad." nicht schreiben";
	        exit;
	        }
	    
	    echo " <p>Die Einstellungen wurden erfolgreich aktualisiert geschrieben</p>
	        <p><a href=\"index.php?modus=NEW&inc=SET\">zur&uuml;ck zur &Uuml;bersicht</a></p>\n";
	    
	    fclose($handle);
	
	}
	else {
	    print "Die Datei ".$pfad." ist nicht schreibbar";
	}
}

//Einstellungen laden
include($pfad);

if($such_ausgb == "eig"){$eig_suche = "checked = 'checked'";
	echo '<style type="text/css"> #eigen_input{ display: block; } </style>';
}
if($such_ausgb == "std"){$std_suche = "checked = 'checked'";
	echo '<style type="text/css"> #eigen_input{ display: none; } </style>';
}
eval($such_ausgb_eigen);


?>

<script src="<?php echo $HttpRoot; ?>/admin/jscripts/CodeMirror/js/codemirror.js" type="text/javascript"></script>
<h3>Suche - Settings</h3>
<br>
<br>
<a href="index.php?modus=SUF&inc=FEL"><b>Felder definieren</b></a>
<br>
<br>
<fieldset><legend>Einstellungen</legend>
<form action="" method="post">
	<div>
		<div style="float:left; clear:left; width: 125px">
			Minimale Wortlänge:
		</div>
		<div style="float:left;">
			<input type="text" name="min_word" value="<?php echo $sufu_min_wordl; ?>" style="width: 20px">
		</div>
	</div>
	<div style="clear:left; float:none">
		<div style="clear:left; float:left; width: 125px">
			Ausnahmen:
		</div>
		<div style="float:left">
			<textarea name="word_ausn" rows="5" cols="25"><?php echo $sufu_word_ausn; ?></textarea>
		</div>
	</div>
	<div style="clear:left; float:left; margin-top: 10px;">
		<div style="float:left; clear:left; width: 125px">
			Ganzer String gefunden Multi:
		</div>
		<div style="float:left;">
			<input type="text" name="ganz_str_multi" value="<?php echo $prio_multi_ganzer_string; ?>" style="width: 20px">
		</div>
	</div>
	<div style="float:left; margin-top: 10px;">
		<div style="float:left; clear:left; width: 125px">
			Word alleine multi:
		</div>
		<div style="float:left;">
			<input type="text" name="ganz_word_multi" value="<?php echo $prio_multi_wort_alleine; ?>" style="width: 20px">
		</div>
	</div>
	<div style="float:left; clear: left; margin-top: 10px;">
		<div style="float:left; clear:left; width: 125px">
			Suchausgabe:
		</div>
		<div style="float:left;">
			<input type="radio" name="such_ausgb" value="std" onclick="document.getElementById('eigen_input').style.display='none'" <?php echo $std_suche; ?> >Standard <input type="radio" name="such_ausgb" value="eig" onclick="document.getElementById('eigen_input').style.display='block'" <?php echo $eig_suche; ?> >Eigen
		</div>
		<div id="eigen_input" style="clear: left">
			<div style="margin-left: 125px; border: 1px solid black; padding: 3px; background-color: white">
			<textarea id="such_ausgb_eigen" name="such_ausgb_eigen" rows="10" cols="40" style="margin-left: 125px;"><?php echo '<?php '.$such_ausgb_eigen.' ?>'; ?></textarea>
			</div>
		</div>
		
		<?php echo'
		<script type="text/javascript">
		  var editor = CodeMirror.fromTextArea("such_ausgb_eigen", {
		    height: "120px",
		    width: "300px",
		    parserfile: ["parsexml.js", "parsecss.js", "tokenizejavascript.js", "parsejavascript.js",
		                 "../contrib/php/js/tokenizephp.js", "../contrib/php/js/parsephp.js",
		                 "../contrib/php/js/parsephphtmlmixed.js"],
		    stylesheet: ["'.$HttpRoot.'/admin/jscripts/CodeMirror/css/xmlcolors.css", "'.$HttpRoot.'/admin/jscripts/CodeMirror/jscolors.css", "'.$HttpRoot.'/admin/jscripts/CodeMirror/css/csscolors.css", "'.$HttpRoot.'/admin/jscripts/CodeMirror/contrib/php/css/phpcolors.css"],
		    path: "'.$HttpRoot.'/admin/jscripts/CodeMirror/js/",
		    continuousScanning: 500
		  });
		</script>
		 '; ?>
	</div>
<br>
<div style="clear:left">
<input type="hidden" value="einst_spei" name="wastun">
<input type="submit" value="speichern" name="speichern">
</div>
</form>
</fieldset>