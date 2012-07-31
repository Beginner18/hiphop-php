--TEST--
Test finfo_open() function : basic functionality 
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php
/* Prototype  : resource finfo_open([int options [, string arg]])
 * Description: Create a new fileinfo resource. 
 * Source code: ext/fileinfo/fileinfo.c
 * Alias to functions: 
 */

$magicFile = dirname(__FILE__) . DIRECTORY_SEPARATOR . 'fileinfo/magic.mgc';

echo "*** Testing finfo_open() : basic functionality ***\n";

// Calling finfo_open() with different options
var_dump( finfo_open( FILEINFO_MIME, $magicFile ) );
var_dump( finfo_open( FILEINFO_NONE, $magicFile ) );
var_dump( finfo_open( FILEINFO_SYMLINK, $magicFile ) );
//var_dump( finfo_open( FILEINFO_COMPRESS, $magicFile ) );
var_dump( finfo_open( FILEINFO_DEVICES, $magicFile ) );
var_dump( finfo_open( FILEINFO_CONTINUE, $magicFile ) );
var_dump( finfo_open( FILEINFO_PRESERVE_ATIME, $magicFile ) );
var_dump( finfo_open( FILEINFO_RAW, $magicFile ) );
?>
===DONE===
--EXPECTF--
*** Testing finfo_open() : basic functionality ***
resource(4) of type (file_info)
resource(4) of type (file_info)
resource(4) of type (file_info)
resource(4) of type (file_info)
resource(4) of type (file_info)
resource(4) of type (file_info)
resource(4) of type (file_info)
===DONE===