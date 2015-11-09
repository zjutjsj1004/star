#ifndef __STAR_COMMON_H__
#define __STAR_COMMON_H__

#define STAR_FORTUNE_COUNT (12) //星座个数
#define STAR_COMMON_FINENAME_MAX_LEN (64) //普通字符串长度
#define STAT_FORTUNE_ROW (4) //行
#define STAT_FORTUNE_COLUMN (3) //列

#define STAR_FORTUNE_BOTTON_SIZE (4) //星座底部按钮格式
#define STAR_FORTUNE_BOTTON_YUNSHI (0) //运势
#define STAR_FORTUNE_BOTTON_SHARE (1) // 分享
#define STAR_FORTUNE_BOTTON_DISCOVERY (2) // 发现
#define STAR_FORTUNE_BOTTON_SET (3) //设置

#define STAR_FORTUNE_FORTUNEDAY_SIZE (5) //星座内容日期数

#define STAR_LANGUAGE_JSON_NAME "starLanguageDesc.json"
#define STAR_JSON_KEY_FORTUNESET_STAR 1
#define STAR_JSON_KEY_FORTUNESET_AUTHOR 2
#define STAR_JSON_KEY_SHARE_STAR 3
#define STAR_JSON_KEY_ABOUT_STAR 4
#define STAR_JSON_KEY_ABOUT_AUTHOR 5


const char gszFortuneName[STAR_FORTUNE_COUNT][STAR_COMMON_FINENAME_MAX_LEN] =
{
	"fortune_aries_img.png",        /* 白羊座:3.21~4.19 */
	"fortune_taurus_img.png",       /* 金牛座:4.20~5.20 */
	"fortune_gemini_omg.png",       /* 双子座:5.21~6.21 */
	"fortune_cancer_img.png",       /* 巨蟹座:6.22~7.22 */
	"fortune_leo_img.png",          /* 狮子座:7.23~8.22 */
	"fortune_virgo_img.png",        /* 处女座:8.23~9.22 */
	"fortune_libra_img.png",        /* 天秤座:9.23~10.23 */
	"fortune_scorpio_img.png",      /* 天蝎座:10:24~11.22 */
	"fortune_sagittarius_img.png",  /* 射手座:11.23~12.21 */
	"fortune_capricornus_img.png",  /* 摩羯座:12.22~1.19 */
	"fortune_aquarius_img.png",     /* 水瓶座:1.20~2.18 */
	"fortune_pisces_img.png"        /* 双鱼座:2.19~3.20 */
};

#define URLFORMAT "http://web.juhe.cn:8080/constellation/getAll?consName=%s&type=%s&key=%s" //格式化URL
#define APPKEY "4995409c793df8ca27fc1a5561d615be" //APPKEY  填写你自己的APPKEY就可以使用
#define BAIYANGZUO   "%E7%99%BD%E7%BE%8A%E5%BA%A7" /* 白羊座:3.21~4.19 */
#define JINNIUZUO    "%E9%87%91%E7%89%9B%E5%BA%A7" /* 金牛座:4.20~5.20 */
#define SHUANFZIZUO  "%E5%8F%8C%E5%AD%90%E5%BA%A7" /* 双子座:5.21~6.21 */
#define JVXIUZUO     "%E5%B7%A8%E8%9F%B9%E5%BA%A7" /* 巨蟹座:6.22~7.22 */
#define SHIZIZUO     "%E7%8B%AE%E5%AD%90%E5%BA%A7" /* 狮子座:7.23~8.22 */
#define CHUNVZUO     "%E5%A4%84%E5%A5%B3%E5%BA%A7" /* 处女座:8.23~9.22 */
#define TIANCHENGZUO "%E5%A4%A9%E7%A7%A4%E5%BA%A7" /* 天秤座:9.23~10.23 */
#define TIANXIEZUO   "%E5%A4%A9%E8%9D%8E%E5%BA%A7" /* 天蝎座:10:24~11.22 */
#define SHEZHOUZUO   "%E5%B0%84%E6%89%8B%E5%BA%A7" /* 射手座:11.23~12.21 */
#define MOJIEZUO     "%E6%91%A9%E7%BE%AF%E5%BA%A7" /* 摩羯座:12.22~1.19 */
#define SHUIPINGZUO  "%E6%B0%B4%E7%93%B6%E5%BA%A7" /* 水瓶座:1.20~2.18 */
#define SHUANGYUZUO  "%E5%8F%8C%E9%B1%BC%E5%BA%A7" /* 双鱼座:2.19~3.20 */

#if 0
class CStartCommon
{
public:
	CStartCommon();
	~CStartCommon();
	static int getFormatLocalTime()
	{
		time_t tt;
		time(&tt);
		struct tm * now;
		//获得本地时间
		now = localtime(&tt);
		//CCLOG("%d/%d/%d %d:%d:%d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
		char szTime[STAR_COMMON_FINENAME_MAX_LEN] = { 0 };
		sprintf(szTime, "%d%d%d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
		return atoi(szTime);
	}

private:

};

CStartCommon::CStartCommon()
{
}

CStartCommon::~CStartCommon()
{
}
#endif

#define ERROR_COMMON_SUCCESS 0
#define ERROR_COMMMON_FAILED 1

#endif // __STAR_COMMON_H__
