#include <cmath>

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

	Vector2(const Vector2 &copy)
	{
		setX(copy.getX());
		setY(copy.getY());
		updateMagnitude();
	}

	// Getters
	T getX() const { return x; }
	T getY() const { return y; }
	float getMagnitude() const { return std::sqrt(mMagnitude); }

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
		setX(getX() / getMagnitude());
		setY(getY() / getMagnitude());
		updateMagnitude();
	}

private:
	float mMagnitude;
};
