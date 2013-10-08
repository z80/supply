
#include "supply.h"
#include "mcu_ctrl.h"

class Supply::PD
{
public:
    PD()
    {
        mcu = new McuCtrl();
    }

    ~PD()
    {
        delete mcu;
    }
    bool ensureOpen()
    {
        if ( !mcu->isOpen() )
            return mcu->open();
        return true;
    }

    McuCtrl * mcu;
};

Supply::Supply()
{
    pd = new PD();
}

Supply::~Supply()
{
    delete pd;
}

bool Supply::setIo( int index, int value )
{
    if ( !pd->ensureOpen() )
        return false;
    return pd->mcu->setIo( index, static_cast<unsigned char>( value ) );
}

int  Supply::io( int index )
{
    if ( !pd->ensureOpen() )
        return -1;
    unsigned char value;
    if ( !pd->mcu->io( index, value ) )
        return -2;
    return static_cast<int>( value );
}

bool Supply::reopen()
{
    pd->mcu->close();
    return pd->mcu->open();
}


