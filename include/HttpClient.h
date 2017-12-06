/*
 * HttpClient.h
 *
 *  Created on: 2017年12月6日
 *      Author: cplusplus
 */

#ifndef INCLUDE_HTTPCLIENT_H_
#define INCLUDE_HTTPCLIENT_H_

#include <string>
#include <vector>
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerResponse.h"
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

namespace BusinessUtil{

enum class EunmHttpMethod
{
	_post,
	_get
};

class HttpClient
{
public:
	/**
	 *
	 */
	static HttpClient* Create(std::string server , int port , int maxCnt = 4);

	/**
	 * ｐｓｏｔ请求
	 */
	std::string SendPostJsonRequest(std::string uri ,  std::string data);
	/**
	 * get 请求
	 */
	std::string SendGetJsonRequest(std::string uri , std::string data);


	void SetTimeout(int timeout);
private:
	HttpClient();
	HttpClient(std::string server , int port,int maxCnt);
	~HttpClient();
	HttpClient(const HttpClient &hc ) = delete;
	HttpClient& operator = (const HttpClient &hc) = delete;

	HttpClient(HttpClient &&hc ) = delete;
	HttpClient& operator = (HttpClient &&hc) = delete;

	void Initilize();
	/**
	 *获取ｓｅｓｓｉｏｎ
	 */
	Poco::Net::HTTPClientSession* GetHttpClientSession();
	/**
	 *　释放ｓｅｓｓｉｏｎ
	 */
	void ReleaseClientSession(Poco::Net::HTTPClientSession* sess);

	/**
	 *发送请求
	 */
	std::string SendRequest(std::string uri , std::string data , EunmHttpMethod method);

	unsigned int m_uCnt;       //最大连接数

	std::vector<Poco::Net::HTTPClientSession*> m_pool;

	std::mutex m_mutex;
	std::condition_variable m_condition;

	std::string m_server;
	int m_port;
	int m_timeout;
};

}




#endif /* INCLUDE_HTTPCLIENT_H_ */
