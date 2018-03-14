#include <time.h>
#include <thread>
#include <AmqpClient.h>
#include <MyTcpHandler.h>

const std::string message = "{\"ACCT_ID\":320150105718968,\"UESR_ID\":120150105199770,\"ADD_ID\":2018030775147003,\"TRADE_TYPE\":8001,\"THIS_FEE\":1000,\"IN_TYPE\":\"1\"}";

void Producer()
{
    BusinessUtil::AmqpClient amqpClient("bill", "BILL", "192.168.88.143" , 5672);
    //MyTcpHandler myHandler(&amqpClient);
    BusinessUtil::ITcpHandler myHandler(&amqpClient);
    amqpClient.EventLoop(&myHandler);

    std::shared_ptr<AMQP::TcpChannel> channel  = amqpClient.CreateChannel();
    channel->onError([](const char *message){
             std::cout<<"onError:"<<message<<std::endl;
         });
    channel->onReady([](){
             std::cout<<"channel onReady"<<std::endl;
    });

    // use the channel object to call the AMQP method you like
    channel->declareExchange("my-exchange", AMQP::direct);
    channel->declareQueue("my-queue");
    channel->bindQueue("my-exchange", "my-queue", "my-routing-key").onSuccess([channel](){
        std::cout<<"bindQueue success!" <<std::endl;
        for(int i = 0 ; i < 1000000 ; ++i)
        {
            channel->publish("my-exchange", "my-routing-key", message);
        }
    });


    while(!amqpClient.IsStop())
    {
       sleep(10);
    }
}

void Consumer()
{
    int total = 0;
    BusinessUtil::AmqpClient amqpClient("bill", "BILL", "192.168.88.143" , 5672);
    //MyTcpHandler myHandler(&amqpClient);
    BusinessUtil::ITcpHandler myHandler(&amqpClient);
    amqpClient.EventLoop(&myHandler);

    std::shared_ptr<AMQP::TcpChannel> channel  = amqpClient.CreateChannel();
    channel->onError([](const char *message){
        std::cout<<"onError:"<<message<<std::endl;
    });

    channel->onReady([&total,&channel](){
         std::cout<<"channel onReady"<<std::endl;
         channel->consume("my-queue").onReceived([&total,channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered){
             total +=1;
			 std::cout<<std::string(message.body(),message.bodySize())<<std::endl;
             channel->ack(deliveryTag);
        });
    });

    while(!amqpClient.IsStop())
    {
       sleep(10);
       std::cout<<"Consumer  consume total:"<<total<<std::endl;
    }
}

void ProducerAndConsumer()
{
    int consumeTotal = 0;
    BusinessUtil::AmqpClient amqpClient("bill", "BILL", "192.168.88.143" , 5672 );
    MyTcpHandler myHandler(&amqpClient);
    //BusinessUtil::ITcpHandler myHandler(&amqpClient);
    amqpClient.EventLoop(&myHandler);

    std::shared_ptr<AMQP::TcpChannel> channel  = amqpClient.CreateChannel();
    channel->onError([](const char *message){
        std::cout<<"onError:"<<message<<std::endl;
    });

    channel->onReady([](){
        std::cout<<"channel onReady"<<std::endl;
    });

    // use the channel object to call the AMQP method you like
    channel->declareExchange("my-exchange", AMQP::direct);
    channel->declareQueue("my-queue").onSuccess([&consumeTotal,channel](){
        channel->consume("my-queue").onReceived([&consumeTotal,channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered){
           consumeTotal +=1;
		   std::cout<<std::string(message.body(),message.bodySize())<<std::endl;
           channel->ack(deliveryTag);
       });
    });

    channel->bindQueue("my-exchange", "my-queue", "my-routing-key").onSuccess([channel](){
        std::cout<<"bindQueue success!" <<std::endl;
        for(int i = 0 ; i < 2000000 ; ++i)
        {
            channel->publish("my-exchange", "my-routing-key", message);
        }
    });

    while(!amqpClient.IsStop())
    {
        sleep(10);
        std::cout<<"ProducerAndConsumer consume:"<<consumeTotal<<std::endl;
    }
}

void PullMessage()
{
    int total = 0;
    BusinessUtil::AmqpClient amqpClient("bill", "BILL", "192.168.88.143" , 5672);
    //MyTcpHandler myHandler(&amqpClient);
    BusinessUtil::ITcpHandler myHandler(&amqpClient);
    amqpClient.EventLoop(&myHandler);

    std::shared_ptr<AMQP::TcpChannel> channel  = amqpClient.CreateChannel();
    channel->onError([](const char *message){
        std::cout<<"onError:"<<message<<std::endl;
    });

    channel->onReady([&total,&channel](){
         std::cout<<"channel onReady"<<std::endl;
    });

    while(!amqpClient.IsStop())
    {
       sleep(1);
       channel->get("my-queue").onSuccess([](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered){
           std::cout<<"get message:"<<std::string(message.body(),message.bodySize())<<std::endl;
       }).onEmpty([](){
           std::cout<<"queue is null"<<std::endl;
       });
    }
}

int main(int argc , char* argv[])
{
//    std::thread t1(ProducerAndConsumer);
//    std::thread t2(Producer);
//    std::thread t3(Consumer);
      std::thread t4(PullMessage);
//    t1.join();
//    t2.join();
//    t3.join();
      t4.join();

    return 0;
}
