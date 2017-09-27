/*
 * soInvokeSendMsg.cpp
 *
 *  Created on: 2015年6月17日
 *      Author: chengl
 */

#include <SdpInvoke/InvokeSendMsg.h>
#include "JsonUtil.h"
#include "SdpInvoke/JsonReqNode.h"
#include "SdpInvoke/JsonRespNode.h"

namespace BusinessUtil
{

InvokeSendMsg::InvokeSendMsg(HTTPClientSession *pHttpSession , std::string strService)
:InvokeBase(pHttpSession,strService)
{

}
InvokeSendMsg::~InvokeSendMsg()
{

}

void InvokeSendMsg::SetProvinceCode(std::string code)
{
    m_strProvinceCode = code;
}
void InvokeSendMsg::SetRegionCode(std::string code)
{
    m_strRegionCode = code;
}
void InvokeSendMsg::SetCityCode(std::string code)
{
    m_strCityCode = code;
}
void InvokeSendMsg::SetSerialNumber(std::string no)
{
    m_strSerialNumber = no;
}
void InvokeSendMsg::SetSmsContent(std::string content)
{
    m_strSmsContent = content;
}

int InvokeSendMsg::MakePackage()
{
    NodeRoot nr;
    NodeSendMsg nsm;
    cJSON *root = NULL;
    int iRetCode = SUCCESS;

    nr.SetOperCode("sendMsg");
    nr.SetStaffID("XK001");
    nr.SetDepartID("XK");
    nr.SetProvinceCode( m_strProvinceCode );
    nr.SetRegionCode( m_strRegionCode );
    nr.SetCityCode(  m_strCityCode.empty()?"ZZZZ":m_strCityCode );
    nr.SetRouteProvinceCode( m_strProvinceCode );
    nr.SetRouteRegionCode( m_strRegionCode );
    nr.SetRouteCityCode( m_strCityCode.empty()?"ZZZZ":m_strCityCode );
    nr.SetInNetMode("X");

    nsm.SetPhoneNum(m_strSerialNumber );
    nsm.SetMsg( m_strSmsContent );

    do
    {
        //创建root节点
        root = NodeRoot::JsonCreateRoot(nr);
        if(NULL == root)
        {
            m_strErrInfo = "JsonCreateRoot failed.";
            iRetCode = FAIL;
            break;
        }

        //添加消息节点
        if(SUCCESS != NodeSendMsg::JsonAddSendMsgNode(root , nsm) )
        {
            m_strErrInfo = "JsonAddSendMsgNode failed.";
            iRetCode = FAIL;
            break;
        }

        //编码格式转换，转为utf-8，strPkg最终包,JsonToUtf8String()
        if( (m_strSendInfo = CommonUtils::JsonUtil::JsonToString(root) ).empty())
        {
            m_strErrInfo = "JsonToString empty.";
            iRetCode = FAIL;
            break;
        }

    }while(false);

    if(root)
    	CommonUtils::JsonUtil::JsonDelete(root);

    return iRetCode;
}
int InvokeSendMsg::ParsePackage()
{
    ////解析返回指令的返回码
    RespNodeRoot rnr;
    if(SUCCESS != RespNodeRoot::JsonParseRespRootNode(m_strReceiveInfo , rnr))
    {
        m_strErrInfo = "JsonToString empty.";
        return FAIL;
    }

    if(0 != rnr.GetRespCode().compare(1,4,"0000"))
    {
        m_strErrInfo = "短信接口返回失败. desc: " +  rnr.GetRespUtf8Desc();
        return FAIL;
    }

    return SUCCESS;

}

}
