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
    ExtraWindow.cpp
    TriangleWidget.cpp
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

enable_iwyu(hello_gui)

#
# Copy shaders to the output directory
#
add_custom_target(copy-vertex-shader ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shaders/vertex.vert)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders/vertex.vert
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex.vert
        ${CMAKE_CURRENT_BINARY_DIR}/shaders/vertex.vert
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex.vert
)

add_custom_target(copy-fragment-shader ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shaders/fragment.frag)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders/fragment.frag
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment.frag
        ${CMAKE_CURRENT_BINARY_DIR}/shaders/fragment.frag
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment.frag
)
