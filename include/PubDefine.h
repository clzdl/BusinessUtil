/*
 * soAppDefine.h
 *
 *  Created on: 2015年11月27日
 *      Author: clzdl
 */

#ifndef SOAPPDEFINE_H_
#define SOAPPDEFINE_H_


////c
#include <stdio.h>
#include <stdlib.h> /* for atoi(3) */
#include <unistd.h> /* for getopt(3) */
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <errno.h>
#include <regex.h>  ///正则
#include <sys/socket.h>
#include <dirent.h>
#include <pwd.h>
#include <iconv.h>  ////字符编码转换
#include <assert.h>
////// c++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>    // std::copy
#include <math.h>
#include <memory>


///poco
#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Util/LoggingConfigurator.h"
#include "Poco/AutoPtr.h"
#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/Timespan.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Foundation.h"
#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadTarget.h"
#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/AbstractHTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/FTPClientSession.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Exception.h"
///////////
#include "Poco/DirectoryIterator.h"
#include "Poco/Path.h"
#include "Poco/SharedLibrary.h"
#include "Poco/HashMap.h"


enum class RunStatus{
	stop = 0,   //停止运行状态
	run = 1,	//正常运行
	reload = 2	//重新加载参数
};


#endif /* SOAPPDEFINE_H_ */
