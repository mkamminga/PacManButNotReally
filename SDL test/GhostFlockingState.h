#pragma once
#include "GhostBaseState.h"
#include "Vector2D.h"
#include "FlockingWorld.h"

class GhostFlockingState :
	public GhostBaseState
{
private:
	Vector2D m_vVelocity;
	//a normalized vector pointing in the direction the entity is heading.
	Vector2D m_vHeading;
	//a vector perpendicular to the heading vector
	Vector2D m_vSide;

	Vector2D m_vPos;

	Vector2D m_TargetPos;

	double m_dMass;
	//the maximum speed at which this entity may travel.
	double m_dMaxSpeed;
	//the maximum force this entity can produce to power itself
	//(think rockets and thrust)
	double m_dMaxForce;
	//the maximum rate (radians per second) at which this vehicle can rotate
	double m_dMaxTurnRate;

	std::vector<std::shared_ptr<GamePlayObject>> closeNeighbours;

	std::shared_ptr<FlockingWorld>									flockingWorld = nullptr;
public:
	GhostFlockingState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager);
	virtual void update(double deltaTime);
	virtual void check();
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
	const Vector2D& getPosition() const;

private:
	Vector2D calculateSteering(const double& dt);
	void tagCloseNeighbors();
	Vector2D separation(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors);
	Vector2D alignment(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors);
	Vector2D seek();
	Vector2D wander(const double& dt);
};

