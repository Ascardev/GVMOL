#pragma once

class cAlerta 
{
public:

	static cAlerta* GetInstance() { static cAlerta instance; return &instance; };
	void Init();
	void Draw();

	enum MAT
	{
		BACKGROUND,
	};

private:

	int Mat[1];
};