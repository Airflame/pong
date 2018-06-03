#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

class Player
{
public:
    Player();
    Player( bool );
    void movement( bool, float );

    sf::RectangleShape entity;
    sf::Vector2f cpos;
    const sf::Vector2f esize = sf::Vector2f(10, 100);
    int pps = 700;
    bool first;
};
