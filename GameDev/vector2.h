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

	// Addition operator: Returns a new Vector2 that is the sum of this vector and the given vector
	Vector2 operator+(const Vector2 &vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	// Addition assignment operator: Adds the given vector to this vector
	void operator+=(const Vector2 &vec)
	{
		x += vec.x;
		y += vec.y;
	}

	// Subtraction operator: Returns a new Vector2 that is the difference between this vector and the given vector
	Vector2 operator-(const Vector2 &vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	// Subtraction assignment operator: Subtracts the given vector from this vector
	void operator-=(const Vector2 &vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	// Dot product operator: Returns the dot product of this vector and the given vector
	double operator*(const Vector2 &vec) const
	{
		return x * vec.x + y * vec.y;
	}

	// Scalar multiplication operator: Returns a new Vector2 that is this vector multiplied by the given scalar
	Vector2 operator*(double val) const
	{
		return Vector2(x * val, y * val);
	}

	// Scalar multiplication assignment operator: Multiplies this vector by the given scalar
	void operator*=(double val)
	{
		x *= val, y *= val;
	}

	// Equality operator: Returns true if this vector is equal to the given vector
	bool operator==(const Vector2 &vec) const
	{
		return x == vec.x && y == vec.y;
	}

	// Greater than operator: Returns true if the length of this vector is greater than the length of the given vector
	bool operator>(const Vector2 &vec) const
	{
		return length() > vec.length();
	}

	// Less than operator: Returns true if the length of this vector is less than the length of the given vector
	bool operator<(const Vector2 &vec) const
	{
		return length() < vec.length();
	}

	// Length function: Returns the length of this vector
	double length() const
	{
		return sqrt(x * x + y * y);
	}

	// Normalize function: Returns a new Vector2 that is this vector normalized
	Vector2 normalize() const
	{
		double len = length();
		if (len == 0)
			return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}

	// Approximation check for zero vectors: Returns true if the length of this vector is less than 0.0001
	bool approx_zero() const
	{
		return length() < 0.0001;
	}

private:
};

#endif // !_VECTOR_H_
