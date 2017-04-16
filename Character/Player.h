#include "Character.h"

class Player : public Character
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

	void TakeDamage(int damage) override;
	void Move(double x, double y) override; // x and y represent the differences in the position vector components
	void Rotate(double rotSpeed);
	void Shoot() override;

private:
	Vector2<double> mDirection,
					mCameraPlane;

	int mArmor,
		mBattery;

	void Die();
};
