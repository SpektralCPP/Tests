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
 * @brief: A helper function to facilitate printing of colored output to the
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
 * @brief: Generate red text for printing to the console
 *
 * @param str The text to print with color
 * @return A formatted string with the relevant color codes
 **/
inline std::string red_out(const std::string &str) {
  return color_out(str, "\033[31m");
}

/**
 * @brief: Generate green text for printing to the console
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

template <typename T, typename... Args>
bool single_test(std::function<T(std::tuple<Args...>)> fn, T expected,
                 std::tuple<Args...> args) {
  T found = fn(args);
  if (found != expected) {
    std::cerr << std::format("Expectd: {} Found: {}", expected, found)
              << std::endl;
    return false;
  }
  return true;
}

template <typename T, typename... Args> struct test_group {
  using input = std::tuple<Args...>;
  using output = T;
  using io_pair = std::pair<input, output>;
  std::string name;
  std::function<output(input)> fn;
  std::vector<io_pair> io_pairs;
  void run();
};

template <typename T, typename... Args>
constexpr test_group<T, Args...>
add_test_group(std::string name, std::function<T(std::tuple<Args...>)> fn,
               std::vector<std::tuple<Args...>> inputs,
               std::vector<T> outputs) {
  if (inputs.size() != outputs.size()) {
    std::cerr << Colors::red_out("Mismatched input and output lengths")
              << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector<std::pair<std::tuple<Args...>, T>> io_pairs{inputs.size()};
  for (size_t ii = 0; ii < inputs.size(); ++ii) {
    io_pairs[ii] = {inputs[ii], outputs[ii]};
  }
  return test_group{name, fn, io_pairs};
}

template <typename T, typename... Args>
constexpr test_group<T, Args...>
add_test_group(std::string name, T (*fn)(std::tuple<Args...>),
               std::vector<std::tuple<Args...>> inputs,
               std::vector<T> outputs) {
  return add_test_group(name, std::function{fn}, inputs, outputs);
}

template <typename T, typename... Args>
constexpr std::function<T(std::tuple<Args...>)>
make_testable_fn(std::function<T(Args...)> fn) {
  return [&fn](std::tuple<Args...> args) -> T { return std::apply(fn, args); };
}
} // namespace Tests
} // namespace Spektral

template <typename T, typename... Args>
void Spektral::Tests::test_group<T, Args...>::run() {
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
