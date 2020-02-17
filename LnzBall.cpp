#include "LnzBall.hpp"

LnzBall::LnzBall(unsigned int p_id, int p_x, int p_y, int p_z, unsigned int p_ball_color, unsigned int p_outline_color)
{
    ball_id = p_id;
    x = p_x;
    y = p_y;
    z = p_z;
    ball_color = p_ball_color;
    outline_color = p_outline_color;
    size_diff = 0;
}

LnzAddBall::LnzAddBall(unsigned int p_base, unsigned int p_id, int p_x, int p_y, int p_z, unsigned int p_ball_color, unsigned int p_outline_color) : 
    LnzBall(p_id, p_x, p_y, p_z, p_ball_color, p_outline_color)
{
    base = p_base;
}

LnzKeyBall::LnzKeyBall(unsigned int p_id, int p_x, int p_y, int p_z, unsigned int p_ball_color, unsigned int p_outline_color) : 
    LnzBall(p_id, p_x, p_y, p_z, p_ball_color, p_outline_color)
{
}
