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
	//*Ŭ������*
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

	//*������*
	int Enemymax;
	float IntervalMax;
	float IntervalStart;

	// Point
	int Point;


public:
	// *���ӷ���*
	// Start up(����)
	Game();
	void InitWindow();
	void InitWindowPointer();
	// Update(�ݺ�����)
	const bool Running()const;
	void EventHandler();
	void Update();
	// Render
	void Render();
	// Shut Down
	~Game();
	void DeleteWindow();

	// *���� �������(Element)*
	// Player
	void InitPlayer();
	void UpdatePlayer();

	// Enemy
	void InitEnemy();
	void InitSpwan();
	void SpawnEnemy();
	void UpdateEnemy();

	// Collision Check(�浹Ȯ��)
	void CollisionCheck();

	// Font
	void InitFont();

	// Text
	void InitPointText();
	void UpdatePointText();
	void InitGameOverText();
	void PrintGameOverText();
};

