/*
 * MyTcpHandler.h
 *
 *  Created on: 2018年3月9日
 *      Author: cplusplus
 */

#ifndef MYTCPHANDLER_H_
#define MYTCPHANDLER_H_

#include <AmqpClient.h>
#include <iostream>
class MyTcpHandler : public BusinessUtil::ITcpHandler
{
public:
    MyTcpHandler(BusinessUtil::AmqpClient *amqpClient):ITcpHandler(amqpClient){}
    /**
     *  Method that is called by the AMQP library when the login attempt
     *  succeeded. After this method has been called, the connection is ready
     *  to use.
     *  @param  connection      The connection that can now be used
     */
    virtual void onConnected(AMQP::TcpConnection *connection)
    {
        // @todo
        //  add your own implementation, for example by creating a channel
        //  instance, and start publishing or consuming
        // and create a channel
    }

    /**
     *  Method that is called by the AMQP library when a fatal error occurs
     *  on the connection, for example because data received from RabbitMQ
     *  could not be recognized.
     *  @param  connection      The connection on which the error occured
     *  @param  message         A human readable error message
     */
    virtual void onError(AMQP::TcpConnection *connection, const char *message)
    {
		BusinessUtil::ITcpHandler::onError(connection , message);
        fprintf(stderr , "tcp handler error: %s \n" , message);
    }
};



#endif /* MYTCPHANDLER_H_ */
