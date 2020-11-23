#include "strings.hpp"

namespace exqudens {

  std::string strings::WHITE_SPACES = " \n\r\t\f\v";

  std::string strings::left_trim(std::string str) {
    int start = str.find_first_not_of(WHITE_SPACES);
    return start == -1 ? "" : str.substr(start);
  }

  std::string strings::right_trim(std::string str) {
    int end = str.find_last_not_of(WHITE_SPACES);
    return end == -1 ? "" : str.substr(0, end + 1);
  }

  std::string strings::trim(std::string str) {
    return left_trim(right_trim(str));
  }

}
