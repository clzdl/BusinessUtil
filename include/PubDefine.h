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







////////
using std::vector;
using std::list;
using std::stack;
using std::map;
using std::cerr;
using std::cout;
using std::set;
using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

using std::endl;

///////
using Poco::DateTime;
using Poco::NumberFormatter;
using Poco::LocalDateTime;
using Poco::DateTimeFormat;
using Poco::Timespan;




using Poco::Util::IniFileConfiguration;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::PropertyFileConfiguration;
using Poco::Util::LoggingConfigurator;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;

using Poco::Logger;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::FileChannel;
using Poco::Message;

using Poco::Thread;
using Poco::ThreadPool;
using Poco::Runnable;
using Poco::ThreadTarget;
using Poco::FastMutex;
using Poco::ScopedLock;
using Poco::Mutex;
using Poco::Exception;
using Poco::FileNotFoundException;
using Poco::NotFoundException;
using Poco::NoThreadAvailableException;
using Poco::Event;

///////////
//////
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::NetException;
using Poco::Net::InvalidSocketException;

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPMessage;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::AbstractHTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Net::ServerSocket;
using Poco::StreamCopier;

using Poco::Net::FTPClientSession;
using Poco::Net::FTPException;
using Poco::Net::NetException;
using Poco::TimeoutException;
using Poco::Net::StreamSocket;
using Poco::Net::SocketAddress;

///////////////
using Poco::DirectoryIterator;
using Poco::Path;
using Poco::SharedLibrary;

using Poco::HashMap;


#endif /* SOAPPDEFINE_H_ */
