cmake_minimum_required(VERSION 3.12)

project(TApp VERSION 1.0.0.0)

# 查找Qt包，根据自己的qt地址自行修改！！！
set(CMAKE_PREFIX_PATH "D:/qt5.14/5.14.2/msvc2017_64")
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

# 设置自动MOC、UIC和RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


#全局添加包含目录以包含头文件所在的目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/lib)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
# 源文件列表

set(SOURCE_FILES
    TinyTsTranslate/BaiduTransfer.cpp
    TinyTsTranslate/tinyxml2.cpp
    TinyTsTranslate/Translate.cpp
    TinyTsTranslate/util.cpp
    TinyTsTranslate/BaiduTransfer.h
    TinyTsTranslate/tinyxml2.h
    TinyTsTranslate/Translate.h
    TinyTsTranslate/util.h
    TinyTsTranslate/TinyTsTranslate.h
    TinyTsTranslate/TinyTsTranslate.cpp
)

set(LIBS
    libcurld
    libcrypto
)

qt5_wrap_ui(ui_FILES ${CMAKE_CURRENT_SOURCE_DIR}/TinyTsTranslate/TinyTsTranslate.ui)



# 添加可执行文件
add_executable(MyApp
    TinyTsTranslate/main.cpp
    ${SOURCE_FILES}
    ${ui_FILES}
)

target_include_directories(MyApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/TinyTsTranslate)
target_include_directories(MyApp PRIVATE ${ui_FILES})
#add_dependencies(MyExecutable, tw)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

# 链接Qt库到目标
target_link_libraries(MyApp PRIVATE Qt5::Widgets Qt5::Core)
target_link_libraries(MyApp PRIVATE ${LIBS})

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#复制dll
file(COPY 
    D:/qt5.14/5.14.2/msvc2017_64/bin/Qt5Widgetsd.dll
    D:/qt5.14/5.14.2/msvc2017_64/bin/Qt5Cored.dll
    D:/qt5.14/5.14.2/msvc2017_64/bin/Qt5Guid.dll
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/Debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/bin/. DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/Debug)
#qt还要复制这个东西
file(COPY D:/qt5.14/5.14.2/msvc2017_64/plugins/platforms/. DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/Debug/platforms)