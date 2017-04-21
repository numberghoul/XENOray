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

bool Enemy::isVisible() const { return mIsVisible; }
void Enemy::setVisibility(const bool &visibility) { mIsVisible = visibility; }

void Enemy::TakeDamage(int damage)
{
	setHealth(getHealth() - damage);
	if (getHealth() <= 0)
	{
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
	std::cout << "I DIED!!!";
	mIsDead = true;
}
