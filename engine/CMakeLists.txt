add_library(rl_engine STATIC)

file(GLOB_RECURSE 
    ENGINE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

target_sources(rl_engine 
    PRIVATE 
        ${ENGINE_SRC}
)

target_include_directories(rl_engine
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_precompile_headers(rl_engine 
    PUBLIC 
        include/core/headers.h
)

target_compile_features(rl_engine 
    PUBLIC 
        cxx_std_20
)

target_link_libraries(rl_engine 
    PUBLIC 
        raylib 
        imgui 
        rlImGui
)