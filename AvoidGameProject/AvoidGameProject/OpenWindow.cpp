#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;

Event mEvent;

void OpenWindow() {
	RenderWindow Window(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close);
	// 프로그램 종료 되지 않도록
	// 무한루프, 윈도우 창이 떠 있을때 프로그램 종료 되지 않도록

	// 윈도우 창이 떠 있을때 프로그램이 종료 되지 않도록
	while (Window.isOpen()) {
		// 이벤트 발생 감지
		while (Window.pollEvent(mEvent)) {
			// 이벤트 종류 판단
			switch (mEvent.type) {
			case Event::Closed:
				// 동작
				Window.close();
				break;
			case Event::KeyPressed:
				if (mEvent.key.code == Keyboard::Escape)Window.close();
				break;
			}

		}

		// clear
		Window.clear(Color(50,50,50,255));
		// display
		Window.display();

	}
}

/*
	이벤트 : (발생된)사건 
	=> 소프트웨어, 어플리케이션의 상태 변화 : 사용자가 변화시킴

	-> Interface 장치와 관련된 이벤트 : 키보드, 마우스, 터치스크린 등
	  - 키보드 이벤트 : 키 입력(Press), 각각의 키 내용을 if로 구분
	  - 마우스 이벤트 : 클릭(Press / Release), 휠 스크롤, 움직임, 드래그(Press / Move), 더블 클릭
	  - 터치 스클린 : 터치, 스와이프, 핀치,
	-> Interface 장치와 관련 없는 이벤트
	  - 로딩 이벤트 : 데이터나 소프트웨어의 화면 구성 요소가 모두 화면에 띄워지면 발생 되는 이벤트

	이벤트 발생시 이벤트 감지 이후 -> 해당 이벤트에 대한 적절한 동작
	 - Event Listening : 이벤트 감지
	 - Event Handling : 감지 된 이벤트에 대해서 적절한 동작 
	
*/