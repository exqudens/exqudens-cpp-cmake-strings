#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <string>

namespace exqudens {

  class strings {

    private:
    static std::string WHITE_SPACES;

    /**
     * @brief - Replace leading whitespaces.
     * @param str - String for replace leading whitespaces.
     * @return - New string without leading whitespaces.
     */
    public:
    std::string left_trim(std::string str);

    /**
     * @brief - Replace trailing whitespaces.
     * @param str - String for replace trailing whitespaces.
     * @return - New string without trailing whitespaces.
     */
    public:
    std::string right_trim(std::string str);

    /**
     * @brief - Replace leading and trailing whitespaces.
     * @param str - String for replace leading and trailing whitespaces.
     * @return - New string without leading and trailing whitespaces.
     */
    public:
    std::string trim(std::string str);

  };

}

#endif // STRINGS_HPP
