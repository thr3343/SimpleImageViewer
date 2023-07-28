#pragma once
using m4x4 [[gnu::aligned(64)]] = float [[clang::matrix_type(4, 4)]];
using float4 = float __attribute__((ext_vector_type(4)));

struct [[gnu::aligned(64)]] mat4
{
   [[no_unique_address]] m4x4 mat_;
   [[nodiscard]] auto mul(mat4 mat) -> m4x4;
   [[nodiscard]] auto transpose() -> mat4;
};