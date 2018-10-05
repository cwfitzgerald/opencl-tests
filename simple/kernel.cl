__kernel void render_kernel(__global float3* output, int width, int height) {
	const int work_item_id = get_global_id(0);
	int x = work_item_id % width;
	int y = work_item_id / width;
	float fx = (float) x / width;
	float fy = (float) y / height;
	output[work_item_id] = (float3) fx, fy, 0;
}