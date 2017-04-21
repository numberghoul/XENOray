#include "Enemy.h"

Enemy::Enemy(int health, int damage, double speed, Vector2<double> pos, int texture) :
	Character(health, speed, 0, 0, 0, 0, texture)
{
	setPosition(pos);
	setDamage(damage);
}

Enemy::Enemy(int health, int damage, double speed, double posX, double posY, int texture) :
	Character(health, speed, posX, posY, 0, 0, texture)
{
	setDamage(damage);
}

int Enemy::getDamage() const { return mDamage; }
void Enemy::setDamage(const int &damage) { mDamage = damage; }

void Enemy::TakeDamage(int damage)
{
	mHealth -= damage;
	if (mHealth <= 0)
	{
		mHealth = 0;
		Die();
	}
}

void Enemy::Move(double x, double y)
{
	mPosition.setX(x);
	mPosition.setY(y);
}

void Enemy::Shoot()
{
}

void Enemy::Die()
{
}
