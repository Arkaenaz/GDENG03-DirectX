#include "AppWindow.h"
#include "InputSystem.h"

using namespace application;
using namespace engine;

int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = (AppWindow*)AppWindow::getInstance();
	runningApp->initializeEngine();

	while(runningApp->isRunning())
	{
		runningApp->broadcast();
	}

	return 0;
}