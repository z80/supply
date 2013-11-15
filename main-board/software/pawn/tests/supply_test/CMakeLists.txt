set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS regex REQUIRED )

include_directories( "./src" 
                     "${ROOT}/usbctrl/src"
                     ${Boost_INCLUDE_DIRS} )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )

add_executable( supply_test ${src} )
set( libs usbctrl0 )
target_link_libraries( supply_test ${libs} )
install( TARGETS supply_test DESTINATION "./" )




