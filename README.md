# SimpleImageViewer

Experiment to test use of alternate Rendering techniques and GPU capabilities to render and handle image and bitmap formats.

This is heavily based on the [VkMod2 Repo](https://github.com/thr3343/VkMod2), so may reuse code from there in some places

This also attempts to ascertain and explore possible theories for more efficient methods of decoding, displaying and scaling very large bitmap-based files (e.g. 32k*32K resolutions or larger) which can be very slow using more conventional methods, where techniques and hardware leveraging SIMD principles such as GPUs and Vulkan Compute may hold potential in handling more efficiently and effectively.

May also explore GPU oriented Image Procesing and Decoding (e.g. Image Scaling/Anti Aliasing) and format decompression (e.g. PNG, JPG) if it is possible 

(Currently Windows x64 only, is also highly unfinished and cannot operate as a fully workable utility program currently due to lacking several critical functions (e.g. Window Callback handling, directory traversal e.g.))
