#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include "flow_shop.h"
#include "cooling_strategies.h"
#include "deadlines.h"

/**
 * @brief Struct representing the result of an objective function.
 *
 * This struct contains information about the result of an objective function,
 * including makespan (Cmax), total tardiness sum, and details about job start
 * and end times on each machine.
 */
struct ObjectFunctionResult {
    int c_max;
    int t_sum;
    std::vector<std::vector<int>> job_begin;
    std::vector<std::vector<int>> job_end;
};

/**
 * @brief Calculate the probability of accepting a worse solution in simulated annealing.
 *
 * The function takes as input the best-known objective function value from a previous
 * iteration, the current objective function value, and the current temperature. It calculates
 * the probability of accepting a worse solution based on the temperature and the difference
 * between the current and best-known objective function values.
 *
 * @param t_star Best-known objective function value from a previous iteration.
 * @param f_st Current objective function value.
 * @param temp Current temperature in simulated annealing.
 *
 * @return double The calculated probability of accepting a worse solution.
 */
double probability(int t_star, int f_st, int temp);


using ObjectFunction = ObjectFunctionResult (*)(const std::vector<std::vector<int>> &,
                                                const std::vector<int> &,
                                                int,
                                                int,
                                                const std::vector<int> &);

/**
 * @brief Perform simulated annealing to find the best job order that minimizes makespan (Cmax).
 *
 * The function takes as input the processing times of jobs, an initial job order,
 * an objective function to evaluate the makespan, the number of iterations,
 * the number of neighbors considered at each iteration, the initial temperature,
 * the number of jobs, the number of machines, the chosen cooling strategy, and deadlines.
 * It returns the best job order found during the simulated annealing process.
 *
 * @param jobs A 2D vector representing the processing times of jobs on each machine.
 * @param s An initial job order.
 * @param object_f A function to calculate the objective function result.
 * @param iterations The number of iterations in the simulated annealing process.
 * @param neighbors The number of neighbors considered at each iteration.
 * @param t0 Initial temperature.
 * @param jobs_num The total number of jobs.
 * @param machines_num The total number of machines.
 * @param cooling_strategy An integer representing the chosen cooling strategy.
 * @param deadlines A vector representing the deadlines for each job.
 *
 * @return std::vector<int> The best job order found during simulated annealing.
 */
std::vector<int> simulated_annealing_cmax(const std::vector<std::vector<int>> &jobs,
                                          const std::vector<int> &s,
                                          ObjectFunction object_f,
                                          int iterations,
                                          int neighbors,
                                          int t0,
                                          int jobs_num,
                                          int machines_num,
                                          int cooling_strategy,
                                          const std::vector<int> &deadlines);

/**
 * @brief Perform simulated annealing to find the best job order that minimizes total tardiness.
 *
 * The function takes as input the processing times of jobs, an initial job order,
 * an objective function to evaluate the total tardiness, the number of iterations,
 * the number of neighbors considered at each iteration, the initial temperature,
 * the number of jobs, the number of machines, the chosen cooling strategy, and deadlines.
 * It returns the best job order found during the simulated annealing process.
 *
 * @param jobs A 2D vector representing the processing times of jobs on each machine.
 * @param s An initial job order.
 * @param object_f A function to calculate the objective function result.
 * @param iterations The number of iterations in the simulated annealing process.
 * @param neighbors The number of neighbors considered at each iteration.
 * @param t0 Initial temperature.
 * @param jobs_num The total number of jobs.
 * @param machines_num The total number of machines.
 * @param cooling_strategy An integer representing the chosen cooling strategy.
 * @param deadlines A vector representing the deadlines for each job.
 *
 * @return std::vector<int> The best job order found during simulated annealing.
 */
std::vector<int> simulated_annealing_tsum(const std::vector<std::vector<int>> &jobs,
                                          const std::vector<int> &s,
                                          ObjectFunction object_f,
                                          int iterations,
                                          int neighbors,
                                          int t0,
                                          int jobs_num,
                                          int machines_num,
                                          int cooling_strategy,
                                          const std::vector<int> &deadlines);

#endif // SIMULATED_ANNEALING_H
