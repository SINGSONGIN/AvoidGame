#include "Game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Game.h"


using namespace sf;

Game::Game() {
	// 윈도우 초기화 및 생성자
	this->InitWindowPointer();
	this->InitWindow();

	// Player 초기화
	this->InitPlayer();
}

Game::~Game() {
	this->DeleteWindow();
}

void Game::InitWindowPointer(){
	// 포인터 변수 초기화
	this->Window = nullptr;
}

void Game::InitWindow()
{
	// 윈도우 동적 생성
	this->Window = new RenderWindow(VideoMode(1280, 720), 
		"Avoid Game", Style::Titlebar | Style::Close);

}

void Game::DeleteWindow() {
	// 동적 생성 되서 추가 된 것
	// 윈도우 메모리에서 제거
	delete this->Window;
}

const bool Game::Running()const {
	return this->Window->isOpen();
}

void Game::EventHandler() {
	// 이벤트 발생 감지
	while (this->Window->pollEvent(Event)) {
		// 이벤트 종류 판단
		switch (Event.type) {
		case Event::Closed:
			// 동작
			this->Window->close();
			break;
		case Event::KeyPressed:
			if (Event.key.code == Keyboard::Escape)this->Window->close();
			break;
		}
	}
}

void Game::Render() 
	{
	// clear
	this->Window->clear(Color(50, 50, 50, 255));
	// Draw
	this->Window->draw(this->Player);
	// display
	this->Window->display();
	}

// Player
void Game::InitPlayer() {
	this->Player.setRadius(50.0f);
	this->Player.setFillColor(Color(255, 0, 0, 255));
	this->Player.setPosition(100, 100);
}

