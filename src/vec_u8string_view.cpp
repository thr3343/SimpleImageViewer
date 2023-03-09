#include "vec_u8string_view.hpp"
#include <array>

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
auto vec_u8string_view::getExtensionfromSubString() const -> __m128i
{
    const auto extOffset= _tzcnt_u64(_mm_movemask_epi8(_mm_cmpeq_epi8(_a,aDot))); //Extension Offset i.e. occurrance of "."
    __v16qu ax=vmovdqu(std::bit_cast<__m128i*>(this+extOffset));
    return ax;
    
}

constexpr __v2du hlfVec{UINT64_MAX, 0};
constexpr __v2du hlfVe1c{0, UINT64_MAX};

__vectorcall __m128i setHalf(__m128i x)
{
  return {0, x[1]};
}

[[gnu::pure]] __vectorcall __v2du mm_bitshift_left(__v2du x, unsigned int count)
{
  __m128i carry = x<< (count&63u);
  return  (carry&hlfVe1c) ? : _mm_srli_si128(carry, 8u);  
}

// __vectorcall __m128i mm_bitshift_left(__m128i x, unsigned int count)
// {
//   __m128i carry = _mm_slli_epi64(x, count&63u);
//   return  _mm_slli_si128((count >= 63u) ? carry:_mm_srli_si128(carry, 8u), 8u);  
// }

void vec_u8string_view::delimAlign()
{
  const auto extOffset= _tzcnt_u64(_mm_movemask_epi8(_mm_cmpeq_epi8(_a,delim)));
  // __builtin_assume(extOffset<=127);
  __builtin_assume(extOffset<=15);


  auto x = _mm_srli_si128(_a, 1);
  _a = mm_bitshift_left(_a, (extOffset)*8);
   
}


[[gnu::pure]] auto vec_u8string_view::begin() -> std::array<char, 16ULL>
{
  
  return std::to_array({
    _a[0],
    _a[1],
    _a[2],
    _a[3],
    _a[4],
    _a[5],
    _a[6],
    _a[7],
    _a[8],
    _a[9],
    _a[10],
    _a[11],
    _a[12],
    _a[13],
    _a[14],
    _a[15]
    });
}