#pragma once
class Candy
{
	int candyType;
public:
	Candy(int x) {
		candyType = x;
	}
	int get_candyType() {
		return candyType;
	}
	void set_candyType(int x) {
		candyType = x;
	}
	~Candy()
	{

	}

};

