set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    OpenGL
    OpenGLWidgets
    Widgets
)
qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

qt_add_executable(hello_gui
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    resources.qrc
)

target_link_libraries(hello_gui PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Widgets
)

set_target_properties(hello_gui PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
