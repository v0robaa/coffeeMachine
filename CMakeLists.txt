cmake_minimum_required(VERSION 3.23)
project(coffeeMachine)

set(CMAKE_CXX_STANDARD 14)

add_executable(coffeeMachine coffeeMachine/Reader.h coffeeMachine/Reader.cpp coffeeMachine/cl_base.h coffeeMachine/cl_base.cpp coffeeMachine/CoffeeDispenser.h coffeeMachine/CoffeeDispenser.cpp coffeeMachine/ControlPanel.h coffeeMachine/ControlPanel.cpp coffeeMachine/MoneyAccepting.h coffeeMachine/MoneyAccepting.cpp coffeeMachine/MoneyRefund.h coffeeMachine/MoneyRefund.cpp coffeeMachine/Output.h coffeeMachine/Output.cpp coffeeMachine/App.h coffeeMachine/App.cpp coffeeMachine/main.cpp)
