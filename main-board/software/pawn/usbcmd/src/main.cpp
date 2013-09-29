
#include "mcu_ctrl.h"

#include <iostream>
#include <sstream>

int main( int argc, char * argv[] )
{
    if ( argc < 2 )
    {
        std::cout << "Usage: expected compiled Pawn script file name to be flashed into a device";
        return 1;
    }

    McuCtrl c;
    bool res = c.open();
    if ( !res )
    {
        std::cout << "Failed to open device";
        return 2;
    }

    res = c.stop();
    if ( !res )
    {
        std::cout << "Pawn stop failed";
        return -1;
    }
    std::string result;
    res = c.flash( argv[1], result );
    std::cout << "Result: " << ( res ? "true" : "false" );
    if ( !res )
        return 3;
    res = c.start();
    if ( !res )
    {
        std::cout << "Pawn start failed\r\n";
        return -2;
    }
    return 0;
}

