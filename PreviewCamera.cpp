#include "PreviewCamera.hpp"

PreviewCamera * PreviewCamera::instance = nullptr;

PreviewCamera * PreviewCamera::get()
{
    if (instance == nullptr)
    {
        instance = new PreviewCamera();
    }
    return instance;
}

PreviewCamera::PreviewCamera()
{
    center = Vertex(0.5, 0.5, 0);
    zoom = 0.005;
}

PreviewCamera::~PreviewCamera()
{
}

void PreviewCamera::set_position(Vertex p_new_center)
{
    center = p_new_center;  
}

Vertex PreviewCamera::get_position()
{
    return center;
}

void PreviewCamera::set_zoom(float p_zoom)
{
    zoom = p_zoom;
}

float PreviewCamera::get_zoom()
{
    return zoom;
}