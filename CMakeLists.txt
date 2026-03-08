cmake_minimum_required(VERSION 3.16)

project(NumbersPerceptron VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appNumbersPerceptron
    main.cpp
)

qt_add_qml_module(appNumbersPerceptron
    URI NumbersPerceptron
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES UI/PixelGrid.qml
        QML_FILES UI/RightPanel.qml
        SOURCES Backend/perceptron.h Backend/perceptron.cpp
        SOURCES Backend/Utils.h
        SOURCES Backend/Utils.cpp
        SOURCES Backend/classifier.h Backend/classifier.cpp
)

target_compile_options(appNumbersPerceptron PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/arch:AVX2>
    $<$<CXX_COMPILER_ID:GNU>:-mavx2 -mfma>
    $<$<CXX_COMPILER_ID:Clang>:-mavx2 -mfma>
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appNumbersPerceptron PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appNumbersPerceptron
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appNumbersPerceptron
    PRIVATE Qt6::Quick
)
target_link_libraries(appNumbersPerceptron PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appNumbersPerceptron
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
