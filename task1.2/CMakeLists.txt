cmake_minimum_required(VERSION 3.21)

project(hse_parallel_task1_2
	VERSION 1.0
	LANGUAGES CXX
)

# Not optimized at all
add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_EXTENSIONS OFF
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Only compiller optimization
add_executable(${PROJECT_NAME}_comp main.cpp)

set_target_properties(${PROJECT_NAME}_comp PROPERTIES
	CXX_EXTENSIONS OFF
)
target_compile_features(${PROJECT_NAME}_comp PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME}_comp PRIVATE -O3 -Ofast)

# Compiller + vectorizing optimization
add_executable(${PROJECT_NAME}_opt main_opt.cpp)
set_target_properties(${PROJECT_NAME}_opt PROPERTIES
	CXX_EXTENSIONS OFF
)

target_compile_features(${PROJECT_NAME}_opt PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME}_opt PRIVATE -mavx2 -mfma -O3 -Ofast)
