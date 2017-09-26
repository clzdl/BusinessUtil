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


/////running status macro
#define STATUS_STOP             0       ///停止运行状态
#define STATUS_RUN              1       ///正常运行
#define STATUS_RELOAD           2       ///重新加载参数


/////record length macro
#define MAX_RECORD_SIZE         4096

///////oracle error
#define ORA_PIPE_BREAK       3113
#define ORA_DISCONNECT       3114



///// logger macro
#ifndef LOGGER_FATAL
#define LOGGER_FATAL(logger , msg)      (logger).fatal( string("[")+ __FILE__ + "," + Number2String(__LINE__) + "]"  +msg);
#endif

#ifndef LOGGER_ERROR
#define LOGGER_ERROR(logger , msg)      (logger).error( string("[")+ __FILE__ + "," + Number2String(__LINE__) + "]" + msg);
#endif

#ifndef LOGGER_INFO
#define LOGGER_INFO(logger , msg)       (logger).information( string("[") + __FILE__ +"," + Number2String(__LINE__) + "]" + msg);
#endif

#ifndef LOGGER_DEBUG
#define LOGGER_DEBUG(logger , msg)      (logger).debug( string("[") + __FILE__  + "," + Number2String(__LINE__) + "]" + msg);
#endif
/////
/////
#ifdef _DEBUG
#define MSG_DEBUG(FMT,...)      printf("[%s,%d]"FMT ,__FILE__ ,__LINE__, ##__VA_ARGS__)
#else
#define MSG_DEBUG(FMT,...)
#endif




////define oracle exceptin
#define DUMP_OTL_EXCEPTION(logger , e)          {                   \
            LOGGER_ERROR(logger,Number2String(e.code));             \
            LOGGER_ERROR(logger,(const char*)e.msg);                \
            LOGGER_ERROR(logger,(const char*)e.stm_text);           \
            LOGGER_ERROR(logger,(const char*)e.var_info);           \
            }


//// chk != chk_code  返回 ret_code
#define NQ_CHK_RETURN(chk , chk_code , ret_code)         if(chk_code != chk) return ret_code;
#define EQ_CHK_RETURN(chk , chk_code , ret_code)         if(chk_code == chk) return ret_code;

#define NQ_CHK_EXIT(chk , chk_code , exit_code )         if(chk_code != chk)  exit(exit_code);
#define EQ_CHK_EXIT(chk , chk_code , exit_code)         if(chk_code == chk)  exit(exit_code);

#define NQ_CHK_CONTINUE(chk , chk_code )         if(chk_code != chk)  continue;
#define EQ_CHK_CONTINUE(chk , chk_code )         if(chk_code == chk)  continue;

#define NQ_CHK_BREAK(chk , chk_code , varErr , brk_code)    if(chk_code != chk){varErr=brk_code ; break; }
#define EQ_CHK_BREAK(chk , chk_code , varErr , brk_code)    if(chk_code == chk){varErr=brk_code ; break; }




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



#endif
