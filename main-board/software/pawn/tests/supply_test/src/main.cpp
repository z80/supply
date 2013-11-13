
#include "mcu_ctrl.h"
#include <iostream>
#include <string>
#include <sstream>


int main( int argc, char * argv[] )
{
    McuCtrl c;
    bool res = c.open();
    if ( !res )
    {
        std::cout << "Failed to open device";
        return 2;
    }
    c.stop();
    res = c.isRunning();
    if ( !res )
    {
        std::cout << "Script isn\'t running at the moment. Trying to turn it on.\r\n";
        //c.start();
    }
    //res = c.setIo( 0, 1 );
    //res = c.setIo( 1, 2 );
    //res = c.setIo( 2, 3 );

    for ( ;; )
    {
        const int SZ = 7;
        unsigned char io[SZ];
        std::ostringstream out;
        for ( int i=0; i<SZ; i++ )
        {
            res = c.io( i, io[i] );

            out << static_cast<int>( io[i] );
            if ( i<(SZ-1) )
                out << " ";
            else
                out << "\r\n";
        }
        std::string stri = out.str();
        std::cout << stri;
    }

    return 0;
}

