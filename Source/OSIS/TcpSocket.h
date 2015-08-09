#pragma once

#include "SocketX.h"

namespace libReactor
{
	class TcpSocket :
		public SocketX
	{
	public:
		TcpSocket(void);
		~TcpSocket(void);
	protected:
		void Create();
	};
}
