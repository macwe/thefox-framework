#include <net/TcpConnection.h>
#include <net/Socket.h>
using namespace thefox;

TcpConnection::TcpConnection(const String &name, 
							SOCKET socket, 
							const InetAddress &localAddr, 
							const InetAddress &peerAddr)
	: _name(name)
	, _socket(new Socket(socket))
	, _localAddr(localAddr)
	, _peerAddr(peerAddr)
{
	_socket->setKeepAlive(true);
	IoContext *ioContext = new IoContext(IoContext::IoType::Recv);
	if (_socket->postRecv(ioContext))
	{
		_ioConetxts.puch_back(ioContext);
	}
	else
	{
		delete ioContext;
	}
}

void TcpConnection::send(const void* data, size_t len)
{
	if (_state == kConnected)
	{
		size_t remain = len;
		while (remain)
		{
            size_t sendLen = (remain > IoContext::kMaxBufLen) ? IoContext::kMaxBufLen : remain;
			IoContext * ioContext = getFreeIoContext();
			ioContext->setIoType(IoContext::IoType::Send);
            ioContext->setBuffer(data, sendLen);
            remain -= sendLen;
            data += sendLen;
		}
	}
}

void TcpConnection::shutdown()
{

}

void TcpConnection::setTcpNoDelay(bool on)
{
  socket_->setTcpNoDelay(on);
}

void TcpConnection::handleRead(IoContext *ioContext, Timestamp receiveTime)
{
    _inBuffer.readIoContext(*ioContext);
    _messageCallback(this, _inBuffer, receiveTime);
    
    ioContext->resetBuffer();
    _socket->postRecv(ioContext)
}

void TcpConnection::handleWrite()
{

}

void TcpConnection::handleClose()
{

}

void TcpConnection::handleError()
{
	
}