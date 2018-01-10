add_executable(workshop2.8 main.cpp)

target_include_directories(workshop2.8 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop2.8 PUBLIC cxx_std_17)
target_compile_definitions(workshop2.8 PRIVATE SFML_STATIC)

target_link_libraries(workshop2.8 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})