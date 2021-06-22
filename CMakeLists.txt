project(sender)
project(receiver)

add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)

target_link_libraries(sender ncurses)
