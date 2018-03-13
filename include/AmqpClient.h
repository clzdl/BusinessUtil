/*
 * AmqpClient.h
 *
 *  Created on: 2018年3月12日
 *      Author: chengl
 */

#ifndef AMQPCLIENT_H_
#define AMQPCLIENT_H_
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <map>
#include <amqpcpp.h>
#include <amqpcpp/linux_tcp.h>
#include <memory>
#include <thread>         // std::thread
#include <mutex>          // std::mutex

namespace BusinessUtil{

class ITcpHandler;
class AmqpClient
{
public:
    /**
     * @user:  用户名
     * @pwd:  用户密码
     * @host:  主机地址
     * @port:  mq对应的端口
     * @vhost:  虚拟目录
     */
    AmqpClient(std::string user , std::string pwd, std::string host , short port , std::string vhost = "");
    ~AmqpClient();

    /**
     * 开启事件调度
     */
    void EventLoop(ITcpHandler *tcpHandler);

    /**
     * 创建通道
     */
    std::shared_ptr<AMQP::TcpChannel> CreateChannel();

    /**
     *关闭客户端链接
     */
    void CloseConnection();
    /**
     *  重建客户端链接
     */
    void ReBuildConnection();
    /**
     * 停止客户段运行
     */
    void Stop();

    /**
    * 事件监控，新线程中调用
    */
    void Run();
private:
    AmqpClient(const AmqpClient &qc ) = delete;
    AmqpClient(AmqpClient &&qc ) = delete;
    AmqpClient& operator = (const AmqpClient &qc ) = delete;
    AmqpClient& operator = (AmqpClient &&qc ) = delete;

    /**
     * 创建链接地址串
     */
    std::string BuildAddress(std::string user , std::string pwd, std::string host , short port , std::string vhost);

    std::map<int,int> m_fdMap;
    ITcpHandler *m_tcpHandler;
    AMQP::Address *m_address;
    AMQP::TcpConnection  *m_connection;   //底层链接
    bool m_stop;   ////是否停止
    ///时间监控线程
    std::thread *m_eventThread;
    friend class ITcpHandler;
};


class ITcpHandler: public AMQP::TcpHandler
{
public:
    ITcpHandler(AmqpClient *amqpClient):m_QmqpClient(amqpClient){}
    ~ITcpHandler() = default;
    /**
     *  Method that is called when the connection was closed. This is the
     *  counter part of a call to Connection::close() and it confirms that the
     *  connection was correctly closed.
     *
     *  @param  connection      The connection that was closed and that is now unusable
     */
    virtual void onClosed(AMQP::TcpConnection *connection) {
        if(!m_QmqpClient->m_stop)
        {
            m_QmqpClient->ReBuildConnection();
            return ;
        }
        m_QmqpClient->CloseConnection();
    }


    /**
     *  Method that is called by the AMQP-CPP library when it wants to interact
     *  with the main event loop. The AMQP-CPP library is completely non-blocking,
     *  and only make "write()" or "read()" system calls when it knows in advance
     *  that these calls will not block. To register a filedescriptor in the
     *  event loop, it calls this "monitor()" method with a filedescriptor and
     *  flags telling whether the filedescriptor should be checked for readability
     *  or writability.
     *
     *  @param  connection      The connection that wants to interact with the event loop
     *  @param  fd              The filedescriptor that should be checked
     *  @param  flags           Bitwise or of AMQP::readable and/or AMQP::writable
     */
    virtual void monitor(AMQP::TcpConnection *connection, int fd, int flags)
    {
        // @todo
        //  add your own implementation, for example by adding the file
        //  descriptor to the main application event loop (like the select() or
        //  poll() loop). When the event loop reports that the descriptor becomes
        //  readable and/or writable, it is up to you to inform the AMQP-CPP
        //  library that the filedescriptor is active by calling the
        //  connection->process(fd, flags) method.
        if(0 == flags )
        {
            m_QmqpClient->m_fdMap.erase(fd);
            return ;
        }

        m_QmqpClient->m_fdMap[fd]=flags;
    }

protected:
    AmqpClient *m_QmqpClient;
};

}

#endif /* AMQPCLIENT_H_ */
