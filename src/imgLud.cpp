#include <cstdint>
#define STB_IMAGE_IMPLEMENTATION
#include "imgLud.hpp"
#include <stb_image.h>


static void convBGRtoRGB(stbi__png &p)
{
    {
        stbi__uint32 i, pixel_count = p.s->img_x * p.s->img_y;
        stbi_uc *pi = p.out;

         // convert bgr to rgb
        for (uint32_t i=0; i < p.s->img_x * p.s->img_y; ++i) 
        {
            stbi_uc t = pi[0];
            pi[0] = pi[2];
            pi[2] = t;
            pi += 4;
        }
   }
}


[[gnu::pure]] auto tstA::loadImg(FILE &F, int &x, int&y, int&cnls) -> stbi_uc*
{

   //     unsigned char *result;
   // stbi__context s;
   // stbi__start_file(&s,&f);
   // stbi__result_info ri;
   // stbi__png p;
   // p.s = &s;
   return (stbi_load_from_file(&F, &x,&y,&cnls,STBI_rgb_alpha));
}

void tstA::freeImg(stbi_uc *limg)
{
    stbi_image_free(limg);
}