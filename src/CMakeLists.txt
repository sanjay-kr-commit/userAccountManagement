qt_add_executable(gui
        main.cpp
        gui.ui
        gui.cpp
        StaticVariables.h
        User.cpp
        User.h
        UserList.cpp
        UserList.h
)

# Use the Widgets module from Qt 6.
target_link_libraries(gui PRIVATE Qt6::Widgets)

# Install the executable
install(TARGETS gui DESTINATION bin)
