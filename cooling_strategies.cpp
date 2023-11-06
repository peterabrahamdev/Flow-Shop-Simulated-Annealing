#include "cooling_strategies.h"

double temp_lin_mult(int t0, double alpha, int t) {
    return t0 / (1 + (alpha * t));
}

double temp_lin_mult2(int t0, double alpha, int t) {
    return t0 / (1 + alpha * (t * t));
}

double temp_exp_mult(int t0, double alpha, int t) {
    return t0 * std::pow(alpha, t);
}

double temp_log_mult(int t0, double alpha, int t) {
    return t0 / (1 + alpha * std::log(1) + t);
}

double temp_non_monotonic(int f_star, int f_si, int t0, double alpha, int t) {
    return (1 + ((f_si - f_star) / f_si)) * temp_lin_mult(t0, alpha, t);
}

double choose_cooling_strategy(int cooling_strategy, int f_star, int f_si, int t0, double alpha, int t) {
    double temp;
    if (cooling_strategy == 1) {
        temp = temp_lin_mult(t0, alpha, t);
    } else if (cooling_strategy == 2) {
        temp = temp_lin_mult2(t0, alpha, t);
    } else if (cooling_strategy == 3) {
        temp = temp_exp_mult(t0, alpha, t);
    } else if (cooling_strategy == 4) {
        temp = temp_log_mult(t0, alpha, t);
    } else if (cooling_strategy == 5) {
        temp = temp_non_monotonic(f_star, f_si, t0, alpha, t);
    }
    return temp;
}

std::string cooling_strategy_name(int cooling_strategy) {
    std::string name;
    if (cooling_strategy == 1) {
        name = "Linear Multiplicative Type 1";
    } else if (cooling_strategy == 2) {
        name = "Linear Multiplicative Type 2";
    } else if (cooling_strategy == 3) {
        name = "Exponential Multiplicative";
    } else if (cooling_strategy == 4) {
        name = "Logarithmical Multiplicative";
    } else if (cooling_strategy == 5) {
        name = "Non-monotonic";
    }
    return name;
}