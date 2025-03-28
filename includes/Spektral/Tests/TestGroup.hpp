/**
 * @file TestGroup.hpp
 * @brief Defines the BaseTestGroup Interface and AssertionGroup class for
 * organizing and running test cases.
 *
 * This file provides the `BaseTestGroup` interface and the `AssertionGroup`
 * template class, which allows grouping multiple `TestCase` instances
 * that test a single function. It handles running these test cases and
 * reporting the overall results for the group.
 */

#pragma once
#include "TestCase.hpp"
#include <vector>

namespace Spektral::Tests {

/**
 * @brief An abstract base class for defining test groups.
 *
 * This interface provides a common `run()` method that derived classes
 * must implement to execute their contained tests. It also includes a
 * virtual destructor for proper cleanup in polymorphic scenarios.
 */
class BaseTestGroup {
public:
  /**
   * @brief Executes the tests contained within the group.
   *
   * This is a pure virtual method that must be implemented by derived
   * classes to define how the tests in the group are run.
   */
  virtual void run() = 0;

  /**
   * @brief Virtual destructor to ensure proper cleanup of derived class resources.
   */
  virtual ~BaseTestGroup() = default;
};

/**
 * @brief A template class for grouping and running assertion-based test cases
 * for a specific function.
 *
 * This class inherits from `BaseTestGroup` and provides functionality to
 * add multiple `TestCase` instances that test a function with the same
 * input and output types. It handles running all the added test cases
 * and reporting the number of passed and failed cases.
 *
 * @tparam output_t The expected output type of the function being tested.
 * @tparam input_ts... The input parameter types of the function being tested.
 */
template <typename output_t, typename... input_ts>
class AssertionGroup : public BaseTestGroup {
public:
  /**
   * @brief Constructs an AssertionGroup object with a name and a function object.
   *
   * @param name The name of this test group, used for reporting.
   * @param function A `std::function` object representing the function to be tested.
   */
  AssertionGroup(std::string name, std::function<output_t(input_ts...)> function)
      : group_name(std::move(name)), fn(std::move(function)) {}

  /**
   * @brief Constructs an AssertionGroup object with a name and a raw function pointer.
   *
   * @param name The name of this test group, used for reporting.
   * @param function A raw function pointer to the function to be tested.
   */
  AssertionGroup(std::string name, output_t (*function)(input_ts...))
      : group_name(std::move(name)), fn(std::move(std::function{function})) {}

public:
  /**
   * @brief Runs all the test cases added to this group.
   *
   * This method iterates through the added `TestCase` instances, executes
   * each one against the stored function, and reports the results to the
   * standard output. It also handles suppressing individual test case
   * success messages if a large number of test cases are present. Failures
   * are always reported, and a summary of passed and failed cases is printed
   * at the end.
   *
   * @override
   */
  void run() override {
    bool suppress = cases.size() >= 50;
    std::println(std::cout, "Running tests for test group: {}.", group_name);
    if (suppress) {
      std::println(
          std::cout,
          "Large number of test cases found: {}, output will be suppressed.",
          cases.size());
    }
    std::ofstream tty{"/dev/tty"};
    tty << std::unitbuf;
    std::vector<size_t> failing_cases;
    size_t tc_number = 0;
    for (TestCase<output_t, input_ts...> &case_ : cases) {
      if (!case_.run(fn, tc_number, tty, suppress)) {
        failing_cases.push_back(tc_number);
      }
      tc_number++;
    }
    if (!failing_cases.empty()) {
      std::print(std::cout, "The following cases failed: ");
      for (const auto &c : failing_cases) {
        std::print(std::cout, "{}, ", c);
      }
      std::cout << std::endl;
      std::cout << (cases.size() - failing_cases.size()) << " out of "
                << cases.size() << " passed." << std::endl;
      return;
    }
    std::println(std::cout, "All {} cases passed.", cases.size());
  }

  /**
   * @brief Adds a vector of test cases to this group.
   *
   * @param in_cases A `std::vector` containing `TestCase` instances to be added
   * to this test group.
   */
  void add_test_cases(std::vector<TestCase<output_t, input_ts...>> in_cases) {
    cases.insert(cases.end(), in_cases.begin(), in_cases.end());
  }

private:
  /** @brief The name of this test group. */
  std::string group_name;
  /** @brief The function to be tested by the cases in this group. */
  std::function<output_t(input_ts...)> fn;
  /** @brief A vector holding the test cases for this group. */
  std::vector<TestCase<output_t, input_ts...>> cases;
};
} // namespace Spektral::Tests
