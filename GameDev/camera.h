#ifndef _CAMERA_H_
#define _CAMERA_H_

/**
 * @file camera.h
 * @brief Defines the Camera class for handling camera movement and effects.
 *
 * This header file contains the Camera class, which provides functionality
 * for managing camera movement and effects in a game environment. The class
 * supports features such as:
 * - Positioning the camera
 * - Initiating screen shake effects
 * - Resetting the camera position
 * - Updating the camera state, including shake effects
 * - Generating random numbers for shake effects
 * - Handling timer events for shake duration
 */

#include "vector2.h"
#include "vector2.h"
#include "timer.h"

#include <random>

class Camera
{
public:
	// Constructor initializes the shake timer
	Camera()
	{
		timer_shake.set_one_shot(true);
		timer_shake.set_on_timeout(
			[&]()
			{
				is_shaking = false;
				reset();
			});
	}

	~Camera() = default;

	// Returns the current position of the camera
	const Vector2 &get_position() const
	{
		return position;
	}

	// Resets the camera position to the origin
	void reset()
	{
		position.x = 0;
		position.y = 0;
	}

	// Updates the camera state, including shake effect
	void on_update(int delta)
	{
		timer_shake.on_update(delta);

		// Random number generation for shake effect
		std::random_device rd;
		std::mt19937 generator(rd());
		std::uniform_real_distribution<double> distribution(-1.0, 1.0);

		// Apply shake effect if currently shaking
		if (is_shaking)
		{
			position.x = distribution(generator) * shaking_strength;
			position.y = distribution(generator) * shaking_strength;
		}
	}

	// Initiates a screen shake effect
	void shake(double strength, int duration)
	{
		is_shaking = true;
		shaking_strength = strength;

		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	}

private:
	Vector2 position;			 // Current position of the camera
	Timer timer_shake;			 // Timer for controlling shake duration
	bool is_shaking = false;	 // Whether the camera is shaking
	double shaking_strength = 0; // The strength of the shaking
};

#endif // !_CAMERA_H_
