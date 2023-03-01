#include <cstdint>
#define STB_IMAGE_IMPLEMENTATION
#include "imgLud.hpp"
#include <stb_image.h>



[[gnu::pure]] auto tstA::loadImg(FILE &F, int &x, int&y, int&cnls) -> stbi_uc*
{
   return (stbi_load_from_file(&F, &x,&y,&cnls,STBI_rgb_alpha));
}

void tstA::freeImg(stbi_uc *limg)
{
    stbi_image_free(limg);
}