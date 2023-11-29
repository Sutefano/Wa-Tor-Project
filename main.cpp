#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <SFML/Window/Keyboard.hpp>



int main()
{
    int windowX = 200;
    int windowY = 200;


    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Wa-Tor Simulation");
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
            sf::RectangleShape recArray[windowX/2][windowY/2];
            for(int i=0;i<windowX/2;++i){
                for(int k=0;k<windowY/2;++k){//give each one a size, position and color
                    recArray[i][k].setSize(sf::Vector2f(2.f,2.f));
                    recArray[i][k].setPosition(i*2,k*2);//position is top left corner!
                    int id=i*1-+k;
                    if (id%2==0) recArray[i][k].setFillColor(sf::Color::Green);
                    else recArray[i][k].setFillColor(sf::Color::Blue);
                }
            }
            //loop these three lines to draw frames
            window.clear(sf::Color::Black);
            for(int i=0;i<windowX/2;++i){
                for(int k=0;k<windowY/2;++k){
                    window.draw(recArray[i][k]);
                }
            }

            window.display();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
            sf::RectangleShape recArray[windowX/2][windowY/2];
            for(int i=0;i<windowX/2;++i){
                for(int k=0;k<windowY/2;++k){//give each one a size, position and color
                    recArray[i][k].setSize(sf::Vector2f(2.f,2.f));
                    recArray[i][k].setPosition(i*2,k*2);//position is top left corner!
                    int id=i*1-+k;
                    if (id%2==0) recArray[i][k].setFillColor(sf::Color::Blue);
                    else recArray[i][k].setFillColor(sf::Color::Green);
                }
            }
            //loop these three lines to draw frames
            window.clear(sf::Color::Black);
            for(int i=0;i<windowX/2;++i){
                for(int k=0;k<windowY/2;++k){
                    window.draw(recArray[i][k]);
                }
            }

            window.display();
        }
    }

    return 0;

}