/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : TcpSocketXO.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#pragma once
#include "socketxo.h"
class TcpSocketXO :
	public SocketXO
{
public:
	TcpSocketXO(void);
	~TcpSocketXO(void);
protected:
	void Create();
};

