add_executable(1.2 main.cpp)

target_include_directories(1.2 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(1.2 PUBLIC cxx_std_17)
target_compile_definitions(1.2 PRIVATE SFML_STATIC)

target_link_libraries(1.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})