#include "AnimationLoader.hpp"

BhdLoader::BhdLoader()
{
}

BhdLoader::~BhdLoader()
{
}

void BhdLoader::load_BHD()
{
    fstream fs;
    fs.open("resources/DOG.bhd", fstream::in | fstream::binary);
    fs.seekg(0);
    uint16 frames_offset = Util::read_uint16(fs);
    uint16 unk1 = Util::read_uint16(fs);
    uint16 bhd_version = Util::read_uint16(fs);
    uint16 ball_count = Util::read_uint16(fs);
    // unknown array of 30 uint8s
    for (int i=0; i<30; i++)
    {
        Util::read_uint8(fs);
    }
    vector<uint16> ball_sizes;
    for (int i=0; i<ball_count; i++)
    {
        ball_sizes.push_back(Util::read_uint16(fs));
    }
    uint16 animation_count = Util::read_uint16(fs);
    vector<uint16> animation_end_offsets;
    for (int i=0; i<animation_count; i++)
    {
        animation_end_offsets.push_back(Util::read_uint16(fs));
    }
    // load each BDT
    for (int i=0; i<animation_count; i++)
    {
        uint32 file_length = Util::read_uint32(fs);
        uint16 bht_version = Util::read_uint16(fs);
        //read copyright string
        string copyright_string = Util::read_string(fs, true);
        //calculate the number of frames
        vector<int> animation_frame_counts;
        int last_end_offset = 0;
        for (int j=0; j<animation_end_offsets.size(); j++)
        {
            animation_frame_counts.push_back(animation_end_offsets[j]-last_end_offset);
            last_end_offset = animation_end_offsets[j];
            printf("Detected %u frame animation.\n", animation_frame_counts[animation_frame_counts.size()]);
        }
    }
}


void BhdLoader::load_BDT()
{
    fstream fs;
    fs.open("resources/DOG0.bdt", fstream::in | fstream::binary);
    fs.seekg(0);
}