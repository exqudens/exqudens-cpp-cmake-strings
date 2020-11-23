#include <iostream>
#include <map>
#include <stdexcept>

#include "exqudens/strings.hpp"

typedef void (* test)();

void test_1() {
  exqudens::strings strings;

  std::string expected = "Asd!";
  std::string actual = strings.trim(" Asd!  ");

  if (expected != actual) {
    std::string error_message;
    error_message.append("expected: '");
    error_message.append(expected);
    error_message.append("' actual: '");
    error_message.append(actual);
    error_message.append("'");
    throw std::runtime_error(error_message);
  }
}

int run_test(
    const std::string name,
    const test t,
    std::ostream& out,
    std::ostream& error_out
) {
  std::string passed = "PASSED";
  std::string failed = "FAILED";
  try {
    t();
    std::string header = std::string(name)
        .append(" ")
        .append(passed);
    out << header << std::endl;
  } catch (std::exception& e) {
    std::string header = std::string(10, '=')
        .append(" ")
        .append(name)
        .append(" ")
        .append(failed)
        .append(" ")
        .append(10, '=');

    error_out << header << std::endl;
    error_out << e.what() << std::endl;
    error_out << std::string(header.size(), '=');

    return 1;
  }

  return 0;
}

int run_tests(
    int argc,
    char** argv,
    std::ostream& out,
    std::ostream& error_out
) {
  std::map<std::string, test> map1;

  map1["test_1"] = test_1;

  int result = 0;

  if (argc < 2) {
    for (auto&[key, val] : map1) {
      int tmp_result = run_test(key, val, out, error_out);
      if (result == 0 && tmp_result != 0) {
        result = tmp_result;
      }
    }
  } else {
    for (int i = 1; i < argc; i++) {
      std::string key = std::string(argv[i]);
      if (map1.contains(key)) {
        test val = map1[key];
        int tmp_result = run_test(key, val, out, error_out);
        if (result == 0 && tmp_result != 0) {
          result = tmp_result;
        }
      }
    }
  }

  return result;
}

int main(int argc, char** argv) {
  return run_tests(argc, argv, std::cout, std::cerr);
}
