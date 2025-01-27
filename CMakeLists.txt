cmake_minimum_required(VERSION 3.6...3.31)
project(aura VERSION 2.5.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -lstdc++fs")
endif(WIN32)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(COMPANY "Vishal ahirwar")
string(TIMESTAMP CURRENT_YEAR "%Y")
set(COPYRIGHT "Copyright(c) ${CURRENT_YEAR} Vishal Ahirwar and all Contributors. All rights reserved.")
include_directories(src ${CMAKE_BINARY_DIR} external/json)
add_subdirectory(external/cpr)
add_subdirectory(external/fmt)
configure_file(auraConfig.h.in auraConfig.h)
add_executable(${PROJECT_NAME} 
    src/main.cc
    src/app/app.cc
    src/aura/aura.cc
    src/downloader/downloader.cc
    src/rt/rt.cc
    src/projectsetting/projectsetting.cc
    src/userinfo/userinfo.cc)

add_executable(utool utool/main.cc src/downloader/downloader.cc src/rt/rt.cc src/userinfo/userinfo.cc)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

target_link_libraries(${PROJECT_NAME} PUBLIC cpr)
target_link_libraries(utool PUBLIC cpr)


include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VENDOR ${COMPANY})
include(CPack)
