#pragma once
#include "defs.tpp"


#include <array>
#include <bit>
#include <immintrin.h>


constexpr __v32qi aDot={'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
constexpr __v32qi delim={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
constexpr __v32qi png={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','.','p','n','g'};
constexpr uint64_t m256Size =sizeof(__m256i);

//Less type restrictive form of _mm_load_si256
//vmovdqa requires min 32 bit alignment (to count as an aligned load, otherwise may regress to unaligned load i.e. vmovdqu))

VEC_CALL(__m256i) constexpr auto vmovdqu(auto P) noexcept
{
  struct __loadu_epi8 {
    __m256i __v;
  } __attribute__((__packed__, __may_alias__));
  auto v = (std::bit_cast<const struct __loadu_epi8*>(P))->__v;

  
  return v;
};



/*
  Experimental class as an excuse to mess around with SIMD/vectorised substring operations (That might be faster than std::stringView::find())
  Not safe for serious use due to various unsafe memory algnment issues though abusing (posibly unbounded) pointer arithmetic (Which is necessary to handle specific offsets for vector register loading correctly)
  
  Somehow can handle > 16 char string_views without crashing or corrupting memory
  Consistently fails Address Sanitiser (Global-Buffer-Overflow), but passes Undefined-Behaviour Sanitiser
*/
class [[gnu::aligned(m256Size)]] vec_u8string_view
{
   public: __v32qi _a=_mm256_undefined_si256();


    constexpr explicit(true) vec_u8string_view(auto sv, bool front=true) noexcept :
              _a(vmovdqu(front?sv.cbegin():sv.cend()-m256Size))
              {};

    
    auto operator == (const vec_u8string_view & ext) const noexcept -> bool {return std::bit_cast<bool>(static_cast<bool>(_mm256_testc_si256(this->_a, ext._a)));}
   [[nodiscard]] auto getExtensionfromSubString() const -> __m256i;
    // auto stringToVecView(std::string_view) -> __v32qu;
    static inline auto initHelper(auto ext) -> vec_u8string_view;
    [[gnu::pure]] auto begin()-> std::array<char, 32ULL>;
    void delimAlign();
};

//Very ugly workaround to fix Character parsing Memory alignment issues if the length is greater than 32 Chars
auto vec_u8string_view::initHelper(auto ext) -> vec_u8string_view
{
     return vec_u8string_view{ext};
}