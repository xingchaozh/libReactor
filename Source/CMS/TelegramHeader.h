#pragma once

#include "../Common/Common.h"

namespace libReactor
{
	class LIB_REACTOR_API TelegramHeader
	{
	public:
		TelegramHeader();
		virtual ~TelegramHeader();
	public:
		virtual void Reset()
		{
			/*UINT16 */Type = 0;
			/*UINT16 */Version = 0;
			/*UINT16 */ReceiverType = 0;
			/*UINT16 */ReceiverID = 0;
			/*UINT16 */TransmitterType = 0;
			/*UINT16 */TransmitterID = 0;
			/*NetPackageTime */Time.Year = 0;
			Time.Month = 0;
			Time.Day = 0;
			Time.Hour = 0;
			Time.Minute = 0;
			Time.Second = 0;
			Time.Millisecond = 0;
			/*UINT16 */RSN = 0;
			/*UINT16 */TSN = 0;
			/*UINT16 */DataLength = 0;
		}
		virtual void SetDataLength(int length)
		{
			DataLength = length;
		}
	public:
		UINT16 Type;
		UINT16 Version;
		UINT16 ReceiverType;
		UINT16 ReceiverID;
		UINT16 TransmitterType;
		UINT16 TransmitterID;
		NetPackageTime Time;
		UINT16 RSN;
		UINT16 TSN;
		UINT16 DataLength;
		//Message MessageData;
		//UINT16 CRC16;
		int size_;
	};
}

