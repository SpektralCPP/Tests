#pragma once
#include "test_group.hpp"
#include "tests.hpp"

namespace Spektral::Tests {
class test_suite {
private:
public:
  /**
   * @brief Creates a test group from a function, input tuples, and expected
   * outputs.
   *
   * This function constructs a `test_group` object by pairing the provided
   * input tuples with their corresponding expected outputs. It performs a size
   * check to ensure the number of inputs matches the number of outputs.
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
  [[nodiscard("Capture the return unless you are immediately calling .run()")]]
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
   * instead of a `std::function`. It internally converts the function pointer
   * to a `std::function` and calls the primary `add_test_group` function.
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
  [[nodiscard("Capture the return unless you are immediately calling .run()")]]
  constexpr test_group<output_t, inputs_t...>
  add_test_group(std::string name, output_t (*fn)(std::tuple<inputs_t...>),
                 std::vector<std::tuple<inputs_t...>> inputs,
                 std::vector<output_t> outputs) {
    return add_test_group(name, std::function{fn}, inputs, outputs);
  }
};
}; // namespace Spektral::Tests
