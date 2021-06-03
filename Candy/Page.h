#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Page {

protected:

	Font arial;
	Font candice;
	
	Texture ButtonTEX;
	
	Page* nextPage = NULL;

	bool reservePage = false;

public:

	Page() {
		arial.loadFromFile("data\\fonts\\arial.ttf");
		candice.loadFromFile("data\\fonts\\candice.ttf");
		ButtonTEX.loadFromFile("data\\tex\\button.png");
	}

	virtual void Update(RenderTarget& mainFrame, Vector2f& mousePos) { }
	
	virtual void Render(RenderTarget& mainFrame) { }

	virtual void UpdateLevel() { }

	virtual Page* UpdatePage(bool& reservePage) {
		reservePage = this->reservePage;
		return nextPage;
	}

	virtual void ResetNextPage() {
		this->nextPage = NULL;
		this->reservePage = false;
	}

	virtual ~Page() {
		//do nothing
	}
};
