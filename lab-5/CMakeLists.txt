# Устанавливаем минимально необходимую версию CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(PMRListProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем директорию заголовочных файлов
include_directories(include)

# Указываем исходные файлы для основной программы
set(SOURCES
    src/custom_memory_resource.cpp
    src/pmr_list.cpp
    src/my_struct.cpp
    main.cpp
)

# Создаём исполняемый файл из указанных исходников
add_executable(PMRListProject ${SOURCES})

# =========================
# Настройка Google Test
# =========================

# Добавляем возможность скачивания зависимостей через FetchContent
include(FetchContent)

# Загружаем GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# Для старых версий CMake требуется установить переменную FETCHCONTENT_FULLY_DISCONNECTED
set(FETCHCONTENT_QUIET FALSE)

# Подключаем GoogleTest
FetchContent_MakeAvailable(googletest)

enable_testing()

# Указываем исходные файлы для тестов
set(TEST_SOURCES
    tests/tests.cpp
    src/custom_memory_resource.cpp
    src/pmr_list.cpp
    src/my_struct.cpp
)

# Создаем исполняемый файл для тестов
add_executable(RunTests ${TEST_SOURCES})

# Подключаем заголовочные файлы
target_include_directories(RunTests PUBLIC include)

# Подключаем Google Test
target_link_libraries(RunTests GTest::gtest GTest::gtest_main)

# Добавляем тесты
add_test(NAME PMRListTests COMMAND RunTests)

