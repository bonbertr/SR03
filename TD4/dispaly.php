<?php
 session_id($GET['sessionid']);
	session_start();
	$_SESSION['adresse']='rue Edouard Branly';
	$_SESSION['ville']='Compiegne';
	$_SESSION['codepostal']='60200';
	print_r($_SESSION);
                                                                            
?>

<!doctype html>
<html>
<head>
		<title>sr03 TD4 php </title>
		<meta charset="utf-8">
</head>

<body>
</body>
</html>
