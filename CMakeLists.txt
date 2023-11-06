cmake_minimum_required(VERSION 3.10)
project(SimulatedAnnealing)

set(CMAKE_CXX_STANDARD 11)


add_executable(SimulatedAnnealing
        main.cpp
        deadlines.cpp
        cooling_strategies.cpp
        flow_shop.cpp
        simulated_annealing.cpp
        # Add other source files here
        )



# Add any additional configurations or libraries if needed
