#pragma once

#include <vector>
#include "io.h"
#include <iostream>
#include <sstream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>



using namespace sf;
using namespace std;

class Game
{
private:
	//*클래스들*
	RenderWindow *Window;
	Event Event;

	// Player
	CircleShape Player;

	// Enemy
	RectangleShape Enemy;
	vector<RectangleShape> EnemyArray;

	// Font
	Font Font;

	// Text
	Text PointText;
	Text GameOverText;

	bool GameOverState;

	//*변수들*
	int Enemymax;
	float IntervalMax;
	float IntervalStart;

	// Point
	int Point;


public:
	// *게임루프*
	// Start up(세팅)
	Game();
	void InitWindow();
	void InitWindowPointer();
	// Update(반복실행)
	const bool Running()const;
	void EventHandler();
	void Update();
	// Render
	void Render();
	// Shut Down
	~Game();
	void DeleteWindow();

	// *게임 구성요소(Element)*
	// Player
	void InitPlayer();
	void UpdatePlayer();

	// Enemy
	void InitEnemy();
	void InitSpwan();
	void SpawnEnemy();
	void UpdateEnemy();

	// Collision Check(충돌확인)
	void CollisionCheck();

	// Font
	void InitFont();

	// Text
	void InitPointText();
	void UpdatePointText();
	void InitGameOverText();
	void PrintGameOverText();
};

