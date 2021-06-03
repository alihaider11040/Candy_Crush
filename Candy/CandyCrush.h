#pragma once

#include "SFML/Graphics.hpp"
#include "Page.h"
#include "MainMenu.h"

class CandyCrush {

private:
	
	Page* currentPage = NULL;
	Page* nextPage = NULL;

public:
	CandyCrush() {
		currentPage = new MainMenu();
	}

	void UpdateApp(RenderWindow& mainFrame, Vector2f mousePos) {
		currentPage->Update(mainFrame, mousePos);

		bool reserve = false;
		nextPage = currentPage->UpdatePage(reserve);
		if (nextPage != NULL) {
			if (reserve) {
				currentPage = nextPage;
			}
			else {
				Page* temp = currentPage;
				currentPage = nextPage;
				nextPage = NULL;
				delete temp;
			}
		}
	}

	~CandyCrush() {
	}

};
