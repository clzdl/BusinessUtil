/*
 * soInvokeSoipSendMsg.h
 *
 *  Created on: 2015年8月21日
 *      Author: chengl
 */

#ifndef SOINVOKESOIPSENDMSG_H_
#define SOINVOKESOIPSENDMSG_H_



/*短信发送接口-soip
 * 2016-08-09   接口规范增加发送时间限制
 *
 */
#include <SdpInvoke/InvokeBase.h>

namespace BusinessUtil
{


typedef struct SoipSmsInfo
{
    std::string strAtTime;
    std::string strDestTermId;
    std::string strMsgContent;
    int iPrority;
    std::string strReserve;
    std::string strValidTime;
    std::string strSendBegTime;  ///SEND_TIME_START
    std::string strSendEndTime;  ///SEND_TIME_END
}_SOIP_SMS_INFO;


typedef struct SoipSmsRetInfo
{
    int iReturnCode;
    std::string strErrMsg;
    std::string strMsgId;
    std::string strOrderSeq;

}_SOIP_SMS_RET_INFO;



class InvokeSoipSendMsg:public InvokeBase
{
public:
    InvokeSoipSendMsg(HTTPClientSession *pHttpSession , std::string strService ,std::string strBusid,std::string strSecretKey="", bool externChannel = false);
    ~InvokeSoipSendMsg();

    void SetBusinessId(std::string id);
    void SetMacCode(std::string code);
    void SetOrderSeq(std::string code);
    void SetReqDate(std::string no);
    void SetSignType(int type);
    void SetSubBusinessId(std::string id);
    void SetExternChannel(bool externChannel);
    void InsertSoipSmsInfo(const _SOIP_SMS_INFO &ssi);
    void CleanSoipSmsInfo();

    int GetReturnCode();
    std::string GetErrMsg();
    std::string GetMsgId();
    std::string GetOrderId();
    bool IsExternChannel() const;

private:
    int MakePackage();
    int ParsePackage();

    /*@action:用于生成业务参数json包
     *
     */
    int ConstructBussPackage();


    /*@action:用于生成md5摘要签名
     *
     */
    int GenMd5Key(std::string &strMd5);

    /*@action: 用于构建请求uri
     *
     */
    void ConstructRequestUri();


    std::string m_strBusinessId; ////BUSINESSID
    std::string m_strSubBusinessId;   //SUBBUSINESSID
    std::string m_strOrderSeq;   ///ORDERSEQ
    std::string m_strReqDate;    ///REQDATE
    int m_iSignType;   /// SIGNTYPE
    std::string m_strMac;    ///MAC


    bool m_bIsReportFlag;    ///是否接受状态报告
    std::string m_strSmsType;   ///短信类型

    std::string m_strSecretKey;

    std::string m_strSmsSendService;

    std::vector<_SOIP_SMS_INFO> m_vecSoipSms;
    _SOIP_SMS_RET_INFO m_stSoipSmsRet; ///soip返回信息

    bool m_externChannel;   //false-内部通道,true-启用外部通道
};

}

#endif /* SOINVOKESOIPSENDMSG_H_ */
