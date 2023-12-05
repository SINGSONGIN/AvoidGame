#include "Game.h"

// Start up(����)
Game::Game() {
	// ������ �ʱ�ȭ �� ������
	this->InitWindowPointer();
	this->InitWindow();

	// Player �ʱ�ȭ
	this->InitPlayer();

	// Enemy �ʱ�ȭ
	this->InitEnemy();
	this->InitSpwan();

	// Point �ʱ�ȭ
	this->Point = 0;

	// Font �ʱ�ȭ
	this->InitFont();

	// Text �ʱ�ȭ
	this->InitPointText();

	// Game Over State �ʱ�ȭ
	this->GameOverState = false;

	// Game Over Text �ʱ�ȭ
	this->InitGameOverText();

}

void Game::InitWindowPointer(){
	// ������ ���� �ʱ�ȭ
	this->Window = nullptr;
}

void Game::InitWindow()
{
	// ������ ���� ����
	this->Window = new RenderWindow(VideoMode(640, 720), 
		"Avoid Game", Style::Titlebar | Style::Close);
	// �����ϰ� �ݺ� ���� ���ִ� ���
	this->Window->setFramerateLimit(60);
}

// Update(�ݺ�����)
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

void Game::Update(){
	this->EventHandler();

	if (!this->GameOverState) {
		this->UpdatePlayer();
		this->UpdateEnemy();
		this->CollisionCheck();
		this->UpdatePointText();
	}
}

// Render
void Game::Render() 
	{
	// clear
	this->Window->clear(Color(50, 50, 50, 255));
	// Draw Player
	this->Window->draw(this->Player);
	// Draw Enemy
	for (int i = 0; i < this->EnemyArray.size(); i++) {
		this->Window->draw(this->EnemyArray[i]);
	}
	// Draw Text
	this->Window->draw(this->PointText);

	// Draw Game Over Text
	this->Window->draw(this->GameOverText);
	
	// display(�ʼ��� �Ǹ������̿��ߵ�)
	this->Window->display();
	}

// Shut Down
Game::~Game() {
	this->DeleteWindow();
}

void Game::DeleteWindow() {
	// ���� ���� �Ǽ� �߰� �� ��
	// ������ �޸𸮿��� ����
	delete this->Window;
}

// Player
void Game::InitPlayer() {
	this->Player.setRadius(30.0f);
	this->Player.setFillColor(Color(217, 207, 98, 255));
	this->Player.setPosition(
		float(this->Window->getSize().x/2)-30.0f, 
		float(this->Window->getSize().y/2)-30.0f);
}

void Game::UpdatePlayer() {
	// Ű�� ���ȴ��� ��� üũ�ϴ°�(�ݺ�����), �̺�Ʈ ���� �ʿ����
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		//�÷��̾ �̵��ӵ� ����
		this->Player.move(-5.5f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		this->Player.move(5.5f, 0.0f);

	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		this->Player.move(0.0f, -5.5f);

	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		this->Player.move(0.0f, 5.5f);

	}
}

// Enemy
void Game::InitEnemy() {
	this->Enemy.setSize(Vector2f(60.0f,60.0f));
	this->Enemy.setFillColor(Color::Blue);
	this->Enemy.setPosition(100, 100);
}

void Game::InitSpwan() {
	this->Enemymax = 350;
	this->IntervalMax = 8.0f;
	this->IntervalStart = 0.0f;
}

void Game::SpawnEnemy() {
	// ��ġ�� �ұ�Ģ�ϰ� ����
	this->Enemy.setPosition(static_cast<float>(rand()%640), 0.0f);
	// Enemy�� vector�Լ�,�迭�� �̿��ؼ� ���� �����ϰ��ϴ� �Լ�
	this->EnemyArray.push_back(this->Enemy);
}

void Game::UpdateEnemy() {
	// Enemy Maximum ����
	if (this->EnemyArray.size() < this->Enemymax) {
		// Enemy Spawn Interval Delay
		if (this->IntervalMax <= this->IntervalStart) {
			this->SpawnEnemy();
			this->IntervalStart = 0.0f;
		}
		else {
			this->IntervalStart += 1.0f;
		}
	}

	// Enemy�� �̵��ӵ� ����
	for(int i=0;i<this->EnemyArray.size();i++){
		this->EnemyArray[i].move(0.0f, 12.5f);

	}

	for (int i = 0; i < this->EnemyArray.size(); i++) {
		// Window �ٱ����� ����� Enemy �����ϴ¹�
		if (this->EnemyArray[i].getPosition().y
			>= this->Window->getSize().y) {
			this->EnemyArray.erase(this->EnemyArray.begin()+i);
			// �����Ǵ� Enemy ������ ������ ����
			Point++;
		}
	}
}

// Collision Check(�浹Ȯ��)
void Game::CollisionCheck() {
	for (int i = 0; i < EnemyArray.size(); i++) {
		if (this->Player.getGlobalBounds().intersects
		(this->EnemyArray[i].getGlobalBounds())) {
		// �浹(intersect)�ϸ� true/��������
			this->GameOverState = true;
			this->PrintGameOverText();
		}
	}
}

// Font
void Game::InitFont() {
	if (this->Font.loadFromFile("Font/NanumSquareR.ttf")) {
		cout << "Load Complete" << endl;
	}
	else {
		cout << "Load Fail" << endl;
	}
}

// Text
void Game::InitPointText(){
	this->PointText.setFont(this->Font);
	this->PointText.setCharacterSize(30);
	this->PointText.setFillColor(Color::Yellow);
	this->PointText.setPosition(
		this->Window->getSize().x - 150,
		this->Window->getSize().y - 50);
}

void Game::UpdatePointText() {
	stringstream pt;

	pt << "Point : " << Point;

	this->PointText.setString(pt.str());
}

void Game::InitGameOverText() {
	this->GameOverText.setFont(this->Font);
	this->GameOverText.setCharacterSize(100);
	this->GameOverText.setFillColor(Color::White);
	this->GameOverText.setPosition(
		this->Window->getSize().x/2 - 250,
		this->Window->getSize().y/2 - 100);
} 

void Game::PrintGameOverText() {
	stringstream pt;

	pt << "Game Over ! ";

	this->GameOverText.setString(pt.str());
}








