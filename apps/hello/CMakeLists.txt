set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

qt_add_executable(hello
    main.cpp
)

target_link_libraries(hello PRIVATE Qt6::Core)

enable_iwyu(hello)
