
cmake_minimum_required( VERSION 2.6 )
project( "embedding_pawn" )
set( ROOT ${CMAKE_CURRENT_SOURCE_DIR} )
set( CMAKE_INSTALL_PREFIX ${ROOT}/build.app )
if ( WIN32 )
    include( "./config-win.cmake" )
endif ( WIN32 )
add_subdirectory( "./3dparty" )
add_subdirectory( "./usbctrl" )
add_subdirectory( "./usbcmd" )
add_subdirectory( "./module.py.usb" )
if ( UNIX )
    add_subdirectory( "./i2cctrl" )
    add_subdirectory( "./module.py.i2c" )
elseif ( WIN32 )
    add_subdirectory( "./usbctrl0" )
endif ( UNIX )
add_subdirectory( "./tests" )
install( DIRECTORY "./pawn_include/include/"         DESTINATION "include" )
install( DIRECTORY "../../../main-board-2/firmware/pawn_header/" 
                                                     DESTINATION "include" )
install( DIRECTORY "./pawn_include/examples/"        DESTINATION "examples" )
install( DIRECTORY "./pawn_include/examples_python/" DESTINATION "python" )
install( DIRECTORY "./gui.py/"                       DESTINATION "./" )
install( DIRECTORY "./doc/"                          DESTINATION "./doc" )




