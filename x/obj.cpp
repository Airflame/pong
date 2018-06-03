#include "obj.h"
#define W_X 1100
#define W_Y 600

ball::ball()
{
    //ctor
}

ball::ball( int posx, int posy, float argangle )
{
    angle = argangle;
    entity.setRadius( radius );
    entity.setOrigin( radius, radius );
    entity.setFillColor( sf::Color::White );
    entity.setPosition( posx, posy );
    cpos = entity.getPosition();
    physical = true;
}

ball::~ball()
{
    //dtor
}

void ball::yref()
{
    angle = 360 - angle;
}

void ball::xref()
{
    angle = 180 - angle;
}

void ball::movement( float adt )
{
    /////////RUCH/////////////////////////////////////////////////////////////////////////
    dt = adt;
    if( physical and !t )
        entity.move( cos( angle * M_PI/180 ) * pps*dt, sin( angle * M_PI/180 ) * pps*dt );
    cpos = entity.getPosition();
    //////////////////////////////////////////////////////////////////////////////////////


    /////////KOLOR////////////////////////////////////////////////////////////////////////
    if( t > 0 )
        t -= dt;
    else
        t = 0;
    int ci = 255 - 255*(t/2);
    sf::Color clr( ci, ci, ci);
    entity.setFillColor( clr );
    //////////////////////////////////////////////////////////////////////////////////////


    /////////ODBICIA//OD//SCIAN///////////////////////////////////////////////////////////
    if( (cpos.y <= radius or cpos.y >= W_Y - radius) and turn )
    {
        turn = false;
        this->yref();
    }
    if( cpos.y > radius and cpos.y < W_Y - radius )
        turn = true;
    //////////////////////////////////////////////////////////////////////////////////////


    /////////WYLOT////////////////////////////////////////////////////////////////////////
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
    //////////////////////////////////////////////////////////////////////////////////////
}

void ball::acollision( sf::Vector2f apos, sf::Vector2f asize )
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

void ball::bcollision( sf::Vector2f apos, sf::Vector2f asize )
{
    if( cpos.x >= W_X - asize.x and (cpos.y <= apos.y + asize.y/2 and cpos.y >= apos.y - asize.y/2) and turn and physical )
    {
        turn = false;
        this->bend( cpos.y - apos.y, asize.y/2 );
    }
    if( cpos.x > asize.x and cpos.x < W_X - asize.x )
        turn = true;
}

void ball::bend( float dy, float fy )
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

void ball::out( bool first )
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

void ball::recreate( bool first )
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

player::player( bool arg )
{
    first = arg;
    entity.setFillColor( sf::Color::White );
    entity.setSize( esize );
    entity.setOrigin( esize.x/2, esize.y/2 );
    if( first )
    {
        entity.setPosition( esize.x/2, W_Y/2 );
    }
    else
    {
        entity.setPosition( W_X-esize.x/2, W_Y/2 );
    }
    cpos = entity.getPosition();
}

void player::movement( bool argdir, float dt )
{
    int dir;
    if( argdir )
        dir = -1;
    else
        dir = 1;
    if( cpos.y + pps*dt*dir < W_Y - esize.y/2 and cpos.y + pps*dt*dir > esize.y/2 )
    entity.move( 0, pps*dt*dir );
    cpos = entity.getPosition();
}
