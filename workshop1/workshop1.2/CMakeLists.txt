add_executable(workshop1.2 main.cpp)

target_include_directories(workshop1.2 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop1.2 PUBLIC cxx_std_17)
target_compile_definitions(workshop1.2 PRIVATE SFML_STATIC)

target_link_libraries(workshop1.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})