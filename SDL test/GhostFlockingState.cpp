#include "GhostFlockingState.h"
#include "GamePlayObject.h"
#include "GhostManager.h"
#include "Random.h"

const double SeeingRad = 30;
const double WanderRad = 6;
const double WanderDist = 6.0;
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
	position.x = xdist(dre);
	position.y = ydist(dre);


	maxSpeed = 110.0;
	mass =4.0;
	maxTurnRate = 3.0;
	maxForce = 20.0;

	double theta = RandFloat() * TwoPi;
}

void GhostFlockingState::update(double deltaTime)
{
	//calculate the combined force from each steering behavior in the
	//vehicle’s list
	Vector2D SteeringForce = calculateSteering(deltaTime);

	Vector2D acceleration = SteeringForce / mass;

	//update velocity
	velocity += acceleration * deltaTime;

	//make sure vehicle does not exceed maximum velocity
	velocity.Truncate(maxSpeed);
	//update the position
	position += velocity * deltaTime;

	//update the heading if the vehicle has a velocity greater than a very small
	//value
	if (velocity.LengthSq() > 0.00000001)
	{
		heading = Vec2DNormalize(velocity);
		object->setHeading(heading);
		side = heading.Perp();

		flockingWorld->wrap(position);
	}

	object->setX(position.x);
	object->setY(position.y);

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
	return position;
}

Vector2D GhostFlockingState::calculateSteering(const double& dt)
{
	Vector2D force;
	Vector2D total;
	
	force = separation(closeNeighbours) * SeparationWeight;

	if (!accumulateForce(total, force))
	{
		return total;
	}

	force = cohesion(closeNeighbours) * CohesionWeight;

	if (!accumulateForce(total, force)) {
		return total;
	}

	force = alignment(closeNeighbours) * AlignmentWeight;

	if (!accumulateForce(total, force))
	{
		return total;
	}

	force = wander(dt) * WanderWeight;

	if (!accumulateForce(total, force))
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
		Vector2D to = posibleNeighbor->getPosition() - position;

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

bool GhostFlockingState::accumulateForce(Vector2D &RunningTot,
	 Vector2D ForceToAdd)
{

	//calculate how much steering force the vehicle has used so far
	double MagnitudeSoFar = RunningTot.Length();

	//calculate how much steering force remains to be used by this vehicle
	double MagnitudeRemaining = maxForce - MagnitudeSoFar;

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
	Vector2D DesiredVelocity = Vec2DNormalize(target - position)
		* maxSpeed;

	return (DesiredVelocity - velocity);
}

Vector2D GhostFlockingState::separation(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors)
{
	Vector2D SteeringForce;

	for (auto neighbor : neighbors)
	{

		Vector2D ToAgent = position - neighbor->getPosition();

		//scale the force inversely proportional to the agents distance  
		//from its neighbor.
		SteeringForce += Vec2DNormalize(ToAgent) / ToAgent.Length();
	}

	return SteeringForce;
}

Vector2D GhostFlockingState::alignment(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors)
{
	//used to record the average heading of the neighbors
	Vector2D AverageHeading;

	//used to count the number of vehicles in the neighborhood
	int    NeighborCount = 0;

	//iterate through all the tagged vehicles and sum their heading vectors  
	for (auto neighbor : neighbors)
	{
		AverageHeading += neighbor->getHeading();

		++NeighborCount;
	}

	//Align with the avg heading of all close neighbors
	if (NeighborCount > 0)
	{
		AverageHeading /= (double)NeighborCount;

		AverageHeading -= object->getHeading();
	}

	return AverageHeading;
}

Vector2D GhostFlockingState::cohesion(const std::vector < std::shared_ptr<GamePlayObject>>& neighbors)
{
	//first find the center of mass of all the agents
	Vector2D CenterOfMass, SteeringForce;

	int NeighborCount = 0;

	for (auto neighbor : neighbors)
	{


		CenterOfMass += neighbor->getPosition();

		++NeighborCount;
	}
	//If any neighbors, move to the center of mass
	if (NeighborCount > 0)
	{
		//the center of mass is the average of the sum of positions
		CenterOfMass /= (double)NeighborCount;

		//now seek towards that position
		SteeringForce = seek(CenterOfMass);
	}

	//return a smaller version
	return Vec2DNormalize(SteeringForce);
}

Vector2D GhostFlockingState::wander(const double& dt)
{
	double JitterThisTimeSlice = WanderJitterPerSec * dt;
	//Add rand target
	wanderTarget += Vector2D(RandomClamped() * JitterThisTimeSlice,
		RandomClamped() * JitterThisTimeSlice);

	//reproject this new vector back on to a unit circle
	wanderTarget.Normalize();

	//increase the length of the vector to the same as the radius
	//of the wander circle
	wanderTarget *= WanderRad;

	return  wanderTarget;
}
