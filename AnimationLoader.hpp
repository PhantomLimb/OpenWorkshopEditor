#ifndef ANIMATION_LOADER_HPP
#define ANIMATION_LOADER_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Util.hpp"
#include "Vertex.hpp"

class Frame 
{
public:
    map<int, Vertex> ball_positions;
};

class Animation
{
public:
    vector<Frame> frames;
};

class AnimationLoader
{
public:
    AnimationLoader();
    ~AnimationLoader();
    void load_BHD();
    void load_BDT();
    static vector<Animation> animations;
    static vector<uint16> ball_sizes;
private:
    uint16 animation_count;
    uint16 ball_count;
    vector<int> animation_lengths;
};

#endif // ANIMATION_LOADER_HPP
