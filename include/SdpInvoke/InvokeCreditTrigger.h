/*
 * InvokeCreditTrigger.h
 *
 *  Created on: 2016年7月7日
 *      Author: clzdl
 */

#ifndef INCLUDE_INVOKECREDITTRIGGER_H_
#define INCLUDE_INVOKECREDITTRIGGER_H_


#include <SdpInvoke/InvokeBase.h>

namespace BusinessUtil
{
//调用触发信控接口
class InvokeCreditTrigger:public InvokeBase
{
public:
    InvokeCreditTrigger(HTTPClientSession *pHttpSession , std::string strService);
    ~InvokeCreditTrigger();

    void SetAcctId(long v);
    void SetUserId(long v);
    void SetAddId(long v);
    void SetTradeTypeCode(int v);
    void SetThisFee(long v);
    void SetInType(std::string v);

private:
    int MakePackage();
    int ParsePackage();

    long m_lAcctId;
    long m_lUserId;
    long m_lAddId;
    int m_iTradeType;
    long m_lThisFee;
    std::string m_strInType;

};

}

#endif /* INCLUDE_INVOKECREDITTRIGGER_H_ */
