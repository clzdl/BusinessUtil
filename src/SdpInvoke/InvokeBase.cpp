/*
 * soInvokeBase.cpp
 *
 *  Created on: 2015年6月16日
 *      Author: chengl
 */

#include <SdpInvoke/InvokeBase.h>
#include "NumberUtil.h"
#include "MacroDefUtil.h"
#include <sstream>

namespace BusinessUtil
{


InvokeBase::InvokeBase(HTTPClientSession *pHttpSession , std::string strService)
:m_pHttpSession(pHttpSession),
 m_strService(strService)
{
}

InvokeBase::~InvokeBase()
{

}


int InvokeBase::SendPackage()
{
    if(SUCCESS != MakePackage())
        return FAIL;

    try
    {
        HTTPRequest httpReq(HTTPRequest::HTTP_POST, m_strService, HTTPMessage::HTTP_1_1);
        httpReq.setContentType("application/json;charset=UTF-8");
        httpReq.set("User-Agent", "Billing");

        httpReq.setContentLength((int) m_strSendInfo.length());
        m_pHttpSession->sendRequest(httpReq) <<m_strSendInfo;
    }
    catch(NetException &e)
    {
        m_strErrInfo = "exception: " + e.displayText();
        return FAIL;
    }
    catch(Exception &e)
    {
        m_strErrInfo = "exception: " + e.displayText();
        return FAIL;
    }

    return SUCCESS;
}


int InvokeBase::ReceivePackage()
{

    HTTPResponse response;
    std::ostringstream ostr;
    try
    {
        std::istream& rs = m_pHttpSession->receiveResponse(response);
        _TRACE_MSG("response status : %d \n" ,response.getStatus() );
        if(200 != response.getStatus())
        {
            m_strErrInfo = "response status " +  CommonUtils::NumberUtil::Number2String(response.getStatus());
            return FAIL;
        }

        StreamCopier::copyStream(rs, ostr);

        if(!response.getKeepAlive())
        {
            ////keep-alive : close
        	_TRACE_MSG("close session.\n");
            m_pHttpSession->reset();
        }

        m_strReceiveInfo =  ostr.str();

        if(SUCCESS != ParsePackage())
            return FAIL;
    }
    catch(NetException &e)
    {
        m_strErrInfo = "exception: " + e.displayText();
        return FAIL;
    }
    catch(Exception &e)
    {
        m_strErrInfo = "exception: " + e.displayText();
        return FAIL;
    }
    return SUCCESS;
}
std::string InvokeBase::GetErrInfo()
{
    return m_strErrInfo;
}

std::string InvokeBase::GetSendInfo()
{
    return m_strSendInfo;
}

std::string InvokeBase::GetReceiveInfo()
{
    return m_strReceiveInfo;
}


}
