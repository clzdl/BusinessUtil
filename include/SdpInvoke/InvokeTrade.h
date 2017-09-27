/*
 * soInvokeTrade.h
 *
 *  Created on: 2015年6月17日
 *      Author: chengl
 */

#ifndef SOINVOKETRADE_H_
#define SOINVOKETRADE_H_

/*  停开机指令接口
 *
 */

#include <SdpInvoke/InvokeBase.h>
#include "JsonReqNode.h"
#include "JsonRespNode.h"

namespace BusinessUtil
{
class InvokeTrade:public InvokeBase
{
public:
    InvokeTrade(HTTPClientSession *pHttpSession , std::string strService);
    ~InvokeTrade();

    void SetProvinceCode(std::string code);
    void SetRegionCode(std::string code);
    void SetCityCode(std::string code);

    void SetTradeId(std::string id);
    void SetCmdCode(std::string code);
    void SetBrandCode(std::string code);
    void SetUserID(long id);
    void SetAcctID(long id);
    void SetCustID(long id);
    void SetCustName(std::string name);
    void SetNetTypeCode(std::string code);
    void SetSerialNumber(std::string no);
    void SetProviderCode(std::string code);

    void SetAcceptProvinceCode(std::string code);
    void SetAcceptRegionCode(std::string code);
    void SetAcceptCityCode(std::string code);

    ///20160427
    void SetRemark(std::string v);
    void AddTradeItem(std::string strAttrCode , std::string strAttrValue);



private:
    int MakePackage();
    int ParsePackage();


    std::string m_strProvinceCode;
    std::string m_strRegionCode;
    std::string m_strCityCode;
    std::string m_strTradeId;
    std::string m_strCmdCode;
    std::string m_strBrandCode;
    long m_lUserID;
    long m_lAcctID;
    long m_lCustID;
    std::string m_strCustName;
    std::string m_strNetTypeCode;
    std::string m_strSerialNumber;
    std::string m_strProviderCode;

    std::string m_strAcceptProvinceCode;   ///20160310
    std::string m_strAcceptRegionCode;   ///20160310
    std::string m_strAcceptCityCode;     ///20160310

    ///20160427
    std::string m_strRemark;
    std::vector<CTradeItem> m_vecTradeItem;

    NodeRoot m_nrRoot;
    NodeTrade m_ntTrade;
};

}


#endif /* SOINVOKETRADE_H_ */
