#pragma once

#include <CL/cl.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std::string_literals;


inline std::string load_file(std::string const& filename) {
	std::ifstream file(filename);

	if (!file) {
		std::cerr << "File not found.\n";
		abort();
	}

	std::ostringstream oss;
	oss << file.rdbuf();

	return oss.str();
}

inline std::vector<cl::Device> enumerate_devices() {
	std::vector<cl::Device> devices;

	// Get list of platforms
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	// Enumerate devices
	for (int i = 0; i < platforms.size(); i++)
	{
		cl_uint num = 0;
		std::vector<cl::Device> plat_devices;
		platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &plat_devices);
		devices.insert(devices.end(), plat_devices.begin(), plat_devices.end());
	}

	return devices;
}

inline std::string get_device_name(cl::Device& device) {
	cl_device_info info = CL_DEVICE_NAME;
	std::string name;

	// Special case for AMD
#ifdef CL_DEVICE_BOARD_NAME_AMD
	device.getInfo(CL_DEVICE_VENDOR, &name);
	if (strstr(name.c_str(), "Advanced Micro Devices"))
		info = CL_DEVICE_BOARD_NAME_AMD;
#endif

	device.getInfo(info, &name);

	return name;
}

inline std::string err_code (cl_int err_in) {
    switch (err_in) {
        case CL_SUCCESS:
            return "CL_SUCCESS"s;
        case CL_DEVICE_NOT_FOUND:
            return "CL_DEVICE_NOT_FOUND"s;
        case CL_DEVICE_NOT_AVAILABLE:
            return "CL_DEVICE_NOT_AVAILABLE"s;
        case CL_COMPILER_NOT_AVAILABLE:
            return "CL_COMPILER_NOT_AVAILABLE"s;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
            return "CL_MEM_OBJECT_ALLOCATION_FAILURE"s;
        case CL_OUT_OF_RESOURCES:
            return "CL_OUT_OF_RESOURCES"s;
        case CL_OUT_OF_HOST_MEMORY:
            return "CL_OUT_OF_HOST_MEMORY"s;
        case CL_PROFILING_INFO_NOT_AVAILABLE:
            return "CL_PROFILING_INFO_NOT_AVAILABLE"s;
        case CL_MEM_COPY_OVERLAP:
            return "CL_MEM_COPY_OVERLAP"s;
        case CL_IMAGE_FORMAT_MISMATCH:
            return "CL_IMAGE_FORMAT_MISMATCH"s;
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:
            return "CL_IMAGE_FORMAT_NOT_SUPPORTED"s;
        case CL_BUILD_PROGRAM_FAILURE:
            return "CL_BUILD_PROGRAM_FAILURE"s;
        case CL_MAP_FAILURE:
            return "CL_MAP_FAILURE"s;
        case CL_MISALIGNED_SUB_BUFFER_OFFSET:
            return "CL_MISALIGNED_SUB_BUFFER_OFFSET"s;
        case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
            return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST"s;
        case CL_INVALID_VALUE:
            return "CL_INVALID_VALUE"s;
        case CL_INVALID_DEVICE_TYPE:
            return "CL_INVALID_DEVICE_TYPE"s;
        case CL_INVALID_PLATFORM:
            return "CL_INVALID_PLATFORM"s;
        case CL_INVALID_DEVICE:
            return "CL_INVALID_DEVICE"s;
        case CL_INVALID_CONTEXT:
            return "CL_INVALID_CONTEXT"s;
        case CL_INVALID_QUEUE_PROPERTIES:
            return "CL_INVALID_QUEUE_PROPERTIES"s;
        case CL_INVALID_COMMAND_QUEUE:
            return "CL_INVALID_COMMAND_QUEUE"s;
        case CL_INVALID_HOST_PTR:
            return "CL_INVALID_HOST_PTR"s;
        case CL_INVALID_MEM_OBJECT:
            return "CL_INVALID_MEM_OBJECT"s;
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
            return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR"s;
        case CL_INVALID_IMAGE_SIZE:
            return "CL_INVALID_IMAGE_SIZE"s;
        case CL_INVALID_SAMPLER:
            return "CL_INVALID_SAMPLER"s;
        case CL_INVALID_BINARY:
            return "CL_INVALID_BINARY"s;
        case CL_INVALID_BUILD_OPTIONS:
            return "CL_INVALID_BUILD_OPTIONS"s;
        case CL_INVALID_PROGRAM:
            return "CL_INVALID_PROGRAM"s;
        case CL_INVALID_PROGRAM_EXECUTABLE:
            return "CL_INVALID_PROGRAM_EXECUTABLE"s;
        case CL_INVALID_KERNEL_NAME:
            return "CL_INVALID_KERNEL_NAME"s;
        case CL_INVALID_KERNEL_DEFINITION:
            return "CL_INVALID_KERNEL_DEFINITION"s;
        case CL_INVALID_KERNEL:
            return "CL_INVALID_KERNEL"s;
        case CL_INVALID_ARG_INDEX:
            return "CL_INVALID_ARG_INDEX"s;
        case CL_INVALID_ARG_VALUE:
            return "CL_INVALID_ARG_VALUE"s;
        case CL_INVALID_ARG_SIZE:
            return "CL_INVALID_ARG_SIZE"s;
        case CL_INVALID_KERNEL_ARGS:
            return "CL_INVALID_KERNEL_ARGS"s;
        case CL_INVALID_WORK_DIMENSION:
            return "CL_INVALID_WORK_DIMENSION"s;
        case CL_INVALID_WORK_GROUP_SIZE:
            return "CL_INVALID_WORK_GROUP_SIZE"s;
        case CL_INVALID_WORK_ITEM_SIZE:
            return "CL_INVALID_WORK_ITEM_SIZE"s;
        case CL_INVALID_GLOBAL_OFFSET:
            return "CL_INVALID_GLOBAL_OFFSET"s;
        case CL_INVALID_EVENT_WAIT_LIST:
            return "CL_INVALID_EVENT_WAIT_LIST"s;
        case CL_INVALID_EVENT:
            return "CL_INVALID_EVENT"s;
        case CL_INVALID_OPERATION:
            return "CL_INVALID_OPERATION"s;
        case CL_INVALID_GL_OBJECT:
            return "CL_INVALID_GL_OBJECT"s;
        case CL_INVALID_BUFFER_SIZE:
            return "CL_INVALID_BUFFER_SIZE"s;
        case CL_INVALID_MIP_LEVEL:
            return "CL_INVALID_MIP_LEVEL"s;
        case CL_INVALID_GLOBAL_WORK_SIZE:
            return "CL_INVALID_GLOBAL_WORK_SIZE"s;
        case CL_INVALID_PROPERTY:
            return "CL_INVALID_PROPERTY"s;

        default:
            return "UNKNOWN ERROR"s;
    }
}

// inline void check_error(cl_int err, const char *operation, char *filename, int line)
// {
//     if (err != CL_SUCCESS) {
//         fprintf(stderr, "Error during operation '%s', ", operation);
//         fprintf(stderr, "in '%s' on line %d\n", filename, line);
//         fprintf(stderr, "Error code was \"%s\" (%d)\n", err_code(err), err);
//         exit(EXIT_FAILURE);
//     }
// }
//
//
// #define CHECK_ERROR(E, S) check_error(E,S,__FILE__,__LINE__)
