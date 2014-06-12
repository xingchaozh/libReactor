#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "CommonX.h"

class DataHandler
{
public:
    DataHandler();
public:
    virtual void DataHanle(UdpBuffer & udpBuffer) = 0;
};

#endif // DATAHANDLER_H
