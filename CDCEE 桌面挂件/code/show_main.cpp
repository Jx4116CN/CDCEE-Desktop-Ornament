#include "Init.h"

struct TimeDifference
{
	int days;
	int hours;
	int minutes;
	int seconds;
	int milliseconds;
}timediff;

SYSTEMTIME createSystemTime(int year, int month, int day,
	int hour = 0, int minute = 0, int second = 0, int millisecond = 0)
{
	SYSTEMTIME st = {};
	st.wYear = year;
	st.wMonth = month;
	st.wDay = day;
	st.wHour = hour;
	st.wMinute = minute;
	st.wSecond = second;
	st.wMilliseconds = millisecond;
	return st;
}

void CalculateTimeDifference(const SYSTEMTIME& st1, const SYSTEMTIME& st2)
{
	FILETIME ft1, ft2;
	SystemTimeToFileTime(&st1, &ft1);
	SystemTimeToFileTime(&st2, &ft2);

	ULARGE_INTEGER uli1, uli2;
	uli1.LowPart = ft1.dwLowDateTime;
	uli1.HighPart = ft1.dwHighDateTime;
	uli2.LowPart = ft2.dwLowDateTime;
	uli2.HighPart = ft2.dwHighDateTime;

	// 计算100纳秒间隔的总差值
	__int64 diff = uli2.QuadPart - uli1.QuadPart;

	// 转换为毫秒并分解各时间单位
	__int64 milliseconds = diff / 10000;
	__int64 seconds = milliseconds / 1000;
	__int64 minutes = seconds / 60;
	__int64 hours = minutes / 60;
	__int64 days = hours / 24;

	// 计算剩余量
	milliseconds %= 1000;
	seconds %= 60;
	minutes %= 60;
	hours %= 24;

	timediff.days = static_cast<int>(days);
	timediff.hours = static_cast<int>(hours);
	timediff.minutes = static_cast<int>(minutes);
	timediff.seconds = static_cast<int>(seconds);
	timediff.milliseconds = static_cast<int>(milliseconds);
}

void show_main()
{
	SDL_Event event;

	SDL_FPS fps(15);

	SDL_Surface* surf_title = NULL;
	SDL_Texture* ture_title = NULL;

	SYSTEMTIME now_time;
	GetLocalTime(&now_time);
	CalculateTimeDifference(now_time, target_time);
	if (timediff.days < 0 || timediff.hours < 0 || timediff.minutes < 0 || timediff.seconds < 0 || timediff.milliseconds < 0)
		target_time = createSystemTime(now_time.wYear, 6, 7, 9);
	CalculateTimeDifference(now_time, target_time);
	if (timediff.days < 0 || timediff.hours < 0 || timediff.minutes < 0 || timediff.seconds < 0 || timediff.milliseconds < 0)
		target_time = createSystemTime(now_time.wYear + 1, 6, 7, 9);
	char text_date[128] = { 0 };
	SDL_Surface* surf_date = NULL;
	SDL_Texture* ture_date = NULL;

init:
	TTF_SetFontSizeDPI(font_msyh, rect_main.w / 15 * 72.0f / DPI, DPI, DPI);
	SDL_FreeSurface(surf_title);
	SDL_DestroyTexture(ture_title);
	surf_title = TTF_RenderUTF8_LCD(font_msyh, text_title.c_str(), colorFG_title, colorBG_title);
	ture_title = SDL_CreateTextureFromSurface(rdr_main, surf_title);
	if (rect_title.w <= 0) rect_title.w = surf_title->w;
	if (rect_title.h <= 0) rect_title.h = surf_title->h;
	if (rect_title.x < 0) rect_title.x = (rect_main.w - rect_title.w) / 2;
	if (rect_title.y < 0) rect_title.y = 0;

again1:

	SDL_RenderClear(rdr_main);

	SDL_RenderCopy(rdr_main, ture_title, NULL, &rect_title);

	GetLocalTime(&now_time);
	CalculateTimeDifference(now_time, target_time);
	sprintf_s(text_date, "%s%d天%d时%d分%d.%ds", text_CD, timediff.days, timediff.hours, timediff.minutes, timediff.seconds, timediff.milliseconds);
	TTF_SetFontSizeDPI(font_msyh, rect_main.w / 17 * 72.0f / DPI, DPI, DPI);
	SDL_FreeSurface(surf_date);
	SDL_DestroyTexture(ture_date);
	surf_date = TTF_RenderUTF8_LCD(font_msyh, text_date, colorFG_CD, colorBG_CD);
	ture_date = SDL_CreateTextureFromSurface(rdr_main, surf_date);
	if (default_rect_CD)
	{
		rect_CD.w = surf_date->w;
		rect_CD.h = surf_date->h;
	}
	if (rect_CD.x < 0) rect_CD.x = (rect_main.w - rect_CD.w) / 2;
	if (rect_CD.y < 0) rect_CD.y = rect_title.h;
	SDL_RenderCopy(rdr_main, ture_date, NULL, &rect_CD);

	SDL_RenderPresent(rdr_main);

	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			continue;
		}
		else break;
	}

	fps++;
	std::cout << fps.SDL_GetFPS() << std::endl;
	goto again1;
}