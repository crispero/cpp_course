add_executable(workshop3.1 main.cpp initials.cpp print.cpp)


target_include_directories(workshop3.1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop3.1 PUBLIC cxx_std_17)
target_compile_definitions(workshop3.1 PRIVATE SFML_STATIC)

target_link_libraries(workshop3.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})