cmake_minimum_required(VERSION 3.10)


project(lmdb)

add_library(lmdb
  mdb.c
  midl.c)

if(FREEBSD)
  target_compile_definitions(lmdb PRIVATE MDB_DSYNC=O_SYNC)
endif()
if(ANDROID)
  target_compile_definitions(lmdb PRIVATE ANDROID=1)
endif()
if(${ARCH_WIDTH} EQUAL 32)
  target_compile_definitions(lmdb PUBLIC MDB_VL32)
endif()

target_include_directories(lmdb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(lmdb PRIVATE Threads::Threads)
set_property(TARGET lmdb PROPERTY POSITION_INDEPENDENT_CODE ON)

# GUI/libwallet install target
if (BUILD_GUI_DEPS)
    if(IOS)
        set(lib_folder lib-${ARCH})
    else()
        set(lib_folder lib)
    endif()
    install(TARGETS lmdb
        ARCHIVE DESTINATION ${lib_folder}
        LIBRARY DESTINATION ${lib_folder})
endif()
