<?php

/* SMART GINGERBREAD HOUSE
 *  
 * Have fun =)
 *
 * This file is part of the Estefannie Explains It All repo.
 *
 * (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
$onoroff = $_GET["state"]; // Declares the request from index.html as a variable

$textfile = "soundState.txt"; // Declares the name and location of the .txt file
 
$fileLocation = "$textfile";
$fh = fopen($fileLocation, 'w   ') or die("Something went wrong!"); // Opens up the .txt file for writing and replaces any previous content
$stringToWrite = "$onoroff"; // Write either 1 or 0 depending on request from index.html
fwrite($fh, $stringToWrite); // Writes it to the .txt file
fclose($fh); 
 
header("Location: index.html"); // Return to frontend (index.html)
?>
