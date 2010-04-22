<script src="<?php echo $HttpRoot; ?>/admin/jscripts/CodeMirror/js/codemirror.js" type="text/javascript"></script>
 

<?php
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);
$wastun = $_POST['wastun'];
require_once 'SDB.inc';
$SuchDB = new SucheDBAufg();



//was tun abfragen vor der ausgabe 
//Hier passiert was 
if($wastun == "feld_hinz") {
	$tabelle = $_POST['tabelle'];
	$feld = $_POST['new_field'];
	$SQL = 'INSERT INTO '._sufufelder.' (tabelle, spalte, prio) VALUES ("'.$tabelle.'", "'.$feld.'", "1")';
	mysql_query($SQL);
}

if($wastun == "feld_loe") {
	$tabelle = $_POST['tabelle'];
	$delfeld = $_POST['del_field'];
	$SQL = 'DELETE FROM '._sufufelder.' WHERE tabelle= "'.$tabelle.'" AND spalte = "'.$delfeld.'"';
	mysql_query($SQL) or die(mysql_error());
}

if($wastun == "prio_ae"){
	$tabelle = $_POST['tabelle'];
	$feld = $_POST['prio_field'];
	$new_prio = $_POST['new_prio'];
	$SQL = 'UPDATE '._sufufelder.' SET prio = "'.$new_prio.'" WHERE tabelle="'.$tabelle.'" AND spalte = "'.$feld.'"' ;
	mysql_query($SQL);
}

if($wastun == "tabelle_loeschen"){
	$tabelle = $_POST['tabelle'];
	$SQL = 'DELETE FROM '._sufufelder.' WHERE tabelle= "'.$tabelle.'"';
	mysql_query($SQL);
	$SQL = 'DELETE FROM '._sufutabellen.' WHERE tabelle= "'.$tabelle.'"';
	mysql_query($SQL);
}

if($wastun == "table_key_chg"){
	$tabelle = $_POST['tabelle'];
	$new_key = $_POST['new_key'];
	$SQL = 'UPDATE '._sufutabellen.' SET table_key = "'.$new_key.'" WHERE tabelle="'.$tabelle.'"' ;
	mysql_query($SQL);
}

if($wastun == "oeffnen_mit"){
	$tabelle = $_POST['tabelle'];
	$textar = $_POST['textar'];
	$textar = str_replace("<?php", "", $textar);
	$textar = str_replace("?>", "", $textar);
	$textar = mysql_real_escape_string($textar);
	$SQL = 'UPDATE '._sufutabellen.' SET oeffnen_mit = "'.$textar.'" WHERE tabelle="'.$tabelle.'"' ;
	mysql_query($SQL);
}

if($wastun == "table_bed"){
	$tabelle = $_POST['tabelle'];
	$textar = $_POST['textar'];
	$SQL = 'UPDATE '._sufutabellen.' SET bedingungen = "'.$textar.'" WHERE tabelle="'.$tabelle.'"' ;
	mysql_query($SQL);
}

if($wastun == "tabelle_status"){
	$tabelle = $_POST['tabelle'];
	$new_status = $_POST['new_status'];
	$SQL = 'UPDATE '._sufutabellen.' SET status = "'.$new_status.'" WHERE tabelle="'.$tabelle.'"' ;
	mysql_query($SQL);
}

//Wenn neue Tabelle dann in array laden
if($wastun == "new_table") {
	$new_table = $_POST['new_table'];
	$SQL = 'INSERT INTO '._sufutabellen.' (tabelle, status) VALUES ("'.$new_table.'", 0)';
	mysql_query($SQL);
}

//Tabellen holen
$tables = $SuchDB->Settings_AlleDBTabellen();








//Tabellen Felder ausgeben
foreach($tables as $ausgb) {
	if($ausgb["vorh"] == true){
		$fieldout .= ' <fieldset><legend>'.$ausgb["name"].'</legend>
		
					<div style="clear:left; float:left;">Tabellenschl&uuml;ssel:
					<form action="" method="post" name="table_key"> 
					<input type="hidden" name="tabelle" value="'.$ausgb["name"].'"> 
					<input type="hidden" name="wastun" value="table_key_chg">
					<select name="new_key" size="1" width="10px" onchange="this.form.submit();">';
					//tabllenschluessel bestimmen
					$key = $SuchDB->Table_Keys($ausgb["name"]);
					foreach($key as $wert) {
						$fieldout .= '<option value='.$wert["key"].' '.$wert["value"].' >'.$wert["key"].'</option>';					
					}
		$fieldout .= '</select></form></div>';
		
		//select feld fuer status ja nein
		if($ausgb["status"] == 1){ $st_opt_ja = "selected"; $st_opt_nein = "";}
		else{$st_opt_nein = "selected"; $st_opt_ja = "";}
		
		//Status Durhcushcen Feld
		$fieldout .= ' <div style="float:left; margin-left: 20px"> Durchsuchen <form action="" method="post">
						<input type="hidden" name="tabelle" value="'.$ausgb["name"].'"> 
						<input type="hidden" name="wastun" value="tabelle_status">
						<select name="new_status" size="1" width="10px" onchange="this.form.submit();">
						<option value="1" '.$st_opt_ja.' >ja</option>
						<option value="0" '.$st_opt_nein.' >nein</option>
						</select> </form></div>
					';

		//Löschen button
		$fieldout .= ' <div style="float:right; margin-left: 20px;"> <form action="" method="post">
						<input type="hidden" name="tabelle" value="'.$ausgb["name"].'"> 
						<input type="hidden" name="wastun" value="tabelle_loeschen">
						<input type="submit" name="l&ouml;schen" value="l&ouml;schen">
						</form>
						</div>
					';					
		//ueberschriften
		$fieldout .= ' <div style="margin-top:20px; float:left; clear: left"><div style="width: 200px; clear:left; float:left"><u>Feldname</u></div><div style="width: 20px; float:left"><u>Prio</u></div></div><br>
		
					';
					
		// in der foreach die selectierten felder holen und ausgeben
		$felder = $SuchDB->Settings_Felder_Sel($ausgb["name"]);
		foreach($felder as $felder2){
			$fieldout .= ' <br><div style="float:none; clear:left">';
			$fieldout .= ' 	    <div style="width: 200px; clear:left; float:left"> '.$felder2["feld"].'</div>
								<div style="width: 40px; float:left">
									<form method="post" action="">
									  <input type="text" name="new_prio" maxlength="2" size="1" value="'.$felder2["prio"].'">
									  <input type="hidden" name="prio_field" value="'.$felder2["feld"].'">
									  <input type="hidden" name="tabelle" value="'.$ausgb["name"].'">
									  <input type="hidden" name="wastun" value="prio_ae">									  
								</div>
								<div style="width: 20px; float:left">
									<input type="submit" value="Akt">
									</form>
								</div>
								<div style="width: 20px; float:left; margin-left: 20px;">
									<form method="post" action="#">
									  <input type="hidden" name="wastun" value="feld_loe">
									  <input type="hidden" name="del_field" value="'.$felder2["feld"].'">
									  <input type="hidden" name="tabelle" value="'.$ausgb["name"].'"> 
									  <input type="submit" value="X">
									</form>
								</div>
							</div>
							<br>';
		}
		//Neues Feld anlegen select  hier stehen nur felder die es noch nicht gab
		$fieldout .= ' <br><div style="float:left; clear:left; margin-top: 20px;">
						<form name="newfield" action="" method="post">
							<input type="hidden" name="wastun" value="feld_hinz">
							<input type="hidden" name="tabelle" value="'.$ausgb["name"].'">
							Neues Feld: <select name="new_field" size="1">';
							
		//Die nicht selectieten in foreach und als option	
		$notfelder = $SuchDB->Settings_Felder_NotSel($ausgb["name"]);
		foreach($notfelder as $notfelder2){
			$fieldout .= '	<option value='.$notfelder2.'>'.$notfelder2.'</option>';
		}
		$fieldout .= ' 		</select><input type="submit" value="Hinzuf&uuml;gen"></form> </div>';
		
		$SQLtar = "SELECT oeffnen_mit, bedingungen FROM "._sufutabellen." WHERE tabelle = '".$ausgb['name']."'";
		$querytar = mysql_query($SQLtar) or die(mysql_error());
		$textareas = mysql_fetch_object($querytar);
		

		
		//oeffnen mit php schreiben
		$fieldout .= ' <div style="float: left; clear:left; margin-top: 20px;">
						&Ouml;ffnen mit in PHP
						<form name="oeff_mit_ch" action="" method="post">
						<input type="hidden" name="wastun" value="oeffnen_mit">
						<input type="hidden" name="tabelle" value="'.$ausgb["name"].'">
						<div style="border: 1px solid black; padding: 3px; background-color: #F8F8F8; width: 450px;">
							<textarea id="code'.$ausgb["name"].'" name="textar" cols="25" rows="7"><?php					'.$textareas->oeffnen_mit.'?>
							</textarea><br>
						</div>
						<input type="submit" value="speichern" name="speichern">
						</form>
						</div>

					    <script type="text/javascript">
					      var editor = CodeMirror.fromTextArea("code'.$ausgb["name"].'", {
					        height: "120px",
					        width: "450px",
					        parserfile: ["parsexml.js", "parsecss.js", "tokenizejavascript.js", "parsejavascript.js",
					                     "../contrib/php/js/tokenizephp.js", "../contrib/php/js/parsephp.js",
					                     "../contrib/php/js/parsephphtmlmixed.js"],
					        stylesheet: ["'.$HttpRoot.'/admin/jscripts/CodeMirror/css/xmlcolors.css", "'.$HttpRoot.'/admin/jscripts/CodeMirror/jscolors.css", "'.$HttpRoot.'/admin/jscripts/CodeMirror/css/csscolors.css", "'.$HttpRoot.'/admin/jscripts/CodeMirror/contrib/php/css/phpcolors.css"],
					        path: "'.$HttpRoot.'/admin/jscripts/CodeMirror/js/",
					        continuousScanning: 500
					      });
					    </script>
			
		
					';
		
		//bedingung php schreiben
		$fieldout .= ' <div style="float: left; clear: left; margin-top: 20px;">
						Bedingungen zum Durchsuchen in PHP
						<form name="bed_chg" action="" method="post">
						<input type="hidden" name="wastun" value="table_bed">
						<input type="hidden" name="tabelle" value="'.$ausgb["name"].'">
						<textarea name="textar" cols="25" rows="7">'.$textareas->bedingungen.'</textarea><br>
						<input type="submit" value="speichern" name="speichern">
						</form>
						</div>
		
					';
		
		
		$fieldout .= '</fieldset><br>';		
	}	
}


//Nicht vorhandene Tabellen ausgeben
$tableout = '<fieldset><legend>Tablle Hinzuf&uuml;gen</legend>
				<form name="newtable" action="" method="post">
    				<select name="new_table" size="1">';
//nur tabellen ausgeben die noch nicht vorhanden sind
foreach($tables as $ausgb) {
	if($ausgb["vorh"] == false){
		$tableout .=  "<option value=".$ausgb["name"].">".$ausgb["name"]."</option>";
}	}
$tableout .=  "</select> <input type='submit' value='Hinzuf&uuml;gen'> <input type='hidden' name='wastun' value='new_table'>
				</form> 
			</fieldset>";

?>

<h3>Suche - Felder</h3>
<?php 
	//ausgaben
	echo $fieldout; 
	echo $tableout;
?>


