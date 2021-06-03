#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "CandyCrush.h"

using namespace sf;

int main() {

	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow mainFrame(VideoMode(1152, 648, desktop.bitsPerPixel), "Candy Blast", Style::Close | Style::Titlebar);
	mainFrame.setVerticalSyncEnabled(true);
	mainFrame.setKeyRepeatEnabled(false);
	mainFrame.setPosition(Vector2i(50, 10));
	mainFrame.setFramerateLimit(60);

	Vector2f currentMousePos;

	CandyCrush candy;

	Music bgm;
	bgm.openFromFile("data\\bgm.ogg");
	bgm.play();

	//Main Loop
	while (mainFrame.isOpen()) {
		// Process events
		Event event;
		while (mainFrame.pollEvent(event)) {
			if (event.type == Event::Closed)
				mainFrame.close();
		}
		
		//Update MousePos
		currentMousePos.x = Mouse::getPosition(mainFrame).x;
		currentMousePos.y = Mouse::getPosition(mainFrame).y;


		candy.UpdateApp(mainFrame, currentMousePos);
		mainFrame.display();
	}
	return 0;
}