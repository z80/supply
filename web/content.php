<?php
    include( "settings.php" );
    
    // echo( "<h1>" . $PAGES_ROOT . "</h1>" );
    
    function readDirs($path)
    {
        $dirHandle = opendir( $path );
        if ( $dirHandle == false )
            return;
        while ( $item = readdir( $dirHandle ) )
        {
            if ( ( $item != '.' ) && ( $item != '..' ) )
            {
                $newPath = $path."/".$item;
                if ( is_dir( $newPath ) )
                {
                    echo "Found Folder $newPath<br>";
                    readDirs($newPath);
                }
                else
                {
                    echo '&nbsp;&nbsp;Found File: ' . $item . '<br>';
                }
            }
        }
    }

    // echo "$path<br>";

    // readDirs($path);    
    
    function displayContent()
    {
        global $PAGES_ROOT;
        readDirs( $PAGES_ROOT );
    }
?>