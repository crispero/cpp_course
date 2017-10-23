add_executable(sfml3.2 main.cpp)

target_include_directories(sfml3.2 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml3.2 PUBLIC cxx_std_17)
target_compile_definitions(sfml3.2 PRIVATE SFML_STATIC)

target_link_libraries(sfml3.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${JPEG_LIBRARIES})