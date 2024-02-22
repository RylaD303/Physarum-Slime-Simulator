#ifndef VECTOR2_HPP
#define VECTOR2_HPP
#include <iostream>
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

    bool operator==(const Vector2<NumericType>& other) const;
    bool operator!=(const Vector2<NumericType>& other) const;

    Vector2<NumericType> operator+(const Vector2<NumericType>& other) const;
    Vector2<NumericType> operator-(const Vector2<NumericType>& other) const;
    double operator*(const Vector2<NumericType>& other) const;
    Vector2<NumericType> operator*(const NumericType scalar) const;
    void operator+=(const Vector2<NumericType>& other);
    void operator-=(const Vector2<NumericType>& other);

};
#endif /* VECTOR2_HPP */