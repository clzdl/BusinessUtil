/*
 * soInvokeBase.h
 *
 *  Created on: 2015年6月16日
 *      Author: chengl
 */

#ifndef SOINVOKEBASE_H_
#define SOINVOKEBASE_H_

#include <SdpInvoke/ISIdefine.h>
namespace BusinessUtil
{


class InvokeBase
{
public:
    InvokeBase(HTTPClientSession *pHttpSession , std::string strService);
    virtual ~InvokeBase();

    virtual int SendPackage();
    virtual int ReceivePackage();

    std::string GetErrInfo();
    std::string GetSendInfo();
    std::string GetReceiveInfo();
protected:
    virtual int MakePackage() = 0;
    virtual int ParsePackage() = 0;
    HTTPClientSession *m_pHttpSession;
    std::string m_strService;
    std::string m_strErrInfo;////错误信息
    std::string m_strSendInfo;   ////发送的报文
    std::string m_strReceiveInfo;    ///接受到的保温
};

}


#endif /* SOINVOKEBASE_H_ */
