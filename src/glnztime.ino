#include "Config.h"


// 【北京时间=GMT时间+8小时】

// 日期数据结构定义：

// typedef struct
// {
// 	uint16_t year;
// 	uint8_t month;
// 	uint8_t day;
// 	uint8_t hour;
// 	uint8_t minute;
// 	uint8_t second;
// }time_tg;

//转换实现：

void UTCToBeijing(Ds1302::DateTime* time)
{
	uint8_t days = 0;
	if (time->month == 1 || time->month == 3 || time->month == 5 || time->month == 7 || time->month == 8 || time->month == 10 || time->month == 12)
	{
		days = 31;
	}
	else if (time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11)
	{
		days = 30;
	}
	else if (time->month == 2)
	{
		if ((time->year % 400 == 0) || ((time->year % 4 == 0) && (time->year % 100 != 0))) /* 判断平年还是闰年 */
		{
			days = 29;
		}
		else
		{
			days = 28;
		}
	}
	time->hour += 8;                 /* 北京时间比格林威治时间快8小时 */
	if (time->hour >= 24)            /* 跨天 */
	{
		time->hour -= 24;
		time->day++;
		if (time->day > days)        /* 跨月 */
		{
			time->day = 1;
			time->month++;
			if (time->month > 12)    /* 跨年 */
			{
				time->year++;
			}
		}
	}
}

//【根据日期计算周几】：

/// 返回值：1-7，对应周一到周天
uint8_t GetWeekDayNum(uint32_t year, uint8_t month, uint8_t day)
{
  uint32_t weekday = 0U;

  if (month < 3U)
  {
	/*D = { [(23 x month)/9] + day + 4 + year + [(year-1)/4] - [(year-1)/100] + [(year-1)/400] } mod 7*/
	weekday = (((23U * month) / 9U) + day + 4U + year + ((year - 1U) / 4U) - ((year - 1U) / 100U) + ((year - 1U) / 400U)) % 7U;
  }
  else
  {
	/*D = { [(23 x month)/9] + day + 4 + year + [year/4] - [year/100] + [year/400] - 2 } mod 7*/
	weekday = (((23U * month) / 9U) + day + 4U + year + (year / 4U) - (year / 100U) + (year / 400U) - 2U) % 7U;
  }

  if(weekday == 0)
  {
	  weekday = 7;
  }

  return (uint8_t)weekday;
}

