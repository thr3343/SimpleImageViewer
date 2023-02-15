# SimpleImageViewer

Experimental program/application or "tech demo" to test using the Vulkan API in tandem with using Rendering techniques and GPU capabilities instead of more conventional CPU/Scalar-based approaches for Rendering and Handling Images and Bitmap formats.

This also attempts to ascertain and explore possible theories for more efficent methods of decoding, displaying and scaling very large bitmap-based files (e.g. 32k*32K resolutions or larger) which can be very slow using more conventional methods, where techniques and hardware leveraging SIMD principles such as GPUs and Vulkan Compute may hold potential in handling more efficently and effectively.

(Currently Windows x64 only, is also highly unfished and cannot be used as a workable program/App currently due to lakcing several critical functions (e.g. Window Callback handling, directory traversal e.g.)
