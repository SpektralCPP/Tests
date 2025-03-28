/**
 * @file TestSuite.hpp
 * @brief Defines the TestSuite class for organizing and running groups of
 * tests.
 *
 * This file provides the `TestSuite` class, which acts as a container for
 * multiple `BaseTestGroup` objects. It allows you to group related tests
 * together and run them collectively.
 */

#pragma once
#include "TestGroup.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

namespace Spektral::Tests {

/**
 * @brief A class for organizing and running collections of test groups.
 *
 * The `TestSuite` class allows you to aggregate multiple `BaseTestGroup`
 * instances into a single unit. You can then run all the test groups
 * within the suite with a single call.
 */
class TestSuite {
public:
  /**
   * @brief Default constructor for the TestSuite.
   *
   * Initializes an empty test suite with an empty name.
   */
  TestSuite() : name(std::string{""}), groups(std::vector<BaseTestGroup *>{}) {}

  /**
   * @brief Constructs a TestSuite with a given name.
   *
   * @param s The name of the test suite.
   */
  TestSuite(std::string s) : name(s){};

  /**
   * @brief Copy constructor for the TestSuite.
   *
   * @param ref The TestSuite object to copy.
   */
  TestSuite(const TestSuite &ref) {
    name = ref.name;
    groups = ref.groups;
  }

  /**
   * @brief Move constructor for the TestSuite.
   *
   * @param ref The TestSuite object to move from.
   */
  TestSuite(TestSuite &&ref) {
    name = std::move(ref.name);
    groups = std::move(ref.groups);
  }

  /**
   * @brief Copy assignment operator for the TestSuite.
   *
   * @param ref The TestSuite object to copy from.
   * @return A reference to the assigned TestSuite object.
   */
  TestSuite &operator=(const TestSuite &ref) {
    if (this != &ref) {
      name = ref.name;
      groups = ref.groups;
    }
    return *this;
  }

  /**
   * @brief Move assignment operator for the TestSuite.
   *
   * @param ref The TestSuite object to move from.
   * @return A reference to the assigned TestSuite object.
   */
  TestSuite &operator=(TestSuite &&ref) {
    name = std::move(ref.name);
    groups = std::move(ref.groups);
    return *this;
  }

  /**
   * @brief Adds a test group to this test suite.
   *
   * @param tg A pointer to a `BaseTestGroup` object to be added to the suite.
   * The TestSuite will manage the execution of this test group during its
   * `run()` method.
   * @note The TestSuite does not take ownership of the `BaseTestGroup` pointer.
   * The caller is responsible for managing the lifetime of the test group
   * object.
   */
  void addTestGroup(BaseTestGroup *tg) { groups.push_back(tg); }

  /**
   * @brief Runs all the test groups contained within this test suite.
   *
   * This method iterates through the added test groups and calls their
   * respective `run()` methods, executing all the tests within each group.
   * It prints the name of the test suite before running the groups.
   */
  void run() {
    std::println(std::cout, "Running tests in test suite: {}", name);
    std::for_each(groups.begin(), groups.end(),
                  [](auto &group) { group->run(); });
  }

private:
  /** @brief The name of this test suite. */
  std::string name;
  /** @brief A vector containing pointers to the test groups within this suite.
   */
  std::vector<BaseTestGroup *> groups;
};
} // namespace Spektral::Tests
