#include "MainMenu.h"

#include "Button.h"
#include "MainGame.h"

MainMenu::MainMenu() {
	bgTEX.loadFromFile("data\\tex\\bg.jpg");
	bg = Sprite(bgTEX);
	ButtonTEX.loadFromFile("data\\tex\\play_button.png");
	playBtn = new Button(500, 330, ButtonTEX, candice, "", Color::White, 32);

}

void MainMenu::Update(RenderTarget& mainFrame, Vector2f& mousePos) {

	playBtn->Update(mousePos);
	if (playBtn->isPressed()) {
		nextPage = new MainGame();
	}


	mainFrame.clear(Color::White);
	mainFrame.draw(bg);
	playBtn->Render(mainFrame);
}

MainMenu::~MainMenu() {
	delete playBtn;
}