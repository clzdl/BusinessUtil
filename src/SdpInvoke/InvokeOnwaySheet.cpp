/*
 * soInvokeOnwaySheet.cpp
 *
 *  Created on: 2015年6月17日
 *      Author: chengl
 */

#include <SdpInvoke/InvokeOnwaySheet.h>
#include "JsonUtil.h"

namespace BusinessUtil
{


InvokeOnwaySheet::InvokeOnwaySheet(HTTPClientSession *pHttpSession , std::string strService)
:InvokeBase(pHttpSession,strService)
{

}
InvokeOnwaySheet::~InvokeOnwaySheet()
{

}


int InvokeOnwaySheet::MakePackage()
{
    NodeRoot nr;
    NodeOnWaySheet nows;
    int iRetCode = SUCCESS;
    cJSON *root = NULL;


    nr.SetOperCode("QryAllUserInfo");
    nr.SetStaffID("XK001");
    nr.SetDepartID("XK");
    nr.SetProvinceCode(m_strProvinceCode);
    nr.SetRegionCode(m_strRegionCode);
    nr.SetCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    nr.SetRouteProvinceCode(m_strProvinceCode);
    nr.SetRouteRegionCode(m_strRegionCode);
    nr.SetRouteCityCode(m_strCityCode.empty()?"ZZZZ":m_strCityCode);
    nr.SetInNetMode("X");



    nows.SetSerialNumber(m_strSerialNumber);
    ////如果是150 则只判断停开机这一类的在途工单
    nows.SetTradeTypeCode(m_strTradeTypeCode);
    do
    {
        root = NodeRoot::JsonCreateRoot(nr);
        if(NULL == root)
        {
            m_strErrInfo = "JsonCreateRoot failed.";
            iRetCode = FAIL;
            break;
        }

        if(FAIL == NodeOnWaySheet::JsonAddOnWaySheetNode(root , nows) )
        {
            m_strErrInfo = "JsonAddOnWaySheetNode failed.";
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

    return iRetCode;
}

int InvokeOnwaySheet::ParsePackage()
{
    RespNodeOnWaySheeNode resp;

    if(FAIL == RespNodeOnWaySheeNode::JsonParseOnWaySheetNode(m_strReceiveInfo , resp))
    {
       m_strErrInfo = "JsonParseOnWaySheetNode fail. ";
       return FAIL;
    }

    m_vecOnwaySheet.clear();

    ////20150914
    if(resp.GetRespCode().compare(1,4,"0000") != SUCCESS)
    {
        m_strErrInfo = "在途工单接口返回失败. desc: " +  resp.GetRespUtf8Desc();
        return FAIL;
    }


    m_vecOnwaySheet.insert(m_vecOnwaySheet.begin(), resp.GetOnWaySheet().begin() , resp.GetOnWaySheet().end());

    return SUCCESS;
}

void InvokeOnwaySheet::SetProvinceCode(std::string code)
{
    m_strProvinceCode = code;
}
void InvokeOnwaySheet::SetRegionCode(std::string code)
{
    m_strRegionCode = code;
}
void InvokeOnwaySheet::SetCityCode(std::string code)
{
    m_strCityCode = code;
}
void InvokeOnwaySheet::SetSerialNumber(std::string no)
{
    m_strSerialNumber = no;
}
void InvokeOnwaySheet::SetTradeTypeCode(std::string code)
{
    m_strTradeTypeCode = code;
}
std::vector<_ON_WAY_SHEET>& InvokeOnwaySheet::GetOnwaySheet()
{
    return m_vecOnwaySheet;
}

}
