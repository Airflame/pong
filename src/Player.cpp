#include "../include/Player.h"
#define W_X 1100
#define W_Y 600

Player::Player( bool arg )
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

void Player::movement( bool argdir, float dt )
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
