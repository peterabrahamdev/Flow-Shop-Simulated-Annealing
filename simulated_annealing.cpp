#include "simulated_annealing.h"
#include "cooling_strategies.h"
#include "flow_shop.h"
#include <iostream>

double probability(int t_star, int f_st, int temp) {
    double expon = static_cast<double>(t_star - f_st) / temp;
    return std::exp(-expon);
}

std::vector<int> simulated_annealing_tsum(const std::vector<std::vector<int>> &jobs, const std::vector<int> &s,
                                          ObjectFunctionResult (*object_f)(const std::vector<std::vector<int>> &,
                                                                           const std::vector<int> &, int, int,
                                                                           const std::vector<int> &), int iterations,
                                          int neighbors, int t0, int jobs_num, int machines_num, int cooling_strategy,
                                          const std::vector<int> &deadlines) {
    std::vector<int> s_best = s;  // stores the best order of jobs
    int t = 0;  // represents time
    try {
        int f_best = object_f(jobs, s_best, jobs_num, machines_num, deadlines).t_sum;  // stores the best Tsum
        std::vector<int> s_base = s_best;
        int f_base = f_best;
        double alpha = 0.8;  // alpha (should be between 0.8 - 0.9)
        for (int i = 0; i < iterations; ++i) {
            std::vector<int> s_best_neighbor = s_base;
            int f_best_neighbor = f_base;
            for (int j = 0; j < neighbors; ++j) {
                ++t;
                std::vector<int> s_neighbor = s_base;
                int a = rand() % s.size();
                int b = rand() % s.size();
                std::swap(s_neighbor[a], s_neighbor[b]);
                int f_neighbor = object_f(jobs, s_neighbor, jobs_num, machines_num, deadlines).t_sum;
                // -- START SIMULATED ANNEALING --
                if (f_neighbor < f_best_neighbor) {
                    f_best_neighbor = f_neighbor;
                    s_best_neighbor = s_neighbor;
                } else {
                    int temp = choose_cooling_strategy(cooling_strategy, f_best_neighbor, f_neighbor, t0, alpha, t);
                    double prob = probability(f_best_neighbor, f_neighbor, temp);
                    int randProb = rand() % 99;
                    if (randProb < prob * 100) {
                        f_best_neighbor = f_neighbor;
                        s_best_neighbor = s_neighbor;
                    }
                }
                // -- END SIMULATED ANNEALING --
            }
            s_base = s_best_neighbor;
            f_base = f_best_neighbor;
            if (f_base < f_best) {
                f_best = f_base;
                s_best = s_base;
            }

        }
    } catch (std::overflow_error &e) {
        std::cout << "\n!!! Overflow Error - Exited at: " << t << "/" << iterations * neighbors << " !!!\n";
        std::cerr << "Overflow error: " << e.what() << std::endl;
    }
    return s_best;
}

std::vector<int> simulated_annealing_cmax(const std::vector<std::vector<int>> &jobs, const std::vector<int> &s,
                                          ObjectFunctionResult (*object_f)(const std::vector<std::vector<int>> &,
                                                                           const std::vector<int> &, int, int,
                                                                           const std::vector<int> &), int iterations,
                                          int neighbors, int t0, int jobs_num, int machines_num, int cooling_strategy,
                                          const std::vector<int> &deadlines) {
    std::vector<int> s_best = s;
    int t = 0;  // represents time// stores the best order of jobs
    try {
        int f_best = object_f(jobs, s_best, jobs_num, machines_num, deadlines).c_max;  // stores the best Cmax
        std::vector<int> s_base = s_best;
        int f_base = f_best;
        double alpha = 0.8;  // alpha (should be between 0.8 - 0.9)
        for (int i = 0; i < iterations; ++i) {
            std::vector<int> s_best_neighbor = s_base;
            int f_best_neighbor = f_base;
            for (int j = 0; j < neighbors; ++j) {
                ++t;
                std::vector<int> s_neighbor = s_base;
                int a = rand() % s.size();
                int b = rand() % s.size();
                std::swap(s_neighbor[a], s_neighbor[b]);
                int f_neighbor = object_f(jobs, s_neighbor, jobs_num, machines_num, deadlines).c_max;
                // -- START SIMULATED ANNEALING --
                if (f_neighbor < f_best_neighbor) {
                    f_best_neighbor = f_neighbor;
                    s_best_neighbor = s_neighbor;
                } else {
                    int temp = choose_cooling_strategy(cooling_strategy, f_best_neighbor, f_neighbor, t0, alpha, t);
                    double prob = probability(f_best_neighbor, f_neighbor, temp);
                    int randProb = rand() % 99;
                    if (randProb < prob * 100) {
                        f_best_neighbor = f_neighbor;
                        s_best_neighbor = s_neighbor;
                    }
                }
                // -- END SIMULATED ANNEALING --
            }
            s_base = s_best_neighbor;
            f_base = f_best_neighbor;
            if (f_base < f_best) {
                f_best = f_base;
                s_best = s_base;
            }
        }
    } catch (std::overflow_error &e) {
        std::cout << "\n!!! Overflow Error - Exited at: " << t << "/" << iterations * neighbors << " !!!\n";
        std::cerr << "Overflow error: " << e.what() << std::endl;
    }
    return s_best;
}