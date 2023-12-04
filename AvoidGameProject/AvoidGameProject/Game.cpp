#include "Game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Game.h"


using namespace sf;

Game::Game() {
	// ������ �ʱ�ȭ �� ������
	this->InitWindowPointer();
	this->InitWindow();

	// Player �ʱ�ȭ
	this->InitPlayer();
}

Game::~Game() {
	this->DeleteWindow();
}

void Game::InitWindowPointer(){
	// ������ ���� �ʱ�ȭ
	this->Window = nullptr;
}

void Game::InitWindow()
{
	// ������ ���� ����
	this->Window = new RenderWindow(VideoMode(1280, 720), 
		"Avoid Game", Style::Titlebar | Style::Close);

}

void Game::DeleteWindow() {
	// ���� ���� �Ǽ� �߰� �� ��
	// ������ �޸𸮿��� ����
	delete this->Window;
}

const bool Game::Running()const {
	return this->Window->isOpen();
}

void Game::EventHandler() {
	// �̺�Ʈ �߻� ����
	while (this->Window->pollEvent(Event)) {
		// �̺�Ʈ ���� �Ǵ�
		switch (Event.type) {
		case Event::Closed:
			// ����
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

