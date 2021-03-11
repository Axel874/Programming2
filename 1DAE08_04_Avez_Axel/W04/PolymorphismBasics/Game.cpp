#include "pch.h"
#include <iostream>
#include "Game.h"
#include "Weapon.h"
#include "Enemy.h"
#include "PickUp.h"

Game::Game()
{

}
Game::~Game()
{
	for (GameObject* g : m_pObjects) {
		delete g;
	}
	m_pWeapons.clear();
}

void Game::AddEnemy()
{
	m_pObjects.push_back(new Enemy());
}

void Game::AddPickUp()
{
	m_pObjects.push_back(new PickUp());
}

void Game::AddWeapon()
{
	m_pObjects.push_back(new Weapon());
}

void Game::ReportAll() const
{
	int seqNr{ 0 };

	std::cout << "--> All Game objects\n";
	for (GameObject* ptr : m_pObjects)
	{
		++seqNr;
		std::cout << seqNr << ": " << ptr->ToString() << "\n";
	}
}

void Game::ReportEnemies() const
{
	const size_t  enemyType = typeid(Enemy).hash_code();

	std::cout << "--> Enemies (typeid comparison)\n";
	for (GameObject* ptr : m_pObjects)
	{
		const size_t ptrType = typeid(*ptr).hash_code();
		const bool isEnemy = ptrType == enemyType;
		if(isEnemy){ std::cout << ptr->ToString() << "\n"; }
	}
	//compare speeds ?
	std::cout << "--> Enemies (dynamic_cast)\n";
	for (GameObject* ptr : m_pObjects)
	{
		const bool isEnemy = dynamic_cast<Enemy*>(ptr) != nullptr;
		if (isEnemy) { std::cout << ptr->ToString() << "\n"; }
	}
}