/*
 * soInvokeOnwaySheet.h
 *
 *  Created on: 2015年6月17日
 *      Author: chengl
 */

#ifndef SOINVOKEONWAYSHEET_H_
#define SOINVOKEONWAYSHEET_H_


/*
 * 查询停开机在途工单接口
 *
 */
#include <SdpInvoke/InvokeBase.h>
#include "JsonReqNode.h"
#include "JsonRespNode.h"

namespace BusinessUtil
{
class InvokeOnwaySheet:public InvokeBase
{
public:
    InvokeOnwaySheet(HTTPClientSession *pHttpSession , std::string strService);
    ~InvokeOnwaySheet();

    void SetProvinceCode(std::string code);
    void SetRegionCode(std::string code);
    void SetCityCode(std::string code);
    void SetSerialNumber(std::string no);
    void SetTradeTypeCode(std::string code);

    std::vector<_ON_WAY_SHEET>& GetOnwaySheet();

private:
    int MakePackage();
    int ParsePackage();
    std::string m_strProvinceCode;
    std::string m_strRegionCode;
    std::string m_strCityCode;
    std::string m_strSerialNumber;
    std::string m_strTradeTypeCode;

    std::vector<_ON_WAY_SHEET> m_vecOnwaySheet;

};

}

#endif /* SOINVOKEONWAYSHEET_H_ */
