#pragma once
#include "defs.tpp"
#include <cstdint>


   
 struct Win {
 
 
   
      void test();
      
        HINSTANCE inst=hInst();
        HWND  window =init();
        bool min=false;
        uint16_t X=width;
        uint16_t Y=height;
      
        auto hInst() -> HINSTANCE;

        auto init() -> HWND;
        [[nodiscard]] auto show(bool a = false) const -> bool;

        static __int64 __stdcall constexpr WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
      
    
  
