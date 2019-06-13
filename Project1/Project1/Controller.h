#pragma once

class Controller
{
public:
	Controller(){}
	virtual ~Controller(){}
	virtual void dispatcher(void* model) = 0;
};
