/*
 * MacroDefine.h
 *
 *  Created on: 2015年11月27日
 *      Author: clzdl
 */

#ifndef MACRODEFINE_H_
#define MACRODEFINE_H_

////////////////////logic macro
#define SUCCESS         0
#define FAIL            -1

#define TRUE            1
#define FALSE           0


/////record length macro
#define MAX_RECORD_SIZE         4096


/////红名单位图宏定义
#define RB_NO_BALANCE_HASTEN        0       ///第一位：1表示免催费
#define RB_NO_HALFSTOP              1       ///第二位：1表示免半停机
#define RB_NO_DOUBLESTOP            2       ///第三位：1表示免停机
#define RB_NO_CALC_CREDIT           3       ///第四位：1表示免信用度计算
#define RB_NO_SMS_REMIND            4       ///第五位：1表示短信提醒
#define RB_NO_LARGE_REMIND          5       ///第六位：免高额提醒
#define RB_NO_OWE_DESTROY           6       ///第七位：免欠费拆机
#define RB_NO_STOP_REMIND           7       ///第八位：免停机提醒
#define RB_NO_BILCDR_REMIND         8       ///第九位：免帐单短信发送
#define RB_NO_USE_REMIND            9       ///第十位：免使用量提醒

#ifdef _DEBUG
#define _TRACE_MSG(FMT, ...)      fprintf(stdout,"[%s,%d]" FMT "\n" ,__FILE__ ,__LINE__, ##__VA_ARGS__)
#else
#define _TRACE_MSG(FMT, ...)
#endif

#define DUMP_OTL_EXCEPTION(logger , e)    poco_error_f4(logger,"code:%d,msg:%s,stm_text:%s,var_info:%s",e.code,std::string((char*)e.msg),std::string((char*)e.stm_text),std::string((char*)e.var_info))

#define THROW_OTL_EXCEPTION(e) 		THROW_C_P4(BusinessUtil::BusiException,E_DB_ERROR,"code:%d,msg:%s,stm_text:%s,var_info:%s",e.code,e.msg,e.stm_text,e.var_info)

#endif
