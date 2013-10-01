
#include "mcu_ctrl.h"
#include <string>
#include <sstream>
#include <boost/regex.hpp>


McuCtrl::McuCtrl()
: UsbIo()
{

}

McuCtrl::~McuCtrl()
{

}

bool McuCtrl::flash( const std::string & fileName, std::string & result )
{
    // Read all data from file.
    std::basic_string<unsigned char> data;
    const int SZ = 1024;
    data.resize( SZ );
    int cnt = 0;
    FILE * fp = fopen( fileName.c_str(), "r" );
    if ( !fp )
        return false;
    int flashPage = 0;
    do
    {
        msleep( 100 );
        cnt = fread( const_cast<unsigned char *>( data.data() ), 1, SZ, fp );
        for ( int i=0; i<cnt; i++ )
        {
            std::ostringstream out;
            out << "setMem ";
            out << i;
            out << " ";
            out << static_cast<int>( data[i] );
            out << "\r\n";
            // qDebug() << out.str().c_str();
            if ( this->write( out.str() ) < out.str().size() )
            {
                this->close();
                if ( !this->open() )
                {
                    fclose( fp );
                    result = "failed to reopen USB device after close\r\n";
                    return false;
                }
                if ( write( out.str() ) < out.str().size() )
                {
                    fclose( fp );
                    result = "failed to write data to USB\r\n";
                    return false;
                }
            }
        }
        std::ostringstream out;
        out << "wrFl ";
        out << flashPage++;
        out << "\r\n";
        // qDebug() << out.str().c_str();
        bool res = ( this->write( out.str() ) >= out.str().size() );
        if ( !res )
        {
            result = "Write FLASH command didn\'t pass to device\r\n";
            return false;
        }

        // Read back result.
        std::string stri;
        res = readString( stri );
        if ( !res )
        {
            fclose( fp );
            result = "can\'t read flash page write result\r\n";
            return false;
        }
        std::istringstream in( stri );
        int v;
        in >> v;
        if ( v != 0 )
        {
            fclose( fp );
            result = "flash write result isn\'t 0\r\n";
            return false;
        }
    }
    while ( cnt >= SZ );

    fclose( fp );

    return true;
}

bool McuCtrl::start()
{
    std::ostringstream out;
    out << "run\r\n";
    bool res = ( this->write( out.str() ) >= out.str().size() );
    return res;
}

bool McuCtrl::stop()
{
    std::ostringstream out;
    out << "stop\r\n";
    bool res = ( this->write( out.str() ) >= out.str().size() );
    return res;
}

bool McuCtrl::isRunning()
{
    std::ostringstream out;
    out << "isRun\r\n";
    bool res = ( this->write( out.str() ) >= out.str().size() );
    if ( !res )
        return false;

    std::string stri;
    res = readString( stri );
    if ( !res )
        return false;
    std::istringstream in ( stri );
    int v;
    in >> v;
    return ( v != 0 );
}

bool McuCtrl::setIo( int ind, unsigned char value )
{
    std::ostringstream out;
    out << "setIo ";
    out << ind;
    out << " ";
    out << static_cast<int>( value );
    out << "\r\n";
    bool res = ( this->write( out.str() ) >= out.str().size() );
    if ( !res )
        return false;
    return true;
}

bool McuCtrl::setIo( int ind, const std::basic_string<unsigned char> & args )
{
    std::ostringstream out;
    out << "setIo ";
    out << ind;
    out << " ";
    for ( unsigned i=0; i<args.size(); i++ )
    {
        out << static_cast<int>( args[i] );
        if ( i < (args.size() - 1) )
            out << " ";
    }
    out << "\r\n";
    bool res = ( this->write( out.str() ) >= out.str().size() );
    return res;
}

bool McuCtrl::io( int ind, unsigned char & value )
{
    std::ostringstream out;
    out << "io ";
    out << ind;
    out << "\r\n";
    bool res =( this->write( out.str() ) >= out.str().size() );
    if ( !res )
        return false;
    std::string stri;
    this->readString( stri );
    // Looking for a cnt numbers if string received.
    std::istringstream in( stri );
    int v;
    in >> v;
    value = static_cast<unsigned char>( v );
    return true;
}

bool McuCtrl::readString( std::string & stri )
{
    const int SZ = 64;
    std::string striBuf;
    striBuf.resize( SZ );
    stri.clear();
    for ( ;; )
    {
        int cnt = this->read( striBuf );
        if ( cnt <= 0 )
            break;
        int endIndex = striBuf.find( "}\r\n" );
        if ( endIndex != std::string::npos )
            striBuf = striBuf.substr( 0, endIndex + 2 );
        stri.append( striBuf );
        if ( endIndex != std::string::npos )
        {
            std::string::const_iterator start = stri.begin();
            std::string::const_iterator end   = stri.end();
            boost::regex patt( "\\{([\\d\\s]{1,})\\}" );
            boost::smatch match;
            if ( boost::regex_search( start, end, match, patt ) )
            {
                stri = match[1];
                return true;
            }
            return false;
        }
    }
    return false;
}



/*
bool McuCtrl::inputs( unsigned long * data, int len )
{
    std::string stri = "st\r\n";
    int cntWr = write( stri );
    int cntRd = read( stri );
    // Here it should be output parser.
    std::string::const_iterator start = stri.begin();
    std::string::const_iterator end   = stri.end();
    boost::regex patt( "\\{([\\w\\s]{1,})\\}" );
    boost::smatch match;
    if ( boost::regex_search( start, end, match, patt ) )
    {
        //std::cout << it->str() << "\n";
        std::string ss = match[1];
        std::istringstream in( ss );
        for ( int i=0; i<len; i++ )
            in >> data[i];
        return true;
    }
    return false;
}

bool McuCtrl::setOutputs( unsigned long * data, int len )
{
    std::ostringstream out;
    out << "out ";
    for ( int i=0; i<len; i++ )
    {
        out << data[i];
        if ( i < (len-1) )
            out << " ";
    }
    out << "\r\n";
    int cntWr = write( out.str() );
    std::string stri;
    stri.resize( 64 );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}

bool McuCtrl::accInit()
{
    // Accelerometer.
    unsigned char accAddr = 25,
                  magAddr = 30;
    unsigned char data[6];

    // Init acc.
    bool res = i2cSetAddr( accAddr );
    if ( !res )
        return false;
    data[0] = 0x20;
    data[1] = 0b00100111; //0x27;
    res = i2cSetBuf( 0, data, 2 );
    if ( !res )
        return false;
    res = i2cIo( 2, 0 );
    if ( !res )
        return false;
    msleep( 100 );
    int status = -1;
    res = i2cStatus( status );
    if ( !res )
        return false;
    //res = c.i2cStatus( status );
    //res = c.i2cStatus( status );

    res = i2cSetAddr( accAddr );
    if ( !res )
        return false;
    data[0] = 0x23;
    data[1] = 0b00000000;
    res = i2cSetBuf( 0, data, 2 );
    if ( !res )
        return false;
    res = i2cIo( 2, 0 );
    if ( !res )
        return false;
    msleep( 100 );
    status = -1;
    res = i2cStatus( status );
    if ( !res )
        return false;
    //res = i2cStatus( status );
    //res = i2cStatus( status );

    // Init mag.
    res = i2cSetAddr( magAddr );
    if ( !res )
        return false;
    data[0] = 0x00;
    data[1] = 0b10010000; //0x00;
    res = i2cSetBuf( 0, data, 2 );
    if ( !res )
        return false;
    res = i2cIo( 2, 0 );
    if ( !res )
        return false;
    msleep( 100 );
    status = -1;
    res = i2cStatus( status );
    if ( !res )
        return false;
    //res = i2cStatus( status );
    //res = i2cStatus( status );

    data[0] = 0x02;
    data[1] = 0b00000000; //0x00;
    res = i2cSetBuf( 0, data, 2 );
    if ( !res )
        return false;
    res = i2cIo( 2, 0 );
    if ( !res )
        return false;
    msleep( 100 );
    status = -1;
    res = i2cStatus( status );
    if ( !res )
        return false;
    //res = i2cStatus( status );
    //res = i2cStatus( status );
    return true;
}

bool McuCtrl::accAcc( int & x, int & y, int & z )
{
    unsigned char accAddr = 25;
    unsigned char data[6];
    int g[3];

    bool res = i2cSetAddr( accAddr );
    if ( !res )
        return false;
    // Reading back.
    data[0] = (0x28 | (1<<7));
    res = i2cSetBuf( 0, data, 1 );
    if ( !res )
        return false;
    res = i2cIo( 1, 6 );
    if ( !res )
        return false;
    msleep( 50 );
    int status = -1;
    res = i2cStatus( status );
    if ( !res )
        return false;
    if ( status != 0 )
        return false;
    //res = i2cStatus( status );
    //res = i2cStatus( status );
    res = i2cBuffer( 6, data );
    if ( !res )
        return false;
    for ( int j=0; j<3; j++ )
    {
        g[j] = ( static_cast<int>(data[j*2]) | (static_cast<int>(data[j*2+1]) * 256) );
        if ( g[j] & (1<<15) )
            g[j] -= 65536;
    }
    x = g[0];
    y = g[1];
    z = g[2];
    return true;
}

bool McuCtrl::accMag( int & x, int & y, int & z )
{
    unsigned char magAddr = 30;
    unsigned char data[6];
    int g[3];

    bool res = i2cSetAddr( magAddr );
    if ( !res )
        return false;
    // Mag read.
    data[0] = 0x03;
    res = i2cSetBuf( 0, data, 1 );
    if ( !res )
        return false;
    res = i2cIo( 1, 6 );
    if ( !res )
        return false;
    msleep( 50 );
    int status = -1;
    res = i2cStatus( status );
    if ( !res )
        return false;
    if ( status != 0 )
        return false;
    //res = i2cStatus( status );
    //res = i2cStatus( status );
    res = i2cBuffer( 6, data );
    if ( !res )
        return false;
    for ( int j=0; j<3; j++ )
    {
        g[j] = (static_cast<int>(data[j*2]) * 256) | static_cast<int>(data[j*2+1]);
        if ( g[j] & (1<<15) )
            g[j] -= 65536;
    }
    // The order is x, z, y.
    x = g[0];
    z = g[1];
    y = g[2];
    return true;
}

bool McuCtrl::accTemp( int & t )
{
    unsigned char magAddr = 30;
    unsigned char data[6];

    bool res = i2cSetAddr( magAddr );
    if ( !res )
        return false;
    // Temp read.
    data[0] = 0x31;
    res = i2cSetBuf( 0, data, 1 );
    if ( !res )
        return false;
    res = i2cIo( 1, 2 );
    if ( !res )
        return false;
    msleep( 50 );
    int status = -1;
    res = i2cStatus( status );
    if ( !res )
        return false;
    if ( status != 0 )
        return false;
    //res = i2cStatus( status );
    //res = i2cStatus( status );
    res = i2cBuffer( 2, data );
    if ( !res )
        return false;
    t = static_cast<int>( data[0]) * 256 + static_cast<int>(data[1]);
    return true;
}


bool McuCtrl::i2cSetAddr( int addr )
{
    std::ostringstream out;
    out << "addr ";
    out << addr;
    out << "\r\n";
    int cntWr = write( out.str() );
    std::string stri;
    stri.resize( 64 );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}

bool McuCtrl::i2cSetBuf( int start, unsigned char * data, int cnt )
{
    std::ostringstream out;
    out << "set_buf ";
    out << start;
    for ( int i=0; i<cnt; i++ )
    {
        out << " ";
        out << static_cast<int>( data[i] );
    }
    out << "\r\n";
    int cntWr = write( out.str() );
    std::string stri;
    stri.resize( 64 );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}

bool McuCtrl::i2cIo( int txCnt, int rxCnt )
{
    std::ostringstream out;
    out << "io ";
    out << txCnt;
    out << " ";
    out << rxCnt;
    out << "\r\n";
    int cntWr = write( out.str() );
    std::string stri;
    stri.resize( 64 );
    int cntRd = read( stri );
    return ( cntRd >= cntWr );
}

bool McuCtrl::i2cStatus( int & status )
{
    std::ostringstream out;
    out << "status\r\n";
    int cntWr = write( out.str() );
    std::string stri;
    stri.resize( 64 );
    int cntRd = read( stri );
    std::string::const_iterator start = stri.begin();
    std::string::const_iterator end   = stri.end();
    boost::regex patt( "\\{([\\w\\s]{1,})\\}" );
    boost::smatch match;
    if ( boost::regex_search( start, end, match, patt ) )
    {
        std::string ss = match[1];
        std::istringstream in( ss );
        in >> status;
        return true;
    }
    return false;
}

bool McuCtrl::i2cBuffer( int cnt, unsigned char * data )
{
    std::ostringstream out;
    out << "buffer ";
    out << cnt;
    out << "\r\n";
    int cntWr = write( out.str() );
    std::string stri;
    stri.resize( 64 );
    int cntRd = read( stri );
    std::string::const_iterator start = stri.begin();
    std::string::const_iterator end   = stri.end();
    boost::regex patt( "\\{([\\w\\s]{1,})\\}" );
    boost::smatch match;
    if ( boost::regex_search( start, end, match, patt ) )
    {
        std::string ss = match[1];
        std::istringstream in( ss );
        for ( int i=0; i<cnt; i++ )
        {
            int v;
            in >> v;
            data[i] = static_cast<unsigned char>( v );
        }
        return true;
    }
    return false;
}
*/








