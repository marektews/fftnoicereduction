cmake_minimum_required(VERSION 3.16)

project(FFTNoiseReduction VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QML_IMPORT_PATH ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_SOURCE_DIR} CACHE STRING "" FORCE)
set(QML_DESIGNER_IMPORT_PATH ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_SOURCE_DIR} CACHE STRING "" FORCE)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appFFTNoiseReduction
    app.qrc
    main.cpp
    AudioFileLoader.h AudioFileLoader.cpp
    MyAVFormatContext.h MyAVFormatContext.cpp
    MyAVCodec.h MyAVCodec.cpp
    MyAVFrame.h MyAVFrame.cpp
    MyAVPacket.h MyAVPacket.cpp
    MySwrContext.h MySwrContext.cpp
    MyAVSamplesBuffer.h MyAVSamplesBuffer.cpp
    FFTRealBuffer.h FFTRealBuffer.cpp
    FFTComplexBuffer.h FFTComplexBuffer.cpp
    FFTPlan.h FFTPlan.cpp
)

qt_add_qml_module(appFFTNoiseReduction
    URI FFTNoiseReduction
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES AudioFileSourcer.h AudioFileSourcer.cpp
    SOURCES WaveShapeView.h WaveShapeView.cpp
    SOURCES SpectrogramView.h SpectrogramView.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFFTNoiseReduction PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFFTNoiseReduction
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

add_compile_definitions(appFFTNoiseReduction
    __STDC_CONSTANT_MACROS
)

if(WIN32)
    target_include_directories(appFFTNoiseReduction PRIVATE
        ${CMAKE_SOURCE_DIR}/win32/ffmpeg/include
        ${CMAKE_SOURCE_DIR}/win32/fftw
    )

    target_link_directories(appFFTNoiseReduction PRIVATE
        ${CMAKE_SOURCE_DIR}/win32/ffmpeg/lib
        ${CMAKE_SOURCE_DIR}/win32/fftw
    )
    target_link_libraries(appFFTNoiseReduction
        PRIVATE fftw3-3
    )
else()
    target_link_libraries(appFFTNoiseReduction
        PRIVATE fftw3
    )
endif()

target_link_libraries(appFFTNoiseReduction
    PRIVATE Qt6::Quick
    PRIVATE avformat
    PRIVATE avcodec
    PRIVATE avutil
    PRIVATE swresample
)

include(GNUInstallDirs)
install(TARGETS appFFTNoiseReduction
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
