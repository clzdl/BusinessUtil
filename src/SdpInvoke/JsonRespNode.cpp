#include <SdpInvoke/JsonRespNode.h>
#include "MacroDefine.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "CharsetUtil.h"

namespace BusinessUtil
{

////
RespNodeBase::RespNodeBase()
{

}

RespNodeBase::~RespNodeBase()
{

}

//////
RespNodeRoot::RespNodeRoot()
{
}

RespNodeRoot::~RespNodeRoot()
{
	
}

RespNodeRoot::RespNodeRoot(const RespNodeRoot &rnr)
:m_strRespCode(rnr.m_strRespCode),
 m_strRespDesc(rnr.m_strRespDesc)
{
}
RespNodeRoot& RespNodeRoot::operator = (const RespNodeRoot &rnr)
{
	if(this == &rnr)
		return *this;

	m_strRespCode = rnr.m_strRespCode;
	m_strRespDesc = rnr.m_strRespDesc;

	return *this;
}

void RespNodeRoot::SetRespCode(std::string code)
{
	m_strRespCode = code;
}
void RespNodeRoot::SetRespDesc(std::string desc)
{
	m_strRespDesc = desc;
}

std::string RespNodeRoot::GetRespCode()
{
	return m_strRespCode;
}
std::string RespNodeRoot::GetRespUtf8Desc()
{
	return m_strRespDesc;
}

std::string RespNodeRoot::GetRespGb18030Desc()
{
	std::string strGbstring;
	if(-1 == CommonUtils::CharsetUtil::Uft8ToGb18030(m_strRespDesc , strGbstring) )
	{
		return "";
	}
	return strGbstring;
}


int RespNodeRoot::JsonParseRespRootNode(std::string strResp , RespNodeRoot &rnr)
{
	cJSON *jRoot=NULL , *jRespCode=NULL,*jRespDesc=NULL;
	char *out=NULL;


	jRoot=cJSON_Parse(strResp.c_str());
	if (!jRoot)
	{
		fprintf(stderr,"cJSON_Parse error, %s\n",cJSON_GetErrorPtr());
		return FAIL;
	}

	jRespCode = cJSON_GetObjectItem(jRoot ,RESP_CODE);
	if(NULL == jRespCode)
	{
		fprintf(stderr,"cJSON_GetObjectItem error, %s\n",cJSON_GetErrorPtr());
		return FAIL;
	}
	out = cJSON_Print(jRespCode);

	rnr.SetRespCode(out);
	free(out);
	out = NULL;


	jRespDesc = cJSON_GetObjectItem(jRoot ,RESP_DESC);
	if(NULL == jRespDesc)
	{
		fprintf(stderr,"cJSON_GetObjectItem error, %s\n",cJSON_GetErrorPtr());
		return FAIL;
	}
	out = cJSON_Print(jRespDesc);

	rnr.SetRespDesc(out);
	free(out);
	out = NULL;

	cJSON_Delete(jRoot);
	return 0;
}

//////////
RespNodeQryOweFeeNode::RespNodeQryOweFeeNode()
{

}

RespNodeQryOweFeeNode::~RespNodeQryOweFeeNode()
{

}

RespNodeQryOweFeeNode::RespNodeQryOweFeeNode(const RespNodeQryOweFeeNode &resp)
{
	m_respRoot = resp.m_respRoot;
	m_vecFee.insert(m_vecFee.begin(),resp.m_vecFee.begin(), resp.m_vecFee.end());
}

RespNodeQryOweFeeNode& RespNodeQryOweFeeNode::operator = (const RespNodeQryOweFeeNode &resp)
{
	if(this == &resp)
		return *this;

	m_respRoot = resp.m_respRoot;
	m_vecFee.clear();
	m_vecFee.insert(m_vecFee.begin(),resp.m_vecFee.begin(), resp.m_vecFee.end());

	return *this;
}

void RespNodeQryOweFeeNode::SetRespNodeRoot(RespNodeRoot &rnr)
{
	m_respRoot = rnr;
}

void RespNodeQryOweFeeNode::PushBack(_OWE_FEE_INFO &ofi)
{
	m_vecFee.push_back(ofi);
}


/*
 * 实时结余：
 *      后付费:  不包含当月账单费用及上月未出帐费用
 *      准预用户：       包含单月账单及上月未出帐费用
 */
long RespNodeQryOweFeeNode::GetLeaveRealFee(long &lCurRealFee , long &lLMNoPayBillFee)
{

	long lFee = 0;
	for(std::vector<_OWE_FEE_INFO>::iterator it = m_vecFee.begin() ; it != m_vecFee.end(); ++it)
	{
	    if(it->lTotalOweFee >0 )//// 此字段为：账本金额-历史欠费-上月未出账单金额-本月实时金额;  [使用于所有用户]
	    {
	        if(it->strPrepayTag[0] == '0')  ///后付费20150601
	            lFee -= (it->lTotalOweFee - it->lLMBillFee - it->lRealFee);
	        else
	            lFee -= it->lTotalOweFee;
	    }
	    else  ///账户余额：后付费不减当月及上月未出帐话费；准予均减
	        lFee += it->lLeaveRealFee;

	    ///当月实时结余
	    lCurRealFee += it->lRealFee;

	    ////未出帐金额
	    if(it->strLMPayTag[0] == '0')
	        lLMNoPayBillFee += it->lLMBillFee;

	}
	return lFee;
}

std::string RespNodeQryOweFeeNode::GetRespCode()
{
    return m_respRoot.GetRespCode();
}
std::string RespNodeQryOweFeeNode::GetRespUtf8Desc()
{
    return m_respRoot.GetRespUtf8Desc();
}


int RespNodeQryOweFeeNode::JsonParseRespQryOweFeeNode(std::string strResp , RespNodeQryOweFeeNode &respQOF)
{
	cJSON *jRoot=NULL, *jRespCode=NULL,*jRespDesc=NULL;
	cJSON *jResult=NULL , *jOweFeeInfo = NULL , *jOweItem = NULL;
	cJSON *json = NULL;
	char *out=NULL;
	RespNodeRoot rnr;
	int iRetValue = 0;

	do
	{
        jRoot=cJSON_Parse(strResp.c_str());
        if (!jRoot)
        {
            fprintf(stderr,"cJSON_Parse error, %s \n" , cJSON_GetErrorPtr());
            iRetValue = FAIL;
            break;
        }

        jRespCode = cJSON_GetObjectItem(jRoot ,RESP_CODE);
        if(NULL == jRespCode)
        {
        	fprintf(stderr,"cJSON_GetObjectItem error, %s \n" , cJSON_GetErrorPtr());
        	iRetValue = FAIL;
            break;
        }
        out = cJSON_Print(jRespCode);
        rnr.SetRespCode(out);
        free(out);
        out = NULL;


        jRespDesc = cJSON_GetObjectItem(jRoot ,RESP_DESC);
        if(NULL == jRespDesc)
        {
        	fprintf(stderr,"cJSON_GetObjectItem error, %s \n" , cJSON_GetErrorPtr());
        	iRetValue = FAIL;
            break;
        }
        out = cJSON_Print(jRespDesc);

        rnr.SetRespDesc(out);
        free(out);
        out = NULL;

        respQOF.SetRespNodeRoot(rnr);

        if(rnr.GetRespCode().compare(1,4,"0000") == 0)
        {
            ///////only suscces， then parse
            jResult = cJSON_GetObjectItem(jRoot ,RESULT);
            if(NULL == jRespCode)
            {
            	fprintf(stderr,"cJSON_GetObjectItem error, %s \n" , cJSON_GetErrorPtr());
            	iRetValue = FAIL;
                break;
            }

            jOweFeeInfo = cJSON_GetObjectItem(jResult , OWE_FEE_INFO);

            int iCnt = cJSON_GetArraySize(jOweFeeInfo);

            _OWE_FEE_INFO owi;

            for(int i = 0 ; i < iCnt ; ++i)
            {
                memset(&owi , 0 , sizeof(_OWE_FEE_INFO));
                ////获取数组中第一个元素
                jOweItem = NULL;
                jOweItem = cJSON_GetArrayItem(jOweFeeInfo ,i);
                if( NULL == jOweItem)
                {
                	fprintf(stderr,"cJSON_GetArrayItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;
                }

                ////用户付费标识
                json = NULL;
                json = cJSON_GetObjectItem(jOweItem ,PREPAY_TAG);
                if( NULL == json )
                {
                	fprintf(stderr,"cJSON_GetObjectItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;

                }

                out = cJSON_Print(json);
                out[strlen(out)-1] = '\0';
                strncpy(owi.strPrepayTag , out+1 , 1);
                free(out);


                ////上月账单出帐标识
                json = NULL;
                json = cJSON_GetObjectItem(jOweItem ,LAST_BILL_PAY_TAG);
                if( NULL == json )
                {
                	fprintf(stderr,"cJSON_GetObjectItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;
                }

                out = cJSON_Print(json);
                out[strlen(out)-1] = '\0';
                strncpy(owi.strLMPayTag , out+1 , sizeof(owi.strLMPayTag)-1);
                free(out);

                ////上月未出帐账单费用
                json = NULL;
                json = cJSON_GetObjectItem(jOweItem ,LAST_MONTH_BILL_FEE);
                if( NULL == json )
                {
                	fprintf(stderr,"cJSON_GetObjectItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;
                }

                out = cJSON_Print(json);
                out[strlen(out)-1] = '\0';
                owi.lLMBillFee= atol(out+1);
                free(out);


                json = NULL;
                json = cJSON_GetObjectItem(jOweItem ,ACCT_ID);
                if( NULL == json )
                {
                	fprintf(stderr,"cJSON_GetObjectItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;
                }

                out = cJSON_Print(json);
                out[strlen(out)-1] = '\0';
                owi.lAcctID= atol(out+1);
                free(out);

                json = NULL;
                json = cJSON_GetObjectItem(jOweItem ,REAL_FEE);
                if( NULL == json )
                {
                	fprintf(stderr,"cJSON_GetObjectItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;
                }

                out = cJSON_Print(json);
                out[strlen(out)-1] = '\0';
                owi.lRealFee= atol(out+1);
                free(out);

                json = NULL;
                json = cJSON_GetObjectItem(jOweItem ,OWE_FEE);
                if( NULL == json )
                {
                	fprintf(stderr,"cJSON_GetObjectItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;
                }

                out = cJSON_Print(json);
                out[strlen(out)-1] = '\0';
                owi.lOweFee= atol(out+1);
                free(out);

                json = NULL;
                json = cJSON_GetObjectItem(jOweItem ,LEAVE_REAL_FEE);
                if( NULL == json )
                {
                	fprintf(stderr,"cJSON_GetObjectItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;
                }

                out = cJSON_Print(json);

                out[strlen(out)-1] = '\0';
                owi.lLeaveRealFee = atol(out+1);
                free(out);

                json = NULL;
                json = cJSON_GetObjectItem(jOweItem ,TOTAL_OWE_FEE);
                if( NULL == json )
                {
                	fprintf(stderr,"cJSON_GetObjectItem return null \n");
                	iRetValue = FAIL;
                    goto LOOP_END;
                }

                out = cJSON_Print(json);
                out[strlen(out)-1] = '\0';
                owi.lTotalOweFee = atol(out+1);
                free(out);

                respQOF.PushBack(owi);

            }
        }

	}while(false);


LOOP_END:

	if(jRoot)
	    cJSON_Delete(jRoot);

	return iRetValue;
}


////
RespNodePayFeeNode::RespNodePayFeeNode()
{

}
RespNodePayFeeNode::~RespNodePayFeeNode()
{

}
RespNodePayFeeNode::RespNodePayFeeNode(const RespNodePayFeeNode &resp)
{
	m_strChargeID = resp.m_strChargeID;
}
RespNodePayFeeNode& RespNodePayFeeNode::operator = (const RespNodePayFeeNode &resp)
{
	if(this == &resp)
		return *this;

	m_strChargeID = resp.m_strChargeID;

	return *this;
}

void RespNodePayFeeNode::SetChargeID(std::string id)
{
	m_strChargeID = id;
}
std::string RespNodePayFeeNode::GetChargeID()
{
	return m_strChargeID;
}


int RespNodePayFeeNode::JsonParseRespPayFeeNode(std::string strResp, RespNodePayFeeNode &respPF)
{
	cJSON *jRoot=NULL;
	cJSON *jResult=NULL ;
	cJSON *json = NULL;
	char *out=NULL;


	jRoot=cJSON_Parse(strResp.c_str());
	if (!jRoot)
	{
		fprintf(stderr,"cJSON_Parse error , %s\n" , cJSON_GetErrorPtr());
		return FAIL;
	}

	json = cJSON_GetObjectItem(jRoot ,RESP_CODE);
	if(NULL == json)
	{
		fprintf(stderr,"cJSON_GetObjectItem error , %s\n" , cJSON_GetErrorPtr());
		return FAIL;
	}
	out = cJSON_Print(json);
	respPF.SetRespCode(out);
	free(out);
	out = NULL;


	json = cJSON_GetObjectItem(jRoot ,RESP_DESC);
	if(NULL == json)
	{
		fprintf(stderr,"cJSON_GetObjectItem error , %s\n" , cJSON_GetErrorPtr());
		return FAIL;
	}
	out = cJSON_Print(json);

	respPF.SetRespDesc(out);
	free(out);
	out = NULL;

	if( respPF.GetRespCode().compare(1,4,"0000") == 0)
	{
		///////
		jResult = cJSON_GetObjectItem(jRoot ,RESULT);
		if(NULL == jResult)
		{
			fprintf(stderr,"cJSON_GetObjectItem error , %s\n" , cJSON_GetErrorPtr());
			return FAIL;
		}

		json = cJSON_GetObjectItem(jResult , CHARGE_ID);
		if(NULL == json)
		{
			fprintf(stderr,"cJSON_GetObjectItem error , %s\n" , cJSON_GetErrorPtr());
			return FAIL;
		}
		out = cJSON_Print(json);

		respPF.SetChargeID(out);
		free(out);
		out = NULL;

	}
	return 0;
}

//////////////////
RespNodeOnWaySheeNode::RespNodeOnWaySheeNode()
{

}
RespNodeOnWaySheeNode::~RespNodeOnWaySheeNode()
{

}
RespNodeOnWaySheeNode::RespNodeOnWaySheeNode(const RespNodeOnWaySheeNode &resp)
{

}
RespNodeOnWaySheeNode& RespNodeOnWaySheeNode::operator = (const RespNodeOnWaySheeNode &resp)
{

}

void RespNodeOnWaySheeNode::PushOnWaySheet(_ON_WAY_SHEET &sheet)
{
    m_vecOnWaySheet.push_back(sheet);
}
const std::vector<_ON_WAY_SHEET> &RespNodeOnWaySheeNode::GetOnWaySheet()
{
    return m_vecOnWaySheet;
}


int RespNodeOnWaySheeNode::JsonParseOnWaySheetNode(std::string strResp, RespNodeOnWaySheeNode &respSheet)
{
    cJSON *jRoot=NULL;
    cJSON *jResult=NULL ;
    cJSON *jTrade = NULL;
    cJSON *jItem = NULL;
    cJSON *json = NULL;
    char *out=NULL;


    jRoot=cJSON_Parse(strResp.c_str());
    if (!jRoot)
    {
        fprintf(stderr, "cJSON_Parse return null. %s \n" , cJSON_GetErrorPtr());
        return FAIL;
    }

    json = cJSON_GetObjectItem(jRoot ,RESP_CODE);
    if(NULL == json)
    {
        fprintf(stderr, "cJSON_GetObjectItem return null. %s \n" , cJSON_GetErrorPtr());
        return FAIL;
    }

    out = cJSON_Print(json);
    respSheet.SetRespCode(out);
    free(out);
    out = NULL;


    json = cJSON_GetObjectItem(jRoot ,RESP_DESC);
    if(NULL == json)
    {
    	fprintf(stderr, "cJSON_GetObjectItem return null. %s \n" , cJSON_GetErrorPtr());
        return FAIL;
    }

    out = cJSON_Print(json);

    respSheet.SetRespDesc(out);
    free(out);
    out = NULL;


    if( respSheet.GetRespCode().compare(1,4,"0000") == 0)
    {
        ///////
        jResult = cJSON_GetObjectItem(jRoot ,RESULT);
        if(NULL == jResult)
        {
        	fprintf(stderr, "cJSON_GetObjectItem return null. %s \n" , cJSON_GetErrorPtr());
            return FAIL;
        }

        jTrade = cJSON_GetObjectItem(jResult , TRADE);

        if(NULL == jTrade)
        {
        	fprintf(stderr, "cJSON_GetObjectItem return null. %s \n" , cJSON_GetErrorPtr());
            return FAIL;
        }
        int iCnt = cJSON_GetArraySize(jTrade);

        for(int i = 0 ; i < iCnt ; ++i)
        {
            _ON_WAY_SHEET owSheet;
            memset(&owSheet , 0 , sizeof(owSheet));
            jItem = NULL;
            jItem = cJSON_GetArrayItem(jTrade ,i);
            if( NULL == jItem)
            {
            	fprintf(stderr, "cJSON_GetArrayItem return null. %s \n" , cJSON_GetErrorPtr());
            	return FAIL;
            }

            ////在途工单类型
            json = NULL;
            json = cJSON_GetObjectItem(jItem ,TRADE_TYPE_CODE);
            if( NULL == json )
            {
            	fprintf(stderr, "cJSON_GetObjectItem return null. %s \n" , cJSON_GetErrorPtr());
            	return FAIL;
            }

            out = cJSON_Print(json);
            out[strlen(out)-1] = '\0';
            strncpy(owSheet.strTradeTypeCode , out+1 , sizeof(owSheet.strTradeTypeCode)-1);
            free(out);

            ////在途工单类型的交易id
            json = NULL;
            json = cJSON_GetObjectItem(jItem ,TRADE_ID);
            if( NULL == json )
            {
            	fprintf(stderr, "cJSON_GetObjectItem return null. %s \n" , cJSON_GetErrorPtr());
            	return FAIL;
            }

            out = cJSON_Print(json);
            out[strlen(out)-1] = '\0';
            strncpy(owSheet.strTradeID , out+1 , sizeof(owSheet.strTradeID)-1);
            free(out);

            respSheet.PushOnWaySheet(owSheet);
        }

    }
    ///20150615
    cJSON_Delete(jRoot);

    return 0;
}

}


