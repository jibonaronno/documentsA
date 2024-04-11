<!DOCTYPE html>
<html>
  <head>
    <title>Very Simple PHP gallery</title>
    <meta charset="utf-8">

    <!-- (A) CSS & JS -->
    <link href="1b-gallery.css" rel="stylesheet">
    <script src="1c-gallery.js"></script>
  </head>
  <body>
    <div class="gallery"><?php
      // (B) GET IMAGES IN GALLERY FOLDER
      //$dir = __DIR__ . DIRECTORY_SEPARATOR . "gallery" . DIRECTORY_SEPARATOR;
	  $dir = __DIR__ . DIRECTORY_SEPARATOR;
	//printf("%s",$dir);
      $images = glob("*.{jpg,JPG,jpeg,gif,png,bmp,webp}", GLOB_BRACE);

      // (C) OUTPUT IMAGES
      foreach ($images as $i) {
	//printf(" %s <br>", $i);
        printf("<img src='%s'>", rawurlencode(basename($i)));
      }
    ?></div>
  </body>
</html>
