#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp> 
#include "Game.h"


int main()
{
    // ���� �� ����(���) -> �ʱⰪ ����
    // Time �� ��� -> �Ź� �����Ҷ����� �ʱⰪ�� �ٸ������� ���
    srand(time(NULL));

    // Start up
    Game Avoid;
    Avoid.InitPlayer();

    // Game Loop
    while (Avoid.Running()) {

    // Update
        Avoid.Update();

    // Render
        Avoid.Render();
        


    }
}

