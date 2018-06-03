#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

class Ball
{
public:
    Ball( int, int, float );
    void xref();
    void yref();
    void movement( float );
    void acollision( sf::Vector2f, sf::Vector2f );
    void bcollision( sf::Vector2f, sf::Vector2f );
    void bend( float, float );
    void out( bool );
    void recreate( bool );

    int apts = 0;
    int bpts = 0;
    float dt;
    sf::CircleShape entity;
    sf::Vector2f cpos;
    int radius = 10;
    float angle;
    int pps = 500;
    bool turn;
    bool physical;
    float t = 0;
};
