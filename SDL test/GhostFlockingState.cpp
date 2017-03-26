#include "GhostFlockingState.h"
#include "GamePlayObject.h"
#include "GhostManager.h"
#include "Random.h"
//the radius of the constraining circle for the wander behavior
const double WanderRad = 1.2;
//distance the wander circle is projected in front of the agent
const double WanderDist = 2.0;
//the maximum amount of displacement along the circle each frame
const double WanderJitterPerSec = 80.0;

//used in path following
const double WaypointSeekDist = 20;

GhostFlockingState::GhostFlockingState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager) : GhostBaseState(object, ghostManager) 
{
	flockingWorld = ghostManager->getWorld();
	flockingWorld->addObject(object);

	m_vPos.x = object->getX();
	m_vPos.y = object->getY();

	m_TargetPos.x = 1100;
	m_TargetPos.y = 700;

	m_dMaxSpeed = 150.0;
	m_dMass = 1.0;
	m_dMaxTurnRate = 3.0;
	m_dMaxForce = 2.0;
}
//
//
//SteeringForce            2.0
//MaxSpeed                 150.0
//VehicleMass              1.0
//VehicleScale             3.0
void GhostFlockingState::update(double deltaTime)
{
	if (m_vPos == m_TargetPos)
	{
		return;
	}

	//calculate the combined force from each steering behavior in the
	//vehicle’s list
	Vector2D SteeringForce = calculateSteering(deltaTime);

	Vector2D acceleration = SteeringForce / m_dMass;

	//update velocity
	m_vVelocity += acceleration * deltaTime;

	//make sure vehicle does not exceed maximum velocity
	m_vVelocity.Truncate(m_dMaxSpeed);
	//update the position
	m_vPos += m_vVelocity * deltaTime;

	//update the heading if the vehicle has a velocity greater than a very small
	//value
	if (m_vVelocity.LengthSq() > 0.00000001)
	{
		m_vHeading = Vec2DNormalize(m_vVelocity);
		m_vSide = m_vHeading.Perp();

		flockingWorld->wrap(m_vPos);
		//todo: check wrap around if object has left 
	}

	object->setX(m_vPos.x);
	object->setY(m_vPos.y);
}

void GhostFlockingState::check(){}

void GhostFlockingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}

const Vector2D& GhostFlockingState::getPosition() const
{
	return m_vPos;
}

Vector2D GhostFlockingState::calculateSteering(const double& dt)
{
	return wander(dt);
}

void GhostFlockingState::tagCloseNeighbors()
{
}

Vector2D GhostFlockingState::seek()
{
	Vector2D DesiredVelocity = Vec2DNormalize(m_TargetPos - m_vPos)
		* m_dMaxSpeed;

	return (DesiredVelocity - m_vVelocity);
}

Vector2D GhostFlockingState::separation(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors)
{
	Vector2D SteeringForce;

	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		//make sure this agent isn't included in the calculations and that
		//the agent being examined is close enough. ***also make sure it doesn't
		//include the evade target ***
		if (neighbors[a] != object)
		{
			Vector2D ToAgent = m_pVehicle->Pos() - neighbors[a]->Pos();

			//scale the force inversely proportional to the agents distance  
			//from its neighbor.
			SteeringForce += Vec2DNormalize(ToAgent) / ToAgent.Length();
		}
	}

	return SteeringForce;
}

//---------------------------- Alignment ---------------------------------
//
//  returns a force that attempts to align this agents heading with that
//  of its neighbors
//------------------------------------------------------------------------
Vector2D GhostFlockingState::alignment(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors)
{
	//used to record the average heading of the neighbors
	Vector2D AverageHeading;

	//used to count the number of vehicles in the neighborhood
	int    NeighborCount = 0;

	//iterate through all the tagged vehicles and sum their heading vectors  
	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough ***also make sure it doesn't
		//include any evade target ***
		if ((neighbors[a] != m_pVehicle) && neighbors[a]->IsTagged() &&
			(neighbors[a] != m_pTargetAgent1))
		{
			AverageHeading += neighbors[a]->Heading();

			++NeighborCount;
		}
	}

	//if the neighborhood contained one or more vehicles, average their
	//heading vectors.
	if (NeighborCount > 0)
	{
		AverageHeading /= (double)NeighborCount;

		AverageHeading -= m_pVehicle->Heading();
	}

	return AverageHeading;
}

Vector2D GhostFlockingState::wander(const double& dt)
{
	//stuff for the wander behavior
	double theta = RandFloat() * TwoPi;

	//create a vector to a target position on the wander circle
	m_vWanderTarget = Vector2D(m_dWanderRadius * cos(theta),
		m_dWanderRadius * sin(theta));
	//this behavior is dependent on the update rate, so this line must
	//be included when using time independent framerate.
	double JitterThisTimeSlice = WanderJitterPerSec * dt;

	//first, add a small random vector to the target's position
	m_TargetPos += Vector2D(RandomClamped() * JitterThisTimeSlice,
		RandomClamped() * JitterThisTimeSlice);

	//reproject this new vector back on to a unit circle
	m_TargetPos.Normalize();

	//increase the length of the vector to the same as the radius
	//of the wander circle
	m_TargetPos *= WanderRad;

	//move the target into a position WanderDist in front of the agent
	Vector2D target = m_TargetPos + Vector2D(WanderDist, 0);

	//and steer towards it
	return target - m_vPos;
}
