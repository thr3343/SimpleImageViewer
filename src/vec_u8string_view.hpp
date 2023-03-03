#pragma once
#include "defs.tpp"

#include <immintrin.h>
#include <string_view>

constexpr __v16qi aDot={'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
constexpr __v16qi png={*".png"};
constexpr uint64_t m128Size =sizeof(__m128i);

//Less type restrictive form of _mm_load_si128
//vmovdqa requires min 32 bit alignment (to count as an aligned load, otherwise may regress to unaligned load i.e. vmovdqu))

VEC_CALL(__m128i) constexpr auto vmovdqu(auto P) noexcept
{
  struct __loadu_epi8 {
    __m128i __v;
  } __attribute__((__packed__, __may_alias__));
  return (std::bit_cast<const struct __loadu_epi8*>(P))->__v;
};



/*
  Experimental class as an excuse to mess around with SIMD/vectorised substring operations (That might be faster than std::stringView::find())
  Not safe for serious use due to various unsafe memory algnment issues though abusing (posibly unbounded) pointer arithmetic (Which is necessary to handle specific offsets for vector register loading correctly)
  
  Somehow can handle > 16 char string_views without crashing or corrupting memory
  Consistently fails Address Sanitiser (Global-Buffer-Overflow), but passes Undefined-Behaviour Sanitiser
*/
class [[gnu::aligned(m128Size)]] vec_u8string_view : public std::string_view 
{
    __v16qu _a=_mm_undefined_si128();


    constexpr explicit(true) vec_u8string_view(std::string_view sv, bool front=true) noexcept :
              _a(vmovdqu(front?sv.cbegin():sv.cend()-m128Size)),
              std::string_view{front?sv.cbegin():sv.cend()-m128Size, m128Size}
              {};

    public:
    auto operator == (const vec_u8string_view & ext) const noexcept -> bool {return std::bit_cast<bool>(static_cast<bool>(_mm_testc_si128(this->_a, ext._a)));}
    auto getExtensionfromSubString() -> __m128i;
    auto stringToVecView(std::string_view) -> __v16qu;
    static inline auto initHelper(std::string_view ext) -> vec_u8string_view;
};

//Very ugly workaround to fix Character parsing Memory alignment issues if the length is greater than 32 Chars
auto vec_u8string_view::initHelper(std::string_view ext) -> vec_u8string_view
{
     return (ext.length()>32)? vec_u8string_view{ext, false}:vec_u8string_view{ext, true};
}
