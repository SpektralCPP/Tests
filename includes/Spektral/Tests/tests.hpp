#pragma once
#include <format>
#include <functional>
#include <iostream>
#include <string>
static_assert(__cplusplus >= 202002, "C++20 is the minimum required version");

namespace Spektral {
namespace Tests {
namespace Colors {
inline std::string color_out(const std::string &str,
                             const std::string &color_code) {
  return std::format("{}{}\033[0m", color_code, str);
}

inline std::string red_out(const std::string &str) {
  return color_out(str, "\033[31m");
}

inline std::string green_out(const std::string &str) {
  return color_out(str, "\033[32m");
}

inline std::string yellow_out(const std::string &str) {
  return color_out(str, "\033[33m");
}

inline std::string blue_out(const std::string &str) {
  return color_out(str, "\033[34m");
}

inline std::string magenta_out(const std::string &str) {
  return color_out(str, "\033[35m");
}

inline std::string cyan_out(const std::string &str) {
  return color_out(str, "\033[36m");
}

inline std::string white_out(const std::string &str) {
  return color_out(str, "\033[37m");
}

inline std::string black_out(const std::string &str) {
  return color_out(str, "\033[30m");
}

inline std::string bright_red_out(const std::string &str) {
  return color_out(str, "\033[1;31m");
}

inline std::string bright_green_out(const std::string &str) {
  return color_out(str, "\033[1;32m");
}

inline std::string bright_yellow_out(const std::string &str) {
  return color_out(str, "\033[1;33m");
}

inline std::string bright_blue_out(const std::string &str) {
  return color_out(str, "\033[1;34m");
}

inline std::string bright_magenta_out(const std::string &str) {
  return color_out(str, "\033[1;35m");
}

inline std::string bright_cyan_out(const std::string &str) {
  return color_out(str, "\033[1;36m");
}

inline std::string bright_white_out(const std::string &str) {
  return color_out(str, "\033[1;37m");
}
} // namespace Colors

template <typename T, typename... Args>
bool single_test(std::function<T(std::tuple<Args...>)> fn, T expected, std::tuple<Args...> args) {
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
      std::cerr
          << Colors::red_out(std::format(
                 "Error running fn for test case {}; Expected: {}, Found: {}",
                 ii + 1, io_pair.second, found))
          << std::endl;
      exit(EXIT_FAILURE);
    }
    ++ii;
  }
  std::cout << Colors::green_out("All tests passed") << std::endl;
}
