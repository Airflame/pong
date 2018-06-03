#include "../include/Ball.h"
#define W_X 1100
#define W_Y 600

Ball::Ball( int posx, int posy, float argangle )
{
    angle = argangle;
    entity.setRadius( radius );
    entity.setOrigin( radius, radius );
    entity.setFillColor( sf::Color::White );
    entity.setPosition( posx, posy );
    cpos = entity.getPosition();
    physical = true;
}

void Ball::yref()
{
    angle = 360 - angle;
}

void Ball::xref()
{
    angle = 180 - angle;
}

void Ball::movement( float adt )
{
    dt = adt;
    if( physical and !t )
        entity.move( cos( angle * M_PI/180 ) * pps*dt, sin( angle * M_PI/180 ) * pps*dt );
    cpos = entity.getPosition();

    if( t > 0 )
        t -= dt;
    else
        t = 0;
    int ci = 255 - 255*(t/2);
    sf::Color clr( ci, ci, ci);
    entity.setFillColor( clr );

    if( (cpos.y <= radius or cpos.y >= W_Y - radius) and turn )
    {
        turn = false;
        this->yref();
    }
    if( cpos.y > radius and cpos.y < W_Y - radius )
        turn = true;

    if( cpos.x > W_X and physical )
    {
        physical = false;
        this->out( true );
    }
    if( cpos.x < 0 and physical )
    {
        physical = false;
        this->out( false );
    }
}

void Ball::acollision( sf::Vector2f apos, sf::Vector2f asize )
{
    if( cpos.x <= asize.x and (cpos.y <= apos.y + asize.y/2 and cpos.y >= apos.y - asize.y/2) and turn and physical )
    {
        turn = false;
        this->bend( cpos.y - apos.y, asize.y/2 );
    }
    else
    if( cpos.x > asize.x and cpos.x < W_X - asize.x )
        turn = true;
}

void Ball::bcollision( sf::Vector2f apos, sf::Vector2f asize )
{
    if( cpos.x >= W_X - asize.x and (cpos.y <= apos.y + asize.y/2 and cpos.y >= apos.y - asize.y/2) and turn and physical )
    {
        turn = false;
        this->bend( cpos.y - apos.y, asize.y/2 );
    }
    if( cpos.x > asize.x and cpos.x < W_X - asize.x )
        turn = true;
}

void Ball::bend( float dy, float fy )
{
    float bendindex = dy/fy;
    if( cpos.x > W_X/2)
    {
        angle = 180 - 70*bendindex;
    }
    if( cpos.x < W_X/2 )
    {
        angle = 0 + 70*bendindex;
        if( angle < 0 )
            angle = 360 + angle;
    }
    pps += 20;
}

void Ball::out( bool first )
{
    if( first )
    {
        apts++;
        this->recreate( true );
    }
    else
    {
        bpts++;
        this->recreate( false );
    }
}

void Ball::recreate( bool first )
{
    entity.setPosition( W_X/2, W_Y/2 );
    cpos = entity.getPosition();
    pps = 500;
    t = 2;
    physical = true;
    if( first )
        angle = 180;
    else
        angle = 0;
}
