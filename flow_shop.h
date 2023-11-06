#ifndef FLOW_SHOP_H
#define FLOW_SHOP_H

#include <vector>
#include "simulated_annealing.h"
#include "deadlines.h"

// Forward declaration of ObjectFunctionResult
struct ObjectFunctionResult;

/**
 * @brief Provides jobs and machines matrix.
 *
 * This function provides a matrix by generating random numbers for the jobs' lengths on each machine.
 *
 * @param jobs_num number of jobs.
 * @param machines_num number of machines.
 * @return The jobs' matrix.
 */
std::vector<std::vector<int>> jobs_input(int jobs_num, int machines_num);

/**
 * @brief Calculate various metrics related to job scheduling.
 *
 * The function takes as input a set of jobs, their order, the number of jobs,
 * the number of machines, and deadlines. It computes the start and end times
 * of each job on each machine, the total cost of the scheduling, and the sum
 * of tardiness with respect to given deadlines.
 *
 * @param jobs A 2D vector representing the processing times of jobs on each machine.
 * @param order A vector specifying the order in which jobs are processed.
 * @param jobs_num An integer representing the total number of jobs.
 * @param machines_num An integer representing the total number of machines.
 * @param deadlines A vector representing the deadlines for each job.
 *
 * @return ObjectFunctionResult A struct containing the calculated metrics,
 * including the total cost, total tardiness sum, and matrices for job start
 * and end times.
 */
using ObjectFunction = ObjectFunctionResult (*)(const std::vector<std::vector<int>>&,
                                                const std::vector<int>&,
                                                int,
                                                int,
                                                const std::vector<int>&);

/**
 * @brief Calculate the length of the schedule based on job deadlines.
 *
 * The function takes as input a set of jobs, their order, the number of jobs,
 * and the number of machines. It computes the completion time of the last job
 * in the provided order, representing the length of the schedule based on job
 * deadlines.
 *
 * @param jobs A 2D vector representing the processing times of jobs on each machine.
 * @param order A vector specifying the order in which jobs are processed.
 * @param jobs_num An integer representing the total number of jobs.
 * @param machines_num An integer representing the total number of machines.
 *
 * @return int The length of the schedule, i.e., the completion time of the last job
 * in the provided order.
 */
int deadline_length(const std::vector<std::vector<int>>& jobs,
                    const std::vector<int>& order,
                    int jobs_num,
                    int machines_num);

/**
 * @brief Print the Gantt chart for a flow-shop scheduling problem.
 *
 * The function takes as input the number of machines, the number of jobs,
 * matrices representing the start and end times of each job on each machine,
 * and prints the Gantt chart for the flow-shop scheduling.
 *
 * @param machines_num An integer representing the total number of machines.
 * @param jobs_num An integer representing the total number of jobs.
 * @param job_begin A 2D matrix representing the start times of each job on each machine.
 * @param job_end A 2D matrix representing the end times of each job on each machine.
 */
void print_flow_shop(int machines_num,
                     int jobs_num,
                     const std::vector<std::vector<int>>& job_begin,
                     const std::vector<std::vector<int>>& job_end);

#endif // FLOW_SHOP_H
