/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : SvcHandler.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "SvcHandler.h"

SvcHandler::SvcHandler(void)
{
}

SvcHandler::~SvcHandler(void)
{
}

int SvcHandler::IsReadable(int socketId,int * errorCode,int timeOut) // milliseconds
{
	fd_set socketReadSet;

	//Initialize the set
	SocketXO::FD_ZERO_X(&socketReadSet);

	//put m_socket->GetSocket() into the set
	SocketXO::FD_SET_X(socketId,&socketReadSet);

	struct timeval tvTimeout;
	if (timeOut > 0)
	{
		tvTimeout.tv_sec  = timeOut / 1000;
		tvTimeout.tv_usec = (timeOut % 1000) * 1000;
	}
	else
	{
		tvTimeout.tv_sec  = 0;
		tvTimeout.tv_usec = 0;
	}

	//check the status of the socket I/O
	int ret = SocketXO::Select(socketId+1,&socketReadSet,0,0,&tvTimeout);
	if (ret == SOCKET_ERROR)
	{
		*errorCode = 1;
		return 0;
	}

	*errorCode = 0;
	return SocketXO::FD_ISSET_X(socketId,&socketReadSet) != 0;
} /* isReadable */

