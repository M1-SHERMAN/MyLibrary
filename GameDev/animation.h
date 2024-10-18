#ifndef _ANIMATION_H_
#define _ANIMATION_H_

/**
 * @file animation.h
 * @brief Defines the Animation class for handling sprite animations in SDL2.
 *
 * This header file contains the Animation class, which provides functionality
 * for creating and managing sprite animations using SDL2. The class supports
 * features such as:
 * - Loading sprite sheets and defining frame data
 * - Controlling animation playback (looping, interval, callbacks)
 * - Updating and rendering animations
 * - Handling animation completion events
 *
 * The Animation class uses a Timer for frame timing and supports various
 * customization options for animation behavior.
 */

#include "timer.h"

#include <vector>
#include <functional>
#include <SDL.h>

class Animation
{
public:
	typedef std::function<void()> PlayCallback;

public:
	Animation()
	{

		timer.set_one_shot(false); // Set the timer to repeat (not one-shot)

		// Set the callback function for when the timer times out
		timer.set_on_timeout(
			[&]()
			{
				idx_frame++; // Move to the next frame

				// Check if the animation has reached the end
				if (idx_frame >= rect_src_list.size())
				{
					// If looping, go back to the first frame
					// If not looping, stay on the last frame
					idx_frame = is_loop ? 0 : rect_src_list.size() - 1;

					// If not looping and a finish callback is set, call it
					if (!is_loop && on_finished)
						on_finished();
				};
			});
	}

	~Animation() = default;

	void reset()
	{
		timer.restart();

		idx_frame = 0;
	}

	// set the frame data of the animation
	void set_frame_data(SDL_Texture *texture, int num_h, int num_v, const std::vector<int> &idx_list)
	{

		int width_tex, height_tex; // Get the dimensions of the texture

		this->texture = texture;											  // Set the texture of the animation
		SDL_QueryTexture(texture, nullptr, nullptr, &width_tex, &height_tex); // Query the texture to get its width and height

		width_frame = width_tex / num_h, height_frame = height_tex / num_v; // Calculate the width and height of each frame

		rect_src_list.resize(idx_list.size()); // Resize the rect_src_list to match the number of frames

		// Iterate through each frame index
		for (size_t i = 0; i < idx_list.size(); i++)
		{
			int idx = idx_list[i];				   // Get the index of the current frame
			SDL_Rect &rect_src = rect_src_list[i]; // Get the source rectangle for the current frame

			// Calculate the x and y coordinates of the frame in the texture
			rect_src.x = (idx % num_h) * width_frame;
			rect_src.y = (idx / num_h) * height_frame;
			//  Set the width and height of the frame
			rect_src.w = width_frame, rect_src.h = height_frame;
		}
	}

	// set the loop mode of the animation
	void set_loop(bool is_loop)
	{
		this->is_loop = is_loop;
	}

	// set the interval time of the animation
	void set_interval(double interval)
	{
		timer.set_wait_time(interval);
	}

	// set the callback function of the animation
	void set_on_finished(PlayCallback on_finished)
	{
		this->on_finished = on_finished;
	}

	// update the animation
	void on_update(double delta)
	{
		timer.on_update(delta);
	}

	// render the animation
	void on_render(SDL_Renderer *renderer, const SDL_Point &pos_dst, double angle = 0) const
	{
		static SDL_Rect rect_dst;							 // Create a static destination rectangle for rendering
		rect_dst.x = pos_dst.x, rect_dst.y = pos_dst.y;		 // Set the position of the destination rectangle
		rect_dst.w = width_frame, rect_dst.h = height_frame; // Set the size of the destination rectangle to match the frame size

		// Render the current frame of the animation
		SDL_RenderCopyEx(renderer, texture, &rect_src_list[idx_frame], &rect_dst, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
		/*
		Parameters:
		- renderer: The renderer to use for rendering the texture
		- texture: The texture to render
		- &rect_src_list[idx_frame]: The source rectangle to use for rendering
		- &rect_dst: The destination rectangle to use for rendering
		- angle: The angle to rotate the texture (in degrees)
		- nullptr: The center of rotation (nullptr for the default center)
		- SDL_RendererFlip::SDL_FLIP_NONE: The flip mode (none in this case)
		*/
	}

private:
	Timer timer;			  // The timer for the animation
	bool is_loop = true;	  // Whether the animation is looping
	size_t idx_frame = 0;	  // The index of the current frame
	PlayCallback on_finished; // Callback function to call when the animation finishes

	SDL_Texture *texture = nullptr;		 // The texture to render
	std::vector<SDL_Rect> rect_src_list; // to store rect of every frame

	int width_frame = 0, height_frame = 0; // width & height of every frame
};

#endif // !_ANIMATION_H_
