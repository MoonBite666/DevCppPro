cmake_minimum_required(VERSION 3.5)

project(DevCppPro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES TSDir/DevCppPro_zh_CN.ts)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(UI)

file(GLOB UI_FILES "UI/*.cpp" "UI/*.h")
file(GLOB SRC_FILES "Src/main.cpp" "Src/FileManager/*.cpp" "Src/FileManager/*.h"
    "Src/TextManager/*.cpp" "Src/TextManager/*.h"
)


set(PROJECT_SOURCES
        ${SRC_FILES}
        ${UI_FILES}
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DevCppPro
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Resources/DCResources.qrc
        ThirdParty/ElaWidgetTools/src/include/ElaWidgetTools.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DevCppPro APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(DevCppPro SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DevCppPro
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

add_subdirectory(ThirdParty/ElaWidgetTools)
include_directories(ThirdParty/ElaWidgetTools/src/include)
include_directories(Src)

target_link_libraries(DevCppPro PRIVATE Qt${QT_VERSION_MAJOR}::Widgets elawidgettools)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DevCppPro)
endif()
set_target_properties(DevCppPro PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DevCppPro
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DevCppPro)
endif()
