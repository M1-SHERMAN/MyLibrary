/**
 * This is a simple SDL practice project that demonstrates various SDL functionalities.
 * It includes window and renderer creation, image loading and rendering, font rendering,
 * music playback, event handling (quit and mouse movement), FPS control, and drawing primitives.
 *
 */

// Include SDL
#define SDL_MAIN_HANDLED		// to prevent SDL change main function
#include <SDL.h>				// core SDL
#include <SDL_ttf.h>			// for font rendering
#include <SDL_image.h>			// for loading & processing image
#include <SDL_mixer.h>			// for sound processing
#include <SDL2_gfxPrimitives.h> // Provides graphical primitives to draw (e.g., circles).

int main()
{
	/*Initialize SDL*/
	SDL_Init(SDL_INIT_EVERYTHING);					   // Init core SDL
	SDL_Init(IMG_INIT_JPG | IMG_INIT_PNG);			   // Init SDL_IMAGE
	SDL_Init(MIX_INIT_MP3);							   // Init SDL_MIXER
	TTF_Init();										   // Init SDL_TTF
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // Open Audio Device

	/*Create window & renderer*/
	SDL_Window *window = SDL_CreateWindow(u8"Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/*Load assets(image, font, sound, music)*/
	// Load image (surface -> texture)
	SDL_Surface *suf_img = IMG_Load("lora-georgieva.jpg");
	SDL_Texture *tex_img_1 = SDL_CreateTextureFromSurface(renderer, suf_img);
	SDL_Rect dst_img_1;
	dst_img_1.w = 416;
	dst_img_1.h = 624;

	// Load image (directe)
	SDL_Texture *tex_img_2 = IMG_LoadTexture(renderer, "soop-kim.jpg");
	SDL_Rect dst_img_2;
	dst_img_2.x = 0;
	dst_img_2.y = 0;
	dst_img_2.w = 380;
	dst_img_2.h = 571;

	// Load font
	TTF_Font *font = TTF_OpenFont("ms-mincho.ttf", 32); // load font & set size as 32
	// Create font texture
	SDL_Color font_color = {255, 255, 255, 255}; // set color: white
	SDL_Surface *suf_text = TTF_RenderUTF8_Blended(font, u8"こんにちは", font_color);
	SDL_Texture *tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);
	SDL_Rect dst_text;
	dst_text.w = suf_text->w;
	dst_text.h = suf_text->h;

	// Load music
	Mix_Music *music = Mix_LoadMUS("Untitled.mp3");
	// Play music
	Mix_FadeInMusic(music, -1, 1500);

	/*Game loop*/
	bool is_quit = false;
	SDL_Event event; // for processing mouse, keyboard event, etc.
	SDL_Point pos_cursor = {0, 0};

	// For controlling fps
	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();

	while (!is_quit)
	{
		/*Process event*/
		while (SDL_PollEvent(&event)) // quit event
		{
			if (event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			else if (event.type == SDL_MOUSEMOTION) // mouse movement event
			{
				pos_cursor.x = event.motion.x;
				pos_cursor.y = event.motion.y;
			}
		}

		/*Control fps*/
		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delta * 1000 < 1000.f / 60)
		{
			SDL_Delay((Uint32)(1000.f / 60 - delta * 1000));
		}

		/*Updating data*/
		dst_img_1.x = pos_cursor.x;
		dst_img_1.y = pos_cursor.y;
		dst_text.x = pos_cursor.x;
		dst_text.y = pos_cursor.y;

		/*Rendering*/
		// clearing last frame
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, tex_img_2, nullptr, &dst_img_2);					// rendering image 2
		SDL_RenderCopy(renderer, tex_img_1, nullptr, &dst_img_1);					// rendering image 1
		SDL_RenderCopy(renderer, tex_text, nullptr, &dst_text);						// rendering text
		filledCircleRGBA(renderer, pos_cursor.x, pos_cursor.y, 50, 255, 0, 0, 125); // rendering circle

		SDL_RenderPresent(renderer);
	}

	return 0;
}
