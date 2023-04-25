#pragma once
#include "defs.tpp"
#include <array>
#include <cstdint>




using IMAGE_DOS_HEADER = struct _IMAGE_DOS_HEADER {
      WORD e_magic;
      WORD e_cblp;
      WORD e_cp;
      WORD e_crlc;
      WORD e_cparhdr;
      WORD e_minalloc;
      WORD e_maxalloc;
      WORD e_ss;
      WORD e_sp;
      WORD e_csum;
      WORD e_ip;
      WORD e_cs;
      WORD e_lfarlc;
      WORD e_ovno;
      std::array<DWORD, 4> e_res;
      WORD e_oemid;
      WORD e_oeminfo;
      std::array<DWORD, 10> e_res2;
      long e_lfanew;
    };


// using QWORD = uint64_t;

extern  constinit const IMAGE_DOS_HEADER   __ImageBase;

const HINSTANCE inst =  std::bit_cast<HINSTANCE>(&__ImageBase);
  
 struct Win {
 
 
   
      void test();
      
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
      
    
  
