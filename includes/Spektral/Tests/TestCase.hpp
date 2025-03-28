/**
 * @file TestCase.hpp
 * @brief Defines a generic TestCase class for a testing framework.
 *
 * This file provides the `TestCase` class template, which allows defining
 * individual test cases with expected outputs and input parameters. It
 * also includes functionality to run these test cases against a given
 * function and report the results.
 */

#pragma once

#include <cstdlib>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <tuple>

namespace Spektral::Tests {

/**
 * @brief Enumeration for specifying parameter options for a test case.
 */
enum class param_option : unsigned char {
  /** @brief Indicates that a test case failure is optional and will not terminate the test run. */
  OPTIONAL = 0x0,
  /** @brief Indicates that a test case failure is not optional and will critically fail the test run. */
  NOT_OPTIONAL = 0x1,
};

/**
 * @brief A template class representing a single test case.
 *
 * This class holds the expected output and input parameters for a test,
 * and provides a method to run the test against a given function.
 *
 * @tparam output_t The expected output type of the function under test.
 * @tparam input_ts... The input parameter types of the function under test.
 */
template <typename output_t, typename... input_ts> class TestCase {
public:
  /**
   * @brief Deleted default constructor to prevent accidental instantiation without parameters.
   */
  TestCase() = delete;

  /**
   * @brief Constructs a TestCase object.
   *
   * @param expect The expected output value for this test case.
   * @param inputs... The input values to be passed to the function under test.
   */
  TestCase(output_t expect, input_ts... inputs)
      : expected(expect), inputs(std::tuple{inputs...}) {}

  /**
   * @brief Runs the test case against the provided function.
   *
   * This method applies the stored input parameters to the given function
   * and compares the result with the expected output. It prints a message
   * indicating whether the test passed or failed to the standard output
   * stream and optionally to a provided output file stream.
   *
   * @param fn The function to be tested. It should accept the `input_ts`
   * as arguments and return a value of type `output_t`.
   * @param tc_number The sequential number of this test case for reporting purposes.
   * @param tty A reference to an output file stream (e.g., for logging).
   * @param suppress If true, suppresses the "passed" message for successful tests.
   * @return True if the test case passed, false otherwise (only for optional failures).
   *
   * @remark If the test case is marked as not optional and the assertion fails,
   * the program will terminate with `EXIT_FAILURE`.
   */
  bool run(const std::function<output_t(input_ts...)> &fn, size_t tc_number,
           std::ofstream &tty, bool suppress = false) const {
    output_t found = std::apply(fn, inputs);
    if (found == expected) {
      if (!suppress) {
        std::print(tty, "\033[32m");
        std::println(std::cout, "Test Case # {} passed.", tc_number);
        std::print(tty, "\033[0m");
      }
      return true;
    }
    if (is_optional()) {
      if (!suppress) {
        tty << "\033[31m";
        std::cout << std::format(
                             "Test Case # {} failed. Expected: {} but Found: {}",
                             tc_number, expected, found)
                  << std::endl;
        tty << "\033[0m";
      }
      return false;
    }
    // this should be unsuppressable imo
    tty << "\033[31m";
    std::cout
        << std::format(
                "Test Case # {} critically failed. Expected: {} but Found: {}",
                tc_number, expected, found)
        << std::endl;
    tty << "\033[0m";
    exit(EXIT_FAILURE);
  }

  /**
   * @brief Overloads the pipe operator to set parameter options for the test
   * case.
   *
   * This allows modifying the behavior of the test case, such as marking it as
   * optional.
   *
   * @param p The `param_option` to set.
   * @return A reference to the modified `TestCase` object.
   */
  TestCase &operator|(param_option &&p) {
    params ^= static_cast<unsigned char>(p);
    return *this;
  }

private:
  /**
   * @brief Checks if the test case is marked as optional.
   *
   * @return True if the test case is optional, false otherwise.
   */
  inline const bool is_optional() const { return !(params & 0x01); }

private:
  /** @brief The input parameters for the test case, stored as a tuple. */
  std::tuple<input_ts...> inputs;
  /** @brief The expected output value for this test case. */
  output_t expected;
  /**
   * @brief Bitmask for storing various test case parameters.
   *
   * Bit 0 (LSB): is_optional - 1 = NOT_OPTIONAL, 0 = OPTIONAL (default)
   * Bits 1-7: Reserved for future parameter options.
   */
  unsigned char params = 0x00;
};
} // namespace Spektral::Tests
