cmake_minimum_required(VERSION 3.21)

project(hse_parallel_task1_1
	VERSION 1.0
	LANGUAGES CXX
)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_EXTENSIONS OFF
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -mavx2 -msse2)

