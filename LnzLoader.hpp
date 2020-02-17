#ifndef LNZ_LOADER_HPP
#define LNZ_LOADER_HPP

#include <string>
#include <cstdio>
#include <map>
#include "LnzBall.hpp"

using namespace std;

class LnzLoader
{
public:
    LnzLoader();
    ~LnzLoader();
    void load(string p_text);
private:
    string default_linez_file;
    string sounds;
    string little_one;
    int head_rotation_min;
    int head_rotation_max;
    int eyelid_color;
    int normal_pet_scale; 
    int normal_ball_scale;
    int leg_extension_front;
    int leg_extension_back;
    int body_extension;
    int face_extension;
    int ear_extension;
    int head_enlargement;
    map<unsigned int, LnzKeyBall*> key_ballz;
    map<unsigned int, LnzAddBall*> add_ballz;
    map<unsigned int, bool> omissions;
};

#endif // LNZ_LOADER_HPP
