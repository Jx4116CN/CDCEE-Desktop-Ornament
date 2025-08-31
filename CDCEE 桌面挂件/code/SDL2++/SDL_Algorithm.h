#pragma once

#include <iostream>
#include <SDL.h>

#define PI 3.14159265359
#define e 2.718281828459

double inline Gaussian2D(int x, int y, double sigma);

int strlenUTF8(const char* s);

int endsizeUTF8(const char* s);

int len_to_sizeUTF8(const char* s, int length);

int num_to_sizeUTF8(const char* s, int order_number);

/*FPS*/
class SDL_FPS
{
private:
	Uint32 frame_start, frame_time, fps_timer;
	float fps, fps_target;
	int frame_count;

	void SDL_CalcFPS();

public:
	SDL_FPS(float fps_target);

	void SDL_FrameCount(unsigned int Count = 1);
	float SDL_GetFPS();
	SDL_FPS operator++(int) { SDL_FrameCount(); return *this; }
	SDL_FPS operator+=(unsigned int Count) { SDL_FrameCount(Count); return *this; }
};