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
	Enemy(int health, int damage, double speed, int texture);

	int getDamage() const;
	int getNumInstances() const;
	void setDamage(const int &damage);

	Node<Vector2<double>> *getFirstLocation();

	void addLocation(const Vector2<double> &newLocation);
	bool removeLocation(int indexToRemoveAt);

	void TakeDamage(int damage) override;
	void Move(double x, double y) override; // x and y represent the differences in the position vector components
	void Shoot() override;

	List<Vector2<double>> getLocations() { return mLocations; }

private:
	List<Vector2<double>> mLocations;
	int mNumInstances;
	int mDamage;

	void Die() override;
};
