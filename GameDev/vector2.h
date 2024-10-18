#ifndef _VECTOR2_H_
#define _VECTOR2_H_

/**
 * @file vector2.h
 * @brief Defines the Vector2 class for handling 2D vector operations.
 *
 * This header file contains the Vector2 class, which provides functionality
 * for handling 2D vector operations in a game environment. The class supports
 * features such as:
 * - Basic vector operations (addition, subtraction, multiplication, normalization)
 * - Dot product calculation
 * - Length calculation
 * - Approximation check for zero vectors
 */

#include <cmath>

class Vector2
{
public:
	// The x & y coordinate of the 2D vector
	double x = 0;
	double y = 0;

public:
	Vector2() = default;
	~Vector2() = default;
	// Constructor for initializing the vector with x and y coordinates
	Vector2(double x, double y) : x(x), y(y) {}

	// Addition
	Vector2 operator+(const Vector2 &vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	// Addition assignment
	void operator+=(const Vector2 &vec)
	{
		x += vec.x;
		y += vec.y;
	}

	// Subtraction
	Vector2 operator-(const Vector2 &vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	// Subtraction assignment
	void operator-=(const Vector2 &vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	// Dot product
	double operator*(const Vector2 &vec) const
	{
		return x * vec.x + y * vec.y;
	}

	// Scalar multiplication
	Vector2 operator*(double val) const
	{
		return Vector2(x * val, y * val);
	}

	// Scalar multiplication assignment
	void operator*=(double val)
	{
		x *= val, y *= val;
	}

	// Equality
	bool operator==(const Vector2 &vec) const
	{
		return x == vec.x && y == vec.y;
	}

	// Greater than
	bool operator>(const Vector2 &vec) const
	{
		return length() > vec.length();
	}

	// Less than
	bool operator<(const Vector2 &vec) const
	{
		return length() < vec.length();
	}

	// Get length
	double length() const
	{
		return sqrt(x * x + y * y);
	}

	// Get distance
	double distance(const Vector2 &vec) const
	{
		return (*this - vec).length();
	}

	// Normalization
	Vector2 normalize() const
	{
		double len = length();
		if (len == 0)
			return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}

	// Approximation check for zero vectors
	bool approx_zero() const
	{
		return length() < 0.0001;
	}
};

#endif // !_VECTOR_H_
