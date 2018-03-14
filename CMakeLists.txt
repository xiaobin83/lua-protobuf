
project(lua_pb C)
cmake_minimum_required(VERSION 2.8)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

set(SRC "pb.c")

# find lua
include_directories("${CMAKE_SOURCE_DIR}/lua-prebuilt/lua-5.3/include" "${CMAKE_SOURCE_DIR}/${LUA_LIB_DIR}")
link_directories("${CMAKE_SOURCE_DIR}/${LUA_LIB_DIR}")

add_definitions(-DPB_STATIC_API)

add_library(libpb ${SRC})
target_link_libraries(libpb lua)
set_target_properties(libpb PROPERTIES OUTPUT_NAME pb CLEAN_DIRECT_OUTPUT 1 )

if(IPHONEOS_DEPLOYMENT_TARGET)
	set_xcode_property(libpb IPHONEOS_DEPLOYMENT_TARGET ${IPHONEOS_DEPLOYMENT_TARGET})
endif()

# install
set(LUA_VDIR "5.3")
install(TARGETS libpb DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/lua/${LUA_VDIR})


