#include "../Vector2.h"

class Player
{
public:
	Player(double posX = 0.0, double posY = 0.0, double dirX = 0.0, double dirY = 0.0, double cameraX = 0.0, double cameraY = 0.0);

	Player(Vector2<double> pos, Vector2<double> dir, Vector2<double> camera);

	Vector2<double> getPosition() const;
	Vector2<double> getDirection() const;
	Vector2<double> getCameraPlane() const;

	void setPosition(const Vector2<double> pos);
	void setPosition(const double posX, const double posY);

	void setDirection(const Vector2<double> dir);
	void setDirection(const double dirX, const double dirY);

	void setCameraPlane(const Vector2<double> cam);
	void setCameraPlane(const double camX, const double camY);

private:
	Vector2<double> mPosition,
	 				mDirection,
					mCameraPlane;

	int mHealth,
		mArmor,
		mBattery;

	double mSpeed;
};
