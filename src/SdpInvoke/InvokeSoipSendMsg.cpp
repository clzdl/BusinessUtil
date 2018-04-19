/*
 * soInvokeSoipSendMsg.cpp
 *
 *  Created on: 2015年8月21日
 *      Author: chengl
 */



#include <SdpInvoke/InvokeSoipSendMsg.h>
#include "StringUtil.h"
#include "DateUtil.h"
#include "Md5Util.h"
#include "NumberUtil.h"

#define EXTERNALCHANNEL     "1"
namespace BusinessUtil
{


InvokeSoipSendMsg::InvokeSoipSendMsg(HTTPClientSession *pHttpSession , std::string strService,std::string strBusid,std::string strSecretKey,bool externChannel)
:InvokeBase(pHttpSession,strService),
 m_strSecretKey(strSecretKey),
 m_iSignType(1),
 m_strBusinessId(strBusid),
 m_bIsReportFlag(false),
 m_strSmsType("内部通知"),
 m_strSmsSendService(strService),
 m_externChannel(externChannel)
{

}
InvokeSoipSendMsg::~InvokeSoipSendMsg()
{

}
void InvokeSoipSendMsg::SetBusinessId(std::string id)
{
    m_strBusinessId = id;
}
void InvokeSoipSendMsg::SetMacCode(std::string code)
{
    m_strMac = code;
}
void InvokeSoipSendMsg::SetOrderSeq(std::string code)
{
    m_strOrderSeq = code;
}
void InvokeSoipSendMsg::SetReqDate(std::string no)
{
    m_strReqDate = no;
}
void InvokeSoipSendMsg::SetSignType(int type)
{
    m_iSignType = type;
}

void InvokeSoipSendMsg::SetSubBusinessId(std::string id)
{
    m_strSubBusinessId = id;
}

void InvokeSoipSendMsg::SetExternChannel(bool externChannel)
{
    m_externChannel = externChannel;
}

void InvokeSoipSendMsg::InsertSoipSmsInfo(const _SOIP_SMS_INFO &ssi)
{
    m_vecSoipSms.push_back(ssi);
}

void InvokeSoipSendMsg::CleanSoipSmsInfo()
{
    m_vecSoipSms.clear();
}

int InvokeSoipSendMsg::GetReturnCode()
{
    return m_stSoipSmsRet.iReturnCode;
}
std::string InvokeSoipSendMsg::GetErrMsg()
{
    return m_stSoipSmsRet.strErrMsg;
}
std::string InvokeSoipSendMsg::GetMsgId()
{
    return m_stSoipSmsRet.strMsgId;
}
std::string InvokeSoipSendMsg::GetOrderId()
{
    return m_stSoipSmsRet.strOrderSeq;
}

bool InvokeSoipSendMsg::IsExternChannel() const
{
    return m_externChannel;
}

int InvokeSoipSendMsg::MakePackage()
{
    m_strSendInfo.clear();
    m_strMac.clear();
    if(SUCCESS != ConstructBussPackage())
        return FAIL;

    ////do md5 signature
    if(SUCCESS != GenMd5Key(m_strMac) )
        return FAIL;

    ////encode request uri
    ConstructRequestUri();

    return SUCCESS;
}
int InvokeSoipSendMsg::ParsePackage()
{
    cJSON *jRoot=NULL;
    cJSON *json = NULL;
    char *out=NULL;
    char strTemp[8092] = {0};
    int iRetValue = SUCCESS;

    CommonUtils::StringUtil::trim(m_strReceiveInfo);

    do
    {
        jRoot=cJSON_Parse(m_strReceiveInfo.c_str());
        if (!jRoot)
        {
            m_strErrInfo = std::string("Error before:11") + cJSON_GetErrorPtr();
            iRetValue = FAIL;
            break;
        }
        ///RETURNCODE
        json = cJSON_GetObjectItem(jRoot ,"RETURNCODE");
        if(NULL == json)
        {
            m_strErrInfo = std::string("Error before:22") + cJSON_GetErrorPtr();
            iRetValue = FAIL;
            break;
        }

        out = cJSON_PrintUnformatted(json);
        m_stSoipSmsRet.iReturnCode = atoi(out);
        free(out);
        out = NULL;

        if(SUCCESS == m_stSoipSmsRet.iReturnCode)
        {
            ///MSGID
            json = cJSON_GetObjectItem(jRoot ,"MSGID");
            if(NULL != json)
            {
                out = cJSON_PrintUnformatted(json);
                memset(strTemp , 0 ,sizeof(strTemp));
                strncpy(strTemp,out+1 , strlen(out)-2);
                m_stSoipSmsRet.strMsgId.append(strTemp);
                free(out);
                out = NULL;
            }

            ///ORDERSEQ
            json = cJSON_GetObjectItem(jRoot ,"ORDERSEQ");
            if(NULL != json)
            {
                out = cJSON_PrintUnformatted(json);
                memset(strTemp , 0 ,sizeof(strTemp));
                strncpy(strTemp,out+1 , strlen(out)-2);
                m_stSoipSmsRet.strOrderSeq.append(strTemp);
                free(out);
                out = NULL;
            }
        }
        else
        {
            ///errmsg
            json = cJSON_GetObjectItem(jRoot ,"ERRORMSG");
            if(NULL != json && (out = cJSON_PrintUnformatted(json)) != NULL)
            {
                    strncpy(strTemp,out+1 , strlen(out)-2);
                    m_stSoipSmsRet.strErrMsg.append(strTemp);
                    free(out);
                    out = NULL;
            }

            m_strErrInfo = "soip短信接口返回失败.desc:" + m_stSoipSmsRet.strErrMsg;
            iRetValue = FAIL;
            break;
        }

    }while(false);

    if(jRoot)
    {
        cJSON_Delete(jRoot);
    }

    return iRetValue;
}


int InvokeSoipSendMsg::GenMd5Key( std::string &strMd5)
{
    char strTemp[128] = {0};
    char strSysdate[14+1] = {0};

    CommonUtils::DateUtil::GetSysdateUsec(strTemp);

    m_strOrderSeq.append(strTemp);
    m_strReqDate.append(strncpy(strSysdate , strTemp , 14));
    m_strSubBusinessId.append("XK");

    std::string strBuff(m_strSecretKey);

    strBuff.append("BUSINESSID");
    strBuff.append(m_strBusinessId);

    //  if(m_externChannel)
    //  {
    //       strBuff.append("EXTERNALCHANNEL");
    //       strBuff.append(EXTERNALCHANNEL);
    //  }


    strBuff.append("ORDERSEQ");
    strBuff.append(m_strOrderSeq);


    strBuff.append("REQDATE");
    strBuff.append(m_strReqDate);

    ///don't include this field, otherwise valid mac fail
//    strBuff.append("SIGNTYPE");
//    strBuff.append(Number2String(m_iSignType).c_str());

    strBuff.append("SUBBUSINESSID");
    strBuff.append(m_strSubBusinessId);

    strBuff.append(m_strSendInfo);

    strBuff.append(m_strSecretKey);



    if(SUCCESS != CommonUtils::Md5Util::Md5StringSummary(strBuff , strMd5) )
        return FAIL;


    return SUCCESS;
}


/*@action:用于生成业务参数json包
 *
 */
int InvokeSoipSendMsg::ConstructBussPackage()
{
    cJSON *root = NULL;
    char *out = NULL;

    root=cJSON_CreateObject();
    if(NULL == root)
    {
        m_strErrInfo = " root cJSON_CreateObject fail.";
        return FAIL;
    }

    cJSON_AddStringToObject(root, "REQREASON",                "notification");
    cJSON_AddStringToObject(root, "BUSINESSTYPE",             "sharingmobile");
    cJSON_AddStringToObject(root, "SMSTYPE",                  m_strSmsType.c_str());
    cJSON_AddNumberToObject(root, "ISREPORT",                m_bIsReportFlag == true ? 1 : 0 );

    ///添加具体短信信息
    cJSON *dataArr = cJSON_CreateArray();
    if(NULL == dataArr)
    {
        m_strErrInfo = " dataArr cJSON_CreateArray fail.";
        return FAIL;
    }

    for(std::vector<_SOIP_SMS_INFO>::iterator it = m_vecSoipSms.begin(); it != m_vecSoipSms.end(); ++it)
    {
        cJSON *data = cJSON_CreateObject();
        if(NULL == data)
        {
            m_strErrInfo = " data cJSON_CreateObject fail.";
            return FAIL;
        }
        ///soip suggest priority value from 0 to 3
        cJSON_AddStringToObject(data , "VALIDTIME" , it->strValidTime.c_str());
        cJSON_AddStringToObject(data , "DESTTERMID" , it->strDestTermId.c_str());
        cJSON_AddStringToObject(data , "MSGCONTENT" , it->strMsgContent.c_str());
        cJSON_AddStringToObject(data , "RESERVE" , it->strReserve.c_str());
        cJSON_AddStringToObject(data , "SEND_TIME_START" , it->strSendBegTime.c_str());
        cJSON_AddStringToObject(data , "SEND_TIME_END" , it->strSendEndTime.c_str());
        cJSON_AddItemToArray(dataArr , data);

    }

    cJSON_AddItemToObject(root , "DATA" , dataArr);
    out = cJSON_PrintUnformatted(root);
    m_strSendInfo.append(out);

    if(out)
    {
        free(out);
    }

    if(root)
    {
        cJSON_Delete(root);
        root = NULL;
    }

    return SUCCESS;
}

/*@action: 用于构建请求uri
 *
 */
void InvokeSoipSendMsg::ConstructRequestUri()
{
    m_strService = m_strSmsSendService;
    m_strService.append("?");
    m_strService.append("BUSINESSID="+m_strBusinessId);
    m_strService.append("&");
    m_strService.append("SUBBUSINESSID="+m_strSubBusinessId);
    m_strService.append("&");
    m_strService.append("ORDERSEQ="+m_strOrderSeq);
    m_strService.append("&");
    m_strService.append("REQDATE="+m_strReqDate);
    m_strService.append("&");
    m_strService.append("SIGNTYPE="+CommonUtils::NumberUtil::Number2String(m_iSignType));

    if(m_externChannel)
    {
        m_strService.append("&EXTERNALCHANNEL=" + std::string(EXTERNALCHANNEL));
    }

    m_strService.append("&");
    m_strService.append("MAC="+m_strMac);

}

}

