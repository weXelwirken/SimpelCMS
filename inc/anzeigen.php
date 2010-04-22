<?php
session_start();

//Session mit den grafiknamen fuellern
$_SESSION['cpt_namen'] = array("mac", "tux", "win");

//Wenn Post dann testen ob richtig
if($_POST['send']==true) {
	//Warten
	sleep(0.7);

	//Richtig oder falsch
	if($_POST['wert']==$_SESSION['cpt_werte'][$_SESSION['cpt_zuf']]) {
	
		echo "captcha gültig";
	
	}
	else {
	
		echo "captcha ungültig";
	}
	
	//Array loeschen
	unset($_SESSION['cpt_namen']);
	unset($_SESSION['cpt_werte']);


}
else {

	//CPT aufbauen

    echo '<img src="cpt.php" alt="blubb">';

	//Warten
	sleep(0.7);
	
	//Zuf. Wert fuer abfrage
	$zuf_wert = rand(0, count($_SESSION['cpt_namen'])-1);
	$_SESSION['cpt_zuf'] = $zuf_wert;
	echo $zuf_wert;
?>

<form action="#" method="post">
	Wie viele <?php echo $_SESSION['cpt_namen'][$zuf_wert]; ?> - Symbole sind vorhanden? <br />
	
	<input type="text" name="wert">
		<input type="submit" name="send" value="send">
</form>
<?php 
}
?>