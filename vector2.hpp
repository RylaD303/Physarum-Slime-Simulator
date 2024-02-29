#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <cmath>
#include <type_traits>

template<typename NumericType>
struct Vector2
{
    static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric.");
    NumericType x;
    NumericType y;

    Vector2();
    Vector2(NumericType x, NumericType y);

    static double distance(const Vector2<NumericType>& first, const Vector2<NumericType>& second);
    double distance_to(const Vector2<NumericType>& other) const;

    double length() const;

    void normalize();
    Vector2<NumericType> normalized() const;

    void rotate(double angle_degrees);
    Vector2<NumericType> rotated(double angle_degrees) const;

    bool operator==(const Vector2<NumericType>& other) const;
    bool operator!=(const Vector2<NumericType>& other) const;

    Vector2<NumericType> operator+(const Vector2<NumericType>& other) const;
    Vector2<NumericType> operator-(const Vector2<NumericType>& other) const;
    double operator*(const Vector2<NumericType>& other) const;
    Vector2<NumericType> operator*(const NumericType scalar) const;
    void operator+=(const Vector2<NumericType>& other);
    void operator-=(const Vector2<NumericType>& other);
    void operator*=(const NumericType scalar);

};


template<typename NumericType>
Vector2<NumericType>::Vector2()
{
    this->x = 0;
    this->y = 0;
}

template<typename NumericType>
Vector2<NumericType>::Vector2(NumericType x, NumericType y)
{
    this->x = x;
    this->y = y;
}

template<typename NumericType>
double Vector2<NumericType>::distance(const Vector2<NumericType>& first, const Vector2<NumericType>& second)
{
    double x1 = first.x - second.x;
    double y1 = first.y - second.y;
    return sqrt(x1 * x1 + y1 * y1);
}


template<typename NumericType>
double Vector2<NumericType>::distance_to(const Vector2<NumericType>& other) const
{
    return Vector2<NumericType>::distance(&this, other);
}

template<typename NumericType>
double Vector2<NumericType>::length() const
{
    return sqrt(this->x*this->x + this->y*this->y);
}

template<typename NumericType>
void Vector2<NumericType>::normalize()
{
    double length = this->length();
    this->x /= length;
    this->y /= length;
}

template<typename NumericType>
Vector2<NumericType> Vector2<NumericType>::normalized() const
{
    Vector2<NumericType> result(*this);
    result.normalize();
    return result;
}

template<typename NumericType>
void Vector2<NumericType>::rotate(double angle_degrees)
{
    double angle_radians = angle_degrees * M_PI / 180.0;
    double cos_angle = std::cos(angle_radians);
    double sin_angle = std::sin(angle_radians);

    this->x = static_cast<NumericType>(x * cos_angle - y * sin_angle);
    this->y = static_cast<NumericType>(x * sin_angle + y * cos_angle);
}

template<typename NumericType>
Vector2<NumericType> Vector2<NumericType>::rotated(double angle_degrees) const
{
    Vector2<NumericType> result(*this);
    result.rotate(angle_degrees);
    return result;
}


template<typename NumericType>
bool Vector2<NumericType>::operator==(const Vector2<NumericType>& other) const
{
    return this->x == other.x && this->y == other.y;
}

template<typename NumericType>
bool Vector2<NumericType>::operator!=(const Vector2<NumericType>& other) const
{
    return !(*this == other);
}

template<typename NumericType>
Vector2<NumericType> Vector2<NumericType>::operator+(const Vector2<NumericType>& other) const
{
    return Vector2<NumericType>(this->x + other.x, this->y + other.y);
}

template<typename NumericType>
Vector2<NumericType> Vector2<NumericType>::operator-(const Vector2<NumericType>& other) const
{
    return Vector2<NumericType>(this->x - other.x, this->y - other.y);
}

template<typename NumericType>
double Vector2<NumericType>::operator*(const Vector2<NumericType>& other) const
{
    return this->x*other.x + this->y*other.y;
}

template<typename NumericType>
Vector2<NumericType> Vector2<NumericType>::operator*(const NumericType scalar) const
{
    return Vector2<NumericType>(this->x * scalar, this->y * scalar);
}

template<typename NumericType>
void Vector2<NumericType>::operator+=(const Vector2<NumericType>& other)
{
    this->x += other.x;
    this->y += other.y;
}

template<typename NumericType>
void Vector2<NumericType>::operator-=(const Vector2<NumericType>& other)
{
    this->x -= other.x;
    this->y -= other.y;
}

template<typename NumericType>
void Vector2<NumericType>::operator*=(const NumericType scalar)
{
    this->x *= scalar;
    this->y *= scalar;
}

#endif /* VECTOR2_HPP */
