#ifndef _TIMER_H_
#define _TIMER_H_

/**
 * @file timer.h
 * @brief Defines the Timer class for handling time-based events and delays.
 *
 * This header file contains the Timer class, which provides functionality
 * for managing time-based events and delays in a game environment. The class
 * supports features such as:
 * - Setting wait times and one-shot behavior
 * - Handling timeout events with customizable callbacks
 * - Pausing and resuming the timer
 * - Restarting the timer
 * - Updating the timer state with delta time
 */

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	// Restarts the timer
	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	// Sets the wait time for the timer
	void set_wait_time(double val)
	{
		wait_time = val;
	}

	// Sets the one-shot behavior of the timer
	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}

	// Sets the callback function for when the timer times out
	void set_on_timeout(std::function<void()> on_timeout)
	{
		this->on_timeout = on_timeout;
	}

	// Pauses the timer
	void pause()
	{
		paused = true;
	}

	// Resumes the timer
	void resume()
	{
		paused = false;
	}

	// Updates the timer state with delta time
	void on_update(double delta)
	{
		// If the timer is paused, do nothing
		if (paused)
			return;

		// Update the time that has passed
		pass_time += delta;

		// If the timer has reached the wait time
		if (pass_time >= wait_time)
		{

			// Check if the timer can be triggered
			bool can_shot = (!one_shot || (one_shot && !shotted));
			shotted = true;

			// Call the callback function if it is set
			if (can_shot && on_timeout)
				on_timeout();

			// Reset the timer if it is one-shot
			if (one_shot)
				pass_time -= wait_time;
		}
	}

private:
	double pass_time = 0;  // The time that has passed
	double wait_time = 0;  // The wait time for the timer
	bool paused = false;   // Whether the timer is paused
	bool shotted = false;  // Whether the timer has been triggered
	bool one_shot = false; // Whether the timer is one-shot

	std::function<void()> on_timeout; // The callback function for when the timer times out
};

#endif // !_TIMER_H_
