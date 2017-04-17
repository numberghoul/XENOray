class Object
{
public:
	Object(double posX, double posY, int angle, int texture);

	double getPosX() const;
	double getPosY() const;
	int getAngle() const;
	int getTexture() const;

	void setPosX(const double &posY);
	void setPosY(const double &posX);
	void setAngle(const int &angle);
	void setTexture(const int &texture);

private:
	double  mPosX,
			mPosY;
	int  mTexture, mAngle;
	bool mRotates;
};
