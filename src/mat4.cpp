#include "mat4.hpp"


auto mat4::mul(mat4 mat)-> m4x4
{
  return this->mat_*mat.mat_;
}
auto mat4::transpose() -> mat4
{
  return {__builtin_matrix_transpose(this->mat_)};
}