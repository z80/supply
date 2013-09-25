
aux_source_directory( "./src" src )
message( STATUS "src: \"${src}\"" )

if ( UNIX )
    include( "../cmake/findlibusb-1.0.cmake" )
    message( STATUS ${LIBUSB_1_DEFINITIONS} )
endif ( UNIX )

include_directories( "./src" 
                     "${ROOT}/dfu/src" 
                     ${GLOB_BIN_DIR} )

if ( UNIX )
    include_directories( "${LIBUSB_1_INCLUDE_DIRS}" )
elseif ( WIN32 )
    include_directories( "${LIBUSB_INC_PATH}" )
endif ( UNIX )


add_executable( dfucmd ${src} )

if ( UNIX )
    target_link_libraries( dfucmd dfu ${LIBUSB_1_LIBRARIES} )
elseif ( WIN32 )
    find_library( dfucmd NAMES libusb-1.0.lib PATHS "${LIBUSB_LIB_PATH}" ) 
    target_link_libraries( dfucmd ${libusb} dfu ${Boost_LIBRARIES} )
endif ( UNIX )




