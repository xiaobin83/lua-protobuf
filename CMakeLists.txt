
project(lua_pb C)
cmake_minimum_required(VERSION 2.8)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

#if(MSVC)
#	set(USE_PORTABLE_ENDIAN ON)
#endif()

#option(USE_PORTABLE_ENDIAN "Use portable_endian.h" ${USE_PORTABLE_ENDIAN})

set(SRC "pb.c")
#file(GLOB LUA_PB_FILES "protobuf/*.lua")

# find lua
include_directories("${CMAKE_SOURCE_DIR}/prebuilt/lua-5.3/include" "${CMAKE_SOURCE_DIR}/${LUA_LIB_DIR}")
link_directories("${CMAKE_SOURCE_DIR}/${LUA_LIB_DIR}")

if(USE_PORTABLE_ENDIAN)
	add_definitions(-D_USE_PORTABLE_ENDIAN)
endif()

if(BUILD_SHARED_LIBS)
	if(WIN32)
		add_definitions(-D_LUA_PB_BUILD_AS_DLL)
	endif()
endif()

add_library(libpb ${SRC})
target_link_libraries(libpb lua)
set_target_properties(libpb PROPERTIES OUTPUT_NAME pb CLEAN_DIRECT_OUTPUT 1 )

# install
set(LUA_VDIR "5.3")
install(TARGETS libpb DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/lua/${LUA_VDIR})

#install(FILES ${LUA_PB_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/lua/${LUA_VDIR})






