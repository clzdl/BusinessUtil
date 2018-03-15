/*
 * HttpClient.cpp
 *
 *  Created on: 2017年12月6日
 *      Author: cplusplus
 */


#include "HttpClient.h"
#include "BusiExceptions.h"

namespace BusinessUtil{

HttpClient* HttpClient::Create(std::string server , int port,int maxCnt)
{
	HttpClient *ptr = new HttpClient(server,port,maxCnt);
	ptr->Initilize();
	return ptr;
}

HttpClient::HttpClient()
:m_port(80),
 m_uCnt(4),
 m_timeout(5)
{

}

HttpClient::HttpClient(std::string server , int port,int maxCnt)
:m_server(server),
 m_port(port),
 m_uCnt(maxCnt),
 m_timeout(5)
{

}
HttpClient::~HttpClient()
{

}

void HttpClient::Initilize()
{
	Poco::Net::HTTPClientSession *sess = nullptr;
	for(int i = 0; i < m_uCnt; ++i)
	{
		sess = new Poco::Net::HTTPClientSession();
		sess->setTimeout(m_timeout);
		sess->setKeepAlive(true);
		m_pool.push_back(sess);
	}
}

void HttpClient::SetTimeout(int timeout)
{
	m_timeout = timeout;
}

Poco::Net::HTTPClientSession* HttpClient::GetHttpClientSession()
{
	Poco::Net::HTTPClientSession* sess = nullptr;
	std::unique_lock<std::mutex> lck(m_mutex);
	while(m_pool.empty())
	{
		m_condition.wait(lck);
	}

	sess = m_pool.back();
	m_pool.pop_back();
	return sess;
}

void HttpClient::ReleaseClientSession(Poco::Net::HTTPClientSession* sess)
{
	std::unique_lock<std::mutex> lck(m_mutex);
	m_pool.push_back(sess);
}

std::string HttpClient::SendPostJsonRequest(std::string uri , std::string data)
{
	return SendRequest(uri,data , EunmHttpMethod::_post);
}
std::string HttpClient::SendGetJsonRequest(std::string uri , std::string data)
{
	return SendRequest(uri,data , EunmHttpMethod::_get);
}

std::string HttpClient::SendRequest(std::string uri , std::string data , EunmHttpMethod method)
{
    std::shared_ptr<Poco::Net::HTTPClientSession> sess(GetHttpClientSession() ,[this](Poco::Net::HTTPClientSession *session){ ReleaseClientSession(session);});
	try
	{
		std::string methodString = method == EunmHttpMethod::_post? Poco::Net::HTTPRequest::HTTP_POST : Poco::Net::HTTPRequest::HTTP_GET ;
		Poco::Net::HTTPRequest httpReq(methodString, uri, Poco::Net::HTTPMessage::HTTP_1_1);
		httpReq.setContentType("application/json;charset=UTF-8");
		httpReq.set("User-Agent", "Billing");

		httpReq.setContentLength((int) data.size());
		sess->sendRequest(httpReq) <<data;

		Poco::Net::HTTPResponse response;
		std::ostringstream ostr;
		std::istream& rs = sess->receiveResponse(response);

		if(200 != response.getStatus())
		{
			THROW(BusiException , "http response status not 200.");
		}

		Poco::StreamCopier::copyStream(rs, ostr);

		if(!response.getKeepAlive())
		{
			sess->reset();
		}
		return ostr.str();
	}
	catch (Poco::Exception &e)
	{
		THROW(BusiException , e.displayText());
	}
	catch(BusiException &e)
	{
		throw;
	}
}
}
