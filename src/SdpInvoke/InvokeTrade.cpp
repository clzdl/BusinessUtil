/*
 * soInvokeTrade.cpp
 *
 *  Created on: 2015年6月17日
 *      Author: chengl
 */

#include <SdpInvoke/InvokeTrade.h>
#include "NumberUtil.h"
#include "JsonUtil.h"

namespace BusinessUtil
{

InvokeTrade::InvokeTrade(HTTPClientSession *pHttpSession , std::string strService)
:InvokeBase(pHttpSession,strService),
 m_lUserID(0),
 m_lAcctID(0),
 m_lCustID(0)
{

}
InvokeTrade::~InvokeTrade()
{

}

void InvokeTrade::SetProvinceCode(std::string code)
{
    m_strProvinceCode = code;
}
void InvokeTrade::SetRegionCode(std::string code)
{
    m_strRegionCode = code;
}
void InvokeTrade::SetCityCode(std::string code)
{
    m_strCityCode = code;
}

void InvokeTrade::SetTradeId(std::string id)
{
    m_strTradeId = id;
}
void InvokeTrade::SetCmdCode(std::string code)
{
    m_strCmdCode = code;
}
void InvokeTrade::SetBrandCode(std::string code)
{
    m_strBrandCode = code;
}
void InvokeTrade::SetUserID(long id)
{
    m_lUserID = id;
}
void InvokeTrade::SetAcctID(long id)
{
    m_lAcctID = id;
}
void InvokeTrade::SetCustID(long id)
{
    m_lCustID = id;
}
void InvokeTrade::SetCustName(std::string name)
{
    m_strCustName = name;
}
void InvokeTrade::SetNetTypeCode(std::string code)
{
    m_strNetTypeCode = code;
}
void InvokeTrade::SetSerialNumber(std::string no)
{
    m_strSerialNumber = no;
}
void InvokeTrade::SetProviderCode(std::string code)
{
    m_strProviderCode = code;
}

void InvokeTrade::SetAcceptProvinceCode(std::string code)
{
    m_strAcceptProvinceCode = code;
}
void InvokeTrade::SetAcceptRegionCode(std::string code)
{
    m_strAcceptRegionCode = code;
}
void InvokeTrade::SetAcceptCityCode(std::string code)
{
    m_strAcceptCityCode = code;
}

void InvokeTrade::SetRemark(std::string v)
{
    m_strRemark = v;
}


int InvokeTrade::MakePackage()
{

    LocalDateTime ldt;
    cJSON *root = NULL;
    int iRetCode = SUCCESS;


    m_nrRoot.SetOperCode("submitTradeInfo");
    m_nrRoot.SetStaffID("XK001");
    m_nrRoot.SetDepartID("XK");
    m_nrRoot.SetProvinceCode(m_strProvinceCode);
    m_nrRoot.SetRegionCode(m_strRegionCode);
    m_nrRoot.SetCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    m_nrRoot.SetRouteProvinceCode(m_strProvinceCode);
    m_nrRoot.SetRouteRegionCode(m_strRegionCode);
    m_nrRoot.SetRouteCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    m_nrRoot.SetInNetMode("X");


    m_ntTrade.SetSubscribeID(m_strTradeId);
    m_ntTrade.SetTradeID(m_strTradeId);
    m_ntTrade.SetTradeTypeCode(m_strCmdCode);
    m_ntTrade.SetInModeCode("X");
    m_ntTrade.SetSubscribeState("0");
    m_ntTrade.SetBrandCode(m_strBrandCode);


    m_ntTrade.SetUserID(CommonUtils::NumberUtil::Number2String(m_lUserID));
    m_ntTrade.SetAcctID(CommonUtils::NumberUtil::Number2String(m_lAcctID));
    m_ntTrade.SetCustID(CommonUtils::NumberUtil::Number2String(m_lCustID));
    m_ntTrade.SetCustName(m_strCustName);

    m_ntTrade.SetNetTypeCode(m_strNetTypeCode);
    m_ntTrade.SetSerialNumber(m_strSerialNumber);

    m_ntTrade.SetAcceptStaffID("XK001");
    m_ntTrade.SetAcceptDepartID("XK");
    m_ntTrade.SetAcceptDate(CommonUtils::NumberUtil::Number2String(ldt.year()) + "-" +
    						CommonUtils::NumberUtil::Number2String(ldt.month()) + "-" +
							CommonUtils::NumberUtil::Number2String(ldt.day()) + " " +
							CommonUtils::NumberUtil::Number2String(ldt.hour()) + ":" +
							CommonUtils::NumberUtil::Number2String(ldt.minute()) + ":" +
							CommonUtils::NumberUtil::Number2String(ldt.second()));
    m_ntTrade.SetOrderType("0");

    ///20150601
    m_ntTrade.SetAcceptProvinceCode(m_strAcceptProvinceCode);
    m_ntTrade.SetAcceptRegionCode(m_strAcceptRegionCode);
    m_ntTrade.SetAcceptCityCode(m_strAcceptCityCode);
    m_ntTrade.SetHaseFee("0");
    m_ntTrade.SetFeeNum("0");

    m_ntTrade.SetProviderCode(m_strProviderCode);

    ////2015-04-30
    m_ntTrade.SetProvinceCode(m_strProvinceCode);
    m_ntTrade.SetRegionCode(m_strRegionCode);
    m_ntTrade.SetCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    m_ntTrade.SetRemark(m_strRemark);

    do
    {
        root = NodeRoot::JsonCreateRoot(m_nrRoot);
        if(NULL == root)
        {
            m_strErrInfo = "JsonCreateRoot failed.";
            iRetCode = FAIL;
            break;
        }

        if(FAIL == NodeTrade::JsonAddTradeNode(root , m_ntTrade) )
        {
            m_strErrInfo = "JsonAddTradeNode failed.";
            iRetCode = FAIL;
            break;
        }

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
int InvokeTrade::ParsePackage()
{
    RespNodeRoot rnr;
    if(FAIL == RespNodeRoot::JsonParseRespRootNode(m_strReceiveInfo , rnr))
    {
        m_strErrInfo = "JsonParseRespRootNode fail.";
        return FAIL;
    }

    ////根据返回码跟新数据数据
    if(rnr.GetRespCode().compare(1,4, "0000") != 0)
    {
        m_strErrInfo = "停开机接口返回失败. desc: " +  rnr.GetRespUtf8Desc();
        return FAIL;
    }

    return SUCCESS;
}

///20160427
void InvokeTrade::AddTradeItem(std::string strAttrCode , std::string strAttrValue)
{
    CTradeItem ti;
    ti.SetAttrCode(strAttrCode);
    ti.SetAttrValue(strAttrValue);
    m_ntTrade.AddTradeItem(ti);
}

}
