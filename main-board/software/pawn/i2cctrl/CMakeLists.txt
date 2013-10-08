
set( LIB_NAME i2cctrl )

aux_source_directory( "./src" src )
message( STATUS "src: \"${src}\"" )

include_directories( "./src" 
                     ${GLOB_BIN_DIR} )

add_library( ${LIB_NAME} STATIC ${src} )




