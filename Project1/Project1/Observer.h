#pragma once
class Observer {
public:
	Observer() {};
	Observer(const Observer& orig) {};
	virtual void update(void* model) = 0;
	virtual ~Observer() {};
};