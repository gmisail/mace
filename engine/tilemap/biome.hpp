#ifndef BIOME
#define BIOME

#include <string>

struct Biome 
{
    std::string tiles;
    std::string name;
    float lowerHeight;
    float upperHeight;
    /*
        add vegetation and stuff, like a list of ranges in which they will occur
    */
};

#endif