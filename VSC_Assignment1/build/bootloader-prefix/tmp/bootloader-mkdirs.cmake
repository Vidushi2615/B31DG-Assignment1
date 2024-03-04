# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/vidus/esp/v5.2/esp-idf/components/bootloader/subproject"
  "D:/EmbeddedSoftware/Assignment/VS_Test/Test/build/bootloader"
  "D:/EmbeddedSoftware/Assignment/VS_Test/Test/build/bootloader-prefix"
  "D:/EmbeddedSoftware/Assignment/VS_Test/Test/build/bootloader-prefix/tmp"
  "D:/EmbeddedSoftware/Assignment/VS_Test/Test/build/bootloader-prefix/src/bootloader-stamp"
  "D:/EmbeddedSoftware/Assignment/VS_Test/Test/build/bootloader-prefix/src"
  "D:/EmbeddedSoftware/Assignment/VS_Test/Test/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/EmbeddedSoftware/Assignment/VS_Test/Test/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/EmbeddedSoftware/Assignment/VS_Test/Test/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
