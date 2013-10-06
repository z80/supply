
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
add_subdirectory( "./tests" )
install( directory "./pawn_include/" destination "pawn" )
install( directory "./pawn_include/tests/" destination "pawn" )





