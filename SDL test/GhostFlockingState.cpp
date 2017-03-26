#include "GhostFlockingState.h"
#include "GamePlayObject.h"
#include "GhostManager.h"
#include "Random.h"
const double SeeingRad = 20;
//the radius of the constraining circle for the wander behavior
const double WanderRad = 6;
//distance the wander circle is projected in front of the agent
const double WanderDist = 6.0;
//the maximum amount of displacement along the circle each frame
const double WanderJitterPerSec = 80.0;

const double SeparationWeight	= 25.0;
const double AlignmentWeight    = 20.0;
const double CohesionWeight     = 8.0;
const double WanderWeight       = 4;


GhostFlockingState::GhostFlockingState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager) : GhostBaseState(object, ghostManager) 
{
	flockingWorld = ghostManager->getWorld();
	flockingWorld->addObject(object);

	auto dimension = flockingWorld->getDimension();

	uniform_int_distribution<int> xdist{ dimension.x0 ,  dimension.x1 };
	uniform_int_distribution<int> ydist{ dimension.y0 ,  dimension.y1 };
	m_vPos.x = xdist(dre);
	m_vPos.y = ydist(dre);


	m_dMaxSpeed = 110.0;
	m_dMass = 2.0;
	m_dMaxTurnRate = 3.0;
	m_dMaxForce = 20.0;

	double theta = RandFloat() * TwoPi;
}
//
//
//SteeringForce            2.0
//MaxSpeed                 150.0
//VehicleMass              1.0
//VehicleScale             3.0
void GhostFlockingState::update(double deltaTime)
{
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
		object->setHeading(m_vHeading);
		m_vSide = m_vHeading.Perp();

		flockingWorld->wrap(m_vPos);
	}

	object->setX(m_vPos.x);
	object->setY(m_vPos.y);

	closeNeighbours.clear();
}

void GhostFlockingState::check()
{
	tagCloseNeighbors();
}

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
	Vector2D force;
	Vector2D total;
	
	force = separation(closeNeighbours) * SeparationWeight;

	if (!AccumulateForce(total, force))
	{
		return total;
	}

	force = cohesion(closeNeighbours) * CohesionWeight;

	if (!AccumulateForce(total, force)) {
		return total;
	}

	force = alignment(closeNeighbours) * AlignmentWeight;

	if (!AccumulateForce(total, force))
	{
		return total;
	}

	force = wander(dt) * WanderWeight;
	if (!AccumulateForce(total, force))
	{
		return total;
	}
	return total;
}

void GhostFlockingState::tagCloseNeighbors()
{
	closeNeighbours.clear();
	auto posibleNeighbors = flockingWorld->getObjects();
	for (auto posibleNeighbor : posibleNeighbors)
	{
		if (posibleNeighbor == object)
		{
			continue;
		}
		Vector2D to = posibleNeighbor->getPosition() - m_vPos;

		//the bounding radius of the other is taken into account by adding it 
		//to the range
		double range = SeeingRad + SeeingRad;

		//if entity within range, tag for further consideration. (working in
		//distance-squared space to avoid sqrts)
		if (to.LengthSq() < range*range)
		{
			closeNeighbours.push_back(posibleNeighbor);
		}

	}//next entity
}

bool GhostFlockingState::AccumulateForce(Vector2D &RunningTot,
	 Vector2D ForceToAdd)
{

	//calculate how much steering force the vehicle has used so far
	double MagnitudeSoFar = RunningTot.Length();

	//calculate how much steering force remains to be used by this vehicle
	double MagnitudeRemaining = m_dMaxForce - MagnitudeSoFar;

	//return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	double MagnitudeToAdd = ForceToAdd.Length();

	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining)
	{
		RunningTot += ForceToAdd;
	}

	else
	{
		//add it to the steering force
		RunningTot += (Vec2DNormalize(ForceToAdd) * MagnitudeRemaining);
	}

	return true;
}

Vector2D GhostFlockingState::seek(Vector2D target)
{
	Vector2D DesiredVelocity = Vec2DNormalize(target - m_vPos)
		* m_dMaxSpeed;

	return (DesiredVelocity - m_vVelocity);
}

Vector2D GhostFlockingState::separation(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors)
{
	Vector2D SteeringForce;

	for (auto neighbor : neighbors)
	{
		//make sure this agent isn't included in the calculations and that
		//the agent being examined is close enough. ***also make sure it doesn't
		//include the evade target ***

		Vector2D ToAgent = m_vPos - neighbor->getPosition();

		//scale the force inversely proportional to the agents distance  
		//from its neighbor.
		SteeringForce += Vec2DNormalize(ToAgent) / ToAgent.Length();
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
	for (auto neighbor : neighbors)
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough ***also make sure it doesn't
		//include any evade target ***

		AverageHeading += neighbor->getHeading();

		++NeighborCount;
	}

	//if the neighborhood contained one or more vehicles, average their
	//heading vectors.
	if (NeighborCount > 0)
	{
		AverageHeading /= (double)NeighborCount;

		AverageHeading -= object->getHeading();
	}

	return AverageHeading;
}


//-------------------------------- Cohesion ------------------------------
//
//  returns a steering force that attempts to move the agent towards the
//  center of mass of the agents in its immediate area
//------------------------------------------------------------------------
Vector2D GhostFlockingState::cohesion(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors)
{
	//first find the center of mass of all the agents
	Vector2D CenterOfMass, SteeringForce;

	int NeighborCount = 0;

	//iterate through all the tagged vehicles and sum their heading vectors  
	for (auto neighbor : neighbors)
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined is close enough ***also make sure it doesn't
		//include the evade target ***

		CenterOfMass += neighbor->getPosition();

		++NeighborCount;
	}

	if (NeighborCount > 0)
	{
		//the center of mass is the average of the sum of positions
		CenterOfMass /= (double)NeighborCount;

		//now seek towards that position
		SteeringForce = seek(CenterOfMass);
	}

	//the magnitude of cohesion is usually much larger than separation or
	//allignment so it usually helps to normalize it.
	return Vec2DNormalize(SteeringForce);
}

Vector2D GhostFlockingState::wander(const double& dt)
{
	//to the range
	//this behavior is dependent on the update rate, so this line must
	//be included when using time independent framerate.
	double JitterThisTimeSlice = WanderJitterPerSec * dt;

	//first, add a small random vector to the target's position
	m_vWanderTarget += Vector2D(RandomClamped() * JitterThisTimeSlice,
		RandomClamped() * JitterThisTimeSlice);

	//reproject this new vector back on to a unit circle
	m_vWanderTarget.Normalize();

	//increase the length of the vector to the same as the radius
	//of the wander circle
	m_vWanderTarget *= WanderRad;

	return  m_vWanderTarget;
}
