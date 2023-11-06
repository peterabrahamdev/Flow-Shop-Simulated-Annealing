#ifndef DEADLINES_H
#define DEADLINES_H

#include <vector>
#include <numeric>

/**
 * @brief Struct representing deadlines-related information.
 *
 * This struct encapsulates various data related to deadlines, including
 * end times, job lateness, job tardiness, original deadlines, processed jobs,
 * and the total tardiness sum.
 */
struct Deadlines {
    std::vector<int> end_times;
    std::vector<int> jobs_l;
    std::vector<int> jobs_t;
    std::vector<int> deadlines;
    std::vector<std::vector<int>> jobs;
    int t_sum;
};

/**
 * @brief Calculate job deadlines and related metrics based on job end times.
 *
 * The function takes as input the processing times of jobs, their end times,
 * and the provided deadlines. It computes the lateness and tardiness for each
 * job, as well as the total tardiness sum.
 *
 * @param jobs A 2D vector representing the processing times of jobs on each machine.
 * @param job_end A 2D vector representing the end times of each job on each machine.
 * @param deadlines A vector representing the deadlines for each job.
 *
 * @return Deadlines A struct containing calculated metrics, including:
 * - end_times: The end times of each job in the last machine.
 * - jobs_l: The lateness of each job (difference between end time and deadline).
 * - jobs_t: The tardiness of each job (max of 0 and difference between end time and deadline).
 * - deadlines: The original deadlines provided.
 * - jobs: The processing times of jobs.
 * - t_sum: The total tardiness sum.
 */
Deadlines calculate_deadlines(const std::vector<std::vector<int>> &jobs,
                              const std::vector<std::vector<int>> &job_end,
                              const std::vector<int> &deadlines);

/**
 * @brief Generate deadlines for jobs in a scheduling problem.
 *
 * The function takes as input the number of machines, the number of jobs,
 * and a length representing the overall schedule deadline. It generates and
 * returns a vector containing deadlines for each job.
 *
 * @param machines_num An integer representing the total number of machines.
 * @param jobs_num An integer representing the total number of jobs.
 * @param deadline_length An integer representing the overall schedule deadline.
 *
 * @return std::vector<int> A vector containing deadlines for each job.
 */
std::vector<int> generate_deadlines(int machines_num, int jobs_num, int deadline_length);

/**
 * @brief Print a table displaying job deadlines and related metrics.
 *
 * The function takes as input the end times of jobs, the processing times of jobs,
 * the lateness, tardiness, and original deadlines. It prints a formatted table
 * displaying information for each job, including job index, completion time, deadline,
 * lateness, and tardiness. Additionally, it shows the sum of lateness and tardiness.
 *
 * @param end_times A vector representing the end times of each job.
 * @param jobs A 2D vector representing the processing times of jobs on each machine.
 * @param jobs_l A vector representing the lateness of each job.
 * @param jobs_t A vector representing the tardiness of each job.
 * @param deadlines A vector representing the original deadlines for each job.
 */
void print_deadlines_table(const std::vector<int> &end_times,
                           const std::vector<std::vector<int>> &jobs,
                           const std::vector<int> &jobs_l,
                           const std::vector<int> &jobs_t,
                           const std::vector<int> &deadlines);

#endif // DEADLINES_H
