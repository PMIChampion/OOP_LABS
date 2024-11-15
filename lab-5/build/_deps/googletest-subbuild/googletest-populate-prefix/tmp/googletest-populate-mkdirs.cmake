# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-src")
  file(MAKE_DIRECTORY "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-src")
endif()
file(MAKE_DIRECTORY
  "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-build"
  "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/vladislavburdinskij/Documents/OOP_labs/OOP_LABS/lab-5/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()