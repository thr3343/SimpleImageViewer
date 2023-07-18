#include "vec_u8string_view.hpp"
#include <array>
#include <immintrin.h>

constexpr auto si128Toint128(__m128i ext) -> __int128
{
  return std::bit_cast<__int128>(ext);
}




// auto vec_u8string_view::vecToStringView(__v16qi const & _a) -> std::string_view
// {

//   auto strView=std::string_view{std::bit_cast<const char*>(_a[1])+15, 16};
//   return strView;
// }


//use string_view to avoid unnessacery heap alloc
auto vec_u8string_view::getExtensionfromSubString() const -> __m256i
{
    const auto extOffset= _tzcnt_u64(_mm256_movemask_epi8(_mm256_cmpeq_epi8(_a,aDot))); //Extension Offset i.e. occurrance of "."
    __v32qu ax=vmovdqu(std::bit_cast<__m256i*>(this+extOffset));
    return ax;
    
}

constexpr unsigned __int128 UINT128_MIN = __int128{};
constexpr unsigned __int128 UINT128_MAX = ~__int128{};
using v2qu [[gnu::vector_size(32)]] =  unsigned __int128;

constexpr v2qu hlfVec{UINT128_MAX, 0};
constexpr v2qu hlfVe1c{0, UINT128_MAX};

__vectorcall __m256i setHalf(__m128i x)
{
  return {0, x[1]};
}

[[gnu::pure]] __vectorcall __m256i mm256_bitshift_left(__v4du x, unsigned int count)
{
  __m256i carry = x<< (count&127u);
  return  (carry&hlfVe1c) ? : _mm256_srli_si256(carry, m256Size);  
}

// __vectorcall __m128i mm_bitshift_left(__m128i x, unsigned int count)
// {
//   __m128i carry = _mm_slli_epi64(x, count&63u);
//   return  _mm_slli_si128((count >= 63u) ? carry:_mm_srli_si128(carry, 8u), 8u);  
// }

void vec_u8string_view::delimAlign()
{
  const auto extOffset= _tzcnt_u64(_mm256_movemask_epi8(_a==delim));
  // __builtin_assume(extOffset<=127);
  __builtin_assume(extOffset<=31);


  auto x = _mm256_srli_si256(_a, 1);
  _a = mm256_bitshift_left(_a, (extOffset)*8);
   
}


[[gnu::pure]] auto vec_u8string_view::begin() -> std::array<char, 32ULL>
{
  
  return std::to_array({
    _a[0], _a[1], _a[2], _a[3], _a[4], _a[5], _a[6], _a[7],
    _a[8], _a[9], _a[10], _a[11], _a[12], _a[13], _a[14], _a[15],
    _a[16], _a[17], _a[18], _a[19], _a[20], _a[21], _a[22], _a[23],
    _a[24], _a[25], _a[26], _a[27], _a[28], _a[29], _a[30], _a[31]});

  }