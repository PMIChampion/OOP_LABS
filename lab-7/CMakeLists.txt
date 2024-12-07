cmake_minimum_required(VERSION 3.10)
project(BalagurFate3)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем директории с заголовочными файлами
include_directories(include)

# Исходные файлы приложения (без main.cpp)
file(GLOB APP_SOURCES "src/*.cpp")

# Основной исполняемый файл (с main.cpp)
set(MAIN_SOURCES ${APP_SOURCES} main.cpp)
add_executable(BalagurFate3 ${MAIN_SOURCES})

# Настройка для тестов
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
# Для Windows: предотвращает конфликт между Google Test и библиотекой pthread
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Тестовые исходные файлы
file(GLOB TEST_SOURCES "tests/*.cpp")

# Тестовый исполняемый файл (без main.cpp)
add_executable(runTests ${TEST_SOURCES} ${APP_SOURCES})
target_link_libraries(runTests gtest_main)

# Обнаружение тестов
gtest_discover_tests(runTests)
