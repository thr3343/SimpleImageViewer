#include "SPIRVUtil.hpp"
#include "Swizzle.inl"
#include <array>
#include <cstdint>

// #include <glslang/Public/ShaderLang.h>

//Using Embedded Precompiled Shader for now due to SPIR_V Libs (ShaderC/GLSLLang) Being increasibly large/complex to use and/or greately increasing compile time and Executable size




void SPIRVUtil::loadShader()
{
//    std::string a;
//    glslang::TShader ax{EShLangCompute};

//    printf("GLSL:: %s\n", glslang::GetGlslVersionString());

        // glslang::TShader aa{EShLangGeometry};
        // aa.parse()
        // printf("Size: %llu\n",a.size());
//    glslang::TIntermediate aa{EShLangCompute, 0, ENoProfile};
//    glslang::SpvVersion spva{};
//    spva.spv=glslang::EShTargetSpv_1_5;
//    spva.vulkan=shaderc_env_version_vulkan_1_3;
//    aa.setSpv(spva);
}