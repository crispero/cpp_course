add_executable(sfml3.3 main.cpp)

target_include_directories(sfml3.3 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml3.3 PUBLIC cxx_std_17)
target_compile_definitions(sfml3.3 PRIVATE SFML_STATIC)

target_link_libraries(sfml3.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${JPEG_LIBRARIES})