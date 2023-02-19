#version 460
#pragma shader_stage(compute)

layout (local_size_x = 32) in;


layout(binding = 0, rgba8) uniform restrict image2D Img;


const uvec4 A = uvec4(255<<24);

void main()
{
	const int xx=int(gl_GlobalInvocationID.x);
	//const uint yy=gl_GlobalInvocationID.y*WORKGROUP_SIZE;
	
	
	for(int xOffs=xx;xOffs<xx+1080;xOffs++)
	{
		
		{
		
			
			imageStore(Img, ivec2(xOffs, xx), imageLoad(Img, ivec2(xOffs, xx)).bgra);
		}
	}
	
	
	
	
}
