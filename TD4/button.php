<?php
session_start();
$_SESSION['prenom']='Mayssa';
$_SESSION['nom']='Harzallah';
$_SESSION['age']='22';
echo session_id();
?>


<!doctype html>
<html>
<head>
		<title> SR03 TD4 PHP </title>
		<meta charset="utf-8">
		
		<script src="http://code.jquery.com/jquery-1.9.1.min.js"></script>
		<script type="text/javascript">
				function redirect()
					{
						
						document.location.href="http://tuxa.sme.utc/~sr03p012/display.php ? sessionid= <?php echo session_id(); ?>"

					}
		</script>
</head>
<body>
		<input type="button" onclick="redirect()" value="redirect me" >
</body>
</html>
