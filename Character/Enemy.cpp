#include "Enemy.h"

Enemy::Enemy(int health, int damage, double speed, int texture) :
	Character(health, speed, 0, 0, 0, 0, texture)
{
	setDamage(damage);
}

Node<Vector2<double>> *Enemy::getFirstLocation()
{
	return mLocations.getHead();
}

int Enemy::getNumInstances() const { return mNumInstances; }
int Enemy::getDamage() const { return mDamage; }
void Enemy::setDamage(const int &damage) { mDamage = damage; }

void Enemy::addLocation(const Vector2<double> &newLocation)
{
	mLocations.insertAtFront(newLocation);
	mNumInstances++;
}

bool Enemy::removeLocation(int indexToRemoveAt)
{
	if (mLocations.deleteAt(indexToRemoveAt))
		mNumInstances--;
	else
		return false;
	return true;
}

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
