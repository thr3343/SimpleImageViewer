cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(SimpleImageViewer LANGUAGES CXX)

add_executable(SimpleImageViewer)
add_compile_definitions(SimpleImageViewer PRIVATE WIN32_LEAN_AND_MEAN VK_USE_PLATFORM_WIN32_KHR)
target_compile_features(SimpleImageViewer PRIVATE cxx_std_23)
# target_compile_features(SimpleImageViewer PRIVATE c_std_23)
# target_link_options(SimpleImageViewer PRIVATE -fsanitize=address,undefined)
target_compile_options(SimpleImageViewer PRIVATE -march=native -mtune=native -save-temps -masm=intel -Ofast -fno-char8_t -fno-exceptions -Wuninitialized -Weffc++)

	target_sources(SimpleImageViewer
		PRIVATE
			"${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Win.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Win.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Vkbase.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Vkbase.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/SwapChain.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/SwapChain.cpp"

			"${CMAKE_CURRENT_SOURCE_DIR}/src/defs.tpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/VkCommSet.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/VkCommSet.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/MemSys2.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/MemSys2.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/ImgLoader.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/ImgLoader.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/imgLud.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/imgLud.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/renderer2.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/ComputePipeline.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/ComputePipeline.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/vec_u8string_view.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/vec_u8string_view.cpp"
			
	)
	find_package(Vulkan REQUIRED)
	include_directories(shaders)
	

	# find_library(SPIRV STATIC "$ENV{VULKAN_SDK}/Lib/")
	# find_library(glslang STATIC "$ENV{VULKAN_SDK}/Lib/")

	
	
	target_include_directories(SimpleImageViewer PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/fast_io/include stb)
	target_precompile_headers(SimpleImageViewer 
		PRIVATE 
		
			$<$<COMPILE_LANGUAGE:C>:<GLFW/glfw3.h$<ANGLE-R>>
			$<$<COMPILE_LANGUAGE:C>:<vulkan/vk_platform.h$<ANGLE-R>>
			$<$<COMPILE_LANGUAGE:C>:<vulkan/vulkan_core.h$<ANGLE-R>>
			$<$<COMPILE_LANGUAGE:C>:<vulkan/vulkan_win32.h$<ANGLE-R>>
			$<$<COMPILE_LANGUAGE:C>:<fmt/core.h$<ANGLE-R>>
			$<$<COMPILE_LANGUAGE:C>:<string$<ANGLE-R>>
			$<$<COMPILE_LANGUAGE:C>:<stb_image.h$<ANGLE-R>>
			

	)

	add_subdirectory(VulkanMemoryAllocator)
	add_subdirectory(fmt)
	add_subdirectory(glfw)
	# add_subdirectory(glslang)
	
	target_link_libraries(SimpleImageViewer PRIVATE VulkanMemoryAllocator fmt glfw)

