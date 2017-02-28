# Find Pangolin (https://github.com/stevenlovegrove/Pangolin)
find_package(Pangolin 0.4 REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

add_executable(HelloPangolin main.cpp)
add_executable(PangolinROSUI rosui_main.cpp)

target_link_libraries(HelloPangolin ${Pangolin_LIBRARIES})
target_link_libraries(PangolinROSUI ${Pangolin_LIBRARIES})    
