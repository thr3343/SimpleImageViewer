# SimpleImageViewer

Experimenal utility tesing use of the Vulkan API in tandem with Rendering techniques and GPU capabilities instead of more conventional CPU/Scalar-based approaches to render and handle image and bitmap formats.

This is heavily based on the [VkMod2 Repo](https://github.com/thr3343/VkMod2), so may reuse code from there in some places

This also attempts to ascertain and explore possible theories for more efficent methods of decoding, displaying and scaling very large bitmap-based files (e.g. 32k*32K resolutions or larger) which can be very slow using more conventional methods, where techniques and hardware leveraging SIMD principles such as GPUs and Vulkan Compute may hold potential in handling more efficently and effectively.

(Currently Windows x64 only, is also highly unfinished and cannot operate as afully workable utility program currently due to lakcing several critical functions (e.g. Window Callback handling, directory traversal e.g.)
