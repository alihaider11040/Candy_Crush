#include "Page.h"
#include "WinPage.h"
#include "LosePage.h"
#include "Game.h"
#include "CandyUI.h"
#include "Animator.h"

using namespace sf;

class MainGame : public Page {

private:

	//TEX
	Texture bgTEX;
	Texture frameTEX;
	Texture sideframeTEX;
	
	Texture pngs[5];
	float scale = 0.78f;


	//SPRITES
	Sprite bg;
	Sprite frame;
	Sprite sideframe;


	//TEXTS
	Text levelNo;
	Text level;
	Text score;
	Text scoreCount;
	Text moves;
	Text movesCount;

	//MAIN VARS
	Game* game;
	CandyUI*** candies;
	
	//CANDY SELECTION
	CandyUI* selectedCandy;
	Vector2i selectedIndex;


	// ANIMATOR
	bool moving = false;
	Vector2f move1To;
	Vector2f move2To;
	CandyUI* move1 = NULL;
	CandyUI* move2 = NULL;
	bool direction = 0;//0-down 1-right
	bool moving1 = false;
	bool moving2 = false;


	bool crush = false;
	int crush_mode;//0-col 1-row
	int* match = NULL;
	float crush_startColPosition;

	int candyBounciness = 10;


	//CRUSH ANIMATION
	Animator** anims = NULL;
	int animCount = 0;

public:

	MainGame() {
		
		game = new Game();
		game->load_Level();


		bgTEX.loadFromFile("data\\tex\\bg2.jpg");
		frameTEX.loadFromFile("data\\tex\\frame.png");
		sideframeTEX.loadFromFile("data\\tex\\sideframe.png");

		pngs[1].loadFromFile("data\\tex\\candy1.png");
		pngs[2].loadFromFile("data\\tex\\candy2.png");
		pngs[3].loadFromFile("data\\tex\\candy3.png");
		pngs[4].loadFromFile("data\\tex\\candy4.png");

		bg = Sprite(bgTEX);
		frame = Sprite(frameTEX);
		sideframe = Sprite(sideframeTEX);

		level = Text("Level", candice, 40);
		level.setOutlineColor(Color::Black);
		level.setOutlineThickness(1);
		level.setPosition(118, 30);

		levelNo = Text(String(to_string(game->get_level())), candice, 50);
		levelNo.setOutlineColor(Color::Black);
		levelNo.setOutlineThickness(1);
		levelNo.setPosition(158, 62);

		
		moves = Text("Moves", candice, 25);
		moves.setOutlineColor(Color::Black);
		moves.setOutlineThickness(1);
		moves.setPosition(135, 150);
		
		movesCount = Text(String(to_string(game->moves_Allowed)), candice, 50);
		movesCount.setOutlineColor(Color::Black);
		movesCount.setOutlineThickness(1);
		movesCount.setPosition(142, 170);


		score = Text("Score", candice, 25);
		score.setOutlineColor(Color::Black);
		score.setOutlineThickness(1);
		score.setPosition(135, 240);

		string scoreSTR = to_string(game->score) + "/" + to_string(game->goal);
		scoreCount = Text(scoreSTR, candice, 25);
		scoreCount.setPosition(140, 272);

		frame.setPosition(470, 20);
		sideframe.setPosition(40, 0);


		int x = 475;
		int y = 25;

		candies = new CandyUI** [game->size];
		for (int i = 0; i < game->size; i++) {
			candies[i] = new CandyUI * [game->size];
			for (int j = 0; j < game->size; j++) {
				candies[i][j] = new CandyUI(x + (85*j*scale), y + (85*i*scale), pngs[1]);
				candies[i][j]->SetScale(Vector2f(scale, scale));
			}
		}

		UpdateCandies();

		selectedIndex = Vector2i(-1, -1);
		selectedCandy = NULL;


		crush_startColPosition = candies[0][0]->GetPosition().y;


		anims = new Animator* [game->size];
		for (int i = 0; i < game->size; i++) {
			anims[i] = new Animator(Vector2f(-100, -100), "data\\tex\\anim\\", 16, 2);
		}
	}

	void Update(RenderTarget& mainFrame, Vector2f& mousePos) {

		for (int i = 0; i < animCount; i++) {
			anims[i]->Update();
		}
		if (animCount != 0 && anims[0]->Ended()) {
			animCount = 0;
		}


		if (moving) {

			if (direction == 0) {
				if (move1->GetPosition().y < move1To.y) {
					move1->Move(0, 3);
				}
				else moving1 = true;
				if (move2->GetPosition().y > move2To.y) {
					move2->Move(0, -3);
				}
				else moving2 = true;

				if (moving1 && moving2) {
					moving = false;
					UpdateCandies();
				}
			}
			else if (direction == 1) {
				if (move1->GetPosition().x < move1To.x) {
					move1->Move(3, 0);
				}
				else moving1 = true;
				if (move2->GetPosition().x > move2To.x) {
					move2->Move(-3, 0);
				}
				else moving2 = true;
				if (moving1 && moving2) {
					moving = false;
					UpdateCandies();
				}
			}
		}

		else if (!crush){
			for (int i = 0; i < game->size; i++) {
				for (int j = 0; j < game->size; j++) {
					candies[i][j]->Update(mousePos);
					if (candies[i][j]->isPressed()) {
					
						bool moved = false;
						if (selectedIndex.x != -1 && selectedIndex != Vector2i(i, j) && selectedCandy != NULL) {
							if (game->move(selectedIndex.x, selectedIndex.y, i, j)) {
								moving = true;
								moving1 = false;
								moving2 = false;
								move1 = candies[selectedIndex.x][selectedIndex.y];
								move2 = candies[i][j];
								move1To = move2->GetPosition();
								move2To = move1->GetPosition();
								Vector2f pos1 = move1->GetPosition();
								Vector2f pos2 = move2->GetPosition();
								if (pos1.x == pos2.x) {
									if (pos1.y > pos2.y) {
										swap(move1, move2);
										swap(move1To, move2To);
									}
									direction = 0;
								}
								else if (pos1.y == pos2.y) {
									if (pos1.x > pos2.x) {
										swap(move1, move2);
										swap(move1To, move2To);
									}
									direction = 1;
								}


								selectedCandy->SetIdle();
								moved = true;
								selectedIndex = Vector2i(-1, -1);
								selectedCandy = NULL;
								candies[i][j]->SetIdle();
								break;
							}
							else selectedCandy->SetIdle();
						}
						if (!moved) {
							selectedIndex = Vector2i(i, j);
							selectedCandy = candies[i][j];
						}
					}
				}
			}
		}

		if (crush) {
			if (crush_mode == 0) {
				if (candies[0][match[0]]->GetPosition().y < crush_startColPosition + candyBounciness) {
					for (int i = 0; i < match[2]+1; i++) {
						candies[i][match[0]]->Move(0, 7);
					}
				}

				else {
					UpdateCandies();
					crush = false;
					delete[] match;
					match = NULL;
				}
			}
			else {
				if (candies[0][match[1]]->GetPosition().y < crush_startColPosition + candyBounciness) {
					for (int i = 0; i < match[0] + 1; i++) {
						for (int j = match[1]; j <= match[2]; j++) {
							candies[i][j]->Move(0, 7);
						}
					}
				}
				else {
					UpdateCandies();
					crush = false;
					delete[] match;
					match = NULL;
				}
			}
		}

		if (!moving && !crush && game->combination()) {
			crush = true;
			match = game->match_Column();
			if (match == NULL) {
				match = game->match_Row();
				//crush in row
				crush_mode = 1;
				
				animCount = match[2] - match[1] + 1;
				for (int i = 0, j = match[1]; i < animCount; i++, j++) {
					anims[i]->Reset();
					anims[i]->SetPosition(candies[match[0]][j]->GetPosition() - Vector2f(30,40));
					anims[i]->SetScale(Vector2f(0.8f, 0.8f));
				}

				for (int i = 0; i < match[0] + 1; i++) {
					for (int j = match[1]; j <= match[2]; j++) {
						candies[i][j]->SetTEX(pngs[game->board[i][j]->get_candyType()], 0, 0);
						candies[i][j]->SetPosition(475 + (85*scale*j), 25 - (85*scale*(1-i)));
						candies[i][j]->SetScale(Vector2f(scale, scale));
					}
				}
			}

			else {
				//crush in col
				crush_mode = 0;
				animCount = match[2] - match[1] + 1;

				for (int i = 0, j = match[1]; i < animCount; i++, j++) {
					anims[i]->Reset();
					anims[i]->SetPosition(candies[j][match[0]]->GetPosition() - Vector2f(35, 45));
					anims[i]->SetScale(Vector2f(0.8f, 0.8f));
				}

				for (int i = 0; i < match[2] + 1; i++) {
					candies[i][match[0]]->SetTEX(pngs[game->board[i][match[0]]->get_candyType()], 0, 0);
					candies[i][match[0]]->SetPosition(475 + (85*scale*match[0]), 25 - (85*scale*(animCount-i)));
					candies[i][match[0]]->SetScale(Vector2f(scale, scale));
				}
			}
		}
		


		if (!crush && !moving) {
			if (game->score >= game->goal) {
				reservePage = true;
				nextPage = new WinPage(this, game);
			}

			else if (game->moves_Allowed == 0) {
				reservePage = true;
				nextPage = new LosePage(this, game);
			}
		}
		

		string scoreSTR = to_string(game->score) + "/" + to_string(game->goal);
		scoreCount.setString(scoreSTR);
		movesCount.setString(to_string(game->moves_Allowed));

		Render(mainFrame);
	}

	void Render(RenderTarget& mainFrame) {

		mainFrame.clear(Color::White);
		mainFrame.draw(bg);
		mainFrame.draw(sideframe);
		mainFrame.draw(moves);
		mainFrame.draw(movesCount);
		mainFrame.draw(level);
		mainFrame.draw(levelNo);
		mainFrame.draw(score);
		mainFrame.draw(scoreCount);
		mainFrame.draw(frame);
		
		for (int i = 0; i < animCount; i++) {
			anims[i]->Render(mainFrame);
		}

		for (int i = 0; i < game->size; i++) {
			for (int j = 0; j < game->size; j++) {
				candies[i][j]->Render(mainFrame);
			}
		}
	}


	void UpdateCandies() {

		int x = 475;
		int y = 25;
		float scale = 0.78f;

		for (int i = 0; i < game->size; i++) {
			for (int j = 0; j < game->size; j++) {
				candies[i][j]->SetTEX(pngs[game->board[i][j]->get_candyType()], x + (85 * j * scale), y + (85 * i * scale));
				candies[i][j]->SetScale(Vector2f(scale, scale));
			}
		}
	}

	void UpdateLevel() {
		levelNo.setString(to_string(game->get_level()));
		UpdateCandies();
	}

	~MainGame() { 
		for (int i = 0; i < game->size; i++) {
			for (int j = 0; j < game->size; j++) {
				delete candies[i][j];
			}
			delete[] candies[i];
		}
		delete[] candies;

		delete game;
	}
};
