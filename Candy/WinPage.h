#pragma once
#include "Page.h"
#include "Button.h"
#include "Game.h"

using namespace sf;

class WinPage : public Page {

private:
	
	RectangleShape fader;
	Page* faded;
	Game* game;

	Button* nextButton;
	Text score;
	Text scoreCount;
	Text level;
	Text win;

	Texture frameTEX;
	Sprite frame;

	bool end = false;

public:
	WinPage(Page* faded, Game* game) {
		this->faded = faded;
		this->game = game;

		frameTEX.loadFromFile("data//tex//win.png");

		fader = RectangleShape(Vector2f(10000, 10000));
		fader.setFillColor(Color(0, 0, 0, 120));

		nextButton = new Button(595, 530, ButtonTEX, candice, "Next Level", Color::White, 32);
		nextButton->SetButtonScale(Vector2f(1.15f, 1.15f));

		string levelSTR = "Level" + to_string(game->get_level());
		level = Text(levelSTR, candice, 38);
		level.setFillColor(Color(0, 57, 137));
		level.setPosition(540, 45);

		score = Text("Score", candice, 40);
		score.setFillColor(Color(15, 136, 229));
		score.setPosition(530, 240);
		
		win = Text("You Win", candice, 45);
		win.setFillColor(Color(15, 136, 229));
		win.setPosition(530, 400);

		scoreCount = Text(to_string(game->get_score()), candice, 30);
		scoreCount.setFillColor(Color::White);
		scoreCount.setPosition(552, 300);
		
		frame = Sprite(frameTEX);
		frame.setPosition(330.5, 24);

		if (game->get_level() == 3) {
			nextButton->SetText("Main Menu");
			end = true;
		}
	}

	void Update(RenderTarget& mainFrame, Vector2f& mousePos) {
		Vector2f disabledMousePos(-1, -1);

		nextButton->Update(mousePos);
		if (nextButton->isPressed()) {
			if (!end) {
				game->load_Level();
				faded->UpdateLevel();
				faded->ResetNextPage();
				nextPage = faded;
			}
			else {
				delete faded;
				nextPage = new MainMenu();
				return;
			}
		}

		faded->Render(mainFrame);
		mainFrame.draw(fader);
		mainFrame.draw(frame);
		mainFrame.draw(level);
		mainFrame.draw(score);
		mainFrame.draw(scoreCount);
		nextButton->Render(mainFrame);

		if (end) {
			mainFrame.draw(win);
		}
	}

	~WinPage() {
		delete nextButton;
	}
};
