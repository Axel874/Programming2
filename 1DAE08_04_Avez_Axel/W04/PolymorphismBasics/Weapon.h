#pragma once
#include "GameObject.h"

class Weapon : public GameObject
{
public:
	Weapon( );
	~Weapon( ); 

	std::string ToString( ) const;

private:
	static int m_InstanceCounter;
};

 
