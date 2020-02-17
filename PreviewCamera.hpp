#ifndef PREVIEW_CAMERA_HPP
#define PREVIEW_CAMERA_HPP

#include "Vertex.hpp"

class PreviewCamera
{
public:
    static PreviewCamera * get();
    void set_position(Vertex p_new_center);
    Vertex get_position();
    float get_zoom();
    void set_zoom(float p_zoom);
private:
    ~PreviewCamera();
    PreviewCamera();
    Vertex center;
    float zoom;
    static PreviewCamera * instance;
};

#endif // PREVIEW_CAMERA_HPP
