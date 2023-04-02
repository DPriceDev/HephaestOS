add_executable(
        initialTask.elf

        InitialTask.cpp
)

target_link_libraries(initialTask.elf PRIVATE user_options)
target_link_libraries(initialTask.elf PUBLIC LibC LibCpp)

target_include_directories(initialTask.elf PUBLIC .)