
set( LIB_NAME usbctrl0 )

set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS regex REQUIRED )

aux_source_directory( "./src" src )
set( src ${src} ${ROOT}/usbctrl/src/mcu_ctrl.cpp )
set( src ${src} src/libusb/opendevice.c )
message( STATUS "src: \"${src}\"" )

include_directories( "./src" 
                     "./src/libusb" 
                     "${ROOT}/usbctrl/src/" 
                     ${GLOB_BIN_DIR} 
                     ${Boost_INCLUDE_DIRS} 
                     "${LIBUSB0_INC_PATH}" 
                     "./src/libusb" )

add_library( ${LIB_NAME} STATIC ${src} )
find_library( libusb0 NAMES libusb.lib PATHS "${LIBUSB0_LIB_PATH}" ) 
target_link_libraries( ${LIB_NAME} ${libusb0} ${Boost_LIBRARIES} )




