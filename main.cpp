#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>


//compile for linux: g++ *.cpp -lsfml-graphics -lsfml-window -lsfml-system
enum AppMode
{
    Standby,
    Draw
};


std::list<sf::Vector2f> points;
sf::Color p_color(sf::Color::Black);
AppMode current_app_mode = Standby;

void ProcessMouseEvents(sf::Event& e,sf::RenderWindow& w)
{
    if(e.type == sf::Event::MouseButtonReleased){
        current_app_mode = Standby;
    }

    if(e.type == sf::Event::KeyPressed){
        if(e.key.code == sf::Keyboard::Space){
            points.clear();
            current_app_mode = Standby;
        }
    }

    if( e.type == sf::Event::MouseButtonPressed ){
        if(e.mouseButton.button == sf::Mouse::Left){
            current_app_mode = Draw;
                       
        }
    }

    if(e.type == sf::Event::MouseMoved){
        if(current_app_mode == Draw){
            sf::Vector2f p;
            p.x = sf::Mouse::getPosition(w).x;
            p.y = sf::Mouse::getPosition(w).y;
            points.push_back(p);
            
        }
    }
}

void DrawPoints(sf::RenderWindow& w)
{
    for(auto it = points.begin(); it != points.end();++it){
        sf::CircleShape c(6,15);
        c.setPosition(*it);
        c.setFillColor(p_color);
        w.draw(c);
    }
}


int main()
{
    sf::RenderWindow w(sf::VideoMode({800,600}),"Simple Drawer");
    sf::Event e;

    while(w.isOpen())
    {
        w.pollEvent(e);

        if(e.type == sf::Event::Closed){
            w.close();
        }

        if(e.type == sf::Event::Resized){
            sf::FloatRect r({0.0f,0.0f},{(float)e.size.width,(float)e.size.height});
            sf::View v(r);
            w.setView(v);

        }

        ProcessMouseEvents(e,w);
        w.clear(sf::Color::White);
        DrawPoints(w);
        w.display();
    }


}