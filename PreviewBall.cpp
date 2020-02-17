#include "PreviewBall.hpp"
#include <cmath>
#include "EditorGLCanvas.hpp"
#include "PreviewCamera.hpp"

#define PI 3.14159265

wxDECLARE_APP(EditorApp);

PreviewBall::PreviewBall(float p_x, float p_y, float p_z, float p_radius, int p_resolution)
{
    set_position(p_x, p_y, p_z, false);
    set_size(p_radius, false);
    set_outline_width(2);
    set_resolution(p_resolution);
    Color outline_color(0,0,0,1);
    set_outline_color(outline_color);
    wxGetApp().preview_ballz.push_back(this);
    omitted = false;
}

void PreviewBall::set_position(float p_x, float p_y, float p_z, bool p_recalculate)
{
    float camera_zoom = PreviewCamera::get()->get_zoom();
    Vertex camera_pos = PreviewCamera::get()->get_position();
    ball.set_position((p_x*camera_zoom)+camera_pos.x, (-p_y*camera_zoom)+camera_pos.y, (p_z*camera_zoom)+camera_pos.z, p_recalculate);
    outline.set_position((p_x*camera_zoom)+camera_pos.x, (-p_y*camera_zoom)+camera_pos.y, (p_z*camera_zoom)+camera_pos.z, p_recalculate);
    real_position = Vertex(p_x, p_y, p_z);
}

void PreviewBall::set_resolution(int p_resolution, bool p_recalculate)
{
    ball.set_resolution(p_resolution, p_recalculate);
    outline.set_resolution(p_resolution, p_recalculate);
}

void PreviewBall::set_size(float p_radius, bool p_recalculate)
{
    float camera_zoom = PreviewCamera::get()->get_zoom();
    ball.set_size(p_radius*camera_zoom*0.5, p_recalculate);
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

void PreviewBall::draw()
{
    if (!omitted)
    {
        outline.draw();
        ball.draw();
    }
}

void PreviewBall::set_outline_width(int p_width)
{
    outline_width = p_width;
    int w=0;
    int h=0;
    wxGetApp().editor_frame->GetSize(&w,&h);
    outline.set_size(ball.get_size()+ ((2*outline_width)/h) );
}

PreviewBall::~PreviewBall()
{
}

void PreviewBall::set_omitted(bool p_omit)
{
    omitted = p_omit;
}

bool PreviewBall::get_omitted()
{
    return omitted;
}