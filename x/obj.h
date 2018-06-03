#ifndef OBJ_H
#define OBJ_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <windows.h>

class ball
{
public:
    ball();
    ball( int, int, float );
    virtual ~ball();
    //////////////////////////////////////////////////////////////////////////////////////////////
    void xref();                                   //ODBICIE W POZIOMIE
    void yref();                                   //ODBICIE W PIONIE - NIE U¯YWANE
    void movement( float );                        //RUCH -> WYWOLANIE OUT I RECREATE
    void acollision( sf::Vector2f, sf::Vector2f ); //KOLIZJA Z GRACZEM PO LEWEJ  -> WYWOLANIE BEND
    void bcollision( sf::Vector2f, sf::Vector2f ); //KOLIZJA Z GRACZEM PO PRAWEJ -> WYWOLANIE BEND
    void bend( float, float );                     //ODGIECIE KATA ODBITEJ KULKI
    void out( bool );                              //AKCJA PO WYLOCIE KULKI -> WYWOLANIE RECREATE
    void recreate( bool );                         //RESET POZYCJI KULKI
    //////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////
    int apts = 0;             //PUNKTY GRACZA PO LEWEJ
    int bpts = 0;             //PUNKTY GRACZA PO PRAWEJ
    float dt;                 //CZAS JEDNEJ KLATKI [S]
    ////////////////////////////////////////////////////
    sf::CircleShape entity;   //RYSOWANY OBIEKT
    sf::Vector2f cpos;        //POZYCJA SRODKA
    int radius = 10;          //PROMIEN
    float angle;              //KAT LOTU
    int pps = 500;            //PREDKOSC [PX/S]
    ////////////////////////////////////////////////////
    bool turn;                //MOZLIWOSC ODBICIA
    bool physical;            //REAGOWANIE
    float t = 0;              //LICZNIK DLA RECREATE
    ////////////////////////////////////////////////////
};

class player
{
public:
    player();
    player( bool );
    ///////////////////////////////////////////////////////
    void movement( bool, float );    //RUCH GRACZA W PIONIE
    ///////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////
    sf::RectangleShape entity;                         //RYSOWANY OBIEKT
    sf::Vector2f cpos;                                 //POZYCJA SRODKA
    const sf::Vector2f esize = sf::Vector2f(10, 100);  //WYMIARY GRACZA
    ////////////////////////////////////////////////////////////////////
    int pps = 700;                                     //PREDKOSC [PX/S]
    bool first;                                        //BYCIE PO LEWEJ
    ////////////////////////////////////////////////////////////////////

};

#endif // OBJ_H
