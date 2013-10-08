
set( DFU_FROM_BIN dfu_from_bin )
set( DFU_STM      dfu_stm )

if ( UNIX )
    include( "${ROOT}/3dparty/cmake/findlibusb-1.0.cmake" )
    message( STATUS ${LIBUSB_1_DEFINITIONS} )
endif ( UNIX )

include_directories( "./src" 
                     ${GLOB_BIN_DIR} )
if ( UNIX )
    include_directories( "${LIBUSB_1_INCLUDE_DIRS}" )
elseif ( WIN32 )
    include_directories( "${LIBUSB_INC_PATH}" )
endif ( UNIX )

set( src_dfu_from_bin "./src/dfuse.c" 
                      "./src/crc32.c" 
		      "./src/bintodfu.c" )
set( src_dfu_stm      "./src/dfucommands.c" 
                      "./src/dfurequests.c" 
		      "./src/dfuse.c" 
		      "./src/crc32.c" 
		      "./src/stmdfu.c" )

add_executable( ${DFU_FROM_BIN} ${src_dfu_from_bin} )
add_executable( ${DFU_STM}      ${src_dfu_stm} )

if ( UNIX )
    target_link_libraries( ${DFU_FROM_BIN} m )
    target_link_libraries( ${DFU_STM}      ${LIBUSB_1_LIBRARIES} m )
elseif ( WIN32 )
    find_library( libusb NAMES libusb-1.0.lib PATHS "${LIBUSB_LIB_PATH}" ) 
    target_link_libraries( ${DFU_STM} ${libusb} ${Boost_LIBRARIES} )
endif ( UNIX )

install( TARGETS ${DFU_FROM_BIN} ${DFU_STM} DESTINATION "./bin" )

