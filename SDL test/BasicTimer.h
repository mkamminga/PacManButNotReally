#pragma once
#include <vector>
#include <memory>
#include <mutex>

class BasicTimerRegisterAble {
public:
	virtual void tick() = 0;
};

class BasicTimer
{
private:
	std::mutex mtx;
	bool started;
	std::vector<std::shared_ptr<BasicTimerRegisterAble>> subscribers;
public:
	BasicTimer() {};
	void start(int timer);
	void stop();
	void reset();
	void subscribe(std::shared_ptr<BasicTimerRegisterAble> registerable);
	void unsubscribe(std::shared_ptr<BasicTimerRegisterAble> registerable);
	~BasicTimer()
	{
		subscribers.clear();
	}
};

extern BasicTimer mainTimer;

