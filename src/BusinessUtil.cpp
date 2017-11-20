
#include <BusinessUtil.h>
#include <HashUtil.h>
#include "Poco/LocalDateTime.h"
#include "BusiExceptions.h"
using Poco::LocalDateTime;


////数据库密码文件加解密密钥
static const std::string m_sKey = "`Fx0&8_j[}1";

namespace BusinessUtil
{


std::string BusiUtil::GetDBPass(const std::string &encryptFile,const std::string& sUser, const std::string& sSid)
{
    char szUser[64]={0};
    char szPass[14]={0};
    char szDBNames[128]={0};

    std::ifstream l_ifstream(encryptFile.c_str());
    if (l_ifstream.fail())
        return "";

    while (!l_ifstream.eof())
	{
		l_ifstream.getline(szUser, sizeof(szUser), ':');
		l_ifstream.getline(szPass, sizeof(szPass), ':');
		l_ifstream.getline(szDBNames, sizeof(szDBNames));

		if (!strcmp(szUser, sUser.c_str()) && !strcmp (szDBNames, sSid.c_str())) 
		{
		    l_ifstream.close();
		    return Decrypt(szPass);
		}
	}
    l_ifstream.close();
	

    return "";
}

const std::string BusiUtil::Encrypt(const std::string& sPass)
{
    std::string l_sPass(sPass);

    char l_szCipher[13];

    char l_cPassHign[12];
    char l_cPassLow[12];

    char l_ch;
    int  i;
    int  ki;

    if ((l_sPass.size() > 12) || (l_sPass.size() < 3))
        return "";

    if (l_sPass.find('~') != std::string::npos)
        return "";

    if (l_sPass.size() < 12)
	l_sPass += "~";
    
    srand(time(NULL));
    for (i = l_sPass.size(); i < 12; ++i)
        l_sPass += static_cast<char>(rand()%78 + 48);
    
    if (l_sPass.size() < 12) 
    {
    	l_sPass.append(12 - l_sPass.size(), '~');
    }

    //拆分高低位
    for (i = 0; i < 12; i++) 
    {
        if (l_sPass[i] > 126 || l_sPass[i] < 48)
            return "";    // invalid characters in passwd

	l_cPassHign[i] = (l_sPass[i] >> 4);
	l_cPassLow[i] = l_sPass[i] & 0x0f;
    }

    /**
    * 低位字节 0 <-> 11, 1 <-> 10, ...
    * 高位字节 0 <-> 6, 1 <-> 7, ...
    */
    for(i = 0; i < 6; i++) 
    {
	l_ch = l_cPassLow[i];
	l_cPassLow[i] = l_cPassLow[11 - i];
	l_cPassLow[11 - i] = l_ch;

	l_ch = l_cPassHign[i];
	l_cPassHign[i] = l_cPassHign[6+i];
	l_cPassHign[6+i] = l_ch;
    }

    /**
    *
    */
    for (i = 0, ki = 0; i < 12; i++) {
        l_cPassHign[i] = ((l_cPassHign[i] - 3 + m_sKey[ki]) % 5) + 3;

	l_cPassLow[i] = l_cPassLow[i] ^ (m_sKey[ki] & 0x0f);
	l_szCipher[i] = (l_cPassHign[i] << 4) | l_cPassLow[i];

	if (l_szCipher[i] == ':')
            l_szCipher[i] = '&';

	if (l_szCipher[i] == 127)
            l_szCipher[i] = '+';

	ki = ( ki == (m_sKey.size() - 1) )? 0 : ki+1;
    }
    l_szCipher[12] = 0;
    return std::string(l_szCipher);
}

const std::string BusiUtil::Decrypt(const std::string& sCipher)
{
	std::string l_sCipher(sCipher);

    char l_szPass[13]={"0"};

    char l_cPassHign[12];
    char l_cPassLow[12];

    char l_ch;
    int  i;
    int  ki;


    if (l_sCipher.size()!= 12)
        return "";

    for (i = 0; i < 12; ++i) {
	if (l_sCipher[i] == '&')
        l_sCipher[i]=':';

	if (l_sCipher[i] == '+')
            l_sCipher[i]=127;

	l_cPassHign[i] = ( l_sCipher[i] >> 4);
	l_cPassLow[i] = l_sCipher[i] & 0x0f;
    }

	/* swap 0 <-> 11, 1 <-> 10, ... */

    for (i = 0, ki = 0; i < 12; ++i) {

        l_cPassHign[i] = (l_cPassHign[i] - 3 + 5 - (m_sKey[ki] % 5)) % 5 + 3;

        l_cPassLow[i] = l_cPassLow[i] ^ (m_sKey[ki] & 0x0f);

        ki = (ki == (m_sKey.size() - 1)) ? 0 : ki + 1;
    }


	/* swap 0 <-> 6, 1 <-> 7, ... */

    for (i = 0; i < 6; ++i) {
	l_ch = l_cPassLow[i];
	l_cPassLow[i] = l_cPassLow[11 - i];
	l_cPassLow[11 - i] = l_ch;

	l_ch = l_cPassHign[i];
	l_cPassHign[i] = l_cPassHign[6 + i];
	l_cPassHign[6 + i] = l_ch;
    }

    for (i = 0; i < 12; ++i) {
	l_szPass[i] = (l_cPassHign[i] << 4) | l_cPassLow[i];
	if (l_szPass[i] == '~') {
            l_szPass[i] = 0;
            break;
        }
    }

    return std::string(l_szPass);
}



bool BusiUtil::isOverdue( int cycle_id , std::string strChargePeriod)
{
    int overdue_date = 0;//逾期日期

    time_t tt = 0;
    struct tm cur;
    char strDate[8+1] = {0};

    overdue_date = CalcOverdueDate(cycle_id , strChargePeriod);
    if(-1 == overdue_date)
    {
        std::cerr<<"CalcOverdueDate return fail."<<std::endl;
        return false;
    }

    tt  = time( NULL );
    localtime_r( &tt ,&cur);
    sprintf(strDate, "%4d%02d%02d", cur.tm_year + 1900, cur.tm_mon + 1, cur.tm_mday);

    //逾期日期<系统日期（YYYYMMDD），则为逾期欠费，
    if( atoi(strDate) > overdue_date )
      return true;

    return false;
}

int BusiUtil::CalcOverdueDate(int cycle_id , std::string strChargePeriod)
{
    std::vector<std::string> vecRes;
    int year = 0;
    int month = 0;
    int end_day = 0;
    int interval = 0;
    int overdue_date = 0;//逾期日期

    CommonUtils::StringUtil::split(strChargePeriod , "#" , vecRes);
    if(vecRes.size() < 3)
        return -1;

    end_day = atoi(vecRes[1].c_str());
    interval = atoi(vecRes[2].c_str());

    //计算逾期日期规则:帐期+interval+1
    year   = cycle_id/100;
    month  = cycle_id%100;
    month +=( 1 + interval );
    if( month>12 ){
      year  = year + month/12 - (month%12==0?1:0);
      month = month%12 + (month%12==0?12:0);
    }

    overdue_date = year*10000 + month*100 + end_day;

    return overdue_date;
}

int BusiUtil::DateSpan(std::string strBegDate , std::string strEndDate , int iFlag , int &iSpan)
{
    int iBegY= 0;
    int iBegM =0;
    int iBegD = 0;

    int iEndY = 0;
    int iEndM = 0;
    int iEndD = 0;

    _TRACE_MSG("src:%s,dst:%s \n" , strBegDate.c_str(),strEndDate.c_str());

    switch(iFlag)
    {
        case 1:  ///日
        {
            if(strBegDate.length() < 8 || strEndDate.length() < 8)
                return -1;

            iBegY = atoi(strBegDate.substr(0,4).c_str());  ///
            iBegM = atoi(strBegDate.substr(4,2).c_str());   ///
            iBegD = atoi(strBegDate.substr(6,2).c_str());

            iEndY = atoi(strEndDate.substr(0,4).c_str());
            iEndM = atoi(strEndDate.substr(4,2).c_str());   ///
            iEndD = atoi(strEndDate.substr(6,2).c_str());
            LocalDateTime ldtBeg(iBegY,iBegM,iBegD);
            LocalDateTime ldtEnd(iEndY,iEndM,iEndD);

            iSpan = (ldtEnd - ldtBeg).days();
            break;
        }
        case 2:  ///月间隔
        {
            if(strBegDate.length() < 6 || strEndDate.length() < 6)
                return -1;

            iBegY = atoi(strBegDate.substr(0,4).c_str());  ///
            iBegM = atoi(strBegDate.substr(4,2).c_str());   ///
            iEndY = atoi(strEndDate.substr(0,4).c_str());
            iEndM = atoi(strEndDate.substr(4,2).c_str());   ///

            _TRACE_MSG("begY=%d,begM=%d,endY=%d,endM=%d \n" , iBegY,iBegM , iEndY,iEndM);

            iSpan = (iEndY-iBegY) * 12 + (iEndM - iBegM) ;

            break;
        }
        case 3:  ///年间隔
            return -1;
            break;

    }

    return 0;
}

}

