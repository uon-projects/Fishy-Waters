#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FileSync.h"

//Compiler Directives
using namespace std;
using namespace sf;

class MapEditor
{

public:
	MapEditor(void);
	~MapEditor(void);
	void setRectanlgeShapes(RectangleShape, RectangleShape, RectangleShape);
	bool rectClicked(RectangleShape, Vector2i);
	bool keyPressed(int&, bool, bool, bool, int, Event, Vector2i&, int[120][200], int[120][200], int[120][200], int, int);
	bool mousePressed(bool, bool&, bool&, int&, int&, Vector2i&, Vector2i&, Vector2i&, int, RectangleShape, RectangleShape[66][8], RectangleShape[12][8], RectangleShape[2][3], RectangleShape[10]);

};

