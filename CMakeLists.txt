cmake_minimum_required (VERSION 3.8)
project(Geometry)

add_library(Geometry INTERFACE)

target_include_directories(Geometry
	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
# Use target sources for IDE
#target_sources(Geometry INTERFACE "$<BUILD_INTERFACE:${detail_header_files};${header_files}>")
