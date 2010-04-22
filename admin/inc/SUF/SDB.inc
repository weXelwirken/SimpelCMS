<?php
class SucheDBAufg {
		
	//Alle Datenbanktabellen ausgeben 
	function Settings_AlleDBTabellen() {
	
		//alle tabellen holen
		$result = mysql_query("SHOW TABLES");
		//leere ausgabe
		$ausgabe =array();
		
		//tabllennamen in array schreiben
		while($row = mysql_fetch_array($result)) {
			//tabllennamen aus den sufufeldern holen
			$SQL = "SELECT tabelle, status FROM "._sufutabellen." WHERE tabelle = '".$row[0]."'";
			$tableq = mysql_query($SQL);
			//wenn der tabllennamen vorhanden ist 2. array wert = vorh sonst leer			
			if(mysql_affected_rows()){ 
				$ausgabe[] = array("name"=>$row[0], "vorh"=>true, "status"=>mysql_fetch_object($tableq)->status);	
				echo $wert->status;
			}
			else{ $ausgabe[] = array("name"=>$row[0],"vorh"=>false, "status"=>"0"); 
		}	}		
		return $ausgabe;
	}	
	

	//Fuer eine Tablle alle Spalten ausgeben die NICHT in den sufufeldern stehen
	//Ist wichtig fuer das Backend
	function Settings_Felder_NotSel($tabelle) {
		//aus sufufeldern spaltennamen fuer tablle holen
		$SQLsel = "SELECT spalte FROM "._sufufelder." WHERE tabelle = '".$tabelle."'";
		$querysel = mysql_query($SQLsel);
		$selfelder = array();
		$ausgabe = array();
		while($wert = mysql_fetch_object($querysel)){
			$selfelder[] = $wert->spalte;
		}

		// fuer eine tablle alle tabellenspalten aus dem infoschema holen
		$SQLnotsel = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '".$tabelle."'";
		$querynotsel = mysql_query($SQLnotsel);
		$allefelder = array();
		//in array 
		while($wert = mysql_fetch_object($querynotsel)){
			$allefelder[] = $wert->COLUMN_NAME;
		}
		
		//array diff um die vorhandenen von allen abzuziehen damit man nur die NICHT ausgewaehlten hat
		$ausgabe = array_diff($allefelder, $selfelder);
		return $ausgabe;
	}	
	
	
	function Table_Keys($tabelle){
	
		$ausgabe = array();
		//aus sufufeldern spaltenkeys fuer tablle holen
		$SQLkey = "SELECT table_key FROM "._sufutabellen." WHERE tabelle = '".$tabelle."'";
		$querykey = mysql_query($SQLkey);
		$oldkey = array();
		//in ein array fuer vorh felder schreiben
		$oldkeywert = mysql_fetch_object($querykey);
		$oldkey[] = array("key"=>$oldkeywert->table_key, "value"=>"selected style='background-color: grey;'");
	
		// fuer eine tablle alle tabellenspalten aus dem infoschema holen
		$SQLall = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = '".$tabelle."'";
		$queryall = mysql_query($SQLall);
		$keysall = array();
		//in array 
		while($wert = mysql_fetch_object($queryall)){
			if($wert->COLUMN_NAME!=$oldkeywert->table_key){
				$keysall[] = array("key"=>$wert->COLUMN_NAME, "value"=>"");
		}	}
		$ausgabe = array_merge($oldkey, $keysall);
		
		return $ausgabe;
	}
	
	
	//ALLE Selectierten felder fuer eine tabelle ausgeben
	function Settings_Felder_Sel($tabelle) {
		$ausgabe = array();
		$SQL = "SELECT * FROM "._sufufelder." WHERE tabelle = '".$tabelle."'";
		$query = mysql_query($SQL);
		
		while($wert = mysql_fetch_object($query)) {
			$ausgabe[] = array("feld"=>$wert->spalte, "prio"=>$wert->prio);
		}
		return $ausgabe;
	}	
		
		
	//Anzahl der Begriffe schreiben bzw aendern zB fuer tag cloud -> was leute in die suche eingeben	
	function Begriff_Anz($eingabe) {

		//DB
		 $SQL = "SELECT * FROM "._sufuhaeufig." WHERE begriff = '".$eingabe."'";
		 $begrquery = mysql_query($SQL);
		 
		 //Wenn begriff vorh = neue anzahl
		 if(mysql_num_rows($begrquery) != 0) {
			 $anz = mysql_fetch_object($begrquery)->anz; 
			 $anz++;
			 $SQL2  = "UPDATE "._sufuhaeufig." SET anz = ".$anz." WHERE begriff = '".$eingabe."'";
			 mysql_query($SQL2);	
		 } // wenn nicht dann neu erstellen mit anz = 1
		 else {
			$SQL3 = 'INSERT INTO '._sufuhaeufig.' (begriff, anz) VALUES ("'.$eingabe.'", "1")';
			 mysql_query($SQL3);		 
		 }

	}			
		
	//Begr ersetzen 
	//einen eingegebenen begriff mit einem anderen aus der db ersetzen
	function Begriff_Repl($begriff) {
			$SQL = "SELECT * FROM "._sufubegriffe." WHERE string = '".$begriff."'";
			$query = mysql_query($SQL);
			$ausgabe = $begriff;
			
			if(mysql_num_rows($query) != 0) {
				$wert = mysql_fetch_object($query);
				$ausgabe = $wert->ersetzung;
			} 
			return $ausgabe;
		}
	
	//Tag Cloud sortiert nach anzahl
	function SUFU_CLOUD() {
	
			$SQL = "SELECT * FROM "._sufuhaeufig;
			$ausgabe = array();
			$cloudquery = mysql_query($SQL);
			while($wert = mysql_fetch_object($cloudquery)) {
				$ausgabe[] = array("begriff"=>$wert->begriff, "anzahl"=>$wert->anz);
			
			}
			// Auagabe nach Prio sortieren
			foreach ($ausgabe as $key => $row) {
			    $anz[$key]    = $row['anzahl'];
			}
			array_multisort($anz, SORT_DESC, $ausgabe);
			
			return $ausgabe;
		}
	
	
	function SuchAusg_oef($array) {
	
		$SQL = mysql_query("SELECT oeffnen_mit FROM "._sufutabellen." WHERE tabelle = '".$array['tabelle']."'");
		
		$objekt = mysql_fetch_object($SQL);
		eval($objekt->oeffnen_mit);
		$ausgabe .= $this->SuchAusg_anz($array['begriff'], $array['id'], $array['tabelle']);
	
		return $ausgabe;
	}
	
	//die suchausgabe
	function SuchAusg_anz($eingabe, $id, $tabelle){
	
		require 'sufu_settings.php';
		if($such_ausgb == "eig"){
			eval($such_ausgb_eigen);
		}
		else{
		
		  foreach($eingabe as $begriff){
		   $SQLhighlight = "SELECT ".$begriff['spalte']." FROM ".$tabelle." WHERE id=".$id;
		  $querybegriff = mysql_query($SQLhighlight);
		  $begriffinh = mysql_fetch_object($querybegriff);
		  $suchenin = strip_tags($begriffinh->{$begriff['spalte']});
		    $pos = strpos($suchenin, $begriff['eingabe']);
		  $bla = substr($suchenin, $pos-100-count($suchenin), 100)."... ";
		    $ersetzung = "<span style='color: red'>".$begriff['eingabe']."</span>";
		    $bla = str_ireplace($begriff['eingabe'], $ersetzung, $bla);
		    $ausgabe .= $bla;
		    if($i == 3){break;}
		    $i++;
		  }
		
		}
		return $ausgabe."<br>";
	
	
	}
	
	//Begriff Sortieren
	function Begr_Parse($begriff){
	
		require 'sufu_settings.php';
		strtolower($begriff);
			
		//leerzeichen durch + ersetzen
		$begriff = ereg_replace ('[ ]+', '+', $begriff);	
		
	
		$ausgabe = array();
		//array am +
		$ausgabe = array_unique(explode("+", $begriff));
		
		//array mit asunahemn und grosskleinschreibung entf 
		$ausnahmen = explode(";", strtolower($sufu_word_ausn));
		
		//leeres raus
		foreach($ausgabe as $key=>$row){
			//wenn leer
			if($row == "") { unset($ausgabe[$key]); }
			//wenn zu kurz und keine ausnahme
			if(strlen($row) <= $sufu_min_wordl && !in_array(strtolower($row), $ausnahmen)) { unset($ausgabe[$key]); }
		}
		return $ausgabe;
	}
	
	
	////////////////*********************Suchen nach String der irgendwo sein kann************************************************///////////////
	function Suche_Ausf_String($ausgabe, $SQL, $Multi, $eingabe, $table_key){

		//alle spalten und tabellen in while schleife suchen lassen 
		
		while($wert = mysql_fetch_object($SQL)) {
			
				//suchen nachen der jeweiligen eingabe in der tabelle und spalte aus der oberen while schleife
				$SQLsuche = 'SELECT '.$wert->spalte.', '.$table_key.' FROM '.$wert->tabelle.' WHERE '.$wert->spalte.' LIKE "%'.$eingabe.'%"';
				$SQLsuche2 = mysql_query($SQLsuche);
	
				//alle gefundenen ergebnisse in while schleife
				while($wert2 = mysql_fetch_object($SQLsuche2)) {
				
					//schauen ob das gefundene feld schon im array steht
					foreach($ausgabe as $key=>$item) {
						if($wert2->{$table_key} == $item["id"] && $wert->tabelle == $item["tabelle"]) {
							$prioNeu = $item["prio"] + $wert->prio;
							$schluessel = $key;
					}	}
					
					//ausgabe aktualisieren bzw neuen wert in array anlegen
					if($prioNeu) {
						$prioNeu = $prioNeu + $Multi;
						$ausgabe[$schluessel]["prio"] = $prioNeu;
						array_push($ausgabe[$schluessel]["begriff"], array("eingabe"=>$eingabe, "prio"=>$wert->prio, "tabelle"=>$wert->tabelle, "spalte"=>$wert->spalte));
						//array("id"=>$wert2->{$table_key}, "tabelle"=>$wert->tabelle, "prio"=>$prioNeu, "begriff"=>array_push($ausgabe[$schluessel]["begriff"], $eingabe));
						
						 //array_push(, $eingabe);
						
						unset($prioNeu);
					}
					else {
						$ausgabe[] = array("id"=>$wert2->{$table_key}, "tabelle"=>$wert->tabelle, "prio"=>$wert->prio + $Multi, "begriff"=>array(array("eingabe"=>$eingabe, "prio"=>$wert->prio, "tabelle"=>$wert->tabelle, "spalte"=>$wert->spalte)));
						
					}
					echo $eingabe." ".$wert->tabelle." ".$wert2->{$table_key};
					echo "<br>";
						
			}	}
	
	
	return $ausgabe;
	}
		
	////////////////*********************Suchen nach String der genau ist************************************************///////////////
	function Suche_Ausf_String_genau($ausgabe, $SQL, $Multi, $eingabe, $table_key){

		//alle spalten und tabellen in while schleife suchen lassen 
		
		while($wert = mysql_fetch_object($SQL)) {
			
				//suchen nachen der jeweiligen eingabe in der tabelle und spalte aus der oberen while schleife
				$SQLsuche = 'SELECT '.$wert->spalte.', '.$table_key.' FROM '.$wert->tabelle.' WHERE '.$wert->spalte.' LIKE "'.$eingabe.'"';
				$SQLsuche2 = mysql_query($SQLsuche);
	
				//alle gefundenen ergebnisse in while schleife
				while($wert2 = mysql_fetch_object($SQLsuche2)) {
				
					//schauen ob das gefundene feld schon im array steht
					foreach($ausgabe as $key=>$item) {
						if($wert2->{$table_key} == $item["id"] && $wert->tabelle == $item["tabelle"]) {
							$prioNeu = $item["prio"] + $wert->prio;
							$schluessel = $key;
					}	}
					
					//ausgabe aktualisieren bzw neuen wert in array anlegen
					if($prioNeu) {
						$prioNeu = $prioNeu + $Multi;
						$ausgabe[$schluessel]["prio"] = $prioNeu;
						array_push($ausgabe[$schluessel]["begriff"], array("eingabe"=>$eingabe, "prio"=>$wert->prio, "tabelle"=>$wert->tabelle, "spalte"=>$wert->spalte));
					}
					else {
						$ausgabe[] = array("id"=>$wert2->{$table_key}, "tabelle"=>$wert->tabelle, "prio"=>$wert->prio + $Multi, "begriff"=>array(array("eingabe"=>$eingabe, "prio"=>$wert->prio, "tabelle"=>$wert->tabelle, "spalte"=>$wert->spalte)));
			}	}	}
	
	
	return $ausgabe;
	}		
		
	//SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE
	//   SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE 
	function Suche($eingabe) {
		require 'sufu_settings.php';
		
		$ausgabe = array();
		
		if(!$eingabe == "") {
		
			$eingabe = mysql_real_escape_string(htmlspecialchars(trim($eingabe)));

			//alle spaltennamen und tabellennamen aus den sufu feldern holen
			$SQLtabellen = "SELECT * FROM "._sufutabellen." WHERE status = '1'";
			$querytabellen = mysql_query($SQLtabellen);
			
			while($tabellen = mysql_fetch_object($querytabellen)){
				

				$SQLfelder = 'SELECT * FROM '._sufufelder.' WHERE tabelle = "'.$tabellen->tabelle.'"' ;	
	
			
			
				//ungeparster string suchen 			
				$SQL = (mysql_query($SQLfelder));		
				$ausgabe = $this->Suche_Ausf_String($ausgabe, $SQL, $prio_multi_ganzer_string, $eingabe, $tabellen->table_key);
				//ungeparster string suchen 			
				$SQL = (mysql_query($SQLfelder));		
				$ausgabe = $this->Suche_Ausf_String_genau($ausgabe, $SQL, $prio_multi_ganzer_string+$prio_multi_wort_alleine, $eingabe, $tabellen->table_key);			
		
				$stringparse = $this->Begr_Parse($eingabe);
				//geparster string suchen
				foreach($stringparse as $string) {			
					$SQL = (mysql_query($SQLfelder));		
					$ausgabe = $this->Suche_Ausf_String($ausgabe, $SQL, "0", $string, $tabellen->table_key);
					//ungeparster string suchen 			
					$SQL = (mysql_query($SQLfelder));		
					$ausgabe = $this->Suche_Ausf_String_genau($ausgabe, $SQL, $prio_multi_wort_alleine, $string, $tabellen->table_key);
				}
			
			
			}
			//wenn leere ausgabe nicht sortieren
			if($ausgabe != NULL){
				// Auagabe nach Prio sortieren
				foreach ($ausgabe as $key => $row) {
				    $prio[$key]    = $row['prio'];
				}
				array_multisort($prio, SORT_DESC, $ausgabe);
			}
	
		}
		if(count($ausgabe) != NULL){$this->Begriff_Anz($eingabe);}
		return $ausgabe;
	}
	//SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE
	//   SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE SUCHE 
}

?>