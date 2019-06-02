#pragma once
#include "EventData.h"
class Controller {
public:
	Controller() {};
	void parseMouseEvent(EventData *mouseEvent);
	void parseNetworkEvent(EventData *mouseEvent);
	virtual ~Controller() {};
};