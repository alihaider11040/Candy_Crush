#pragma once

#include"SFML/Graphics.hpp"
//#include"SFML/Audio.hpp"

using namespace sf;
using namespace std;


class CandyUI {

	static enum class candy_state { IDLE, PRESSED, HOVERED };

private:

	candy_state state;

	Sprite sprite;

	Vector2f texSize;

	Color IdleColor = Color::White;
	Color HoverColor = Color(200, 200, 200, 255);
	Color PressedColor = Color(170, 170, 170, 255);
	
public:

	CandyUI(float x, float y, const Texture& tex) {
		this->state = candy_state::IDLE;
		this->sprite.setColor(IdleColor);

		this->sprite = Sprite(tex);
		this->sprite.setPosition(x, y);
	}

	~CandyUI() { }


	//-------------------- F U N C T I O N S -----------------------

	void SetPosition(float x, float y) {
		this->sprite.setPosition(x, y);
	}

	Vector2f GetPosition() {
		return sprite.getPosition();
	}

	void Move(float x, float y) {
		sprite.move(x, y);
	}

	void SetTEX(Texture& tex, float x, float y) {
		this->sprite = Sprite(tex);
		this->sprite.setPosition(x, y);
	}

	void SetScale(Vector2f scale) {
		sprite.setScale(scale);
	}

	void SetIdle() {
		state = candy_state::IDLE;
	}

	void Render(RenderTarget& target) {
		target.draw(sprite);
	}

	void Update(const Vector2f& mousePos) {
		if (state != candy_state::PRESSED) {
			state = candy_state::IDLE;
		}

		if (sprite.getGlobalBounds().contains(mousePos)) {

			if (state != candy_state::PRESSED) {
				state = candy_state::HOVERED;
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				state = candy_state::PRESSED;
			}
		}
		//else state = candy_state::PRESSED;

		switch (state) {

		case candy_state::IDLE:
			sprite.setColor(IdleColor);
			break;

		case candy_state::HOVERED:
			sprite.setColor(HoverColor);
			break;

		case candy_state::PRESSED:
			sprite.setColor(PressedColor);
			break;
		}
	}

	const bool isPressed()const {
		return (state == candy_state::PRESSED);
	}

	const bool isHovered()const {
		return (state == candy_state::HOVERED);
	}

};