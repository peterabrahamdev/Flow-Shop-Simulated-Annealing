#ifndef COOLING_STRATEGIES_H
#define COOLING_STRATEGIES_H

#include <cmath>
#include <string>

/**
 * @brief Linear multiplicative cooling strategy for simulated annealing.
 *
 * The function calculates the temperature for the next iteration using the
 * linear multiplicative cooling strategy. The temperature decreases linearly
 * with the number of iterations.
 *
 * @param t0 Initial temperature.
 * @param alpha Cooling rate.
 * @param t Current iteration number.
 * @return double The calculated temperature for the next iteration.
 */
double temp_lin_mult(int t0, double alpha, int t);

/**
 * @brief Modified linear multiplicative cooling strategy for simulated annealing.
 *
 * The function calculates the temperature for the next iteration using a modified
 * linear multiplicative cooling strategy. The temperature decreases with the square
 * of the number of iterations, allowing smaller values.
 *
 * @param t0 Initial temperature.
 * @param alpha Cooling rate.
 * @param t Current iteration number.
 * @return double The calculated temperature for the next iteration.
 */
double temp_lin_mult2(int t0, double alpha, int t);

/**
 * @brief Exponential multiplicative cooling strategy for simulated annealing.
 *
 * The function calculates the temperature for the next iteration using the
 * exponential multiplicative cooling strategy. The temperature decreases
 * exponentially with the number of iterations.
 *
 * @param t0 Initial temperature.
 * @param alpha Cooling rate.
 * @param t Current iteration number.
 * @return double The calculated temperature for the next iteration.
 */
double temp_exp_mult(int t0, double alpha, int t);

/**
 * @brief Logarithmic multiplicative cooling strategy for simulated annealing.
 *
 * The function calculates the temperature for the next iteration using the
 * logarithmic multiplicative cooling strategy. The temperature decreases
 * logarithmically with the number of iterations.
 *
 * @param t0 Initial temperature.
 * @param alpha Cooling rate.
 * @param t Current iteration number.
 * @return double The calculated temperature for the next iteration.
 */
double temp_log_mult(int t0, double alpha, int t);

/**
 * @brief Non-monotonic multiplicative cooling strategy for simulated annealing.
 *
 * The function calculates the temperature for the next iteration using a
 * non-monotonic multiplicative cooling strategy. It incorporates the current
 * and best-known objective function values.
 *
 * @param f_star Best-known objective function value.
 * @param f_si Current objective function value.
 * @param t0 Initial temperature.
 * @param alpha Cooling rate.
 * @param t Current iteration number.
 * @return double The calculated temperature for the next iteration.
 */
double temp_non_monotonic(int f_star, int f_si, int t0, double alpha, int t);

/**
 * @brief Choose a cooling strategy for simulated annealing and calculate the next temperature.
 *
 * The function takes as input the chosen cooling strategy identifier, the best-known
 * objective function value, the current objective function value, the initial temperature,
 * the cooling rate, and the current iteration number. It selects the specified cooling
 * strategy and calculates the temperature for the next iteration.
 *
 * @param cooling_strategy An integer representing the chosen cooling strategy:
 *   - 1: Linear multiplicative cooling.
 *   - 2: Modified linear multiplicative cooling.
 *   - 3: Exponential multiplicative cooling.
 *   - 4: Logarithmic multiplicative cooling.
 *   - 5: Non-monotonic multiplicative cooling.
 * @param f_star Best-known objective function value.
 * @param f_si Current objective function value.
 * @param t0 Initial temperature.
 * @param alpha Cooling rate.
 * @param t Current iteration number.
 *
 * @return double The calculated temperature for the next iteration based on the chosen cooling strategy.
 */
double choose_cooling_strategy(int cooling_strategy, int f_star, int f_si, int t0, double alpha, int t);

/**
 * @brief Get the name of a specified cooling strategy.
 *
 * The function takes as input the identifier of a cooling strategy and returns
 * the corresponding name of the strategy.
 *
 * @param cooling_strategy An integer representing the cooling strategy:
 *   - 1: Linear Multiplicative Type 1.
 *   - 2: Linear Multiplicative Type 2.
 *   - 3: Exponential Multiplicative.
 *   - 4: Logarithmic Multiplicative.
 *   - 5: Non-monotonic.
 *
 * @return std::string The name of the specified cooling strategy.
 */
std::string cooling_strategy_name(int cooling_strategy);

#endif // COOLING_STRATEGIES_H
