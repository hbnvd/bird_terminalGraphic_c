
cmake_minimum_required(VERSION 3.31.5)
project(bird_terminalGraphic_c)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 1. Ép file thực thi .exe xuất hiện trong thư mục bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# ĐÂY LÀ DÒNG THIẾU: Chỉ đường cho trình biên dịch tìm thấy các file .h trong include/
include_directories(include)

# 2. Khai báo đúng đường dẫn mã nguồn trong thư mục src/
add_executable(FlappyGame
    src/main.c
    src/terminalGraphic.c
)

# 3. ÉP CẮM CỜ -O3 ĐỂ TỐI ƯU HÓA TỐC ĐỘ (Dành cho GCC/MinGW/Clang)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(FlappyGame PRIVATE -O3)
endif()
