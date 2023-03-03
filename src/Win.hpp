#pragma once
#include "defs.tpp"
#include <cstdint>




  
 struct Win {
 
 
   
      void test();
      
        HINSTANCE inst=hInst();
        GLFWwindow*  window =init();
        HWND hwnd = nInit();
        bool min=false;
        uint16_t X=width;
        uint16_t Y=height;
      
        auto hInst() -> HINSTANCE;

        auto init() -> GLFWwindow*;
        [[nodiscard]] auto show(bool a = false) const -> bool;
        auto nInit() -> HWND;

       
};
      
    
  
