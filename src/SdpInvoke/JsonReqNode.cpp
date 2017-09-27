#include <SdpInvoke/JsonReqNode.h>
#include "MacroDefine.h"
#include "stdio.h"

namespace BusinessUtil
{

NodeBase::NodeBase()
{

}

NodeBase::~NodeBase()
{

}
/////////////////
NodeTrade::NodeTrade()
{

}

NodeTrade::~NodeTrade()
{

}

NodeTrade::NodeTrade(const NodeTrade &nt)
{
	m_strSubscribeID = nt.m_strSubscribeID;
	m_strTradeID =nt.m_strTradeID;
	m_strTradeTypeCode = nt.m_strTradeTypeCode;
	m_strInModeCode = nt.m_strInModeCode;
	m_strSubscribeState = nt.m_strSubscribeState;
	m_strPackageID = nt.m_strPackageID;
	m_strBrandCode = nt.m_strBrandCode;
	m_strUserID = nt.m_strUserID;
	m_strCustID = nt.m_strCustID;
	m_strAcctID = nt.m_strAcctID;
	m_strNetTypeCode = nt.m_strNetTypeCode;
	m_strSerialNumber = nt.m_strSerialNumber;
	m_strCustName = nt.m_strCustName;
	m_strFinishDate = nt.m_strFinishDate;
	m_strAcceptStaffID = nt.m_strAcceptStaffID;
	m_strAcceptDepartID = nt.m_strAcceptDepartID;
	m_strAcceptProvinceCode = nt.m_strAcceptProvinceCode;
	m_strAcceptRegionCode = nt.m_strAcceptRegionCode;
	m_strAcceptCityCode = nt.m_strAcceptCityCode;
	m_strTermIP = nt.m_strTermIP;
	m_strProvinceCode = nt.m_strProvinceCode;
	m_strRegionCode = nt.m_strRegionCode;
	m_strCityCode = nt.m_strCityCode;
	m_strHaseFee = nt.m_strHaseFee;
	m_strFeeSum = nt.m_strFeeSum;
	m_strActorName = nt.m_strActorName;
	m_strActorCertTypeID = nt.m_strActorCertTypeID;
	m_strActorPhone = nt.m_strActorPhone;
	m_strActorCertNum = nt.m_strActorCertNum;
	m_strContact = nt.m_strContact;
	m_strContactPhone = nt.m_strContactPhone;
	m_strContactAddress = nt.m_strContactAddress;
	m_strRemark = nt.m_strRemark;
	m_strProviderCode = nt.m_strProviderCode;

	m_vecTradeItem.insert(m_vecTradeItem.begin() , nt.m_vecTradeItem.begin(), nt.m_vecTradeItem.end());

}
NodeTrade& NodeTrade::operator = (const NodeTrade &nt)
{
	if(this == &nt)
		return *this;

	m_strSubscribeID = nt.m_strSubscribeID;
	m_strTradeID =nt.m_strTradeID;
	m_strTradeTypeCode = nt.m_strTradeTypeCode;
	m_strInModeCode = nt.m_strInModeCode;
	m_strSubscribeState = nt.m_strSubscribeState;
	m_strPackageID = nt.m_strPackageID;
	m_strBrandCode = nt.m_strBrandCode;
	m_strUserID = nt.m_strUserID;
	m_strCustID = nt.m_strCustID;
	m_strAcctID = nt.m_strAcctID;
	m_strNetTypeCode = nt.m_strNetTypeCode;
	m_strSerialNumber = nt.m_strSerialNumber;
	m_strCustName = nt.m_strCustName;
	m_strFinishDate = nt.m_strFinishDate;
	m_strAcceptStaffID = nt.m_strAcceptStaffID;
	m_strAcceptDepartID = nt.m_strAcceptDepartID;
	m_strAcceptProvinceCode = nt.m_strAcceptProvinceCode;
	m_strAcceptRegionCode = nt.m_strAcceptRegionCode;
	m_strAcceptCityCode = nt.m_strAcceptCityCode;
	m_strTermIP = nt.m_strTermIP;
	m_strProvinceCode = nt.m_strProvinceCode;
	m_strRegionCode = nt.m_strRegionCode;
	m_strCityCode = nt.m_strCityCode;
	m_strHaseFee = nt.m_strHaseFee;
	m_strFeeSum = nt.m_strFeeSum;
	m_strActorName = nt.m_strActorName;
	m_strActorCertTypeID = nt.m_strActorCertTypeID;
	m_strActorPhone = nt.m_strActorPhone;
	m_strActorCertNum = nt.m_strActorCertNum;
	m_strContact = nt.m_strContact;
	m_strContactPhone = nt.m_strContactPhone;
	m_strContactAddress = nt.m_strContactAddress;
	m_strRemark = nt.m_strRemark;
	m_strProviderCode = nt.m_strProviderCode;

	m_vecTradeItem.clear();
	m_vecTradeItem.insert(m_vecTradeItem.begin() , nt.m_vecTradeItem.begin(), nt.m_vecTradeItem.end());

	return *this;
}

void NodeTrade::SetSubscribeID(std::string id)
{
	m_strSubscribeID = id;
}	
void NodeTrade::SetTradeID(std::string id)
{
	m_strTradeID = id;
}
void NodeTrade::SetTradeTypeCode(std::string id)
{
	m_strTradeTypeCode = id;
}
void NodeTrade::SetInModeCode(std::string code)
{
	m_strInModeCode = code;
}
void NodeTrade::SetSubscribeState(std::string state)
{
	m_strSubscribeState = state;
}
void NodeTrade::SetPackageID(std::string id)
{
	m_strPackageID = id;
}
void NodeTrade::SetBrandCode(std::string code)
{
	m_strBrandCode = code;
}
void NodeTrade::SetUserID(std::string id)
{
	m_strUserID = id;
}
void NodeTrade::SetCustID(std::string id)
{
	m_strCustID = id;
}
void NodeTrade::SetAcctID(std::string id)
{
	m_strAcctID = id;
}
void NodeTrade::SetNetTypeCode(std::string code)
{
	m_strNetTypeCode = code;
}
void NodeTrade::SetSerialNumber(std::string number)
{
	m_strSerialNumber = number;
}
void NodeTrade::SetCustName(std::string name)
{
	m_strCustName = name;
}
void NodeTrade::SetFinishDate(std::string date)
{
	m_strFinishDate = date;
}
void NodeTrade::SetAcceptStaffID(std::string id)
{
	m_strAcceptStaffID = id;
}
void NodeTrade::SetAcceptDepartID(std::string id)
{
	m_strAcceptDepartID = id;
}
void NodeTrade::SetAcceptProvinceCode(std::string code)
{
	m_strAcceptProvinceCode = code;
}
void NodeTrade::SetAcceptRegionCode(std::string code)
{
	m_strAcceptRegionCode = code;
}
void NodeTrade::SetAcceptCityCode(std::string code)
{
	m_strAcceptCityCode = code;
}
void NodeTrade::SetTermIP(std::string ip)
{
	m_strTermIP = ip;
}
void NodeTrade::SetProvinceCode(std::string code)
{
	m_strProvinceCode = code;
}
void NodeTrade::SetRegionCode(std::string code)
{
	m_strRegionCode = code;
}
void NodeTrade::SetCityCode(std::string code)
{
	m_strCityCode = code;
}
void NodeTrade::SetHaseFee(std::string hasfee)
{
	m_strHaseFee = hasfee;
}
void NodeTrade::SetFeeNum(std::string fee)
{
	m_strFeeSum = fee;
}
void NodeTrade::SetActorName(std::string name)
{
	m_strActorName = name;
}
void NodeTrade::SetActorCertTypeID(std::string id)
{
	m_strActorCertTypeID = id;
}
void NodeTrade::SetActorPhone(std::string phone)
{
	m_strActorPhone = phone;
}
void NodeTrade::SetActorCertNum(std::string num)
{
	m_strActorCertNum = num;
}
void NodeTrade::SetContact(std::string contact)
{
	m_strContact = contact;
}
void NodeTrade::SetContactPhone(std::string phone)
{
	m_strContactPhone = phone;
}
void NodeTrade::SetContactAddress(std::string addr)
{
	m_strContactAddress = addr;
}
void NodeTrade::SetRemark(std::string remark)
{
	m_strRemark = remark;
}
void NodeTrade::SetProviderCode(std::string code)
{
	m_strProviderCode = code;
}	
void NodeTrade::SetAcceptDate(std::string date)
{
	m_strAcceptDate = date;
}
void NodeTrade::SetOrderType(std::string type)
{
	m_strOrderType = type;
}

void NodeTrade::AddTradeItem(CTradeItem &ti)
{
    m_vecTradeItem.push_back(ti);
}



std::string NodeTrade::GetAcceptDate()
{
	return m_strAcceptDate;
}
std::string NodeTrade::GetOrderType()
{
	return m_strOrderType;
}


std::string NodeTrade::GetSubscribeID()
{
	return m_strSubscribeID;
}
std::string NodeTrade::GetTradeID()
{
	return m_strTradeID;
}
std::string NodeTrade::GetTradeTypeCode()
{
	return m_strTradeTypeCode;
}
std::string NodeTrade::GetInModeCode()
{
	return m_strInModeCode;
}
std::string NodeTrade::GetSubscribeState()
{
	return m_strSubscribeState;
}
std::string NodeTrade::GetPackageID()
{
	return m_strPackageID;
}
std::string NodeTrade::GetBrandCode()
{
	return m_strBrandCode;
}
std::string NodeTrade::GetUserID()
{
	return m_strUserID;
}
std::string NodeTrade::GetCustID()
{
	return m_strCustID;
}
std::string NodeTrade::GetAcctID()
{
	return m_strAcctID;
}
std::string NodeTrade::GetNetTypeCode()
{
	return m_strNetTypeCode;
}
std::string NodeTrade::GetSerialNumber()
{
	return m_strSerialNumber;
}
std::string NodeTrade::GetCustName()
{
	return m_strCustName;
}
std::string NodeTrade::GetFinishDate()
{
	return m_strFinishDate;
}
std::string NodeTrade::GetAcceptStaffID()
{
	return m_strAcceptStaffID;
}
std::string NodeTrade::GetAcceptDepartID()
{
	return m_strAcceptDepartID;
}
std::string NodeTrade::GetAcceptProvinceCode()
{
	return m_strAcceptProvinceCode;
}
std::string NodeTrade::GetAcceptRegionCode()
{
	return m_strAcceptRegionCode;
}
std::string NodeTrade::GetAcceptCityCode()
{
	return m_strAcceptCityCode;
}
std::string NodeTrade::GetTermIP()
{
	return m_strTermIP;
}
std::string NodeTrade::GetProvinceCode()
{
	return m_strProvinceCode;
}
std::string NodeTrade::GetRegionCode()
{
	return m_strRegionCode;
}
std::string NodeTrade::GetCityCode()
{
	return m_strCityCode;
}
std::string NodeTrade::GetHaseFee()
{
	return m_strHaseFee;
}
std::string NodeTrade::GetFeeNum()
{
	return m_strFeeSum;
}
std::string NodeTrade::GetActorName()
{
	return m_strActorName;
}
std::string NodeTrade::GetActorCertTypeID()
{
	return m_strActorCertTypeID;
}
std::string NodeTrade::GetActorPhone()
{
	return m_strActorPhone;
}
std::string NodeTrade::GetActorCertNum()
{
	return m_strActorCertNum;
}
std::string NodeTrade::GetContact()
{
	return m_strContact;
}
std::string NodeTrade::GetContactPhone()
{
	return m_strContactPhone;
}
std::string NodeTrade::GetContactAddress()
{
	return m_strContactAddress;
}
std::string NodeTrade::GetRemark()
{
	return m_strRemark;
}
std::string NodeTrade::GetProviderCode()
{
	return m_strProviderCode;
}

int NodeTrade::JsonAddTradeNode(cJSON *root ,NodeBase &nb)
{
	cJSON *parm = NULL,*tradeNode=NULL;

	NodeTrade &nt = dynamic_cast<NodeTrade & >(nb);


	parm=cJSON_CreateObject();
	if(NULL == parm)
	{
		fprintf(stderr,"cJSON_CreateObject return null.\n");
		return FAIL;
	}

	cJSON_AddItemToObject(root, PARAMETERS, parm);

	tradeNode=cJSON_CreateObject();
	if(NULL == parm)
	{
		fprintf(stderr,"cJSON_CreateObject return null.\n");
		return FAIL;
	}

	cJSON_AddItemToObject(parm , TRADE , tradeNode);
	/////

	cJSON_AddStringToObject(tradeNode,ORDER_TYPE,		nt.GetOrderType().c_str());
	cJSON_AddStringToObject(tradeNode,SUBSCRIBE_ID,		nt.GetSubscribeID().c_str());
	cJSON_AddStringToObject(tradeNode,TRADE_ID,			nt.GetTradeID().c_str());
	cJSON_AddStringToObject(tradeNode,TRADE_TYPE_CODE,	nt.GetTradeTypeCode().c_str());
	cJSON_AddStringToObject(tradeNode,IN_MODE_CODE,		nt.GetInModeCode().c_str());
	cJSON_AddStringToObject(tradeNode,SUBSCRIBE_STATE,	nt.GetSubscribeState().c_str());
	cJSON_AddStringToObject(tradeNode,PACKAGE_ID,		nt.GetPackageID().c_str());
	cJSON_AddStringToObject(tradeNode,BRAND_CODE,		nt.GetBrandCode().c_str());

	cJSON_AddStringToObject(tradeNode,USER_ID,			nt.GetUserID().c_str());
	cJSON_AddStringToObject(tradeNode,CUST_ID,			nt.GetCustID().c_str());
	cJSON_AddStringToObject(tradeNode,ACCT_ID,			nt.GetAcctID().c_str());
	cJSON_AddStringToObject(tradeNode,NET_TYPE_CODE,	nt.GetNetTypeCode().c_str());
	cJSON_AddStringToObject(tradeNode,SERIAL_NUMBER,	nt.GetSerialNumber().c_str());
	cJSON_AddStringToObject(tradeNode,CUST_NAME,		nt.GetCustName().c_str());
	cJSON_AddStringToObject(tradeNode,FINISH_DATE,		nt.GetFinishDate().c_str());
	cJSON_AddStringToObject(tradeNode,ACCEPT_STAFF_ID,	nt.GetAcceptStaffID().c_str());
	cJSON_AddStringToObject(tradeNode,ACCEPT_DEPART_ID,			nt.GetAcceptDepartID().c_str());
	cJSON_AddStringToObject(tradeNode,ACCEPT_PROVINCE_CODE,		nt.GetAcceptProvinceCode().c_str());
	cJSON_AddStringToObject(tradeNode,ACCEPT_REGION_CODE,		nt.GetAcceptRegionCode().c_str());
	cJSON_AddStringToObject(tradeNode,ACCEPT_CITY_CODE,			nt.GetAcceptCityCode().c_str());
	cJSON_AddStringToObject(tradeNode,ACCEPT_DATE,			nt.GetAcceptDate().c_str());


	cJSON_AddStringToObject(tradeNode,TERM_IP,					nt.GetTermIP().c_str());
	cJSON_AddStringToObject(tradeNode,PROVINCE_CODE,			nt.GetProvinceCode().c_str());
	cJSON_AddStringToObject(tradeNode,REGION_CODE,				nt.GetRegionCode().c_str());
	cJSON_AddStringToObject(tradeNode,CITY_CODE,				nt.GetCityCode().c_str());
	cJSON_AddStringToObject(tradeNode,HASE_FEE,					nt.GetHaseFee().c_str());
	cJSON_AddStringToObject(tradeNode,FEE_SUM,					nt.GetFeeNum().c_str());
	cJSON_AddStringToObject(tradeNode,ACTOR_NAME,				nt.GetActorName().c_str());
	cJSON_AddStringToObject(tradeNode,ACTOR_CERT_TYPE_ID,		nt.GetActorCertTypeID().c_str());
	cJSON_AddStringToObject(tradeNode,ACTOR_PHONE,				nt.GetActorPhone().c_str());
	cJSON_AddStringToObject(tradeNode,ACTOR_CERT_NUM,			nt.GetActorCertNum().c_str());
	cJSON_AddStringToObject(tradeNode,CONTACT,					nt.GetContact().c_str());
	cJSON_AddStringToObject(tradeNode,CONTACT_PHONE,			nt.GetContactPhone().c_str());
	cJSON_AddStringToObject(tradeNode,CONTACT_ADDRESS,			nt.GetContactAddress().c_str());
	cJSON_AddStringToObject(tradeNode,REMARK,					nt.GetRemark().c_str());
	cJSON_AddStringToObject(tradeNode,PROVIDER_CODE,			nt.GetProviderCode().c_str());

	///20160427
	if( nt.m_vecTradeItem.size() > 0)
	{
	    cJSON *jsonAr = cJSON_CreateArray();

	    for(std::vector<CTradeItem>::iterator it = nt.m_vecTradeItem.begin() ; it != nt.m_vecTradeItem.end() ; ++it)
	    {
            cJSON *jsonItem = cJSON_CreateObject();

            cJSON_AddStringToObject(jsonItem , TRADE_ID , nt.GetTradeID().c_str());
            cJSON_AddStringToObject(jsonItem , UPDATE_STAFF_ID , it->GetUpdateStaffId().c_str());
            cJSON_AddStringToObject(jsonItem , UPDATE_DEPART_ID , it->GetUpdateDepartId().c_str());
            cJSON_AddStringToObject(jsonItem , UPDATE_DATE , it->GetUpdateDate().c_str());
            cJSON_AddStringToObject(jsonItem , ITEM_ID , it->GetItemId().c_str());
            cJSON_AddStringToObject(jsonItem , ATTR_CODE , it->GetAttrCode().c_str());
            cJSON_AddStringToObject(jsonItem , ATTR_VALUE , it->GetAttrValue().c_str());

            cJSON_AddItemToArray(jsonAr , jsonItem);
	    }

	    cJSON_AddItemToObject(parm , TRADE_ITEM, jsonAr);
	}

	return 0;
}


///////////////////
NodeQryOweFee::NodeQryOweFee()
{

}

NodeQryOweFee::~NodeQryOweFee()
{

}

NodeQryOweFee::NodeQryOweFee(const NodeQryOweFee &nqof)
{
	m_iRecvTag = nqof.m_iRecvTag;
	m_strQryID = nqof.m_strQryID;
}

NodeQryOweFee& NodeQryOweFee::operator  = (const NodeQryOweFee &nqof)
{
	if(this == &nqof)
		return *this;
	
	m_iRecvTag = nqof.m_iRecvTag;
	m_strQryID = nqof.m_strQryID;
	return *this;
}

void NodeQryOweFee::SetRecvTag(int tag)
{
	m_iRecvTag = tag;
}
void NodeQryOweFee::SetQryID(std::string id)
{
	m_strQryID = id;
}
int NodeQryOweFee::GetRecvTag()
{
	return m_iRecvTag;
}
std::string NodeQryOweFee::GetQryID()
{
	return m_strQryID;
}

int NodeQryOweFee::JsonAddQryOweFeeNode(cJSON *root , NodeBase &nb)
{
	cJSON *parm = NULL;

	NodeQryOweFee &nqof = dynamic_cast<NodeQryOweFee & >(nb);


	parm=cJSON_CreateObject();
	if(NULL == parm)
		return -1;

	cJSON_AddItemToObject(root, PARAMETERS, parm);
	switch(nqof.GetRecvTag())
	{
		case 0: //按账户id查询，1
			cJSON_AddStringToObject(parm,RECV_TAG,	"0");
			cJSON_AddStringToObject(parm,ACCT_ID,	nqof.GetQryID().c_str());
			break;
		case 1:// 按号码
			cJSON_AddStringToObject(parm,RECV_TAG,	"1");
			cJSON_AddStringToObject(parm,SERIAL_NUMBER,	nqof.GetQryID().c_str());
			break;
		case 3: // 按用户id
			cJSON_AddStringToObject(parm,RECV_TAG,	"3");
			cJSON_AddStringToObject(parm,USER_ID,	nqof.GetQryID().c_str());
			break;
	}

}

/////////
NodePayFee::NodePayFee()
{
}
NodePayFee::~NodePayFee()
{

}
NodePayFee::NodePayFee(const NodePayFee &npf)
{
	m_strSerialNumber = npf.m_strSerialNumber;
	m_strRecvTag = npf.m_strRecvTag;		///
	m_strAcctID = npf.m_strAcctID;
	m_strUserID = npf.m_strUserID;
	m_strRecvFee = npf.m_strRecvFee;
	m_strPaymentID = npf.m_strPaymentID;
	m_strPayfeeModeCode = npf.m_strPayfeeModeCode;
	m_strChannelID = npf.m_strChannelID;
	m_strPayOrderNumber = npf.m_strPayOrderNumber;
	m_strPayChargeID = npf.m_strPayChargeID;
	m_strBankCode = npf.m_strBankCode;
	m_strCardType = npf.m_strCardType;
	m_strPostNumber = npf.m_strPostNumber;
}
NodePayFee& NodePayFee::operator = (const NodePayFee &npf)
{
	if(this == &npf)
		return *this;

	m_strSerialNumber = npf.m_strSerialNumber;
	m_strRecvTag = npf.m_strRecvTag;		///
	m_strAcctID = npf.m_strAcctID;
	m_strUserID = npf.m_strUserID;
	m_strRecvFee = npf.m_strRecvFee;
	m_strPaymentID = npf.m_strPaymentID;
	m_strPayfeeModeCode = npf.m_strPayfeeModeCode;
	m_strChannelID = npf.m_strChannelID;
	m_strPayOrderNumber = npf.m_strPayOrderNumber;
	m_strPayChargeID = npf.m_strPayChargeID;
	m_strBankCode = npf.m_strBankCode;
	m_strCardType = npf.m_strCardType;
	m_strPostNumber = npf.m_strPostNumber;

	return *this;
}

void NodePayFee::SetSerialNumber(std::string number)
{
	m_strSerialNumber = number;
}
void NodePayFee::SetRecvTag(std::string tag)
{
	m_strRecvTag = tag;
}
void NodePayFee::SetAcctID(std::string id)
{
	m_strAcctID = id;
}
void NodePayFee::SetUserID(std::string id)
{
	m_strUserID = id;
}
void NodePayFee::SetRecvFee(std::string fee)
{
	m_strRecvFee = fee;
}
void NodePayFee::SetPaymentID(std::string id)
{
	m_strPaymentID= id;
}
void NodePayFee::SetPayfeeModeCode(std::string code)
{
	m_strPayfeeModeCode = code;
}
void NodePayFee::SetChannelID(std::string id)
{
	m_strChannelID = id;
}
void NodePayFee::SetPayOrderNumber(std::string number)
{
	m_strPayOrderNumber = number;
}
void NodePayFee::SetPayChargeID(std::string id)
{
	m_strPayChargeID = id;
}
void NodePayFee::SetBankCode(std::string code)
{
	m_strBankCode = code;
}
void NodePayFee::SetCardType(std::string type)
{
	m_strCardType = type;
}
void NodePayFee::SetActionCode(std::string code)
{
    m_strActionCode = code;
}

void NodePayFee::SetPostNumber(std::string number)
{
	m_strPostNumber = number;
}
void NodePayFee::SetTradeTypeCode(std::string code)
{
    m_strTradeTypeCode = code;
}


std::string NodePayFee::GetSerialNumber()
{
	return m_strSerialNumber;
}
std::string NodePayFee::GetRecvTag()
{
	return m_strRecvTag;
}
std::string NodePayFee::GetAcctID()
{
	return m_strAcctID;
}

std::string NodePayFee::GetUserID()
{
	return m_strUserID;
}
std::string NodePayFee::GetRecvFee()
{
	return m_strRecvFee;
}
std::string NodePayFee::GetPaymentID()
{
	return m_strPaymentID;
}
std::string NodePayFee::GetPayfeeModeCode()
{
	return m_strPayfeeModeCode;
}
std::string NodePayFee::GetChannelID()
{
	return m_strChannelID;
}
std::string NodePayFee::GetPayOrderNumber()
{
	return m_strPayOrderNumber;
}
std::string NodePayFee::GetPayChargeID()
{
	return m_strPayChargeID;
}
std::string NodePayFee::GetBankCode()
{
	return m_strBankCode;
}
std::string NodePayFee::GetCardType()
{
	return m_strCardType;
}

std::string NodePayFee::GetPostNumber()
{
	return m_strPostNumber;
}
std::string NodePayFee::GetActionCode()
{
    return m_strActionCode;
}
std::string NodePayFee::GetTradeTypeCode()
{
    return m_strTradeTypeCode;
}

int NodePayFee::JsonAddPayFeeNode(cJSON *root , NodeBase &nb)
{
	cJSON *parm = NULL,*tradeNode=NULL;

	NodePayFee &npf = dynamic_cast<NodePayFee & >(nb);


	parm=cJSON_CreateObject();
	if(NULL == parm)
	{
		fprintf(stderr,"cJSON_CreateObject return null.\n");
		return FAIL;
	}

	cJSON_AddItemToObject(root, PARAMETERS, parm);

	if(npf.GetRecvTag() == "")
	{
		fprintf(stderr,"GetRecvTag is empty.\n");
		return FAIL;
	}

	cJSON_AddStringToObject(parm,RECV_TAG,		npf.GetRecvTag().c_str());

	///sdp 要求必填  20141124
	cJSON_AddStringToObject(parm,SERIAL_NUMBER, 		npf.GetSerialNumber().c_str());
	switch(npf.GetRecvTag().at(0))
	{
		case '0':	//账户
			cJSON_AddStringToObject(parm,ACCT_ID, 		npf.GetAcctID().c_str());
			break;
		case '3': //用户
			cJSON_AddStringToObject(parm,USER_ID, 		npf.GetUserID().c_str());
			break;
		default:
			return FAIL;
	}

	cJSON_AddStringToObject(parm,RECV_FEE,			npf.GetRecvFee().c_str());
	cJSON_AddStringToObject(parm,PAYMENT_ID,		npf.GetPaymentID().c_str());
	cJSON_AddStringToObject(parm,PAYFEE_MODE_CODE,	npf.GetPayfeeModeCode().c_str());
	cJSON_AddStringToObject(parm,CHANNEL_ID,		npf.GetChannelID().c_str());
	cJSON_AddStringToObject(parm,PAYORDER_NUMBER,		npf.GetPayOrderNumber().c_str());
	cJSON_AddStringToObject(parm,PAYCHARGE_ID,		npf.GetPayChargeID().c_str());
	cJSON_AddStringToObject(parm,BANK_CODE,			npf.GetBankCode().c_str());
	cJSON_AddStringToObject(parm,CARD_TYPE,			npf.GetCardType().c_str());
	cJSON_AddStringToObject(parm,POST_NUMBER,		npf.GetPostNumber().c_str());
	if(npf.GetActionCode() != "")
	    cJSON_AddStringToObject(parm,ACTION_CODE,              npf.GetActionCode().c_str());

	if(npf.GetTradeTypeCode() != "")
	    cJSON_AddStringToObject(parm,TRADE_TYPE_CODE,              npf.GetTradeTypeCode().c_str());

	return 0;
}

/////////////
NodeSendMsg::NodeSendMsg()
{
	
}
NodeSendMsg::NodeSendMsg(std::string phone, std::string msg)
:m_strPhoneNum(phone),
 m_strMsg(msg)
{

}

NodeSendMsg::~NodeSendMsg()
{


}

NodeSendMsg::NodeSendMsg(const NodeSendMsg &nsm)
{
	m_strPhoneNum = nsm.m_strPhoneNum;
	m_strMsg = nsm.m_strMsg;
}

NodeSendMsg& NodeSendMsg::operator = (const NodeSendMsg &nsm)
{
	if(this == &nsm)
		return *this;

	m_strPhoneNum = nsm.m_strPhoneNum;
	m_strMsg = nsm.m_strMsg;

	return *this;
}

void NodeSendMsg::SetPhoneNum(std::string num)
{
	m_strPhoneNum = num;
}
void NodeSendMsg::SetMsg(std::string msg)
{
	m_strMsg = msg;
}	

std::string NodeSendMsg::GetPhoneNum()
{
	return m_strPhoneNum;
}
std::string NodeSendMsg::GetMsg()
{
	return m_strMsg;
}


int NodeSendMsg::JsonAddSendMsgNode(cJSON *root , NodeBase &nb)
{
	cJSON *parm = NULL;

	NodeSendMsg &nsm = dynamic_cast<NodeSendMsg & >(nb);


	parm=cJSON_CreateObject();
	if(NULL == parm)
	{
		fprintf(stderr,"cJSON_CreateObject return null.\n");
		return FAIL;
	}

	cJSON_AddItemToObject(root, PARAMETERS, parm);

	cJSON_AddStringToObject(parm,PHONE_NUMBER,	nsm.GetPhoneNum().c_str());
	cJSON_AddStringToObject(parm,MSG,nsm.GetMsg().c_str());

	return 0;
}

//////////
NodeOnWaySheet::NodeOnWaySheet()
{

}
NodeOnWaySheet::NodeOnWaySheet(std::string strTradeTypeCode, std::string strSeialNumber)
{
    m_strSerialNumber = strSeialNumber;
    m_strTradeTypeCode = strTradeTypeCode;
}
NodeOnWaySheet::~NodeOnWaySheet()
{

}
NodeOnWaySheet::NodeOnWaySheet(const NodeOnWaySheet &nows)
{
    m_strSerialNumber = nows.m_strSerialNumber;
    m_strTradeTypeCode = nows.m_strTradeTypeCode;
}
NodeOnWaySheet& NodeOnWaySheet::operator = (const NodeOnWaySheet &nows)
{
    if(this == &nows)
        return *this;

    m_strSerialNumber = nows.m_strSerialNumber;
    m_strTradeTypeCode = nows.m_strTradeTypeCode;

    return *this;
}

void NodeOnWaySheet::SetSerialNumber(std::string num)
{
    m_strSerialNumber = num;
}
void NodeOnWaySheet::SetTradeTypeCode(std::string code)
{
    m_strTradeTypeCode = code;
}

std::string NodeOnWaySheet::GetSerialNumber()
{
    return m_strSerialNumber;
}
std::string NodeOnWaySheet::GetTradeTypeCode()
{
    return m_strTradeTypeCode;
}


///查询停在途工单 20150511
int NodeOnWaySheet::JsonAddOnWaySheetNode(cJSON *root , NodeBase &nb)
{
    cJSON *parm = NULL,*tradeNode=NULL;

    NodeOnWaySheet &nows = dynamic_cast<NodeOnWaySheet & >(nb);


    parm=cJSON_CreateObject();
    if(NULL == parm)
        return -1;

    cJSON_AddItemToObject(root, PARAMETERS, parm);
    cJSON_AddStringToObject(parm,TRADE_TYPE_CODE,      nows.GetTradeTypeCode().c_str());
    cJSON_AddStringToObject(parm,SERIAL_NUMBER,      nows.GetSerialNumber().c_str());

    return 0;
}


//////////
NodeRoot::NodeRoot()
{

}
NodeRoot::~NodeRoot()
{

}

NodeRoot::NodeRoot(const NodeRoot &nt)
{
	m_strOperCode = nt.m_strOperCode;
	m_strStaffID = nt.m_strStaffID;
	m_strDepartID = nt.m_strDepartID;
	m_strProvinceCode = nt.m_strProvinceCode;
	m_strRegionCode = nt.m_strRegionCode;
	m_strCityCode = nt.m_strCityCode;
	m_strRouteProvinceCode = nt.m_strRouteProvinceCode;
	m_strRouteRegionCode = nt.m_strRouteRegionCode;
	m_strRouteCityCode = nt.m_strRouteCityCode;
	m_strInNetMode = nt.m_strInNetMode;
}
NodeRoot& NodeRoot::operator = (const NodeRoot &nt)
{
	if(this == &nt)
		return *this;
	m_strOperCode = nt.m_strOperCode;
	m_strStaffID = nt.m_strStaffID;
	m_strDepartID = nt.m_strDepartID;
	m_strProvinceCode = nt.m_strProvinceCode;
	m_strRegionCode = nt.m_strRegionCode;
	m_strCityCode = nt.m_strCityCode;
	m_strRouteProvinceCode = nt.m_strRouteProvinceCode;
	m_strRouteRegionCode = nt.m_strRouteRegionCode;
	m_strRouteCityCode = nt.m_strRouteCityCode;
	m_strInNetMode = nt.m_strInNetMode;

	return *this;
}

void NodeRoot::SetOperCode(std::string code)
{	
	m_strOperCode = code;
}
void NodeRoot::SetStaffID(std::string id)
{
	m_strStaffID = id;
}
void NodeRoot::SetDepartID(std::string id)
{
	m_strDepartID = id;
}
void NodeRoot::SetProvinceCode(std::string code)
{
	m_strProvinceCode = code;
}
void NodeRoot::SetRegionCode(std::string code)
{
	m_strRegionCode = code;
}
void NodeRoot::SetCityCode(std::string code)
{
	m_strCityCode = code;
}
void NodeRoot::SetRouteProvinceCode(std::string code)
{
	m_strRouteProvinceCode = code;
}
void NodeRoot::SetRouteRegionCode(std::string code)
{
	m_strRouteRegionCode = code;
}
void NodeRoot::SetRouteCityCode(std::string code)
{
	m_strRouteCityCode = code;
}
void NodeRoot::SetInNetMode(std::string mode)
{
	m_strInNetMode = mode;
}


std::string NodeRoot::GetOperCode()
{
	return m_strOperCode;
}
std::string NodeRoot::GetStaffID()
{
	return m_strStaffID;
}
std::string NodeRoot::GetDepartID()
{
	return m_strDepartID;
}
std::string NodeRoot::GetProvinceCode()
{
	return m_strProvinceCode;
}
std::string NodeRoot::GetRegionCode()
{
	return m_strRegionCode;
}
std::string NodeRoot::GetCityCode()
{
	return m_strCityCode;
}
std::string NodeRoot::GetRouteProvinceCode()
{
	return m_strRouteProvinceCode;
}
std::string NodeRoot::GetRouteRegionCode()
{
	return m_strRouteRegionCode;
}
std::string NodeRoot::GetRouteCityCode()
{
	return m_strRouteCityCode;
}
std::string NodeRoot::GetInNetMode()
{
	return m_strInNetMode;
}

cJSON* NodeRoot::JsonCreateRoot(NodeRoot &nr)
{
	cJSON *root = NULL;
	root=cJSON_CreateObject();
	if(NULL == root)
		return NULL;

	cJSON_AddStringToObject(root, OPER_CODE, 				nr.GetOperCode().c_str());
	cJSON_AddStringToObject(root, STAFF_ID, 				nr.GetStaffID().c_str());
	cJSON_AddStringToObject(root, DEPART_ID, 				nr.GetDepartID().c_str());
	cJSON_AddStringToObject(root, PROVINCE_CODE, 			nr.GetProvinceCode().c_str());
	cJSON_AddStringToObject(root, REGION_CODE, 				nr.GetRegionCode().c_str());
	cJSON_AddStringToObject(root, CITY_CODE, 				nr.GetCityCode().c_str());
	cJSON_AddStringToObject(root, ROUTE_PROVINCE_CODE, 		nr.GetRouteProvinceCode().c_str());
	cJSON_AddStringToObject(root, ROUTE_REGION_CODE, 		nr.GetRouteRegionCode().c_str());
	cJSON_AddStringToObject(root, ROUTE_CITY_CODE, 			nr.GetRouteCityCode().c_str());
	cJSON_AddStringToObject(root, IN_NET_CODE, 				nr.GetInNetMode().c_str());

	return root;
}

}

