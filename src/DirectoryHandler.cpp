#include "defs.tpp"
#include "DirectoryHandler.hpp"
#include <immintrin.h>

[[clang::vectorcall]] consteval auto si128Toint128(__m128i ext) -> __int128
{
  return std::bit_cast<__int128>(ext);
}
constexpr __v16qu aDot={'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
constexpr __v16qu aMask={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
constexpr __int128 _png={'.png'};
constexpr __m128i _jpg={'.jpg'};

//Less type restrictive form of _mm_load_si128
//vmovdqa requires min 32 bit alignment (to count as an aligned load, otherwise may regress to unaligned load i.e. vmovdqu))

template<typename aData> requires(sizeof(aData)<=sizeof(__m128i))
VEC_CALL(__m128i) auto vmovdqa(const aData P) noexcept
{
  struct __loadu_epi8 {
    __m128i __v;
  } __attribute__((__packed__, __may_alias__));
  return ((const struct __loadu_epi8*)P)->__v;
}

[[clang::vectorcall]] auto chkExt(__m128i ext) -> bool
{
  return static_cast<bool>(_mm_testc_si128(ext, _png|_jpg)); //cast to bool avoids a xor op when compiled
}




//use string_view to avoid unnessacery heap alloc
[[clang::vectorcall]] auto DirectoryHandler::getExtensionfromSubString(std::string_view a) -> __m128i
{
    const __m128i aa=vmovdqa(a.cend()-(a.length()<15?a.length():15)); //load end of string with a max 15 byte offset

    const auto extOffset= _tzcnt_u32(_mm_movemask_epi8(_mm_cmpeq_epi8(aa,aDot))); //Extension Offset i.e. occurrance of "."
    
    return vmovdqa(a.cbegin()+extOffset);
}