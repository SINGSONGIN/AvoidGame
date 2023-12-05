#include "Game.h"

// Start up(세팅)
Game::Game() {
	// 윈도우 초기화 및 생성자
	this->InitWindowPointer();
	this->InitWindow();

	// Player 초기화
	this->InitPlayer();

	// Enemy 초기화
	this->InitEnemy();
	this->InitSpwan();

	// Point 초기화
	this->Point = 0;

	// Font 초기화
	this->InitFont();

	// Text 초기화
	this->InitPointText();

	// Game Over State 초기화
	this->GameOverState = false;

	// Game Over Text 초기화
	this->InitGameOverText();

}

void Game::InitWindowPointer(){
	// 포인터 변수 초기화
	this->Window = nullptr;
}

void Game::InitWindow()
{
	// 윈도우 동적 생성
	this->Window = new RenderWindow(VideoMode(640, 720), 
		"Avoid Game", Style::Titlebar | Style::Close);
	// 일정하게 반복 실행 해주는 기능
	this->Window->setFramerateLimit(60);
}

// Update(반복실행)
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
	
	// display(필수로 맨마지막이여야됨)
	this->Window->display();
	}

// Shut Down
Game::~Game() {
	this->DeleteWindow();
}

void Game::DeleteWindow() {
	// 동적 생성 되서 추가 된 것
	// 윈도우 메모리에서 제거
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
	// 키가 눌렸는지 계속 체크하는것(반복실행), 이벤트 감지 필요없음
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		//플레이어에 이동속도 설정
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
	// 위치값 불규칙하게 설정
	this->Enemy.setPosition(static_cast<float>(rand()%640), 0.0f);
	// Enemy를 vector함수,배열을 이용해서 많이 생성하게하는 함수
	this->EnemyArray.push_back(this->Enemy);
}

void Game::UpdateEnemy() {
	// Enemy Maximum 갯수
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

	// Enemy들 이동속도 조절
	for(int i=0;i<this->EnemyArray.size();i++){
		this->EnemyArray[i].move(0.0f, 12.5f);

	}

	for (int i = 0; i < this->EnemyArray.size(); i++) {
		// Window 바깥으로 벗어나는 Enemy 삭제하는법
		if (this->EnemyArray[i].getPosition().y
			>= this->Window->getSize().y) {
			this->EnemyArray.erase(this->EnemyArray.begin()+i);
			// 삭제되는 Enemy 개수를 점수로 만듬
			Point++;
		}
	}
}

// Collision Check(충돌확인)
void Game::CollisionCheck() {
	for (int i = 0; i < EnemyArray.size(); i++) {
		if (this->Player.getGlobalBounds().intersects
		(this->EnemyArray[i].getGlobalBounds())) {
		// 충돌(intersect)하면 true/게임종료
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








