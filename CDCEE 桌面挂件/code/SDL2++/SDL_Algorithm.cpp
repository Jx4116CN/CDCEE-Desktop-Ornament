#include "SDL_Algorithm.h"

double inline Gaussian2D(
	int x,
	int y,
	double sigma)
{
	return (1 / 2.0 * PI * pow(sigma, 2.0)) * pow(e, -((x * x + y * y) / 2 * pow(sigma, 2.0)));
}

int strlenUTF8(
	const char* s)
{
	int i = 0, j = 0;
	while (s[i])
	{
		if ((s[i] & 0xc0) != 0x80)
			j++;
		i++;
	}
	return j;
}

int endsizeUTF8(
	const char* s)
{
	for (int i = strlen(s) - 1; i >= 0; i--)
	{
		if ((s[i] & 0xc0) != 0x80)
			return strlen(s) - i;
	}
}

int len_to_sizeUTF8(
	const char* s,
	int length)
{
	if (strlen(s) == 0) return 0;
	int i;
	for (i = 0; i <= strlen(s) - 1; i++)
	{
		if ((s[i] & 0xc0) != 0x80)
		{
			if (length < 1)
				break;
			else
				length--;
		}
	}
	return i;
}

int num_to_sizeUTF8(
	const char* s,
	int order_number)
{
	if (strlen(s) == 0) return 0;
	int i, size = 0;
	for (i = 0; i <= strlen(s) - 1; i++)
	{
		if ((s[i] & 0xc0) != 0x80)
		{
			if (order_number < 0)
				break;
			else
				order_number--;
		}
		else if (order_number < 0)
			size++;
	}
	return size + 1;
}

/*FPS*/
SDL_FPS::SDL_FPS(float fps_target)
{
	this->frame_start = 0;
	this->frame_time = 0;
	this->fps_timer = SDL_GetTicks();
	this->fps = 0.0f;
	this->fps_target = fps_target;
	this->frame_count = 0;
}
void inline SDL_FPS::SDL_CalcFPS()
{
	Uint32 current_time = SDL_GetTicks();
	if (current_time - fps_timer >= 1000)
	{
		fps = frame_count / ((current_time - fps_timer) / 1000.0f);
		fps_timer = current_time;
		frame_count = 0;
	}
}
void SDL_FPS::SDL_FrameCount(unsigned int Count)
{
	frame_count += Count;
	SDL_CalcFPS();
	frame_time = SDL_GetTicks() - frame_start;
	if (1000.0f / fps_target * Count > frame_time)
		SDL_Delay((Uint32)(1000.0f / fps_target - frame_time));
	frame_start = SDL_GetTicks();
}
float SDL_FPS::SDL_GetFPS()
{
	SDL_CalcFPS();
	return fps;
}