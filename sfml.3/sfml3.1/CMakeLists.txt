add_executable(sfml3.1 main.cpp)

target_include_directories(sfml3.1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml3.1 PUBLIC cxx_std_17)
target_compile_definitions(sfml3.1 PRIVATE SFML_STATIC)

target_link_libraries(sfml3.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})