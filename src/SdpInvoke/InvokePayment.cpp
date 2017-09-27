/*
 * soInvokePayment.cpp
 *
 *  Created on: 2015年6月16日
 *      Author: chengl
 */


#include <SdpInvoke/InvokePayment.h>
#include "NumberUtil.h"
#include "StringUtil.h"
#include "JsonUtil.h"
#include "SdpInvoke/JsonReqNode.h"
#include "SdpInvoke/JsonRespNode.h"

namespace BusinessUtil
{

InvokePayment::InvokePayment(HTTPClientSession *pHttpSession , std::string strService)
:InvokeBase(pHttpSession,strService)
{
    ///20150729
    m_lActivityID = 0;
    m_lUserID = 0;
    m_lRecvFee = 0;
}
InvokePayment::~InvokePayment()
{

}

void InvokePayment::SetProvinceCode(std::string code)
{
    m_strProvinceCode = code;
}
void InvokePayment::SetRegionCode(std::string code)
{
    m_strRegionCode = code;
}
void InvokePayment::SetCityCode(std::string code)
{
    m_strCityCode = code;
}
void InvokePayment::SetUserID(long id)
{
    m_lUserID = id;
}
void InvokePayment::SetSerialNumber(std::string no)
{
    m_strSerialNumber = no;
}
void InvokePayment::SetRecvFee(long fee)
{
    m_lRecvFee = fee;
}
void InvokePayment::SetActivityID(long id)
{
    m_lActivityID = id;
}
void InvokePayment::SetPaymentID(std::string id)
{
    m_strPaymentID = id;
}
void InvokePayment::SetPayfeeModeCode(std::string code)
{
    m_strPayfeeModeCode = code;
}
void InvokePayment::SetTradeTypeCode(std::string code)
{
    m_strTradeTypeCode = code;
}

std::string InvokePayment::GetChargeID()
{
    return m_strChargeID;
}


int InvokePayment::MakePackage()
{
    NodeRoot nr;
    NodePayFee npf;
    cJSON *root = NULL;
    int iRetCode = SUCCESS;

    nr.SetOperCode("pay");
    nr.SetStaffID("XK001");
    nr.SetDepartID("XK");
    nr.SetProvinceCode(m_strProvinceCode);
    nr.SetRegionCode(m_strRegionCode);
    nr.SetCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    nr.SetRouteProvinceCode(m_strProvinceCode);
    nr.SetRouteRegionCode(m_strRegionCode);
    nr.SetRouteCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    ///sdp要求修改 20150409
    nr.SetInNetMode("X");


    npf.SetRecvTag("3");
    npf.SetUserID(CommonUtils::NumberUtil::Number2String(m_lUserID));
    npf.SetSerialNumber(m_strSerialNumber);

    npf.SetRecvFee(CommonUtils::NumberUtil::Number2String(m_lRecvFee));
    npf.SetPaymentID(m_strPaymentID);
    npf.SetPayfeeModeCode(m_strPayfeeModeCode);
    npf.SetChannelID("C");

    ///20150729
    if(m_lActivityID > 0)
        npf.SetActionCode(CommonUtils::NumberUtil::Number2String(m_lActivityID));

    npf.SetTradeTypeCode(m_strTradeTypeCode);


    do
    {
        root = NodeRoot::JsonCreateRoot(nr);
        if(NULL == root)
        {
            m_strErrInfo = "JsonCreateRoot failed.";
            iRetCode = FAIL;
            break;
        }

        if(FAIL == NodePayFee::JsonAddPayFeeNode(root , npf) )
        {
            m_strErrInfo = "JsonAddPayFeeNode failed.";
            iRetCode = FAIL;
            break;
        }

        m_strSendInfo.clear();
        if( (m_strSendInfo = CommonUtils::JsonUtil::JsonToString(root) ).empty())
        {
            m_strErrInfo = "JsonString is empty.";
            iRetCode = FAIL;
            break;
        }

    }while(false);

    if(root)
    	CommonUtils::JsonUtil::JsonDelete(root);

    return SUCCESS;
}



int InvokePayment::ParsePackage()
{
    RespNodePayFeeNode npf;
    if(SUCCESS != RespNodePayFeeNode::JsonParseRespPayFeeNode(m_strReceiveInfo, npf ))
    {
        m_strErrInfo = "JsonParseRespPayFeeNode fail.";
        return FAIL;
    }


    if(npf.GetRespCode().compare(1,4,"0000") != SUCCESS)
    {
        m_strErrInfo = "缴费接口返回失败. desc: " +  npf.GetRespUtf8Desc();
        return FAIL;
    }

    m_strChargeID = CommonUtils::StringUtil::replace(npf.GetChargeID() , "\"" , "");

    return SUCCESS;
}

}
