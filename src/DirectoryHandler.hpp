#include <immintrin.h>

#include <string_view>
struct DirectoryHandler
{
    // [[gnu::pure]] __vectorcall auto handleExt(std::string a) -> __m128i;
    __vectorcall auto getExtensionfromSubString(std::string_view a) -> __m128i;
};