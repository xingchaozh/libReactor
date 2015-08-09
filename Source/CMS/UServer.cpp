#include "UServer.h"
#include "UServerBase.h"
namespace libReactor
{
UServer::UServer(void)
{
	m_serverBase = new UServerBase();
}

UServer::~UServer(void)
{
	delete m_serverBase;
}

bool  UServer::SetParameters(UINT16 bufferSize, UINT16 numDataReader, UINT16 numDataProcesser, long timeOut)
{
	return m_serverBase->SetParameters(bufferSize, numDataReader, numDataProcesser, timeOut);
}

void UServer::Execute(string serverHost,       //Local host location
						  int serverPort,              //Local host port
						  string dataHandlerClassName)
{
	m_serverBase->Execute(serverHost, serverPort, dataHandlerClassName);
}

bool UServer::HandleOutput(UdpBuffer & udpBuffer)
{
	return m_serverBase->HandleOutput(udpBuffer);
}
}
