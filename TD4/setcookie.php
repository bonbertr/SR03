
<?php 
	 if (isset($_GET['cookie_name']) && isset($_GET['cookie_value'])) {
			setcookie($_GET['cookie_name'], $_GET['cookie_value']);
			
			echo 'Deposer un nouveau cookie';
		}
		else{
			echo 'Deposer un cookie';
		}
?>
<form action="setcookie.php" method="get">
	<input type="text" name="cookie_name" >
	<input type="text" name="cookie_value" >
	<input type="submit" name="cookie_submit" value="envoyer" >
</form>

<?php
	echo 'Liste des cookies existants: <br/>';
	var_dump($_COOKIE);

	

/*	foreach ($_COOKIE as $key => $value){
			echo "<table><tr><td>$key</td>";
			echo "<td>$value</td></tr>";
		}
		echo '</table>';*/
?>
	<script>
window.location.replace='setcookie.php';
</script> 







