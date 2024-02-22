#include "vector2.hpp"

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
double Vector2<NumericType>::distance_to(const Vector2<NumericType>& other) const
{
    return Vector2<NumericType>::distance(&this, other);
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

