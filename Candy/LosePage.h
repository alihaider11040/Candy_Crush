#pragma once
#include "MainMenu.h"
#include "Page.h"
#include "Button.h"
#include "Game.h"

using namespace sf;


class LosePage : public Page {

private:

	RectangleShape fader;
	Page* faded;
	Game* game;

	Button* exit;
	Text fail;
	Text fail2;
	Text score;
	Text scoreCount;
	Text level;

	Texture frameTEX;
	Sprite frame;

public:
	LosePage(Page* faded, Game* game) {
		this->faded = faded;
		this->game = game;

		frameTEX.loadFromFile("data//tex//lose.png");

		fader = RectangleShape(Vector2f(10000, 10000));
		fader.setFillColor(Color(0, 0, 0, 120));

		exit = new Button(510, 520, ButtonTEX, candice, "Exit", Color::White, 32);
	

		string levelSTR = "Level" + to_string(game->get_level());
		level = Text(levelSTR, candice, 38);
		level.setFillColor(Color(0, 57, 137));
		level.setPosition(540, 45);

		fail = Text("You Failed", candice, 45);
		fail.setFillColor(Color(15, 136, 229));
		fail.setPosition(500, 150);
		
		fail2 = Text("You did not reach the target.", arial, 16);
		fail2.setFillColor(Color::White);
		fail2.setPosition(472, 267);
		
		score = Text("Score", candice, 40);
		score.setFillColor(Color(15, 136, 229));
		score.setPosition(530, 320);

		scoreCount = Text(to_string(game->get_score()), candice, 30);
		scoreCount.setFillColor(Color::White);
		scoreCount.setPosition(570, 370);

		frame = Sprite(frameTEX);
		frame.setPosition(330.5, 24);
	}

	void Update(RenderTarget& mainFrame, Vector2f& mousePos) {
		Vector2f disabledMousePos(-1, -1);

		exit->Update(mousePos);
		if (exit->isPressed()) {
			nextPage = new MainMenu();
		}

		faded->Render(mainFrame);
		mainFrame.draw(fader);
		mainFrame.draw(frame);
		mainFrame.draw(fail);
		mainFrame.draw(fail2);
		mainFrame.draw(level);
		mainFrame.draw(score);
		mainFrame.draw(scoreCount);
		exit->Render(mainFrame);
	}

	~LosePage() {
		delete faded;
		delete exit;
	}
};
