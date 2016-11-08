<!DOCTYPE html>
<html>

<head>
<title>a3.php</title>
<link href="cssPop.css" type="text/css" rel="stylesheet" />

<script>
function popWind(buttonName){
        window.open("convertWind.php", buttonName, "height=400, width=300, scrollbars=yes");
}

function uploadClick(elemId){
        document.getElementById(elemId).click();
        document.getElementById("myFile").addEventListener("change", submitClick);
}

function submitClick(){
        document.getElementById("subFile").click();
}

function toggle_popUp(elemId){
	var e = document.getElementById(elemId);
	if(e.style.display == "block"){
		e.style.display = "none";
	}
	else{
		e.style.display = "block";
	}
}

</script>

<style>
colorUp{
        color: black;
}

big{
        font-size: 23px;
}
bordChange{
        border-style: solid;
}

fieldset{
	display: block;
	margin-left: -18px;
	padding-left: 1.90em;
	padding-right: 1.90em;
	padding-bottom: 1.90em;
	border: 3px solid white;
	border-style: solid;
	border-radius: 12px;
}
</style>

</head>

<body bgcolor=808080>

<?php
$dir = getcwd()."/files";
//make sure to take out the bgordo01 since it will ONLY be in /srv/www
$cisServer = "https://2750web.socs.uoguelph.ca/bgordo01/";
$currFiles = scandir($dir,1);
?>

<div id="conDiv" style="position: fixed; left: 180px; top: 50px;">
        <div id="wrapper" style="position:fixed; left: 570px; top:10px;">
                <button id="Con" onclick="toggle_popUp('conPop');" style="height:50px;width:150px;" >
                        <a href="javascript:void(0)"><b><big>Convert</big></b></a>
                </button>
        </div>
</div>

<div id="conPop" class="popup-position" style="position: fixed; top: 300px; left: 560px">
	<div id="pop_wrapper">
		<div id="pop_cont">
			<h3>Convert</h3>
				<div id="fileList" style="position:fixed; left:575px;">
					<fieldset style="width:460px;">
						<form action = "" method="post">
							<?php
								foreach($currFiles as $fpNames){
									if(strpos($fpNames, ".html") == false && strlen($fpNames) > 2){
										if(strpos($fpNames, ".info") == false){
					                                                //echo "<input type=\"radio\" name=\"fileName\" value=$fpNames\" >", $fpNames, "<br>";
                                					        	echo "<input type='radio' name='fileName' value=$fpNames>", $fpNames, "<br>";
										}
									}
								}
								unset($fpNames);
							?>
							<button id="submitCon" type="submit" name="submitCon" value="Ok" style="position: fixed; left: 585px; bottom:290px;">Ok</button>
						<!-- </form> -->
						<?php
				                        //$currDir = getcwd()."/files/
                       					//$currFile = $currDir.basename($_FILES['myFile']['name']);

      					                if(isset($_POST['submitCon'])){
                                				if(isset($_POST['fileName'])){
                                        				$fpValue = "./files/". $_POST['fileName'];
									//echo $fpValue;
                                        				exec("./a3 ".$fpValue);
                                        				//print_r($out);
                                				}
			                                        header('Location: ./a3.php');
                                        			//exit();
                        				}
                				?>
						</form>
					</fieldset>
				</div>
				<div id="cancButt" style="position:fixed; left:670px; bottom:290px;">
        				<button id="CANCEL" onclick="toggle_popUp('conPop');">
                				 <a href="javascript:void(0)">Cancel</a>
        				</button>
				</div>
		</div>
	</div>
</div>

<!-- Uploading Button & functionality as form -->
<div id="upDiv" style="position: fixed; left: 960px; top: 50px;">
	<button id="upButt" style="height:50px;width:150px;" type="button" onclick="uploadClick('myFile');"><b><big><colorUp>Upload</colorUp></b></big></button>
</div>

<form id="upLoading" method="post" action="upClick.php" enctype="multipart/form-data">
	<input id="myFile" name="myFile" type="file" style="display:none;"/>
	<input id="subFile" value="Upload" type="submit" style="display:none;"/>
</form>

<!-- Uploading Button & functionality as form -->

<div id="rawFileDiv" style="position: fixed; left: 590px; top: 100px;">
	<fieldset>
		<?php
			foreach($currFiles as &$fpNames){
                                if((strpos($fpNames, ".html") == false) && (strlen($fpNames) > 2)){
                                        if(strpos($fpNames, ".info") == false){
						//if(strpost($fpNames, ".html") == false){
						echo "<a href=\"files/$fpNames\">", $fpNames."<br>", "</a> ";
                                		//}
					}
				}
                        }
                        unset($fpNames);
		?>
	    <!-- </a> -->
	</fieldset>
</div>

<div id="htmlDiv" style="position: fixed; left: 980px; top: 100px;">
        <fieldset>
                <?php
                        foreach($currFiles as &$fpNames){
                                if(strpos($fpNames, ".html") == true){
					echo "<a href=\"files/$fpNames\">", $fpNames."<br>", "</a> ";
                                }
                        }
                        unset($fpNames);
                ?>
        </fieldset>
</div>


</body>
</html>
