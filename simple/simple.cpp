#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>
#include "util.hpp"
#include <iostream>
#include <chrono>

constexpr std::size_t width = 1920 * 2;
constexpr std::size_t height = 1080 * 2;

struct DeviceData {
	cl::Device device;
	cl::Context context;
	cl::CommandQueue queue;
	cl::Buffer buf_color;
	cl::Program program;
	cl::make_kernel<cl::Buffer, int, int> kernel;
};

int main() {
	try {
		// Get list of devices
		auto devices = enumerate_devices();

		for (auto&& device : devices) {
			auto name = get_device_name(device);
			std::cout << "Available Device: " << name << '\n';
		}

		// Preparation
		std::vector<DeviceData> d_device_data;
		d_device_data.reserve(devices.size());

		for (auto&& device : devices) {
			cl::Program d_program;
			try {
				auto d_context = cl::Context(std::vector<cl::Device>{device});
				auto d_queue = cl::CommandQueue(d_context, device);
				auto d_buf_color = cl::Buffer(d_context, CL_MEM_WRITE_ONLY, sizeof(float) * 4 * width * height);
				d_program = cl::Program(d_context, load_file("C:/Users/connor/Programming/OpenCL-Tests/simple/kernel.cl"), false);
				d_program.build(std::vector<cl::Device>{device});
				auto d_kernel = cl::make_kernel<cl::Buffer, int, int>(d_program, "render_kernel");

				DeviceData d_data{ std::move(device), std::move(d_context), std::move(d_queue), std::move(d_buf_color), std::move(d_program), std::move(d_kernel) };
				d_device_data.emplace_back(std::move(d_data));
			}
			catch (cl::Error& e) {
				if (e.err() == CL_BUILD_PROGRAM_FAILURE) {
					// Check the build status
					cl_build_status status = d_program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(device);

					// Get the build log
					std::string name = device.getInfo<CL_DEVICE_NAME>();
					std::string buildlog = d_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
					std::cerr << "Build log for " << name << ":" << std::endl
						<< buildlog << std::endl;
					throw e;
				}
				else {
					throw e;
				}
			}
		}

		// Actual Rendering
		for (auto&& device_data : d_device_data) {
			std::cout << "Rendering on: " << get_device_name(device_data.device) << '\n';

			std::vector<float> results(4 * width * height, 0.0f);

			auto&& d_queue = device_data.queue;
			auto&& d_buf_color = device_data.buf_color;
			auto&& d_kernel = device_data.kernel;

			auto start = std::chrono::high_resolution_clock::now();

			cl::NDRange const global_range(width * height);
			d_kernel(cl::EnqueueArgs(d_queue, global_range), d_buf_color, width, height);

			d_queue.finish();

			auto end = std::chrono::high_resolution_clock::now();

			cl::copy(d_queue, d_buf_color, results.begin(), results.end());

			std::cout << "Rendered in: " << (end - start).count() / 1000 << "us\n";
		}
	}
	catch(cl::Error& e) {
		std::cerr << "Exception\n";
		std::cerr << "ERROR: " << e.what() << '(' << err_code(e.err()) << ')' << '\n';

	}
}
