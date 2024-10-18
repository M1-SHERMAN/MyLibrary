#ifndef _VECTOR3_H_
#define _VECTOR3_H_

/**
 * @file vector3.h
 * @brief Defines the Vector3 class for handling 3D vectors.
 *
 * This header file contains the Vector3 class, which provides functionality
 * for managing 3D vectors in a game environment. The class supports features
 * such as:
 * - Addition and subtraction of vectors
 * - Scalar multiplication and division
 * - Dot product and cross product calculations
 * - Vector normalization
 * - Approximation check for zero vectors
 * - Get distance between two vectors
 */

#include <cmath>

class vector3
{
private:
    double x = 0;
    double y = 0;
    double z = 0;

public:
    vector3() = default;
    ~vector3() = default;

    // Constructor
    vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    // Addition
    vector3 operator+(const vector3 &vec) const
    {
        return vector3(x + vec.x, y + vec.y, z + vec.z);
    }

    // Addition assignment
    void operator+=(const vector3 &vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
    }

    // Subtraction
    vector3 operator-(const vector3 &vec) const
    {
        return vector3(x - vec.x, y - vec.y, z - vec.z);
    }

    // Subtraction assignment
    void operator-=(const vector3 &vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
    }

    // Scalar multiplication
    vector3 operator*(double val) const
    {
        return vector3(x * val, y * val, z * val);
    }

    // Dot product
    double operator*(const vector3 &vec) const
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    // Cross product
    vector3 operator^(const vector3 &vec) const
    {
        return vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
    }

    // Scalar multiplication assignment
    void operator*=(double val)
    {
        x *= val;
        y *= val;
        z *= val;
    }

    // Equality
    bool operator==(const vector3 &vec) const
    {
        return x == vec.x && y == vec.y && z == vec.z;
    }

    // Greater than
    bool operator>(const vector3 &vec) const
    {
        return length() > vec.length();
    }

    // Less than
    bool operator<(const vector3 &vec) const
    {
        return length() < vec.length();
    }

    // Get length
    double length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    // Get distance
    double distance(const vector3 &vec) const
    {
        return (*this - vec).length();
    }

    // Normalization
    vector3 normalize() const
    {
        double len = length();
        if (len == 0)
            return vector3(0, 0, 0);
        return vector3(x / len, y / len, z / len);
    }

    // Approximation check for zero vectors
    bool approx_zero() const
    {
        return length() < 0.0001;
    }
};

#endif // !_VECTOR3_H_
