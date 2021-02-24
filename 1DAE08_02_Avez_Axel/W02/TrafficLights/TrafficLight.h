#pragma once
class TrafficLight {
public:
	const static Vector2f dimensions;
	enum class State {
		GREEN,
		ORANGE,
		RED,
		OFF
	};

	explicit TrafficLight(const Vector2f& position);
	~TrafficLight();

	void Update(const float dx);
	void SetState(const State& state);
	void Draw() const;
	void DrawSupport() const;
	void DrawLights() const;
	void ProcessMouseLeftClick(const Vector2f& pos);
private:
	const static Color4f grey;
	const static Vector2f lightRadii;

	float m_AccumulatedSeconds;
	const Vector2f m_Position;
	State m_State;

	bool IsActive() const;
	void DrawLight(const State& requiredState, const Color4f& lightColor, const Vector2f position) const;
	
};