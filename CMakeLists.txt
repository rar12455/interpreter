cmake_minimum_required(VERSION 4.1.4)
project(repl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Sources ───────────────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME}
    main.cpp
)

# ── Dependencies ──────────────────────────────────────────────────────────────
find_library(READLINE_LIB readline REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${READLINE_LIB}
)

# ── Compiler flags ────────────────────────────────────────────────────────────
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2>
)
