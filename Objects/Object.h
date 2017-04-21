#pragma once
#include "../HelperClasses/Vector2.h"

class Object
{
public:
	Object(double posX, double posY, double directionX, double directionY, int texture, bool rotates = true);
	Object(Vector2<double> pos, Vector2<double> dir, int texture, bool rotates = true);

	Vector2<double> getDirection() const;
	Vector2<double> getPosition() const;
	int getTexture() const;
	bool rotates() const;

	void setDirection(const Vector2<double> &dir);
	void setDirection(const double &dirX, const double &dirY);

	void setPosition(const Vector2<double> &pos);
	void setPosition(const double &posX, const double &posY);

	void setTexture(const int &texture);
	void setRotation(const bool &rotates);

protected:
	Vector2<double>  mPosition, mDirection;
	int  mTexture;
	bool mRotates;
};
