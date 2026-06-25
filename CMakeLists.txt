cmake_minimum_required(VERSION 3.20)

project(cpp_concepts LANGUAGES CXX)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UBSan" OFF)
option(ENABLE_TIDY "Enable clang-tidy during build" OFF)

function(configure_cpp_target target_name)
    target_compile_features(${target_name} PRIVATE cxx_std_20)

    target_compile_options(${target_name} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )

    if(ENABLE_SANITIZERS)
        target_compile_options(${target_name} PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer
                -g
        )

        target_link_options(${target_name} PRIVATE
                -fsanitize=address,undefined
        )
    endif()

    if(ENABLE_TIDY)
        find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)

        set_target_properties(${target_name} PROPERTIES
                CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
        )
    endif()
endfunction()

function(add_concept concept_name)
    set(concept_dir "${CMAKE_CURRENT_SOURCE_DIR}/concepts/${concept_name}")

    file(GLOB concept_sources CONFIGURE_DEPENDS
            "${concept_dir}/*.cpp"
            "${concept_dir}/*.cc"
            "${concept_dir}/*.cxx"
    )

    file(GLOB concept_headers CONFIGURE_DEPENDS
            "${concept_dir}/*.h"
            "${concept_dir}/*.hpp"
            "${concept_dir}/*.hxx"
    )

    if(NOT concept_sources)
        message(FATAL_ERROR
                "Concept '${concept_name}' has no source files in: ${concept_dir}"
        )
    endif()

    add_executable(${concept_name}
            ${concept_sources}
            ${concept_headers}
    )

    target_include_directories(${concept_name} PRIVATE
            "${concept_dir}"
    )

    configure_cpp_target(${concept_name})
endfunction()

add_concept(indexed-vector-is-lvalue)
add_concept(odr-inline-vs-static-vs-namespace)
add_concept(braced-initialization-return)
add_concept(nodiscard)


