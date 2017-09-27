#Makefile#

#模块类型(必选)：P主程序 S静态连接库 D动态链接库
U_TYPE =S

#模块名称(必填)
MODULE =soInvokeSdpInterface

#目标文件集合(必填)
U_OBJS =soInvokeBase.cpp\
        soInvokeOnwaySheet.cpp\
        soInvokePayment.cpp\
        soInvokeQryFee.cpp\
        soInvokeSendMsg.cpp\
        soInvokeSoipSendMsg.cpp\
        soInvokeTrade.cpp \
        InvokeCreditTrigger.cpp\

#链接库集合
U_LIB =

#头文件路径
U_INC =

#如果编译共享库(必填)需写明头文件名称
U_HEAD =  soInvokeOnwaySheet.h\
          soInvokePayment.h\
          soInvokeQryFee.h\
          soInvokeSendMsg.h\
          soInvokeSoipSendMsg.h\
          soInvokeTrade.h\
          soISIdefine.h\
          soInvokeBase.h \
          InvokeCreditTrigger.h\
	 
#调试
U_DEBUG = -D_DEBUG

#编译参数 C++11版本参数 -std=c++0x
U_CFLAGS = 

#链接参数
U_LFLAGS = 

#引用mk模板
include ${make_path}/mk.pub
