#pragma once
#include "Character.h"
#include <unistd.h>

class Player : public Character
{
public:
	// Constructors
	Player();
	Player(int health, int armor, int battery, double speed, double posX = 0.0, double posY = 0.0, double dirX = 0.0, double dirY = 0.0,
		   double cameraX = 0.0, double cameraY = 0.0);
	Player(int health, int armor, int battery, double speed, Vector2<double> pos, Vector2<double> dir, Vector2<double> camera);

	// Accessors
	// Getters
	Vector2<double> getCameraPlane() const;
	int getArmor() const;
	int getBattery() const;

	// Setters
	void setCameraPlane(const Vector2<double> &cam);
	void setCameraPlane(const double &camX, const double &camY);

	void setArmor(const int &armor);
	void setBattery(const int &battery);

	// Member Functions
	void TakeDamage(int damage) override;
	void Move(double x, double y) override; // x and y represent the differences in the position vector components
	void Rotate(double rotSpeed);
	void Shoot() override;

private:
	Vector2<double> mCameraPlane;

	int mArmor, mBattery;

	void Die();
};
