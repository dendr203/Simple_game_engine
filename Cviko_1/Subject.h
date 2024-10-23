#pragma once
#include "Observer.h"

class Subject
{
	virtual void addObserver(Observer* observer) = 0;
	virtual void removeObserver(Observer* observer) = 0;
	virtual void notifyObservers() = 0;
	virtual void clearLinkShaders() = 0;
};
