
set( EXEC_NAME usbcmd )

include_directories( "./src" 
                     "${ROOT}/usbctrl/src" )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )

add_executable( ${EXEC_NAME} ${src} )
if ( UNIX )
    set( libs usbctrl )
elseif ( WIN32 )
    set( libs usbctrl0 )
endif ( UNIX )
target_link_libraries( ${EXEC_NAME} ${libs} )
install( TARGETS ${EXEC_NAME} DESTINATION "./bin" )




