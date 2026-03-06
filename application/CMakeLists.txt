add_executable(application)

file(GLOB_RECURSE
    APPLICATION_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

target_sources(application
    PRIVATE
        ${APPLICATION_SRC}
)

target_include_directories(application
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(application
    PRIVATE
        rl_engine
)

target_compile_definitions(application 
    PRIVATE
        RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources"
)
