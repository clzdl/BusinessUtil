#ifndef _CRM_JSON_REQ_NODE_H_
#define _CRM_JSON_REQ_NODE_H_

#include <SdpInvoke/JsonFieldDefine.h>
#include <string>
#include <vector>
#include "cJSON.h"

namespace BusinessUtil
{
///请求包节点类
class NodeBase
{
	public:
		NodeBase();
		virtual ~NodeBase() = 0;
};


////20160427
class CTradeItem
{
public:
    void SetUpdateStaffId(std::string v ){strUpdateStaffId = v;}
    void SetUpdateDepartId(std::string v){strUpdateDepartId = v;}
    void SetUpdateDate(std::string v) {strUpdateDate = v;}
    void SetItemId(std::string v){ strItemId = v;}
    void SetAttrCode(std::string v) {strAttrCode = v;}
    void SetAttrValue(std::string v) { strAttrValue = v;}

    std::string GetUpdateStaffId(){ return strUpdateStaffId; }
    std::string GetUpdateDepartId(){ return strUpdateDepartId;}
    std::string GetUpdateDate() {return strUpdateDate;}
    std::string GetItemId(){ return strItemId;}
    std::string GetAttrCode(){ return strAttrCode;}
    std::string GetAttrValue(){ return strAttrValue; }


private:
    std::string strUpdateStaffId;
    std::string strUpdateDepartId;
    std::string strUpdateDate;
    std::string strItemId;
    std::string strAttrCode;
    std::string strAttrValue;
};

class NodeTrade:public NodeBase
{
	public:
		
		NodeTrade();
		~NodeTrade();

		NodeTrade(const NodeTrade &nt);
		NodeTrade& operator = (const NodeTrade &nt);

		void SetSubscribeID(std::string id);
		void SetTradeID(std::string id);
		void SetTradeTypeCode(std::string id);
		void SetInModeCode(std::string code);
		void SetSubscribeState(std::string state);
		void SetPackageID(std::string id);
		void SetBrandCode(std::string code);
		void SetUserID(std::string id);
		void SetCustID(std::string id);
		void SetAcctID(std::string id);
		void SetNetTypeCode(std::string code);
		void SetSerialNumber(std::string number);
		void SetCustName(std::string name);
		void SetFinishDate(std::string date);
		void SetAcceptStaffID(std::string id);
		void SetAcceptDepartID(std::string id);
		void SetAcceptProvinceCode(std::string code);
		void SetAcceptRegionCode(std::string code);
		void SetAcceptCityCode(std::string code);
		void SetTermIP(std::string ip);
		void SetProvinceCode(std::string code);
		void SetRegionCode(std::string code);
		void SetCityCode(std::string code);
		void SetHaseFee(std::string hasfee);
		void SetFeeNum(std::string fee);
		void SetActorName(std::string name);
		void SetActorCertTypeID(std::string id);
		void SetActorPhone(std::string phone);
		void SetActorCertNum(std::string num);
		void SetContact(std::string contact);
		void SetContactPhone(std::string phone);
		void SetContactAddress(std::string addr);
		void SetRemark(std::string remark);
		void SetProviderCode(std::string code);
		void SetAcceptDate(std::string date);
		void SetOrderType(std::string type);
		void AddTradeItem(CTradeItem &ti);


		std::string GetSubscribeID();
		std::string GetTradeID();
		std::string GetTradeTypeCode();
		std::string GetInModeCode();
		std::string GetSubscribeState();
		std::string GetPackageID();
		std::string GetBrandCode();
		std::string GetUserID();
		std::string GetCustID();
		std::string GetAcctID();
		std::string GetNetTypeCode();
		std::string GetSerialNumber();
		std::string GetCustName();
		std::string GetFinishDate();
		std::string GetAcceptStaffID();
		std::string GetAcceptDepartID();
		std::string GetAcceptProvinceCode();
		std::string GetAcceptRegionCode();
		std::string GetAcceptCityCode();
		std::string GetTermIP();
		std::string GetProvinceCode();
		std::string GetRegionCode();
		std::string GetCityCode();
		std::string GetHaseFee();
		std::string GetFeeNum();
		std::string GetActorName();
		std::string GetActorCertTypeID();
		std::string GetActorPhone();
		std::string GetActorCertNum();
		std::string GetContact();
		std::string GetContactPhone();
		std::string GetContactAddress();
		std::string GetRemark();
		std::string GetProviderCode();
		std::string GetAcceptDate();
		std::string GetOrderType();
		
		static int JsonAddTradeNode(cJSON *root ,NodeBase &nb);

		std::vector<CTradeItem> m_vecTradeItem;

	private:
		std::string m_strSubscribeID;
		std::string m_strTradeID;
		std::string m_strTradeTypeCode;
		std::string m_strInModeCode;
		std::string m_strSubscribeState;
		std::string m_strPackageID;
		std::string m_strBrandCode;
		std::string m_strUserID;
		std::string m_strCustID;
		std::string m_strAcctID;
		std::string m_strNetTypeCode;
		std::string m_strSerialNumber;
		std::string m_strCustName;
		std::string m_strFinishDate;
		std::string m_strAcceptStaffID;
		std::string m_strAcceptDepartID;
		std::string m_strAcceptProvinceCode;
		std::string m_strAcceptRegionCode;
		std::string m_strAcceptCityCode;
		std::string m_strAcceptDate;
		std::string m_strOrderType;
		std::string m_strTermIP;
		std::string m_strProvinceCode;
		std::string m_strRegionCode;
		std::string m_strCityCode;
		std::string m_strHaseFee;
		std::string m_strFeeSum;
		std::string m_strActorName;

		std::string m_strActorCertTypeID;
		std::string m_strActorPhone;
		std::string m_strActorCertNum;
		std::string m_strContact;
		std::string m_strContactPhone;
		std::string m_strContactAddress;
		std::string m_strRemark;
		std::string m_strProviderCode;


	
};

///缴费查询
class NodeQryOweFee:public NodeBase
{
	public:
		NodeQryOweFee();
		~NodeQryOweFee();
		NodeQryOweFee(const NodeQryOweFee &nqof);
		NodeQryOweFee& operator  = (const NodeQryOweFee &nqof);

		void SetRecvTag(int tag);
		void SetQryID(std::string id);

		int GetRecvTag();
		std::string GetQryID();
		
		static int JsonAddQryOweFeeNode(cJSON *root , NodeBase &nb);

	private:
		int m_iRecvTag;
		std::string m_strQryID;
		
};

///用户缴费
class NodePayFee:public NodeBase
{
public:
	NodePayFee();
	~NodePayFee();
	NodePayFee(const NodePayFee &npf);
	NodePayFee& operator = (const NodePayFee &npf);

	void SetSerialNumber(std::string number);
	void SetRecvTag(std::string tag);
	void SetAcctID(std::string id);
	void SetUserID(std::string id);
	void SetRecvFee(std::string fee);
	void SetPaymentID(std::string id);
	void SetPayfeeModeCode(std::string code);
	void SetChannelID(std::string id);
	void SetPayOrderNumber(std::string number);
	void SetPayChargeID(std::string id);
	void SetBankCode(std::string code);
	void SetCardType(std::string type);
	void SetPostNumber(std::string number);
	void SetActionCode(std::string code);
	void SetTradeTypeCode(std::string code);

	std::string GetSerialNumber();
	std::string GetRecvTag();
	std::string GetAcctID();
	std::string GetUserID();
	std::string GetRecvFee();
	std::string GetPaymentID();
	std::string GetPayfeeModeCode();
	std::string GetChannelID();
	std::string GetPayOrderNumber();
	std::string GetPayChargeID();
	std::string GetBankCode();
	std::string GetCardType();
	std::string GetPostNumber();
	std::string GetActionCode();
	std::string GetTradeTypeCode();
	static int JsonAddPayFeeNode(cJSON *root , NodeBase &nb);
private:

	std::string m_strSerialNumber;		///
	std::string m_strRecvTag;			///
	std::string m_strAcctID;
	std::string m_strUserID;
	std::string m_strRecvFee;
	std::string m_strPaymentID;
	std::string m_strPayfeeModeCode;
	std::string m_strChannelID;
	std::string m_strPayOrderNumber;
	std::string m_strPayChargeID;
	std::string m_strBankCode;
	std::string m_strCardType;
	std::string m_strPostNumber;
	std::string m_strActionCode;
	std::string m_strTradeTypeCode;


};


////短信发送
class NodeSendMsg:public NodeBase
{
	public:
		NodeSendMsg();
		NodeSendMsg(std::string phone, std::string msg);
		~NodeSendMsg();
		NodeSendMsg(const NodeSendMsg &nsm);
		NodeSendMsg& operator = (const NodeSendMsg &nsm);

		void SetPhoneNum(std::string num);
		void SetMsg(std::string msg);

		std::string GetPhoneNum();
		std::string GetMsg();
		static int JsonAddSendMsgNode(cJSON *root , NodeBase &nb);
	private:
		std::string m_strPhoneNum;
		std::string m_strMsg;
		
};

////在途工单判断
class NodeOnWaySheet:public NodeBase
{
    public:
        NodeOnWaySheet();
        NodeOnWaySheet(std::string strTradeTypeCode, std::string strSeialNumber);
        ~NodeOnWaySheet();
        NodeOnWaySheet(const NodeOnWaySheet &nows);
        NodeOnWaySheet& operator = (const NodeOnWaySheet &nows);

        void SetSerialNumber(std::string num);
        void SetTradeTypeCode(std::string code);

        std::string GetSerialNumber();
        std::string GetTradeTypeCode();
        static int JsonAddOnWaySheetNode(cJSON *root , NodeBase &nb);
    private:
        std::string m_strSerialNumber;
        std::string m_strTradeTypeCode;

};


///////////////

///包头类
class NodeRoot
{
	public:
		NodeRoot();
		~NodeRoot();

		NodeRoot(const NodeRoot &nr);
		NodeRoot& operator = (const NodeRoot &nr);
		
		void SetOperCode(std::string code);
		void SetStaffID(std::string id);
		void SetDepartID(std::string id);
		void SetProvinceCode(std::string code);
		void SetRegionCode(std::string code);
		void SetCityCode(std::string code);
		void SetRouteProvinceCode(std::string code);
		void SetRouteRegionCode(std::string code);
		void SetRouteCityCode(std::string code);
		void SetInNetMode(std::string mode);


		std::string GetOperCode();
		std::string GetStaffID();
		std::string GetDepartID();
		std::string GetProvinceCode();
		std::string GetRegionCode();
		std::string GetCityCode();
		std::string GetRouteProvinceCode();
		std::string GetRouteRegionCode();
		std::string GetRouteCityCode();
		std::string GetInNetMode();
		static cJSON* JsonCreateRoot(NodeRoot &nr);

		
	private:
		std::string m_strOperCode;
		std::string m_strStaffID;
		std::string m_strDepartID;
		std::string m_strProvinceCode;
		std::string m_strRegionCode;
		std::string m_strCityCode;
		std::string m_strRouteProvinceCode;
		std::string m_strRouteRegionCode;
		std::string m_strRouteCityCode;
		std::string m_strInNetMode;
		
};

}

#endif

