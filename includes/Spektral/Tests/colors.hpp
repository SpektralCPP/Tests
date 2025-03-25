#pragma once
#include <format>
#include <string>

namespace Spektral::Tests::Colors {
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
} // namespace Spektral::Tests::Colors
