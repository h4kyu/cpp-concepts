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
    add_executable(${concept_name}
            concepts/${concept_name}.cpp
    )

    configure_cpp_target(${concept_name})
endfunction()

add_concept(vector_type_ambiguity)

#add_concept(noexcept_vector_bad)
#add_concept(noexcept_vector_good)
#
#add_concept(lambda_lifetime_bad)
#add_concept(lambda_lifetime_good)
#
#add_concept(erase_iteration_bad)
#add_concept(erase_iteration_good)