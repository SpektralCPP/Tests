/**
 * @file Spektral/Tests/tests.hpp
 * @brief A quick testing framework for small C++ projects
 */

#pragma once
#include <format>
#include <functional>
#include <iostream>
#include <string>
static_assert(__cplusplus >= 202002, "C++20 is the minimum required version");

namespace Spektral {
namespace Tests {
namespace Colors {
/**
 * @brief A helper function to facilitate printing of colored output to the
 * console
 *
 * @param str The text to print with color
 * @param color_code The [ANSI color
 *
 * @return A formatted string with the relevant color codes
 *code](https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124) to
 *print with
 **/
inline std::string color_out(const std::string &str,
                             const std::string &color_code) {
  return std::format("{}{}\033[0m", color_code, str);
}

/**
 * @brief Generate red text for printing to the console
 *
 * @param str The text to print with color
 * @return A formatted string with the relevant color codes
 **/
inline std::string red_out(const std::string &str) {
  return color_out(str, "\033[31m");
}

/**
 * @brief Generate green text for printing to the console
 *
 * @param str The text to print with color
 * @return A formatted string with the relevant color codes
 **/
inline std::string green_out(const std::string &str) {
  return color_out(str, "\033[32m");
}

/**
 * @brief Generate yellow text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string yellow_out(const std::string &str) {
  return color_out(str, "\033[33m");
}

/**
 * @brief Generate blue text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string blue_out(const std::string &str) {
  return color_out(str, "\033[34m");
}

/**
 * @brief Generate magenta text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string magenta_out(const std::string &str) {
  return color_out(str, "\033[35m");
}

/**
 * @brief Generate cyan text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string cyan_out(const std::string &str) {
  return color_out(str, "\033[36m");
}

/**
 * @brief Generate white text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string white_out(const std::string &str) {
  return color_out(str, "\033[37m");
}

/**
 * @brief Generate black text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string black_out(const std::string &str) {
  return color_out(str, "\033[30m");
}

/**
 * @brief Generate bright_red text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string bright_red_out(const std::string &str) {
  return color_out(str, "\033[1;31m");
}

/**
 * @brief Generate bright_green text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string bright_green_out(const std::string &str) {
  return color_out(str, "\033[1;32m");
}

/**
 * @brief Generate bright_yellow text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string bright_yellow_out(const std::string &str) {
  return color_out(str, "\033[1;33m");
}

/**
 * @brief Generate bright_blue text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string bright_blue_out(const std::string &str) {
  return color_out(str, "\033[1;34m");
}

/**
 * @brief Generate bright_magenta text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string bright_magenta_out(const std::string &str) {
  return color_out(str, "\033[1;35m");
}

/**
 * @brief Generate bright_cyan text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string bright_cyan_out(const std::string &str) {
  return color_out(str, "\033[1;36m");
}

/**
 * @brief Generate bright_white text for printing to the console
 *
 * @param str The text to print with color
 * @return A formmated string with the relevant color codes
 **/
inline std::string bright_white_out(const std::string &str) {
  return color_out(str, "\033[1;37m");
}
} // namespace Colors

/**
 * @brief run a single test
 *
 * @param fn the function to test
 * @param args the arguments to test with
 * @param expected the expected output
 *
 * @tparam output_t the output type
 * @tparam ...inputs_t variadic parameter pack of outputs
 *
 * @return bool Returns whether or not the output matched the input
 */
template <typename output_t, typename... inputs_t>
bool single_test(std::function<output_t(std::tuple<inputs_t...>)> fn,
                 std::tuple<inputs_t...> args, output_t expected) {
  output_t found = fn(args);
  if (found != expected) {
    std::cerr << std::format("Expectd: {} Found: {}", expected, found)
              << std::endl;
    return false;
  }
  return true;
}

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

/**
 * @brief Creates a test group from a function, input tuples, and expected
 * outputs.
 *
 * This function constructs a `test_group` object by pairing the provided input
 * tuples with their corresponding expected outputs. It performs a size check to
 * ensure the number of inputs matches the number of outputs.
 *
 * @tparam output_t The type of the output of the function being tested.
 * @tparam inputs_t... The types of the input arguments of the function being
 * tested.
 * @param name The name of the test group.
 * @param fn The function to be tested, provided as a `std::function`.
 * @param inputs A vector of input tuples.
 * @param outputs A vector of expected outputs.
 * @return A `test_group` object containing the provided test data.
 *
 * @note If the sizes of `inputs` and `outputs` vectors do not match, the
 * program will terminate with an error message.
 */
template <typename output_t, typename... inputs_t>
constexpr test_group<output_t, inputs_t...>
add_test_group(std::string name,
               std::function<output_t(std::tuple<inputs_t...>)> fn,
               std::vector<std::tuple<inputs_t...>> inputs,
               std::vector<output_t> outputs) {
  if (inputs.size() != outputs.size()) {
    std::cerr << Colors::red_out("Mismatched input and output lengths")
              << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector<std::pair<std::tuple<inputs_t...>, output_t>> io_pairs{
      inputs.size()};
  for (size_t ii = 0; ii < inputs.size(); ++ii) {
    io_pairs[ii] = {inputs[ii], outputs[ii]};
  }
  return test_group{name, fn, io_pairs};
}

/**
 * @brief Creates a test group from a function pointer, input tuples, and
 * expected outputs.
 *
 * This overloaded version of `add_test_group` accepts a function pointer
 * instead of a `std::function`. It internally converts the function pointer to
 * a `std::function` and calls the primary `add_test_group` function.
 *
 * @tparam output_t The type of the output of the function being tested.
 * @tparam inputs_t... The types of the input arguments of the function being
 * tested.
 * @param name The name of the test group.
 * @param fn The function to be tested, provided as a function pointer.
 * @param inputs A vector of input tuples.
 * @param outputs A vector of expected outputs.
 * @return A `test_group` object containing the provided test data.
 */
template <typename output_t, typename... inputs_t>
constexpr test_group<output_t, inputs_t...>
add_test_group(std::string name, output_t (*fn)(std::tuple<inputs_t...>),
               std::vector<std::tuple<inputs_t...>> inputs,
               std::vector<output_t> outputs) {
  return add_test_group(name, std::function{fn}, inputs, outputs);
}

/**
 * @brief Convert any function to a function that can accept tuple
 *
 * @tparam output_t the output type
 * @tparam ...inputs_t variadic parameter pack of outputs
 *
 * @param fn Any function
 *
 * @return A function that accepts a tuple of arguments rather than arguments
 */
template <typename output_t, typename... inputs_t>
constexpr std::function<output_t(std::tuple<inputs_t...>)>
make_testable_fn(std::function<output_t(inputs_t...)> fn) {
  return [&fn](std::tuple<inputs_t...> args) -> output_t {
    return std::apply(fn, args);
  };
}
} // namespace Tests
} // namespace Spektral

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
