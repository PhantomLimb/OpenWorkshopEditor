#ifndef LNZ_BALL_HPP
#define LNZ_BALL_HPP

#include "PreviewBall.hpp"

class LnzBall
{
public:
    LnzBall(unsigned int p_id, int p_x, int p_y, int p_z, unsigned int p_ball_color = 0, unsigned int p_outline_color = 0);
    unsigned int ball_id;
    int x;
    int y;
    int z;
    int size_diff;
    unsigned int ball_color;
    unsigned int outline_color;
    PreviewBall * preview_ball;
};

class LnzAddBall : public LnzBall
{
public:
    unsigned int base; // the parent ball's ID (ball_id)
    LnzAddBall(unsigned int p_base, unsigned int p_id, int p_x, int p_y, int p_z, unsigned int p_ball_color = 0, unsigned int p_outline_color = 0);
};

class LnzKeyBall : public LnzBall
{
public:
    LnzKeyBall(unsigned int p_id, int p_x, int p_y, int p_z, unsigned int p_ball_color = 0, unsigned int p_outline_color = 0);
};

#endif // LNZ_BALL_HPP
