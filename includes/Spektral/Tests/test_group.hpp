#pragma once
#include "colors.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <tuple>

namespace Spektral {
namespace Tests {
/**
 * @brief A collection of test caes
 *
 * @tparam output_t the output type
 * @tparam ...inputs_t variadic parameter pack of outputs
 */
template <typename output_t, typename... inputs_t> struct test_group {
  /**
   * @brief A tuple representing a single test case's input.
   *
   * The `input` type alias is defined using the provided argument types,
   * allowing multiple inputs to be grouped together in a structured format.
   */
  using input = std::tuple<inputs_t...>;

  /**
   * @brief Type of the expected output from processing an input tuple.
   *
   * This type corresponds to the return type of the function that processes
   * each test case's input. It is specified by the template parameter `T`.
   */
  using output = output_t;

  /**
   * @brief A pair representing a single test case with input and expected
   * output.
   *
   * The `io_pair` type alias defines a relationship between an input tuple
   * and its corresponding expected output. This allows for easy definition
   * and verification of individual test cases within the group.
   */
  using io_pair = std::pair<input, output>;

  /**
   * @brief Name of the test group.
   *
   * A descriptive name that identifies this specific group of tests.
   */
  std::string name;

  /**
   * @brief Function to process an input tuple and produce an output.
   *
   * This function is used to evaluate each input case within `io_pairs`.
   * It takes a single argument of type `input` and returns a value of
   * type `output`. The behavior should align with the expected logic for
   * processing inputs in this test group.
   */
  std::function<output(input)> fn;

  /**
   * @brief A vector containing all input-output pairs for testing.
   *
   * Each element is an instance of `io_pair`, representing a specific
   * test case with its expected result. This collection allows for batch
   * processing and validation of multiple scenarios.
   */
  std::vector<io_pair> io_pairs;

  /**
   * @brief Run all the tests within this group.
   *
   * The `run` function executes each test case in `io_pairs`, applying
   * the function `fn` to process the input, and compares the result with
   * the expected output. This function is responsible for iterating through
   * the test cases, invoking the processing function, and managing any
   * necessary assertions or validations.
   */
  void run();
};
}; // namespace Tests
}; // namespace Spektral

template <typename output_t, typename... inputs_t>
void Spektral::Tests::test_group<output_t, inputs_t...>::run() {
  std::cout << Colors::bright_white_out(
                   std::format("Running Test Group: {}", name))
            << std::endl;
  for (size_t ii = 0; const io_pair &io_pair : io_pairs) {
    auto found = fn(io_pair.first);
    if (found != io_pair.second) {
      std::cerr << Colors::red_out(
                       std::format("Error running function for test case {}; "
                                   "Expected: {}, Found: {}",
                                   ii + 1, io_pair.second, found))
                << std::endl;
      exit(EXIT_FAILURE);
    }
    ++ii;
  }
  std::cout << Colors::green_out("All tests passed") << std::endl;
}
