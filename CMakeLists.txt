cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(SimpleImageViewer LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_executable(SimpleImageViewer)
add_compile_definitions(SimpleImageViewer PRIVATE WIN32_LEAN_AND_MEAN VK_USE_PLATFORM_WIN32_KHR _GLFW_VULKAN_STATIC _LIBCPP_HAS_NO_CHAR8_T)
target_compile_features(SimpleImageViewer PRIVATE cxx_std_23)
# target_compile_features(SimpleImageViewer PRIVATE c_std_23)
# target_link_options(SimpleImageViewer PRIVATE -fsanitize=address,undefined)
target_compile_options(SimpleImageViewer PRIVATE -march=native -mtune=native -save-temps -masm=intel -Ofast -fno-char8_t -fno-exceptions -Wuninitialized -Weffc++)

	target_sources(SimpleImageViewer
		PRIVATE
		FILE_SET HEADERS
		BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
		FILES
			"src/MemSys2.hpp"
			"src/defs.tpp"
			"src/Win.hpp"
			"src/renderer2.hpp"
			"src/Vkbase.hpp"
			"src/imgLud.hpp"
			"src/ImgLoader.hpp"
			"src/SwapChain.hpp"
			"src/vec_u8string_view.hpp"
			"src/ComputePipeline.hpp"
			"src/VkCommSet.hpp"
			
		PRIVATE	
			"src/main.cpp"
			"src/SwapChain.cpp"
			"src/Vkbase.cpp"
			"src/Win.cpp"
			"src/VkCommSet.cpp"
			"src/MemSys2.cpp"
			"src/ImgLoader.cpp"
			"src/imgLud.cpp"
			"src/ComputePipeline.cpp"
			"src/vec_u8string_view.cpp"
			
	)
	find_package(Vulkan REQUIRED)
	
	

	# find_library(SPIRV STATIC "$ENV{VULKAN_SDK}/Lib/")
	# find_library(glslang STATIC "$ENV{VULKAN_SDK}/Lib/")

	
	
	target_sources(SimpleImageViewer PRIVATE FILE_SET HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/stb" FILES "stb/stb_image.h")
	
	
	target_precompile_headers(SimpleImageViewer 
		PRIVATE 
		
			$<$<COMPILE_LANGUAGE:C>:
				GLFW/glfw3.h
				vulkan/vk_platform.h
				vulkan/vulkan_core.h
				vulkan/vulkan_win32.h
				fmt/core.h
				string
				string_view
				stb_image.h>
			

	)

	add_subdirectory(VulkanMemoryAllocator)
	add_subdirectory(fmt)
	add_subdirectory(glfw)
	# add_subdirectory(glslang)
	
	target_link_libraries(SimpleImageViewer PRIVATE VulkanMemoryAllocator fmt glfw)

