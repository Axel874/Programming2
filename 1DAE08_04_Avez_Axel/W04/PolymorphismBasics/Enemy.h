#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy( );
	~Enemy( );

	std::string ToString( ) const;

private:
	static int m_InstanceCounter;
};


 
