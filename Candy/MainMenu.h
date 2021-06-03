#pragma once

#include <SFML/Graphics.hpp>
#include "Page.h"

class Button;

using namespace sf;

class MainMenu : public Page {

	Texture bgTEX;
	Sprite bg;

	Button* playBtn;

public:

	MainMenu();
	~MainMenu();
	void Update(RenderTarget& mainFrame, Vector2f& mousePos);
	
};

