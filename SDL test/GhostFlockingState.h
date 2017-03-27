#pragma once
#include "GhostBaseState.h"
#include "Vector2D.h"
#include "FlockingWorld.h"

class GhostFlockingState :
	public GhostBaseState
{
private:
	Vector2D velocity;
	Vector2D heading;
	Vector2D side;
	Vector2D position;
	Vector2D targetPosition;
	Vector2D wanderTarget;

	double mass;
	double maxSpeed;
	double maxForce;
	double maxTurnRate;

	std::vector<std::shared_ptr<GamePlayObject>>					closeNeighbours;

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
	bool accumulateForce(Vector2D &RunningTot, Vector2D ForceToAdd);
	Vector2D separation(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors);
	Vector2D alignment(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors);
	Vector2D cohesion(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors);
	Vector2D seek(Vector2D target);
	Vector2D wander(const double& dt);
};

