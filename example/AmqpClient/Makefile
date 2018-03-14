#Makefile#

#模块类型(必选)：P主程序 S静态连接库 D动态链接库
U_TYPE = P

#模块名称(必填)
MODULE = AmqpClientTest

#目标文件集合(必填)
U_OBJS = main.cpp

#链接库集合
U_LIB = -lPocoFoundation -lPocoNet -lPocoUtil -lssh2 \
	-lcrypto -lamqpcpp -lBusinessUtil -lCommonUtil -lclntsh 
 

#头文件路径
U_INC =-I./. -I$(PUBLICINCLUDE)/CommonUtil -I$(PUBLICINCLUDE)/BusinessUtil

#调试
U_DEBUG = -D_DEBUG 

#编译参数 C++11版本参数 -std=c++0x
U_CFLAGS =  -std=c++0x

#链接参数
U_LFLAGS = 

#引用mk模板
include ${make_pathv2}/mk.pub
