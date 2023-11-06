#include "flow_shop.h"
#include <iostream>
#include <string>
#include <ctime>
#include "deadlines.h"

std::vector<std::vector<int>> jobs_input(int jobs_num, int machines_num) {
    std::vector<std::vector<int>> jobs(jobs_num, std::vector<int>(machines_num, 0));

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < jobs_num; ++i) {
        for (int j = 0; j < machines_num; ++j) {
            jobs[i][j] = std::rand() % 8 + 1;  // Generate a random number between 1 and 8
        }
    }

//    jobs = {
//            {3, 4, 6, 7},
//            {4, 5, 4, 6},
//            {8, 7, 2, 2},
//            {5, 3, 1, 5},
//            {7, 6, 8, 4}
//    };

    return jobs;
}

ObjectFunctionResult
object_function(const std::vector<std::vector<int>> &jobs, const std::vector<int> &order, int jobs_num,
                int machines_num, const std::vector<int> &deadlines) {
    std::vector<std::vector<int>> job_begin(machines_num, std::vector<int>(jobs_num, 0));
    std::vector<std::vector<int>> job_end(machines_num, std::vector<int>(jobs_num, 0));
    std::vector<int> cost(jobs_num, 0);

    for (int i = 0; i < machines_num; ++i) {
        for (int j = 0; j < jobs_num; ++j) {
            int c_max = cost[j];
            if (j > 0) {
                c_max = std::max(cost[j - 1], cost[j]);
            }
            cost[j] = c_max + jobs[order[j] - 1][i];
            job_end[i][j] = cost[j];
            job_begin[i][j] = job_end[i][j] - jobs[order[j] - 1][i];
            c_max = job_end[i][j];
        }
    }

    int t_sum = calculate_deadlines(jobs, job_end, deadlines).t_sum;

    return {cost[jobs_num - 1], t_sum, job_begin, job_end};
}

int deadline_length(const std::vector<std::vector<int>> &jobs, const std::vector<int> &order, int jobs_num,
                    int machines_num) {
    std::vector<int> cost(jobs_num, 0);

    for (int i = 0; i < machines_num; ++i) {
        int c_max = 0;
        for (int j = 0; j < jobs_num; ++j) {
            c_max = std::max(c_max, j > 0 ? cost[j - 1] : 0) + jobs[order[j] - 1][i];
            cost[j] = c_max;
        }
    }

    return cost[jobs_num - 1];
}

void print_flow_shop(int machines_num, int jobs_num, const std::vector<std::vector<int>> &job_begin,
                     const std::vector<std::vector<int>> &job_end) {
    std::vector<int> represent_job(jobs_num);
    for (int i = 0; i < jobs_num; ++i) {
        represent_job[i] = i + 1;
    }

    // printing the Gantt chart
    std::cout << "\nFLOW-SHOP GANTT CHART:\n\n";
    for (int i = 0; i < machines_num; ++i) {
        for (int j = 0; j < jobs_num; ++j) {
            if (j == 0 && job_begin[i][j] != 0) {
                std::string segment = std::string(job_begin[i][j], '-');
                for (char &ch: segment) {
                    std::cout << ch << "|";
                }
            }
            if (j < jobs_num - 1) {
                std::string segment = std::string(job_end[i][j] - job_begin[i][j], '0' + represent_job[j]);
                for (char &ch: segment) {
                    std::cout << ch << "|";
                }
                std::string segment2 = std::string(job_begin[i][j + 1] - job_end[i][j], '-');
                for (char &ch: segment2) {
                    std::cout << ch << "|";
                }
            }
            if (j == jobs_num - 1) {
                std::string segment = std::string(job_end[i][j] - job_begin[i][j], '0' + represent_job[j]);
                for (char &ch: segment) {
                    std::cout << ch << "|";
                }
            }
        }
        std::cout << "\n\n";
    }

}