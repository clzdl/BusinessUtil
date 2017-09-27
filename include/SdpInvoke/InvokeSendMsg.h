/*
 * soInvokeSendMsg.h
 *
 *  Created on: 2015年6月17日
 *      Author: chengl
 */

#ifndef SOINVOKESENDMSG_H_
#define SOINVOKESENDMSG_H_


/*短信发送接口-sdp
 *
 */
#include <SdpInvoke/InvokeBase.h>
namespace BusinessUtil
{
class InvokeSendMsg:public InvokeBase
{
public:
    InvokeSendMsg(HTTPClientSession *pHttpSession , std::string strService);
    ~InvokeSendMsg();

    void SetProvinceCode(std::string code);
    void SetRegionCode(std::string code);
    void SetCityCode(std::string code);
    void SetSerialNumber(std::string no);
    void SetSmsContent(std::string content);





private:
    int MakePackage();
    int ParsePackage();

    std::string m_strProvinceCode;
    std::string m_strRegionCode;
    std::string m_strCityCode;
    std::string m_strSerialNumber;
    std::string m_strSmsContent;

};

}


#endif /* SOINVOKESENDMSG_H_ */
