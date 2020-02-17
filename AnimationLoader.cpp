#include "AnimationLoader.hpp"

vector<Animation> AnimationLoader::animations = vector<Animation>();
vector<uint16> AnimationLoader::ball_sizes = vector<uint16>();

AnimationLoader::AnimationLoader()
{
    
}

AnimationLoader::~AnimationLoader()
{
}

void AnimationLoader::load_BHD()
{
    fstream fs;
    fs.open("resources/DOG.bhd", fstream::in | fstream::binary);
    fs.seekg(0);
    uint16 frames_offset = Util::read_uint16(fs);
    uint16 unk1 = Util::read_uint16(fs);
    uint16 bhd_version = Util::read_uint16(fs);
    ball_count = Util::read_uint16(fs);
    // unknown array of 30 uint8s
    for (int i=0; i<30; i++)
    {
        Util::read_uint8(fs);
    }
    for (int i=0; i<ball_count; i++)
    {
        ball_sizes.push_back(Util::read_uint16(fs));
    }
    animation_count = Util::read_uint16(fs);
    printf("Animation Count: %u\n", animation_count);
    vector<uint16> animation_end_offsets;
    for (int i=0; i<animation_count; i++)
    {
        animation_end_offsets.push_back(Util::read_uint16(fs));
    }
    // load each BDT
    int last_end_offset = 0;
    for (int i=0; i<animation_count; i++)
    {
        animation_lengths.push_back(animation_end_offsets[i]-last_end_offset);
        last_end_offset = animation_end_offsets[i];
        printf("Detected %i frame animation.\n", animation_lengths[animation_lengths.size()-1]);
    }
    //fs.seekg(frames_offset);clTabCtrl
    fs.close();
    load_BDT();
}


void AnimationLoader::load_BDT()
{
    animations.push_back(Animation());
    fstream fs;
    fs.open("resources/DOG0.bdt", fstream::in | fstream::binary);
    fs.seekg(0);
    uint32 file_length = Util::read_uint32(fs);
    uint16 bht_version = Util::read_uint16(fs);
    //read copyright string
    string copyright_string = Util::read_string(fs, true);
    //read each frame
    for (int i=0; i<animation_lengths[0]; i++)
    {
        animations.back().frames.push_back(Frame());
        sint16 min_x = Util::read_sint16(fs);
        sint16 min_y = Util::read_sint16(fs);
        sint16 min_z = Util::read_sint16(fs);
        sint16 max_x = Util::read_sint16(fs);
        sint16 max_y = Util::read_sint16(fs);
        sint16 max_z = Util::read_sint16(fs);
        uint16 tag = Util::read_uint16(fs);
        for (int j = 0; j<ball_count; j++)
        {
            sint16 x = Util::read_sint16(fs);
            sint16 y = Util::read_sint16(fs);
            sint16 z = Util::read_sint16(fs);
            uint16 q1 = Util::read_uint16(fs);
            uint16 q2 = Util::read_uint16(fs);
            animations.back().frames.back().ball_positions[j] = (Vertex(x,y,z));
        }
    }
    fs.close();
}