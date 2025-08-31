#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include "SDL2++/SDL2++.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")

#pragma execution_character_set("utf-8")

#include <string>
#include <fstream>
#include <windows.h>

__declspec(selectany) int screenW = GetSystemMetrics(SM_CXSCREEN);
__declspec(selectany) int screenH = GetSystemMetrics(SM_CYSCREEN);

__declspec(selectany) SDL_Window* win_main = nullptr;
__declspec(selectany) SDL_Window* win_setting = nullptr;
__declspec(selectany) SDL_Renderer* rdr_main = nullptr;
__declspec(selectany) SDL_Renderer* rdr_setting = nullptr;

__declspec(selectany) const char* path_msyh = "font\\msyh.ttc";
__declspec(selectany) TTF_Font* font_msyh = nullptr;

void Init_main();

void show_main();

void Quit();
void Quit_main();
void Quit_setting();

void Load_cfg();
void Save_cfg();
__declspec(selectany) const char* cfgPath_main = "config\\UI\\win_main.cfg";
__declspec(selectany) SDL_Rect rect_main = { -1, -1, 0, 0 };
__declspec(selectany) SDL_Color colorBG_main = { 0, 0, 0, 0x88 };
__declspec(selectany) const char* cfgPath_title = "config\\UI\\title.cfg";
__declspec(selectany) bool show_title = true;
__declspec(selectany) SDL_Rect rect_title = { -1, -1, 0, 0 };
__declspec(selectany) SDL_Color colorFG_title = { 255, 255, 255, 255 };
__declspec(selectany) SDL_Color colorBG_title = { 0, 0, 0, 255 };
__declspec(selectany) const char* cfgPath_title_text = "config\\UI\\title.txt";
__declspec(selectany) std::string text_title = "高考倒计时";
__declspec(selectany) const char* cfgPath_CD = "config\\UI\\CD.cfg";
__declspec(selectany) SDL_Rect rect_CD = { -1, -1, 0, 0 };
__declspec(selectany) SDL_Color colorFG_CD = { 255, 0, 0, 255 };
__declspec(selectany) SDL_Color colorBG_CD = { 255, 255, 255, 0x88 };
#define MAX_CD_LEN 128
__declspec(selectany) char text_CD[MAX_CD_LEN] = "%d天%d时%d分%d秒";
__declspec(selectany) SYSTEMTIME target_time = { 0, 0, 0, 0, 0, 0, 0, 0 };