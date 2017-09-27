/*
 * soInvokeQryFee.cpp
 *
 *  Created on: 2015年6月17日
 *      Author: chengl
 */

#include <SdpInvoke/InvokeQryFee.h>
#include "JsonUtil.h"
#include "SdpInvoke/JsonReqNode.h"
#include "SdpInvoke/JsonRespNode.h"

namespace BusinessUtil
{

InvokeQryFee::InvokeQryFee(HTTPClientSession *pHttpSession , std::string strService)
:InvokeBase(pHttpSession,strService),
 m_iRecvTag(0),
 m_lLeaveRealFee(0),
 m_lCruRealFee(0),
 m_lLMNoPayBillFee(0)
{
}


InvokeQryFee::~InvokeQryFee()
{
}

void InvokeQryFee::SetProvinceCode(std::string code)
{
    m_strProvinceCode = code;
}
void InvokeQryFee::SetRegionCode(std::string code)
{
    m_strRegionCode = code;
}
void InvokeQryFee::SetCityCode(std::string code)
{
    m_strCityCode = code;
}
void InvokeQryFee::SetQryId(std::string id)
{
    m_strQryId = id;
}
void InvokeQryFee::SetRecvTag(int tag)
{
    m_iRecvTag = tag;
}
long InvokeQryFee::GetLeaveRealFee()
{
    return m_lLeaveRealFee;
}
long InvokeQryFee::GetCurRealFee()
{
    return m_lCruRealFee;
}
long InvokeQryFee::GetLMNoPayBillFee()
{
    return m_lLMNoPayBillFee;
}

int InvokeQryFee::MakePackage()
{
    NodeRoot nr;
    NodeQryOweFee nqof;
    int iRetCode = SUCCESS;
    cJSON *root = NULL;

    nr.SetOperCode("QryOweFee");
    nr.SetStaffID("XK001");
    nr.SetDepartID("XK");
    nr.SetProvinceCode(m_strProvinceCode);
    nr.SetRegionCode(m_strRegionCode);
    nr.SetCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    nr.SetRouteProvinceCode(m_strProvinceCode);
    nr.SetRouteRegionCode(m_strRegionCode);
    nr.SetRouteCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    nr.SetInNetMode("X");

    nqof.SetRecvTag(m_iRecvTag);
    nqof.SetQryID(m_strQryId);

    do
    {
        root = NodeRoot::JsonCreateRoot(nr);
        if(NULL == root)
        {
            m_strErrInfo = "JsonCreateRoot failed.";
            iRetCode = FAIL;
            break;
        }

        if(FAIL == NodeQryOweFee::JsonAddQryOweFeeNode(root , nqof) )
        {
            m_strErrInfo = "JsonAddTradeNode failed.";
            iRetCode = FAIL;
            break;
        }

        m_strSendInfo.clear();
        if( (m_strSendInfo = CommonUtils::JsonUtil::JsonToString(root) ).empty())
        {
            m_strErrInfo = "JsonString empty.";
            iRetCode = FAIL;
            break;
        }


    }while(false);

    if(root)
    	CommonUtils::JsonUtil::JsonDelete(root);

    return SUCCESS;
}
int InvokeQryFee::ParsePackage()
{
    RespNodeQryOweFeeNode resp;

    if(FAIL == RespNodeQryOweFeeNode::JsonParseRespQryOweFeeNode(m_strReceiveInfo , resp))
    {
        m_strErrInfo = "JsonParseRespQryOweFeeNode fail.";
        return FAIL;
    }

    if(resp.GetRespCode().compare(1,4,"0000") != SUCCESS)
    {
        m_strErrInfo = "余额查询接口返回失败. desc: " +  resp.GetRespUtf8Desc();
        return FAIL;
    }

    m_lLeaveRealFee = 0;
    m_lCruRealFee = 0;
    m_lLMNoPayBillFee = 0;
    m_lLeaveRealFee = resp.GetLeaveRealFee(m_lCruRealFee,m_lLMNoPayBillFee);

    return SUCCESS;
}

}

