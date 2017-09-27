/*
 * InvokeCreditTrigger.cpp
 *
 *  Created on: 2016年7月7日
 *      Author: clzdl
 */

#include "SdpInvoke/InvokeCreditTrigger.h"
#include "StringUtil.h"

namespace BusinessUtil
{

InvokeCreditTrigger::InvokeCreditTrigger(HTTPClientSession *pHttpSession , std::string strService)
:InvokeBase(pHttpSession,strService),
 m_lAcctId(0),
 m_lUserId(0),
 m_lAddId(0),
 m_iTradeType(0),
 m_lThisFee(0)
{
}
InvokeCreditTrigger::~InvokeCreditTrigger()
{

}

void InvokeCreditTrigger::SetAcctId(long v)
{
    m_lAcctId = v;
}
void InvokeCreditTrigger::SetUserId(long v)
{
    m_lUserId = v;
}
void InvokeCreditTrigger::SetAddId(long v)
{
    m_lAddId = v;
}
void InvokeCreditTrigger::SetTradeTypeCode(int v)
{
    m_iTradeType = v;
}
void InvokeCreditTrigger::SetThisFee(long v)
{
    m_lThisFee = v;
}
void InvokeCreditTrigger::SetInType(std::string v)
{
    m_strInType = v;
}

int InvokeCreditTrigger::MakePackage()
{
    LocalDateTime ldt;
    cJSON *root = NULL;
    int iRetCode = SUCCESS;


    do
    {
        root=cJSON_CreateObject();
        if(NULL == root)
        {
           m_strErrInfo = " root cJSON_CreateObject fail.";
           iRetCode = FAIL;
           break;
        }

        cJSON_AddNumberToObject(root, "ACCT_ID",                m_lAcctId);
        cJSON_AddNumberToObject(root, "UESR_ID",                m_lUserId);
        cJSON_AddNumberToObject(root, "ADD_ID",                 m_lAddId);
        cJSON_AddNumberToObject(root, "TRADE_TYPE",             m_iTradeType);
        cJSON_AddNumberToObject(root, "THIS_FEE",               m_lThisFee);
        cJSON_AddStringToObject(root, "IN_TYPE",                m_strInType.c_str());

        char *out = cJSON_PrintUnformatted(root);

        if(out)
        {
            m_strSendInfo.append(out);
            free(out);
        }

        if(root)
        {
            cJSON_Delete(root);
            root = NULL;
        }

    }while(false);

    return iRetCode;
}
int InvokeCreditTrigger::ParsePackage()
{
    cJSON *jRoot=NULL;
    cJSON *json = NULL;
    char *out=NULL;
    char strTemp[4092] = {0};
    int iRetValue = SUCCESS;
    int iRetCode = SUCCESS;

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
        iRetCode = atoi(out);
        free(out);

        if(iRetCode != SUCCESS)
        {
            ///errmsg
            json = cJSON_GetObjectItem(jRoot ,"ERRORMSG");
            if(NULL == json)
                m_strErrInfo = std::string("Error before:33") + cJSON_GetErrorPtr();

            if((out = cJSON_PrintUnformatted(json)) != NULL)
            {
                strncpy(strTemp,out+1 , strlen(out)-2);
                free(out);
                out = NULL;
            }
             m_strErrInfo.append("信控分发接口返回失败.desc:").append(strTemp);
             iRetValue = FAIL;
        }

    }while(false);

    if(jRoot)
       cJSON_Delete(jRoot);

    return iRetValue;
}


}
