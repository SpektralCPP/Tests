#pragma once
#include <format>
#include <functional>
#include <iostream>

namespace Spektral {
namespace Tests {

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
 * @brief Convert any function to a function that can accept tuple
 *
 * @tparam output_t the output type
 * @tparam ...inputs_t variadic parameter pack of outputs
 *
 * @param fn Any std::function
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

/**
 * @brief Convert any function pointer to a function that can accept tuple
 *
 * @tparam output_t the output type
 * @tparam ...inputs_t variadic parameter pack of outputs
 *
 * @param fn Any std::function
 *
 * @return A function that accepts a tuple of arguments rather than arguments
 */
template <typename output_t, typename... inputs_t>
constexpr std::function<output_t(std::tuple<inputs_t...>)>
make_testable_fn(output_t (*fn)(inputs_t...)) {
  return [&fn](std::tuple<inputs_t...> args) -> output_t {
    return std::apply(fn, args);
  };
}
} // namespace Tests
} // namespace Spektral
