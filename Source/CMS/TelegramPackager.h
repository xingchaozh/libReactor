#pragma once

#include "../Common/Common.h"
#include "TelegramHeader.h"

namespace libReactor
{
	class LIB_REACTOR_API TelegramPackager
	{
	public:
		TelegramPackager();
		virtual ~TelegramPackager();

		//Buffer
		static UCHAR8 GetCharFromBuffer(UCHAR8 * & buffer);
		static UINT16 GetShortFromBuffer(UCHAR8 * & bufferPtr, NET_BYTE_ORDER netByteOrder = NET_BYTE_BIG_ENDIAN);// = NET_BYTE_BIG_ENDIAN);
		static UINT32 GetLongFromBuffer(UCHAR8 * & bufferPtr, NET_BYTE_ORDER netByteOrder = NET_BYTE_BIG_ENDIAN);// = NET_BYTE_BIG_ENDIAN)
		static NetPackageTime GetPackageTimeFromBuffer(UCHAR8 * & bufferPtr, NET_BYTE_ORDER netByteOrder = NET_BYTE_BIG_ENDIAN);// = NET_BYTE_BIG_ENDIAN);;

		static UINT16 PutCharToBuffer(UCHAR8 * & bufferPtr, UCHAR8 vle);
		static UINT16 PutShortToBuffer(UCHAR8 * & bufferPtr, UINT16 vle, NET_BYTE_ORDER netByteOrder = NET_BYTE_BIG_ENDIAN);// = NET_BYTE_BIG_ENDIAN);
		static UINT16 PutLongToBuffer(UCHAR8 * & bufferPtr, UINT32 vle, NET_BYTE_ORDER netByteOrder = NET_BYTE_BIG_ENDIAN);// = NET_BYTE_BIG_ENDIAN);

		//CRC
		static void CalculateCrc32(UINT32 * const crcPtr, const UCHAR8 * const bufferPtr, UINT16 const bufferLength);
		static bool CRC32Check(UCHAR8 * buffer, UINT16 bufferLength, NET_BYTE_ORDER netByteOrder);// = NET_BYTE_BIG_ENDIAN);

		//Decode
		bool TelegramDecode(Buffer & buffer, TelegramHeader * telegramHeader, void * telegramData);

		bool TelegramHeaderDecode(UCHAR8 * & buffer, TelegramHeader * telegramHeader);
		virtual bool TelegramHeaderAssign(UCHAR8 * & buffer, TelegramHeader * telegramHeader) = 0;
		virtual bool TelegramHeaderValidation(TelegramHeader * telegramHeader) = 0;

		bool TelegramDataDecode(UCHAR8 * & buffer, TelegramHeader * telegramHeader, void * telegramData);
		virtual void TelegramDataAssign(UCHAR8 * & buffer, TelegramHeader * telegramHeader, void * telegramData) = 0;
		virtual bool TelegramDataValidation(TelegramHeader * telegramHeader, void * telegramData) = 0;

		//Encode
		bool TelegramEncode(Buffer & buffer, TelegramHeader * telegramHeader, void * telegramData, int telegramDataLength = -1);

		virtual UINT16 TelegramDataEncode(UCHAR8 * & buffer, void * telegramData, int telegramDataLength = -1) = 0;

		void TelegramHeaderEncode(UCHAR8 * & buffer, TelegramHeader * telegramHeader);
		virtual void TelegramHeaderReassign(TelegramHeader * telegramHeader) = 0;
		virtual void TelegramHeaderPackage(UCHAR8 * & buffer, TelegramHeader * telegramHeader) = 0;

	protected:
		NET_BYTE_ORDER netByteOrder_;
	};
}

