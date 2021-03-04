#include "pch.h"
#include "PowerUpManager.h"

PowerUpManager::PowerUpManager(){}
PowerUpManager::~PowerUpManager(){
	for (PowerUp* p : m_pItems)delete p;
}

void PowerUpManager::Update(float elapsedSec){
	for (PowerUp* p : m_pItems)p->Update(elapsedSec);
}
void PowerUpManager::Draw() const{
	for (PowerUp* p : m_pItems)p->Draw();
}

size_t PowerUpManager::Size() const { return m_pItems.size(); }
bool PowerUpManager::HitItem(const Rectf& rect) {
	for (unsigned int i = 0; i < m_pItems.size(); i++) {
		const PowerUp* p = m_pItems[i];
		const bool isOverLapping = p->IsOverlapping(rect);
		if (isOverLapping) { 
			RemoveItem(i);
			return true;
		}
	}
	return false;
}
PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type) { 
	PowerUp* p = new PowerUp(center, type);
	m_pItems.push_back(p);
	return p; 
}
void PowerUpManager::RemoveItem(unsigned int index) {
	delete m_pItems[index];
	m_pItems[index] = m_pItems.back();
	m_pItems.pop_back();
}