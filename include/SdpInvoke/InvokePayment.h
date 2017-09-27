/*
 * soInvokePayment.h
 *
 *  Created on: 2015年6月16日
 *      Author: chengl
 */

#ifndef SOINVOKEPAYMENT_H_
#define SOINVOKEPAYMENT_H_

/* 缴费接口
 *
 */
#include <SdpInvoke/InvokeBase.h>
namespace BusinessUtil
{


class InvokePayment:public InvokeBase
{
public:
    InvokePayment(HTTPClientSession *pHttpSession , std::string strService);
    ~InvokePayment();

    void SetProvinceCode(std::string code);
    void SetRegionCode(std::string code);
    void SetCityCode(std::string code);
    void SetUserID(long id);
    void SetSerialNumber(std::string no);
    void SetRecvFee(long fee);
    void SetActivityID(long id);
    void SetPaymentID(std::string id);
    void SetPayfeeModeCode(std::string code);
    void SetTradeTypeCode(std::string code);

    std::string GetChargeID();

private:
    int MakePackage();
    int ParsePackage();

    std::string m_strProvinceCode;
    std::string m_strRegionCode;
    std::string m_strCityCode;
    long m_lUserID;
    std::string m_strSerialNumber;
    long m_lRecvFee;        ///缴费金额
    long m_lActivityID;
    std::string m_strPaymentID;
    std::string m_strPayfeeModeCode;
    std::string m_strTradeTypeCode;

    std::string m_strChargeID;   ///返回的充值流水

};

}


#endif /* SOINVOKEPAYMENT_H_ */
