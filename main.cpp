#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "include/Ball.h"
#include "include/Player.h"
#define W_X 1100
#define W_Y 600
using namespace std;

int main()
{
    sf::Clock clock;
    float dt = 0;

    Ball o(300, 300, 0);
    Player a( true );
    Player b( false );

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(W_X, W_Y), "Pong", sf::Style::Default, settings);
    window.setFramerateLimit(120);
    bool wfocus = true;

    sf::RectangleShape line;
    line.setSize( sf::Vector2f(10, W_Y) );
    line.setOrigin( 5, W_Y/2 );
    line.setPosition( W_X/2, W_Y/2 );
    sf::Color c_line( 50, 50, 50 );
    line.setFillColor( c_line );

    sf::Text t_apts;
    sf::Text t_bpts;
    string s_apts;
    string s_bpts;
    sf::Font font;
    font.loadFromFile("res/font.ttf");
    t_apts.setFont(font);
    t_bpts.setFont(font);
    t_apts.setCharacterSize(60);
    t_bpts.setCharacterSize(60);
    t_apts.setColor(sf::Color::White);
    t_bpts.setColor(sf::Color::White);
    sf::Vector2i i_tasize;
    sf::Vector2i i_tbsize;

    while (window.isOpen())
    {
        ostringstream ss_a;
        ostringstream ss_b;
        ss_a << o.apts;
        ss_b << o.bpts;
        s_apts = ss_a.str();
        s_bpts = ss_b.str();
        t_apts.setString( s_apts );
        t_bpts.setString( s_bpts );
        t_apts.setPosition( W_X/8, 10 );
        t_bpts.setPosition( 7*W_X/8 - t_bpts.getScale().x, 10);

        window.clear(sf::Color::Black);
        window.draw( line );
        window.draw( o.entity );
        window.draw( a.entity );
        window.draw( b.entity );
        window.draw( t_apts );
        window.draw( t_bpts );

        if( wfocus )
        {
            o.movement( dt );
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                a.movement( true, dt );
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                a.movement( false, dt );
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                b.movement( true, dt );
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                b.movement( false, dt );
            }
            o.acollision(a.cpos, a.esize);
            o.bcollision(b.cpos, b.esize);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::GainedFocus )
                wfocus = true;
            if (event.type == sf::Event::LostFocus )
                wfocus = false;
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
        dt = clock.restart().asSeconds();
    }

    return 0;
}
