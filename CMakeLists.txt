cmake_minimum_required(VERSION 3.17)

project("ngsd")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(NGSD_ENABLE_EXAMPLE ON)

if (NGSD_ENABLE_EXAMPLE)
	add_executable(ngsd_test "src/ngsd.h" "test/ngsd_test.cpp")

	# SET C++ STANDARD
	target_compile_features(ngsd_test PUBLIC cxx_std_17)
	set_target_properties(ngsd_test PROPERTIES CXX_EXTENSIONS OFF)
endif()


