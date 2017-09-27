#ifndef _SO_ISI_DEFINE_H
#define _SO_ISI_DEFINE_H


#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>	/* for atoi(3) */
#include <unistd.h>	/* for getopt(3) */
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

//////
#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>    // std::copy
#include <math.h>

///////
#include "cJSON.h"
#include "MacroDefine.h"


#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/Timespan.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/NumberFormatter.h"

#include "Poco/Foundation.h"

#include "Poco/Net/NetException.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/StreamCopier.h"


#include "Poco/Exception.h"



///////
using Poco::DateTime;
using Poco::NumberFormatter;
using Poco::LocalDateTime;
using Poco::DateTimeFormat;
using Poco::Timespan;

using Poco::FastMutex;
using Poco::Exception;
using Poco::NotFoundException;

///////////
//////
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::NetException;

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;






#endif

