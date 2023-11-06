#include "deadlines.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

std::vector<int> generate_deadlines(int machines_num, int jobs_num, int deadline_length) {
    std::vector<int> deadlines;
    deadlines.reserve(jobs_num);
    for (int i = 0; i < jobs_num; ++i) {
        deadlines.push_back(rand() % (deadline_length / 5) + deadline_length / 5);
    }
//    deadlines = {25, 30, 30, 45, 30};
    return deadlines;
}

Deadlines calculate_deadlines(const std::vector<std::vector<int>> &jobs, const std::vector<std::vector<int>> &job_end,
                              const std::vector<int> &deadlines) {
    int num_jobs = jobs.size();
    std::vector<int> end_times = job_end.back();
    std::vector<int> jobs_l(num_jobs);
    std::vector<int> jobs_t(num_jobs);

    for (int i = 0; i < num_jobs; ++i) {
        jobs_l[i] = end_times[i] - deadlines[i];
        jobs_t[i] = std::max(0, end_times[i] - deadlines[i]);
    }

    return {end_times, jobs_l, jobs_t, deadlines, jobs, std::accumulate(jobs_t.begin(), jobs_t.end(), 0)};
}

void print_deadlines_table(const std::vector<int> &end_times,
                           const std::vector<std::vector<int>> &jobs,
                           const std::vector<int> &jobs_l,
                           const std::vector<int> &jobs_t,
                           const std::vector<int> &deadlines) {
    std::cout << "DEADLINE TABLE:\n";

    std::cout << std::setw(5) << "Ji" << std::setw(10) << "Ci" << std::setw(10) << "di" << std::setw(10) << "Li"
              << std::setw(10) << "Ti" << std::endl;
    std::cout << "------------------------------------------------\n";
    for (size_t i = 0; i < jobs.size(); ++i) {
        std::cout << std::setw(5) << "J" << i + 1 << std::setw(10) << end_times[i] << std::setw(10) << deadlines[i]
                  << std::setw(10) << jobs_l[i] << std::setw(10) << jobs_t[i] << std::endl;
    }

    std::cout << "------------------------------------------------\n";
    std::cout << std::setw(5) << "SUM" << std::setw(40) << std::setw(31)
              << std::accumulate(jobs_l.begin(), jobs_l.end(), 0) << std::setw(11)
              << std::accumulate(jobs_t.begin(), jobs_t.end(), 0) << std::endl;
}