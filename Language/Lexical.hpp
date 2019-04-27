#ifndef _LEXICAL_HPP_
#define _LEXICAL_HPP_

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace Citra { namespace Language {

class Lexical
{
  public:

    template <class T>
    static T fromString(const std::string& inValue)
    {
        return boost::lexical_cast<T>(inValue);
    }

    template <class T>
    static std::string toString(const T& inValue)
    {
        std::stringstream ss;
        ss << inValue;
        return ss.str();
    }

  private:
    Lexical() {}
};

    template <>
    inline bool Lexical::fromString<bool>(const std::string& inValue)
    {
        static std::string TRUE = "true";

        return boost::iequals(inValue, TRUE); // case-insensitive compare
    }

    template <>
    inline std::string Lexical::toString<bool>(const bool& inValue)
    {
        return (inValue ? "true" : "false");
    }

} /* namespace Language*/ } /* namespace Citra */

#endif /* _LEXICAL_HPP_ */
