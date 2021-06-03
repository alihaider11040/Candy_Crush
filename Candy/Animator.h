#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Animator {

private:
	
	Vector2f pos;
	Vector2f scale;

	Texture* texs = NULL;
	string path;
	int n;
	int current = 0;

	Sprite anim;
	unsigned int speed;	//greater value slower animation
	unsigned int counter;

	bool finish = false;

public:
	
	Animator(Vector2f pos, string path, int n, int speed) {
		this->pos = pos;
		this->path = path;
		this->n = n;
		this->speed = speed;
		counter = speed;

		texs = new Texture[n];
		for (int i = 0; i < n; i++) {
			texs[i].loadFromFile(path + char(i+48) +".png");
		}

		scale.x = 1;
		scale.y = 1;

		anim = Sprite(texs[0]);
		anim.setPosition(pos);
		anim.setScale(scale);
	}

	void Update() {
		if (finish) {
			return;
		}

		counter--;

		if (counter == 0) {
			counter = speed;
			current++;
			if (current == n) {
				finish = true;
				return;
			}

			anim = Sprite(texs[current]);
			anim.setPosition(pos);
			anim.setScale(scale);
		}
	}

	void SetScale(Vector2f scale) {
		this->scale = scale;
	}
	
	void SetPosition(Vector2f pos) {
		this->pos = pos;
	}

	void Render(RenderTarget& target) {
		target.draw(anim);
	}

	bool Ended()const {
		return finish;
	}

	void Reset() {
		current = 0;
		counter = speed;
		finish = false;
	}

	~Animator() {
		delete[] texs;
	}
};
