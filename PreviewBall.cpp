#include "PreviewBall.hpp"
#include <cmath>
#include "EditorGLCanvas.hpp"

#define PI 3.14159265

wxDECLARE_APP(EditorApp);

PreviewBall::PreviewBall(float p_x, float p_y, float p_z, float p_radius, int p_resolution)
{
    set_position(p_x, p_y, p_z, false);
    set_size(p_radius, false);
    set_outline_width(2);
    set_resolution(p_resolution);
}

void PreviewBall::set_position(float p_x, float p_y, float p_z, bool p_recalculate)
{
    ball.set_position(p_x, p_y, p_z, p_recalculate);
    outline.set_position(p_x, p_y, p_z, p_recalculate);
}

void PreviewBall::set_resolution(int p_resolution, bool p_recalculate)
{
    ball.set_resolution(p_resolution, p_recalculate);
    outline.set_resolution(p_resolution, p_recalculate);
}

void PreviewBall::set_size(float p_radius, bool p_recalculate)
{
    ball.set_size(p_radius, p_recalculate);
    set_outline_width(outline_width);
}

Vertex & PreviewBall::get_position()
{
    return ball.get_position();
}

void PreviewBall::set_ball_color(Color & p_color)
{
    ball.set_color(p_color);
}

void PreviewBall::set_outline_color(Color & p_color)
{
    outline.set_color(p_color);
}

void PreviewBall::draw(EditorFrame* p_frame)
{
    outline.draw(p_frame);
    ball.draw(p_frame);
}

void PreviewBall::set_outline_width(int p_width)
{
    outline_width = p_width;
    int w=0;
    int h=0;
    wxGetApp().editor_frame->GetSize(&w,&h);
    outline.set_size(ball.get_size()+ ((2*outline_width))/h );
}

PreviewBall::~PreviewBall()
{
}

