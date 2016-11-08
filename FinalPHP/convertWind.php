<!DOCTYPE html>
<html>
<head>
<title>Convert</title>
</head>


<body style="background-color:#808080;color:white">

<div id="cancButt" style="position:fixed; left:140px; bottom:10px;">
        <button id="CANCEL" for="CANCEL" onclick="window.close()">
                <b>CANCEL<b>
        </button>
</div>

<div id="fileList" style="position: fixed; left: 60px; top: 15px;">
	<fieldset>
	    <form action="" method="post">
		<?php
			$dir = getcwd()."/files";
			$currFiles = scandir($dir, 1);

			 foreach($currFiles as &$fpNames){
                                if(strpos($fpNames, ".html") == false && strlen($fpNames) > 2){
					if(strpos($fpNames, ".info") == false){
						echo "<input type=\"radio\" name=\"fileName\" value=\"$fpNames\" >", $fpNames, "<br>";
					}
				}
                        }
                        unset($fpNames);
		?>
		<input type="submit" name="submit" value="Ok" style="position: fixed; left: 70px; bottom:10px;" />
	    </form>
		<?php
			$currDir = getcwd()."/files/";
			$currFile = $currDir.basename($_FILES['myFile']['name']);

			if(isset($_POST['submit'])){
				if(isset($_POST['fileName'])){
					$fpValue = "./files/".$_POST['fileName'];
					//echo "You have: ".$fpValue;
					exec("./a2 ".$fpValue, $out);

					print_r($out);
				}
        				//header('Location: ./a3.php');
					exit();
			}
		?>
	</fieldset>
</div>



</body>




</html>
