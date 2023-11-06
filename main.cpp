#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "deadlines.h"
#include "flow_shop.h"
#include "simulated_annealing.h"
#include <chrono>
#include <iomanip>

// Function declarations
void separator();

template<typename T>
void print_vector(const std::vector<T> &vec);

ObjectFunctionResult
object_function(const std::vector<std::vector<int>> &jobs, const std::vector<int> &order, int jobs_num,
                int machines_num, const std::vector<int> &deadlines);


void separator() {
    std::cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
}

template<typename T>
void print_vector(const std::vector<T> &vec) {
    for (const auto &elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

int main() {
    // The console code page needs to be set to UTF-8 in order to be able to print out the "Σ" character
    system("chcp 65001");

    // INPUTS
    int jobs_num, machines_num, iteration_num, cooling_strategy, init_temperature;
    std::cout << "Number of Jobs: ";
    std::cin >> jobs_num;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Number of Machines: ";
    std::cin >> machines_num;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Number of Iterations: ";
    std::cin >> iteration_num;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "============================\n"
              << "COOLING STRATEGIES\n1 | Linear Multiplicative Type 1\n2 | Linear Multiplicative Type 2\n3 | Exponential Multiplicative\n4 | Logarithmical Multiplicative\n5 | Non-monotonic\n"
              << "============================\n";
    std::cout << "Number of the cooling strategy: ";
    std::cin >> cooling_strategy;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Initial temperature: ";
    std::cin >> init_temperature;

    // ARRANGING INPUTS
    std::vector<int> init_order(jobs_num);
    for (int i = 0; i < jobs_num; ++i)
        init_order[i] = i + 1;
    std::shuffle(init_order.begin(), init_order.end(), std::mt19937(std::random_device()()));

    // INITIALIZATION
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> jobs = jobs_input(jobs_num, machines_num);
    std::vector<int> gen_deadlines = generate_deadlines(machines_num, jobs_num,
                                                        deadline_length(jobs, init_order, jobs_num, machines_num));
    std::vector<int> order = simulated_annealing_cmax(jobs, init_order, object_function, iteration_num, 100,
                                                      init_temperature, jobs_num,
                                                      machines_num, cooling_strategy, gen_deadlines);
    std::vector<int> order2 = simulated_annealing_tsum(jobs, init_order, object_function, iteration_num, 100,
                                                       init_temperature, jobs_num,
                                                       machines_num, cooling_strategy, gen_deadlines);
    auto result = object_function(jobs, order, jobs_num, machines_num, gen_deadlines);
    auto result2 = object_function(jobs, order2, jobs_num, machines_num, gen_deadlines);
    auto deadlines = calculate_deadlines(jobs, result.job_end, gen_deadlines);
    auto deadlines2 = calculate_deadlines(jobs, result2.job_end, gen_deadlines);

    // Here I assume that the runtime ie. the calculations end when the printing out starts
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // PRINTING OUT THE RESULTS
    separator();
    std::cout << "CMAX ";
    print_flow_shop(machines_num, jobs_num, result.job_begin, result.job_end);

    separator();
    std::cout << "\u03A3" << "Ti ";
    print_flow_shop(machines_num, jobs_num, result2.job_begin, result2.job_end);

    separator();
    std::cout << "CMAX ";
    print_deadlines_table(deadlines.end_times, jobs, deadlines.jobs_l, deadlines.jobs_t, deadlines.deadlines);

    separator();
    std::cout << "\u03A3" << "Ti ";
    print_deadlines_table(deadlines2.end_times, jobs, deadlines2.jobs_l, deadlines2.jobs_t, deadlines2.deadlines);

    separator();
    std::cout << "Cmax data:\n";
    std::cout << "Initial order: ";
    print_vector(init_order);
    std::cout << "Best order: ";
    print_vector(order);
    std::cout << "C-max: " << result.c_max << "\n";
    std::cout << "T-sum: " << deadlines.t_sum << "\n";

    separator();
    std::cout << "ΣTi data:\n";
    std::cout << "Initial order: ";
    print_vector(init_order);
    std::cout << "Best order: ";
    print_vector(order2);
    std::cout << "C-max: " << result2.c_max << "\n";
    std::cout << "T-sum: " << deadlines2.t_sum << "\n";

    separator();


    std::cout << "Runtime: " << std::fixed << std::setprecision(3) << static_cast<double>(duration.count()) / 1000.0
              << " seconds\n";

    return 0;
}
