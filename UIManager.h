#pragma once

#include <unordered_map>
#include <vector>

#include "GameObject.h"
#include "UIScreen.h"

class UINames {
public:
	const String MENU_SCREEN = "MENU_SCREEN";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const String COLOR_PICKER_SCREEN = "COLOR_PICKER_SCREEN";
};

class UIManager
{
private:
	std::unordered_map<std::string, UIScreen*> mapUI;
	std::vector<UIScreen*> listUI;

public:
	void draw();
	void setActive(String name);
	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

	static int RESIZE_WIDTH;
	static int RESIZE_HEIGHT;
private:
	static UIManager* P_SHARED_INSTANCE;

private:
	UIManager(HWND hwnd);
	UIManager(const UIManager&);
	UIManager& operator = (const UIManager&);

public:
	static UIManager* getInstance();
	static void initialize(HWND hwnd);
	static void destroy();
};

