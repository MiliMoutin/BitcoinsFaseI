#pragma once
class Observer {
public:
	Observer() {};
	Observer(const Observer& orig) {};
	virtual void update() = 0;
	virtual ~Observer() {};
};