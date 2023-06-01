cmake_minimum_required(VERSION 3.25)
MESSAGE("${CMAKE_SYSTEM_NAME}")
# Setting vcpkg.
set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/modules/vcpkg")
IF (UNIX)
    MESSAGE(STATUS "current platform: Linux ")
    include_directories("${VCPKG_ROOT}/installed/x64-linux/include")
ELSEIF (WIN32)
    MESSAGE(STATUS "current platform: Windows")
    include_directories("${VCPKG_ROOT}/installed/x64-windows/include")
ENDIF ()
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(ReflectiveShadowMapsRemake)
set(CMAKE_CXX_STANDARD 14)
add_executable(ReflectiveShadowMapsRemake
        src/main.cpp src/include/model/Light.h src/include/model/Mesh.h src/include/model/GameObject.h src/include/model/Material.h src/src/controller/ResoureManager.cpp src/include/controller/ResourceManager.h src/src/controller/Engine.cpp src/include/controller/Engine.h)
include_directories("src/include")
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ReflectiveShadowMapsRemake PRIVATE glfw)
find_package(glm CONFIG REQUIRED)
target_link_libraries(ReflectiveShadowMapsRemake PRIVATE glm::glm)
find_package(glad CONFIG REQUIRED)
target_link_libraries(ReflectiveShadowMapsRemake PRIVATE glad::glad)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(ReflectiveShadowMapsRemake PUBLIC assimp::assimp)

add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND echo "Move assets files. From ${CMAKE_SOURCE_DIR}/src/assets to ${CMAKE_BUILD_RPATH}/assets"
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/assets ${CMAKE_BUILD_RPATH}/assets
        )