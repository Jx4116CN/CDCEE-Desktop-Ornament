#include "Init.h"

void Init_SDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
		SDL_Quit();
		return;
	}
	if (TTF_Init() != 0)
	{
		SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
		IMG_Quit();
		SDL_Quit();
		return;
	}
}
void Init_main_device()
{
	win_main = SDL_CreateWindow(
		"CDCEE",
		rect_main.x,
		rect_main.y,
		rect_main.w,
		rect_main.h,
		SDL_WINDOW_BORDERLESS |
		SDL_WINDOW_ALWAYS_ON_TOP |
		SDL_WINDOW_SKIP_TASKBAR
	);
	if (win_main == nullptr)
	{
		SDL_Log("Could not create main window: %s", SDL_GetError());
		Quit();
		return;
	}
	SDL_SetWindowOpacity(win_main, (float)colorBG_main.a / 255.0f);
	SDL_ShowWindow(win_main);

	rdr_main = SDL_CreateRenderer(win_main, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (rdr_main == nullptr)
	{
		SDL_Log("Could not create main renderer: %s", SDL_GetError());
		Quit();
		return;
	}
	SDL_SetRenderDrawBlendMode(rdr_main, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rdr_main, colorBG_main.r, colorBG_main.g, colorBG_main.b, colorBG_main.a);

	font_msyh = TTF_OpenFont(path_msyh, 128);
	if (font_msyh == nullptr)
	{
		SDL_Log("Failed to load font: %s", TTF_GetError());
		Quit();
		return;
	}
}

void Init_main()
{
	Init_SDL();
	Load_cfg();
	Init_main_device();
}

void Quit_main()
{

}
void Quit_setting()
{
	Save_cfg();
}

void Quit()
{
	Quit_setting();
	Quit_main();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Load_cfg()
{
	std::ifstream file;
	file.open(cfgPath_main, std::ios::in);
	if (file.is_open())
	{
		file.read((char*)&rect_main, sizeof(SDL_Rect));
		file.read((char*)&colorBG_main, sizeof(SDL_Color));
		file.close();
	}
	if (rect_main.w <= 0) rect_main.w = screenW / 8;
	if (rect_main.h <= 0) rect_main.h = rect_main.w / 2;
	if (rect_main.x < 0) rect_main.x = (screenW - rect_main.w) / 2;
	if (rect_main.y < 0) rect_main.y = 0;

	file.open(cfgPath_title, std::ios::in);
	if (file.is_open())
	{
		file.read((char*)&show_title, sizeof(bool));
		file.read((char*)&rect_title, sizeof(SDL_Rect));
		file.read((char*)&colorBG_title, sizeof(SDL_Color));
		file.read((char*)&colorFG_title, sizeof(SDL_Color));
		file.close();
	}
	if (rect_title.w <= 0) rect_title.w = rect_main.w / 4 * 3;
	if (rect_title.h <= 0) rect_title.h = rect_main.h / 3;
	if (rect_title.x < 0) rect_title.x = (rect_main.w - rect_title.w) / 2;
	if (rect_title.y < 0) rect_title.y = 0;

	file.open(cfgPath_title_text, std::ios::in);
	if (file.is_open())
	{
		std::getline(file, text_title, '\0');
		file.close();
	}

	file.open(cfgPath_CD, std::ios::in);
	if (file.is_open())
	{
		file.read((char*)&rect_CD, sizeof(SDL_Rect));
		file.read((char*)&colorFG_CD, sizeof(SDL_Color));
		file.read((char*)&colorBG_CD, sizeof(SDL_Color));
		file.read((char*)text_CD, MAX_CD_LEN);
		file.read((char*)&target_time, sizeof(SYSTEMTIME));
		file.close();
	}
	if (rect_CD.w <= 0) rect_CD.w = rect_title.w;
	if (rect_CD.h <= 0) rect_CD.h = rect_title.h;
	if (rect_CD.x < 0) rect_CD.x = (rect_main.w - rect_CD.w) / 2;
	if (rect_CD.y < 0) rect_CD.y = rect_title.y + rect_title.h * 3 / 2;
}
void Save_cfg_UI()
{
	std::ofstream file;
	file.open(cfgPath_main, std::ios::out);
	if (file.is_open())
	{
		file.write((char*)&rect_main, sizeof(SDL_Rect));
		file.write((char*)&colorBG_main, sizeof(SDL_Color));
		file.close();
	}

	file.open(cfgPath_title, std::ios::out);
	if (file.is_open())
	{
		file.write((char*)&show_title, sizeof(bool));
		file.write((char*)&rect_title, sizeof(SDL_Rect));
		file.write((char*)&colorBG_title, sizeof(SDL_Color));
		file.write((char*)&colorFG_title, sizeof(SDL_Color));
		file.close();
	}

	file.open(cfgPath_title_text, std::ios::out);
	if (file.is_open())
	{
		file << text_title;
		file.close();
	}

	file.open(cfgPath_CD, std::ios::out);
	if (file.is_open())
	{
		file.write((char*)&rect_CD, sizeof(SDL_Rect));
		file.write((char*)&colorFG_CD, sizeof(SDL_Color));
		file.write((char*)&colorBG_CD, sizeof(SDL_Color));
		file.write((char*)text_CD, MAX_CD_LEN);
		file.write((char*)&target_time, sizeof(SYSTEMTIME));
		file.close();
	}
}
void Save_cfg()
{
	Save_cfg_UI();
}