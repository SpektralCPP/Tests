#   Spektral - C++ Testing Framework

Spektral is a lightweight and flexible C++ testing framework designed to simplify the process of writing and organizing unit tests. It provides a set of tools to define test cases, group them, and execute them in a structured manner.

##   Key Features

* **TestCase:** Defines individual test cases with expected outputs and input parameters.
* **AssertionGroup:** Groups multiple test cases for a specific function, facilitating focused testing.
* **TestSuite:** Organizes collections of test groups, enabling the execution of related tests.
* **Flexible Assertions:** Supports defining test case pass/fail criteria.
* **Test Organization:** Provides a clear structure for grouping and managing tests.
* **Reporting:** Offers detailed test results, including pass/fail counts and specific failure information.

##   Components

###   TestCase.hpp

The `TestCase.hpp` file defines the `TestCase` template class, which represents a single test case.

* It allows you to specify the expected output and input parameters for a test.
* The `run()` method executes the test against a given function and reports the result.
* It supports optional test case failures using the `param_option` enum, allowing tests to continue even if some cases fail.

###   TestGroup.hpp

The `TestGroup.hpp` file defines the `BaseTestGroup` interface and the `AssertionGroup` template class.

* `BaseTestGroup` is an abstract base class for defining test groups.
* `AssertionGroup` is a template class that groups `TestCase` instances for testing a specific function.
* It handles running the test cases and reporting the overall results for the group.

###   TestSuite.hpp

The `TestSuite.hpp` file defines the `TestSuite` class, which is used to organize and run groups of tests.

* It acts as a container for multiple `BaseTestGroup` objects.
* It allows you to group related tests together and run them collectively.
* It provides methods to add test groups and execute all tests within the suite.

##   Usage

1.  **Include Headers:** Include the necessary header files (`TestCase.hpp`, `TestGroup.hpp`, and `TestSuite.hpp`) in your test files.
2.  **Define Test Cases:** Use the `TestCase` template class to define individual test cases, specifying the expected output and input parameters.
3.  **Group Test Cases:** Use the `AssertionGroup` template class to group test cases that test a specific function. Provide the function to be tested and add the `TestCase` instances.
4.  **Create Test Suite:** Create a `TestSuite` object to organize your test groups. Add the `AssertionGroup` instances to the `TestSuite`.
5.  **Run Tests:** Call the `run()` method on the `TestSuite` object to execute all the tests. The framework will report the results to the console.

##   Example

```c++
#include <Spektral/Tests/TestCase.hpp>
#include <Spektral/Tests/TestGroup.hpp>
#include <Spektral/Tests/TestSuite.hpp>

// Function to be tested
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int main() {
  using namespace Spektral::Tests;

  // Create a test group for the add function
  AssertionGroup<int, int, int> add_test_group("Add Function Tests", add);
  AssertionGroup<int, int, int> sub_test_group("Subtract Function Tests", sub);

  // Add test cases to the group
  add_test_group.add_test_cases({
      TestCase(5, 2, 3),
      TestCase(0, 0, 0),
      TestCase(10, 5, 5),
      TestCase(100, 50, 50),
      TestCase(1, 2, -1) | param_option::OPTIONAL // An optional test case
  });

  sub_test_group.add_test_cases({
      TestCase(-1, 2, 3),
      TestCase(0, 0, 0),
      TestCase(0, 5, 5),
      TestCase(0, 50, 50),
      TestCase(3, 2, -1) | param_option::OPTIONAL // An optional test case
  });

  // Create a test suite
  TestSuite suite("My Math Library Tests");

  // Add the test group to the suite
  suite.addTestGroup(&add_test_group);
  suite.addTestGroup(&sub_test_group);

  // Run the tests
  suite.run();

  return 0;
}
```
