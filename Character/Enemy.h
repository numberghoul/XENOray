#pragma once
#include "../HelperClasses/List.h"
#include "../E_Def.h"
#include "Character.h"

struct EnemyState
{
	Vector2<double> position;
	void (*stateAction)();
};

class Enemy : public Character
{
public:
	Enemy(int health, int damage, double speed, Vector2<double> pos, int texture);
	Enemy(int health = 0, int damage = 0, double speed = 0, double posX = 0.0, double posY = 0.0, int texture = 0);

	int getDamage() const;
	void setDamage(const int &damage);

	void TakeDamage(int damage) override;
	void Move(double x, double y) override; // x and y represent the differences in the position vector components
	void Shoot() override;

private:
	int mDamage;

	void Die() override;
};
