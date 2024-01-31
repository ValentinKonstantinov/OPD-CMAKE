# Минимальная версия CMake: 3.8 Описание проекта какие файлы и п.т. для компиляции
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Имя проекта: sfml-lab-1
project(sfml-lab-1)

# Подкаталог 00 содержит ещё один CMakeLists.txt

add_subdirectory(1.1)
add_subdirectory(1.2)
add_subdirectory(1.3)
