#pragma once
class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 dimensions, glm::vec3 up, glm::vec3 direction);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::vec3 GetPosition() const;

	virtual void Update(float deltaSeconds);
protected:
	glm::vec3 m_Position;
	glm::vec3 m_Dimensions;
private:
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
	
};