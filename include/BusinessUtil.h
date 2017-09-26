#ifndef _PUBLIC_FUN_LIB_H_
#define _PUBLIC_FUN_LIB_H_

#include <PubDefine.h>
#include "openssl/md5.h"

#include "PatternMatcher.h"
#include "StringUtil.h"
/// macro definition file
#include "MacroDefine.h"

namespace BusinessUtil
{
class BusiUtil
{
public:
	/*@action:用于获取数据的用户的解密后的密码
	 *@param：
	 *		encryptFile--入参，密码加密文件
	 *		sUser--入参，用户名
	 *		sSid--入参，tns名
	 *@return：解密后的密码
	 */
	string GetDBPass(const string &encryptFile,const string& sUser, const string& sSid);

	/*@action:用于加密数据库的密码
	 *@param：
	 *		sPass--入参，密码
	 *@return：加密后字符串
	 */
	const string Encrypt(const string& sPass);

	/*@action:用于解密数据库的密码
	 *@param：
	 *		sCipher--入参，加密的密码
	 *@return：解密后字符串
	 */
	const string Decrypt(const string& sCipher);


	/*@action :判断某账期是否逾期  20150805
	 *@param
	 *      cycle_id--入参，账期
	 *      strChargePeriod--入参，缴费周期  start#end#interval
	 *Return   :true 逾期 false  未逾期
	 */
	bool isOverdue( int cycle_id , string strChargePeriod);

	/*@action :用于获取逾期日期  20150805
	 *@param:
	 *      cycle_id--入参，账期
	 *      strChargePeriod--入参，缴费周期  start#end#interval
	 *Return  : >0 逾期日期， -1-fail
	 */
	int CalcOverdueDate(int cycle_id , string strChargePeriod);


	/*@action: 用于计算日期间隔，iFlag= 1：日间隔  2：月间隔，
	 *@param:
	 *      strBegDate--入参，  开始日期
	 *      strEndDate--入参， 结束日期
	 *      iFlag--入参，日期类型
	 *      iSpan--出参，  日期间隔数
	 *@return: 0-success,-1-fail
	 */
	int DateSpan(string strBegDate , string strEndDate , int iFlag , int &iSpan);

};
}
#endif

