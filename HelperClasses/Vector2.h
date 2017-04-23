#pragma once
#include <cmath>
#include <iostream>

template <class T>
class Vector2
{
public:
	T x, y;

	// Constructors
	Vector2(T _x = 0.0f, T _y = 0.0f)
	{
		setX(_x);
		setY(_y);
		updateMagnitude();
	}

	Vector2(const Vector2<T> &copy)
	{
		setX(copy.getX());
		setY(copy.getY());
		updateMagnitude();
	}

	// Getters
	T getX() const { return x; }
	T getY() const { return y; }
	float getMagnitude() const { return std::sqrt(mMagnitude); }
	float getSqrMagnitude() const { return mMagnitude; }

	// Setters
	void setX(const T _x) { x = _x; }
	void setY(const T _y) { y = _y; }
	void updateMagnitude() { mMagnitude = getX() * getX() + getY() * getY(); }

	float distanceTo(const Vector2 other)
	{
		return std::sqrt(std::pow(getX() - other.getX(), 2) + std::pow(getY() - other.getY(), 2));
	}

	void normalize()
	{
		updateMagnitude();
		setX(getX() / getMagnitude());
		setY(getY() / getMagnitude());
		updateMagnitude();
	}

private:
	float mMagnitude;
};

template <class T>
std::ostream &operator<<(std::ostream &out, const Vector2<T> &vec)
{
	out << vec.x << " " << vec.y;

	return out;
}

template <class T>
Vector2<T> operator+(const Vector2<T> &v1, const Vector2<T> &v2)
{
	Vector2<T> v3(v1.x + v2.x, v1.y + v2.y);
	return v3;
}

template <class T>
Vector2<T> operator-(const Vector2<T> &v1, const Vector2<T> &v2)
{
	Vector2<T> v3(v1.x - v2.x, v1.y - v2.y);
	return v3;
}

template <class T>
Vector2<T> operator*(const double &c, const Vector2<T> &v2)
{
	Vector2<T> v3(c * v2.x, c * v2.y);
	return v3;
}