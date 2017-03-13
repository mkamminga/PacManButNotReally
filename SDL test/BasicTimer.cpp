#include "BasicTimer.h"
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>

BasicTimer mainTimer;

void BasicTimer::start(int timer)
{
	started = true;
	using namespace std::chrono_literals;
	while (started)
	{
		mtx.lock();
		auto size = subscribers.size();
		for (auto subscriber : subscribers)
		{
			subscriber->tick();
		}
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(timer));
	}
}

void BasicTimer::stop()
{
	started = false;
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
