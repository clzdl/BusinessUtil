/*
 * BusiExceptions.h
 *
 *  Created on: 2017年9月30日
 *      Author: cplusplus
 */

#ifndef INCLUDE_BUSIEXCEPTIONS_H_
#define INCLUDE_BUSIEXCEPTIONS_H_

#include "Exception.h"

namespace BusinessUtil{

using namespace CommonUtils;
/**
 * 定义系统级原始的异常
 */
DECLARE_EXCEPTION(PrimalException, CommonUtils::Exception);



}



#endif /* INCLUDE_BUSIEXCEPTIONS_H_ */
