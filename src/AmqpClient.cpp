/*
 * AmqpClient.cpp
 *
 *  Created on: 2018年3月12日
 *      Author: chengl
 */

#include <AmqpClient.h>
#include <sstream>

namespace BusinessUtil{

AmqpClient::AmqpClient(std::string user , std::string pwd, std::string host , short port , std::string vhost)
:m_stop(false),
 m_connection(nullptr),
 m_tcpHandler(nullptr),
 m_eventThread(nullptr)
{
    m_address = new AMQP::Address(BuildAddress(user,pwd,host,port,vhost));
}

AmqpClient::~AmqpClient()
{
    CloseConnection();
    delete m_address;
    m_eventThread->join();
    delete m_eventThread;
}

void AmqpClient::EventLoop(ITcpHandler *tcpHandler)
{
    m_tcpHandler = tcpHandler;
    m_connection = new AMQP::TcpConnection(tcpHandler , *m_address);
    m_eventThread = new std::thread(std::bind(&AmqpClient::Run ,this));
}

void AmqpClient::ReEventLoop()
{
    CloseConnection();
    m_eventThread->join();
    delete m_eventThread;

    m_connection = new AMQP::TcpConnection(m_tcpHandler , *m_address);
    m_eventThread = new std::thread(std::bind(&AmqpClient::Run ,this));
}

void AmqpClient::Stop()
{
    m_stop = true;
    CloseConnection();
}

bool AmqpClient::IsStop()
{
    return m_stop;
}

void AmqpClient::CloseConnection()
{
    if(m_connection)
    {
        m_connection->close();
        delete m_connection;
        m_connection = nullptr;
    }
}

void AmqpClient::Run()
{
    int err  = 0;
    int maxFd = 0;
    fd_set readSet;
    fd_set wirteSet;
    while(!m_stop)
    {
        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        FD_ZERO(&readSet);
        FD_ZERO(&wirteSet);
        for(auto it : m_fdMap)
        {
            if(it.second & AMQP::readable)
                FD_SET(it.first , &readSet);

            if(it.second & AMQP::writable )
                FD_SET(it.first , &wirteSet);

            if(it.first > maxFd)
                maxFd = it.first;
        }
        err = select(maxFd + 1, &readSet, &wirteSet, NULL, &tv);
        if( err == EINTR)
        {
            continue;
        }
        else if (err < 0)
        {
            fprintf(stderr , "select error.\n");
            continue;
        }
        else if (err == 0)
        {
            fprintf(stderr , "select timeout.\n");
            continue;
        }

        int flags = 0;
        for(auto it : m_fdMap)
        {
            flags = 0;
            if(FD_ISSET(it.first,&readSet))
            {
                flags |= AMQP::readable;
            }

            if(FD_ISSET(it.first,&wirteSet))
            {
                flags |= AMQP::writable;
            }
            m_connection->process(it.first , flags);
        }
    }
}


std::string AmqpClient::BuildAddress(std::string user , std::string pwd, std::string host , short port , std::string vhost)
{
    std::stringstream ss;
    ss<<"amqp://"<<user<<":"<<pwd<<"@"<<host<<":"<<port<<"/"<<vhost;
    return ss.str();
}

std::shared_ptr<AMQP::TcpChannel> AmqpClient::CreateChannel()
{
    return  std::make_shared<AMQP::TcpChannel>(m_connection);
}

}
