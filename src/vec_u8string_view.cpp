#include "vec_u8string_view.hpp"
#include <immintrin.h>
#include <string_view>

[[clang::vectorcall]] consteval auto si128Toint128(__m128i ext) -> __int128
{
  return std::bit_cast<__int128>(ext);
}


auto vec_u8string_view::stringToVecView(std::string_view string_view) -> __v16qi
{
  const_reverse_iterator rItr=string_view.crend();
  int i;
  for(const auto& x : string_view)
  {
    if(i++==15) return _a;
    this->_a[i]=x;
  }
  return _a;
}

// auto vec_u8string_view::vecToStringView(__v16qi const & _a) -> std::string_view
// {

//   auto strView=std::string_view{std::bit_cast<const char*>(_a[1])+15, 16};
//   return strView;
// }


//use string_view to avoid unnessacery heap alloc
auto vec_u8string_view::getExtensionfromSubString() -> __m128i
{
    const auto extOffset= _tzcnt_u64(_mm_movemask_epi8(_mm_cmpeq_epi8(_a,aDot))); //Extension Offset i.e. occurrance of "."
    
    return vmovdqu(std::bit_cast<__m128i*>(cbegin()+extOffset));
}