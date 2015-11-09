#ifndef __STAR_COMMON_H__
#define __STAR_COMMON_H__

#define STAR_FORTUNE_COUNT (12) //��������
#define STAR_COMMON_FINENAME_MAX_LEN (64) //��ͨ�ַ�������
#define STAT_FORTUNE_ROW (4) //��
#define STAT_FORTUNE_COLUMN (3) //��

#define STAR_FORTUNE_BOTTON_SIZE (4) //�����ײ���ť��ʽ
#define STAR_FORTUNE_BOTTON_YUNSHI (0) //����
#define STAR_FORTUNE_BOTTON_SHARE (1) // ����
#define STAR_FORTUNE_BOTTON_DISCOVERY (2) // ����
#define STAR_FORTUNE_BOTTON_SET (3) //����

#define STAR_FORTUNE_FORTUNEDAY_SIZE (5) //��������������

#define STAR_LANGUAGE_JSON_NAME "starLanguageDesc.json"
#define STAR_JSON_KEY_FORTUNESET_STAR 1
#define STAR_JSON_KEY_FORTUNESET_AUTHOR 2
#define STAR_JSON_KEY_SHARE_STAR 3
#define STAR_JSON_KEY_ABOUT_STAR 4
#define STAR_JSON_KEY_ABOUT_AUTHOR 5


const char gszFortuneName[STAR_FORTUNE_COUNT][STAR_COMMON_FINENAME_MAX_LEN] =
{
	"fortune_aries_img.png",        /* ������:3.21~4.19 */
	"fortune_taurus_img.png",       /* ��ţ��:4.20~5.20 */
	"fortune_gemini_omg.png",       /* ˫����:5.21~6.21 */
	"fortune_cancer_img.png",       /* ��з��:6.22~7.22 */
	"fortune_leo_img.png",          /* ʨ����:7.23~8.22 */
	"fortune_virgo_img.png",        /* ��Ů��:8.23~9.22 */
	"fortune_libra_img.png",        /* �����:9.23~10.23 */
	"fortune_scorpio_img.png",      /* ��Ы��:10:24~11.22 */
	"fortune_sagittarius_img.png",  /* ������:11.23~12.21 */
	"fortune_capricornus_img.png",  /* Ħ����:12.22~1.19 */
	"fortune_aquarius_img.png",     /* ˮƿ��:1.20~2.18 */
	"fortune_pisces_img.png"        /* ˫����:2.19~3.20 */
};

#define URLFORMAT "http://web.juhe.cn:8080/constellation/getAll?consName=%s&type=%s&key=%s" //��ʽ��URL
#define APPKEY "4995409c793df8ca27fc1a5561d615be" //APPKEY  ��д���Լ���APPKEY�Ϳ���ʹ��
#define BAIYANGZUO   "%E7%99%BD%E7%BE%8A%E5%BA%A7" /* ������:3.21~4.19 */
#define JINNIUZUO    "%E9%87%91%E7%89%9B%E5%BA%A7" /* ��ţ��:4.20~5.20 */
#define SHUANFZIZUO  "%E5%8F%8C%E5%AD%90%E5%BA%A7" /* ˫����:5.21~6.21 */
#define JVXIUZUO     "%E5%B7%A8%E8%9F%B9%E5%BA%A7" /* ��з��:6.22~7.22 */
#define SHIZIZUO     "%E7%8B%AE%E5%AD%90%E5%BA%A7" /* ʨ����:7.23~8.22 */
#define CHUNVZUO     "%E5%A4%84%E5%A5%B3%E5%BA%A7" /* ��Ů��:8.23~9.22 */
#define TIANCHENGZUO "%E5%A4%A9%E7%A7%A4%E5%BA%A7" /* �����:9.23~10.23 */
#define TIANXIEZUO   "%E5%A4%A9%E8%9D%8E%E5%BA%A7" /* ��Ы��:10:24~11.22 */
#define SHEZHOUZUO   "%E5%B0%84%E6%89%8B%E5%BA%A7" /* ������:11.23~12.21 */
#define MOJIEZUO     "%E6%91%A9%E7%BE%AF%E5%BA%A7" /* Ħ����:12.22~1.19 */
#define SHUIPINGZUO  "%E6%B0%B4%E7%93%B6%E5%BA%A7" /* ˮƿ��:1.20~2.18 */
#define SHUANGYUZUO  "%E5%8F%8C%E9%B1%BC%E5%BA%A7" /* ˫����:2.19~3.20 */

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
		//��ñ���ʱ��
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
