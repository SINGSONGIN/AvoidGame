#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;

Event mEvent;

void OpenWindow() {
	RenderWindow Window(VideoMode(1280, 720), "Avoid Game", Style::Titlebar | Style::Close);
	// ���α׷� ���� ���� �ʵ���
	// ���ѷ���, ������ â�� �� ������ ���α׷� ���� ���� �ʵ���

	// ������ â�� �� ������ ���α׷��� ���� ���� �ʵ���
	while (Window.isOpen()) {
		// �̺�Ʈ �߻� ����
		while (Window.pollEvent(mEvent)) {
			// �̺�Ʈ ���� �Ǵ�
			switch (mEvent.type) {
			case Event::Closed:
				// ����
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
	�̺�Ʈ : (�߻���)��� 
	=> ����Ʈ����, ���ø����̼��� ���� ��ȭ : ����ڰ� ��ȭ��Ŵ

	-> Interface ��ġ�� ���õ� �̺�Ʈ : Ű����, ���콺, ��ġ��ũ�� ��
	  - Ű���� �̺�Ʈ : Ű �Է�(Press), ������ Ű ������ if�� ����
	  - ���콺 �̺�Ʈ : Ŭ��(Press / Release), �� ��ũ��, ������, �巡��(Press / Move), ���� Ŭ��
	  - ��ġ ��Ŭ�� : ��ġ, ��������, ��ġ,
	-> Interface ��ġ�� ���� ���� �̺�Ʈ
	  - �ε� �̺�Ʈ : �����ͳ� ����Ʈ������ ȭ�� ���� ��Ұ� ��� ȭ�鿡 ������� �߻� �Ǵ� �̺�Ʈ

	�̺�Ʈ �߻��� �̺�Ʈ ���� ���� -> �ش� �̺�Ʈ�� ���� ������ ����
	 - Event Listening : �̺�Ʈ ����
	 - Event Handling : ���� �� �̺�Ʈ�� ���ؼ� ������ ���� 
	
*/