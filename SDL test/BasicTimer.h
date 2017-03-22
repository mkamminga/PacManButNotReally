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
	bool paused;
	bool stopped;
	std::vector<std::shared_ptr<BasicTimerRegisterAble>> subscribers;
	int timer = 0;
public:
	BasicTimer() {};
	void start();
	void setTimer(int timer);
	int getTimer();
	void pause();
	void resume();
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

