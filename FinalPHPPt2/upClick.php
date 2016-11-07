<<!DOCTYPE html>
<html>
<body>

<?php
$currDir = getcwd()."/files/";
$currFile = $currDir.basename($_FILES['myFile']['name']);

if(move_uploaded_file($_FILES['myFile']['tmp_name'],$currFile)){
	//redirect back to a3.php
	header('Location: ./a3.php');
	echo "yes styll ".$currFile;
}
else{
	echo "NULL";
}

?>


</body>
</html>
