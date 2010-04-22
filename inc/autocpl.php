<?php
include($_SERVER['DOCUMENT_ROOT']."/SimpelCMS_raf/admin/config/settings.php");
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);
$begriff = $_GET['q'];
if(isset($begriff)){  // Post Variable Input Feld ?
   // Dann eine Abfrage mit like %string%
   $sqlbla = "SELECT begriff, anz FROM sufu_haeufig WHERE begriff LIKE '%".$begriff."%' ORDER BY anz DESC";
   $blabla = mysql_query($sqlbla);
   // z.B. Ergebnisse werden in einem Array gespeichert
	$i=6;
   while($reihe = mysql_fetch_object($blabla)){
   	if($i >= 0){
      echo $reihe->begriff." | ".$reihe->anz."\n";
      }
      $i--;
   }
	
}
?>