#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp> 
#include "Game.h"


int main()
{
    // 랜덤 값 세팅(사용) -> 초기값 설정
    // Time 값 사용 -> 매번 실행할때마다 초기값을 다른값으로 사용
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

