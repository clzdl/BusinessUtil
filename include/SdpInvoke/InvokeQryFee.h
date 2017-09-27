/*
 * soInvokeQryFee.h
 *
 *  Created on: 2015年6月17日
 *      Author: chengl
 */

#ifndef SOINVOKEQRYFEE_H_
#define SOINVOKEQRYFEE_H_

/*余额查询接口
 *
 */
#include <SdpInvoke/InvokeBase.h>
namespace BusinessUtil
{
class InvokeQryFee:public InvokeBase
{
public:
    InvokeQryFee(HTTPClientSession *pHttpSession , std::string strService);
    ~InvokeQryFee();

    void SetProvinceCode(std::string code);
    void SetRegionCode(std::string code);
    void SetCityCode(std::string code);
    void SetQryId(std::string id);
    void SetRecvTag(int tag);

    long GetLeaveRealFee();
    long GetCurRealFee();
    long GetLMNoPayBillFee();


private:
    int MakePackage();
    int ParsePackage();

    std::string m_strProvinceCode;
    std::string m_strRegionCode;
    std::string m_strCityCode;
    std::string m_strQryId;
    int m_iRecvTag;    ///1： 按电话号码查询

    long m_lLeaveRealFee;  ///实时结余
    long m_lCruRealFee;   ///当月话费
    long m_lLMNoPayBillFee;   ///上月未出帐话费

};

}

#endif /* SOINVOKEQRYFEE_H_ */
