#include "BasicTimer.h"
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>

BasicTimer mainTimer;

void BasicTimer::start()
{
	started = true;
	while (started)
	{
		mtx.lock();
		auto size = subscribers.size();
		for (auto subscriber : subscribers)
		{
			subscriber->tick();
		}
		int remainingTimeToSleep = timer;
		int steps = (timer > 10 ? timer / (timer / 10) : timer);
		
		mtx.unlock();
		while (remainingTimeToSleep > 0 && started && !paused) {
			std::this_thread::sleep_for(std::chrono::microseconds(steps));
			remainingTimeToSleep -= steps;
		}

		while (paused); // wait while paused
	}
}

void BasicTimer::setTimer(int timer)
{
	mtx.lock();
	this->timer = timer;
	mtx.unlock();
}

int BasicTimer::getTimer()
{
	return timer;
}

void BasicTimer::pause()
{
	paused = true;
}

void BasicTimer::resume()
{
	paused = false;
}

void BasicTimer::stop()
{
	started = false;
	reset();
}

void BasicTimer::reset()
{
	mtx.lock();
	subscribers.clear();
	mtx.unlock();
}

void BasicTimer::subscribe(std::shared_ptr<BasicTimerRegisterAble> registerable)
{
	mtx.lock();
	subscribers.push_back(registerable);
	mtx.unlock();
}

void BasicTimer::unsubscribe(std::shared_ptr<BasicTimerRegisterAble> registerable)
{
	mtx.lock();
	if (subscribers.size() > 0)
	{
		auto pos = std::find(subscribers.begin(), subscribers.end(), registerable);
		subscribers.erase(pos);
	}
	
	mtx.unlock();
}
