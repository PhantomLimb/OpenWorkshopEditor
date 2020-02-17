#include "EditorApp.hpp"
#include "LnzLoader.hpp"
#include "Util.hpp"
#include <iostream> 
#include <sstream> 
#include "LnzBall.hpp"
#include "PreviewBall.hpp"
#include "AnimationLoader.hpp"

LnzLoader::LnzLoader()
{
}

LnzLoader::~LnzLoader()
{
}

void LnzLoader::load(string p_text)
{
    //load positions from animation
    for (int i = 0; i<AnimationLoader::animations[0].frames[0].ball_positions.size(); i++)
    {
        Vertex anim_vertex = AnimationLoader::animations[0].frames[0].ball_positions[i];
        if (key_ballz.count(i) == 0)
        { 
            key_ballz[i] = new LnzKeyBall(i, anim_vertex.x, anim_vertex.y, anim_vertex.z);
        }
    }
    unsigned int last_delim = 0;
    
    unsigned int current_ball_number = 0;
    vector<string> lines;
    while (last_delim != string::npos)
    {
        unsigned int current_delim = p_text.find("\r\n", last_delim+1);
        if (current_delim != string::npos)
        {
            lines.push_back( p_text.substr(last_delim, current_delim-last_delim) );
        }
        last_delim = current_delim;
    }
    string current_header = "";
    unsigned int line_of_section = 0;
    for (int i = 0; i<lines.size(); i++)
    {
        // strip comments
        unsigned int comment_pos = lines[i].find(";");
        if (comment_pos != string::npos)
        {
            lines[i] = lines[i].substr(0, comment_pos);
        }
        
        if (lines[i].find("[") != string::npos && lines[i].find("]") != string::npos) // it's a header
        {
            current_ball_number = 0;
            current_header = lines[i].substr(lines[i].find("["), lines[i].find("]"));
            printf("current_header = %s \n", current_header.c_str());
            line_of_section = 0;
        }
        else if (lines[i].length() <= 2)
        {
        }
        else  //its not a header so lets read that data!
        {
            lines[i] = Util::string_strip(lines[i], "\t");
            lines[i] = Util::string_strip(lines[i], " ");
            if (lines[i].size()>0)
            {
                line_of_section++;
            }
            if (current_header == "[Default Linez File]")
            {
            }
            if (current_header == "[Omissions]")
            {
                unsigned int omitted_ball = Util::string_to_uint(lines[i]);
                omissions[omitted_ball] = true;
            }
            if (current_header == "[Ballz Info]")
            {
                vector<string> numbers;
                Util::string_split(lines[i], ",", numbers);
                int size_diff = Util::string_to_int(numbers[5]);
                unsigned int ball_number = line_of_section;
                if (key_ballz.count(ball_number) > 0)
                {
                    printf("Set size of ball %u to %i\n", ball_number, size_diff);
                    key_ballz[ball_number]->size_diff = size_diff;
                }
            }
            if (current_header == "[Move]")
            {
                
                vector<string> numbers;
                Util::string_split(lines[i], ",", numbers);
                unsigned int ball_number = Util::string_to_uint(numbers[0]);
                printf("Ball number: %u \n", ball_number);
                int ball_x = Util::string_to_int(numbers[1]);
                printf("Ball x: %d \n", ball_x);
                int ball_y = Util::string_to_int(numbers[2]);
                printf("Ball y: %d \n", ball_y);
                int ball_z = Util::string_to_int(numbers[3]);
                printf("Ball z: %d \n", ball_z);
                if (key_ballz.count(ball_number) == 0)
                {
                    key_ballz[ball_number] = new LnzKeyBall(ball_number, ball_x, ball_y, ball_z);
                }
                else 
                {
                    key_ballz[ball_number]->x += ball_x;
                    key_ballz[ball_number]->y += ball_y;
                    key_ballz[ball_number]->z += ball_z;
                }
            }
            if (current_header == "[Ballz Info]")
            {
                lines[i]=Util::string_strip(lines[i], "\t");
                lines[i]=Util::string_strip(lines[i], " ");
                
                vector<string> numbers;
                Util::string_split(lines[i], ",", numbers);
                int ball_color = Util::string_to_uint(numbers[0]);
                int outline_color = Util::string_to_uint(numbers[1]);
                if (key_ballz.count(current_ball_number) > 0)
                {
                    key_ballz[current_ball_number]->ball_color = ball_color;
                    key_ballz[current_ball_number]->outline_color = outline_color;
                }
                current_ball_number++;
            }
        }
        printf("Line %u: %s \n", i, lines[i].c_str());
    }
    // turn key ballz into previewballs
    for (map<unsigned int, LnzKeyBall*>::iterator it=key_ballz.begin(); it!=key_ballz.end(); it++)
    {
        printf("SIZE DIFFERENCE: %i \n", it->second->size_diff);
        unsigned int base_size = 0;
        if (it->first < AnimationLoader::ball_sizes.size())
        {
            base_size = AnimationLoader::ball_sizes[it->first];
            printf("BASE_SIZE for BALL %u: %u \n", it->first, base_size);
        }
        it->second->preview_ball = new PreviewBall(it->second->x, it->second->y, it->second->z, base_size+(it->second->size_diff/2));
        printf("MADE PREVIEWBALL FOR for BALL %u\n", it->first);
        if (AnimationLoader::animations[0].frames[0].ball_positions.count(it->first) == 1)
        {
            Vertex anim_vertex = AnimationLoader::animations[0].frames[0].ball_positions[it->first];
            anim_vertex = anim_vertex + it->second->preview_ball->get_position();
            it->second->preview_ball->set_position(anim_vertex.x, anim_vertex.y, anim_vertex.z, true);
        }
        //printf("PREVIEWBALL ADDED \n");
        if (omissions.count(it->first) == 1 && omissions[it->first] == true)
        {
            it->second->preview_ball->set_omitted(true);
            printf("OMITTED BALL %i\n", it->first);
        }
    }
}