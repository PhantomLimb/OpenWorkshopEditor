#ifndef PREVIEW_BALL_HPP
#define PREVIEW_BALL_HPP

#include <glew.h>
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "EditorFrame.hpp"
#include <vector>
#include "Color.hpp"
#include "RenderCircle.hpp"

class PreviewBall
{
public:
    PreviewBall(float p_x=0, float p_y=0, float p_z=0, float p_radius=0.25, int p_resolution=8);
    void set_outline_width(int p_width);
    void set_size(float p_radius, bool p_recalculate=true);
    void set_resolution(int p_resolution, bool p_recalculate=true);
    void set_position(float p_x, float p_y, float p_z, bool p_recalculate=true);
    Vertex & get_position();
    void set_ball_color(Color & p_color);
    void set_outline_color(Color & p_color);
    void draw(EditorFrame* p_frame);
    ~PreviewBall();
private:
    RenderCircle ball;
    RenderCircle outline;
    float outline_width;
};

#endif // PREVIEW_BALL_HPP
