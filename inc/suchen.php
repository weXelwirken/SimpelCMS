<style type="text/css">

    .ac_input {

            width: 200px;

    }

    .ac_results {

            width: 200px;
            background: #eee;

            cursor: pointer;

            position: absolute;

            left: 0;
            font-size: 90%;
            z-index: 101;

    }

    .ac_results ul {

            width: 200px;

            list-style: none;

            padding: 0px;

            margin: 0px;

            border: 1px solid #000;

    }

    .ac_results li {

            width: 190px;

            padding: 2px 5px;

    }

    .ac_results a {

            width: 100%;

    }

    /* thanks udoline: this fixed position error into msie */

    .ac_results iframe {

            width: 200px;

            position: absolute;

    }

    .ac_loading {

            background : url('admin/img/ladebalken.gif') right center no-repeat;

    }

    .over {

            background: yellow;

    }



</style>

<?php
//post get
$suchen = $_GET['suchen'];
$begriff = $_GET['begriff'];

//db verb
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Suchfunktion laden
require_once $ServerRoot.'/admin/inc/SUF/SDB.inc';
$Suche = new SucheDBAufg();


/*
echo "<pre>";
print_r($Suche->Suche($begriff));
echo"</pre>";*/
//inhalt
$inhalt .= "<h3>Suchen</h3>";

//fieldset fuer CLOUD ***********************************************************************************
$inhalt .= "<fieldset><legend>CLOUD</legend><center>";
//cloud funkt
$cloud = $Suche->SUFU_CLOUD();

$i = 50;
foreach($cloud as $werte) {

	$inhalt .= " <a href='index.php?begriff=".$werte["begriff"]."&id=81&ord=31&suchen=los&LOS=Los'><span style='font-size:".$i."px; color: black'> ".$werte["begriff"]."</span></a> ";
	$i = $i - 10;
	if($i < 10){ break; }
}
$inhalt .= "</center></fieldset><br><br>";


//sucheingabe *********************************************************************************************
$inhalt .= '<form action ="?id=81&ord=31" method="get">
				Suchbegriff:<input type="text" id="begriff" name="begriff" value="'.$begriff.'">
				
				<input type="hidden" name="id" value="81">
				<input type="hidden" name="ord" value="31">
				<input type="hidden" name="suchen" value="los">
				<input type="submit" name="LOS" value="Los">
			</form><br><br><br>
			';

$inhalt .= '

    <script type="text/javascript">

    function selectItem(li) {

            return false;

    }

    function formatItem(row) {

            return row[0] + "<i>" + row[1] + "</i>";

    }

    $(document).ready(function() {

            $("#begriff").autocomplete("/SimpelCMS_raf/inc/autocpl.php", {

                    minChars:1,

                    matchSubset:1,

                    matchContains:1,

                    cacheLength:5,

                    onItemSelect:selectItem,

                    formatItem:formatItem,

                    selectOnly:1

            });

    });


	</script>
	
	</div>';


//SUCHEN *******************************************************************************************************************
if($suchen == "los") {


	$ausgb= $Suche->Suche($begriff);
	echo "<pre>";
	print_r($ausgb);
	echo "</pre>";
	if($ausgb){
		foreach($ausgb as $wert){
				$inhalt.= $Suche->SuchAusg_oef($wert)."<br>";
	}	}
	else {
		$inhalt .= "nichts gefunden meinten Sie ".$Suche->Begriff_Repl($begriff);
}	}



?>

 
