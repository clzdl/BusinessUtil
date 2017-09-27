#ifndef _CRM_JSON_INTERFACE_DATA_H_
#define _CRM_JSON_INTERFACE_DATA_H_

#include <SdpInvoke/JsonFieldDefine.h>
#include <string>
#include <vector>
#include "cJSON.h"
namespace BusinessUtil
{


////////////应答包
class RespNodeBase
{
	public:
		RespNodeBase();
		virtual ~RespNodeBase() = 0;
};

////
class RespNodeRoot:public RespNodeBase
{
	public:
		RespNodeRoot();
		~RespNodeRoot();

		RespNodeRoot(const RespNodeRoot &rnr);
		RespNodeRoot& operator = (const RespNodeRoot &rnr);

		void SetRespCode(std::string code);
		void SetRespDesc(std::string desc);

		std::string GetRespCode();
		std::string GetRespUtf8Desc();
		std::string GetRespGb18030Desc();
		static int JsonParseRespRootNode(std::string strResp , RespNodeRoot &rnr);
	private:
		std::string m_strRespCode;
		std::string m_strRespDesc;
};



typedef struct OweFeeInfo
{
	long lAcctID;
	long lRealFee;///当月实时话费（实时账单）
	long lOweFee;  /// 往月欠费
	long lTotalOweFee;  ///总欠费金额
	long lLeaveRealFee; /// 账户余额
	char strLMPayTag[4];    ///上月账单出帐表示； 0-未出帐，1-已出帐
	long lLMBillFee;     ///上月账单费用
	char strPrepayTag[1+1] ; ///用户付费类型
}_OWE_FEE_INFO;

class RespNodeQryOweFeeNode
{
	
	public:
		
		
		RespNodeQryOweFeeNode();
		~RespNodeQryOweFeeNode();

		RespNodeQryOweFeeNode(const RespNodeQryOweFeeNode &resp);
		RespNodeQryOweFeeNode& operator = (const RespNodeQryOweFeeNode &resp);

		void SetRespNodeRoot(RespNodeRoot &rnr);
		/*
		 * 实时结余：
		 *      后付费:  不包含当月账单费用及上月未出帐费用
		 *      准预用户：       包含单月账单及上月未出帐费用
		 */
		long GetLeaveRealFee(long &lCurRealFee, long &lLMNoPayBillFee);
		void PushBack(_OWE_FEE_INFO &ofi);

		std::string GetRespCode();
		std::string GetRespUtf8Desc();

		static int JsonParseRespQryOweFeeNode(std::string strResp , RespNodeQryOweFeeNode &respQOF);
	private:

		RespNodeRoot m_respRoot;
		std::vector<_OWE_FEE_INFO> m_vecFee;
		
			
};
//////////用户充值
class RespNodePayFeeNode:public RespNodeRoot
{
public:
	RespNodePayFeeNode();
	~RespNodePayFeeNode();
	RespNodePayFeeNode(const RespNodePayFeeNode &resp);
	RespNodePayFeeNode& operator = (const RespNodePayFeeNode &resp);

	void SetChargeID(std::string id);
	std::string GetChargeID();
	static int JsonParseRespPayFeeNode(std::string strResp, RespNodePayFeeNode &respPF);
private:
	std::string m_strChargeID;
};

//////////在途工单
typedef struct
{
    char strTradeID[20];
    char strTradeTypeCode[6];
}_ON_WAY_SHEET;

class RespNodeOnWaySheeNode:public RespNodeRoot
{
public:
    RespNodeOnWaySheeNode();
    ~RespNodeOnWaySheeNode();


    void PushOnWaySheet(_ON_WAY_SHEET &sheet);
    const std::vector<_ON_WAY_SHEET> &GetOnWaySheet();
    static int JsonParseOnWaySheetNode(std::string strResp, RespNodeOnWaySheeNode &respSheet);

private:
    RespNodeOnWaySheeNode(const RespNodeOnWaySheeNode &resp);
    RespNodeOnWaySheeNode& operator = (const RespNodeOnWaySheeNode &resp);
    std::vector<_ON_WAY_SHEET> m_vecOnWaySheet;
};

}

#endif

