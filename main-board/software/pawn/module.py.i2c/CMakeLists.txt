
set( LIB_NAME supplyctrli2c )

set( Boost_USE_STATIC_LIBS   True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS python REQUIRED )
find_package(PythonLibs REQUIRED)

aux_source_directory( "./src" src )

include_directories( "./src" 
                     "${ROOT}/i2cctrl/src"
                     ${GLOB_BIN_DIR}
                     ${Boost_INCLUDE_DIRS}
		     ${PYTHON_INCLUDE_DIRS} )

add_library( ${LIB_NAME} SHARED ${src} )
target_link_libraries( ${LIB_NAME} 
                                   ${Boost_LIBRARIES} 
                                   ${PYTHON_LIBRARIES}
                                   i2cctrl )
SET_TARGET_PROPERTIES( ${LIB_NAME} PROPERTIES PREFIX "" )
install( TARGETS ${LIB_NAME} DESTINATION "./python" )




