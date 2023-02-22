#pragma once
#include "defs.tpp"
#include <bit>
#include <immintrin.h>
#include <string_view>

constexpr __v16qi aDot={'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};

//Less type restrictive form of _mm_load_si128
//vmovdqa requires min 32 bit alignment (to count as an aligned load, otherwise may regress to unaligned load i.e. vmovdqu))

VEC_CALL(__m128i) constexpr auto vmovdqu(auto P) noexcept
{
  struct __loadu_epi8 {
    __m128i __v;
  } __attribute__((__packed__, __may_alias__));
  return (std::bit_cast<const struct __loadu_epi8*>(P))->__v;
};

//Somehow can handle > 16 char string_views without crashing or corrupting memory
//Consistently fails Address Sanitiser (Global-Buffer-Overflow), but passes Undefined-Behaviour Sanitiser
struct vec_u8string_view : std::string_view
{
    __v16qi _a=_mm_undefined_si128();
    auto operator == (const vec_u8string_view & ext) const noexcept -> bool {return std::bit_cast<bool>(static_cast<bool>(_mm_testc_si128(this->_a, ext._a)));}


    constexpr explicit(true) vec_u8string_view(std::string_view sv) noexcept :
              _a(vmovdqu(cbegin())),
              std::string_view{sv.cbegin(), 16}
              {};

    auto getExtensionfromSubString() -> __m128i;
    auto stringToVecView(std::string_view) -> __v16qi;
} __attribute__((aligned(16)));