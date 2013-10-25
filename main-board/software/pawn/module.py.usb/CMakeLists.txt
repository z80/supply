
if ( WIN32 )
    include( ${ROOT}/config-win.cmake )
endif ( WIN32 )

set( LIB_NAME supplyctrlusb )

# In windows it can't link static library somewhy...
if ( UNIX )
    set( Boost_USE_STATIC_LIBS   True )
elseif ( WIN32 )
	set( Boost_USE_STATIC_LIBS   False )
endif ( UNIX )
set( Boost_USE_MULTITHREADED True )
#if ( UNIX )
    find_package( Boost COMPONENTS python REQUIRED )
#endif ( UNIX )
find_package(PythonLibs REQUIRED)

aux_source_directory( "./src" src )

include_directories( "./src" 
                     "${ROOT}/usbctrl/src"
                     ${GLOB_BIN_DIR}
                     ${Boost_INCLUDE_DIRS}
		     ${PYTHON_INCLUDE_DIRS} )

add_library( ${LIB_NAME} SHARED ${src} )
if ( UNIX )
target_link_libraries( ${LIB_NAME} 
                                   ${Boost_LIBRARIES} 
                                   ${PYTHON_LIBRARIES}
                                   usbctrl )
elseif ( WIN32 )
	# for windows somewhy doesn't find library by it's name. WTF(!!!)
	target_link_libraries( ${LIB_NAME} 
									   ${Boost_LIBRARIES} 
									   ${PYTHON_LIBRARIES}
									   usbctrl )
									   #${ROOT}/../../../_temp/py.lib )
endif ( UNIX )
SET_TARGET_PROPERTIES( ${LIB_NAME} PROPERTIES PREFIX "" )
install( TARGETS ${LIB_NAME} DESTINATION "./python" )




