#pragma once
#include "UIScreen.h"
#include "UIManager.h"

class MenuBar : public UIScreen
{
public:
	MenuBar();
	~MenuBar();
	void DrawUI() override;
};

