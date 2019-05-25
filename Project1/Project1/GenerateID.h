#pragma once
#include <iostream>

using namespace std;

static unsigned long generateID(unsigned char *str)
{
	unsigned long ID = 0;
	int c;
	while (c = *str++)
		ID = c + (ID << 6) + (ID << 16) - ID;
	return ID;
}