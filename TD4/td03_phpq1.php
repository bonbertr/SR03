<?php
	$filename = "./chienpapillon.jpg";
	$handle = fopen($filename, "r");
	$contents = fread($handle, filesize($filename));
	$base64 = base64_encode($contents); 
	fclose($handle);
	echo "<img src=data:image/jpg;base64,$base64 alt='A dog catching butterflies' />";
?>


