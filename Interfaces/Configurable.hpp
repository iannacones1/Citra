#ifndef _CONFIGURATION_
#define _CONFIGURATION_
// http://stackoverflow.com/questions/11031062/c-preprocessor-avoid-code-repetition-of-member-variable-list

#include <boost/preprocessor.hpp>
#include <boost/preprocessor/repetition/detail/for.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include "Configurator.h"

#define REM(...) __VA_ARGS__
#define EAT(...)

// Retrieve the type
#define DETAIL_TYPEOF_PROBE(...) (__VA_ARGS__),
#define DETAIL_TYPEOF_HEAD(x, ...) REM x
#define DETAIL_TYPEOF(...) DETAIL_TYPEOF_HEAD(__VA_ARGS__)
#define TYPEOF(x) DETAIL_TYPEOF(DETAIL_TYPEOF_PROBE x,)

// Strip off the type
#define STRIP(x) EAT x
// Show the type without parenthesis
#define PAIR(x) REM x

#define STR(x) #x
#define XSTR(x) STR(x)

#define DECLARE_EACH(r, data, i, x) PAIR(x);
//#define CONFIG_EACH(r, data, x) Configurator::Instance()->get<TYPEOF(x)>(inClassName, XSTR(STRIP(x)), STRIP(x));
#define CONFIG_EACH(r, data, x) Configurator::Instance()->get(inClassName, XSTR(STRIP(x)), STRIP(x));

#define CONFIGURABLE(...)                                                            \
BOOST_PP_SEQ_FOR_EACH_I(DECLARE_EACH, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))   \
 virtual void configure(const std::string& inClassName)                              \
{                                                                                    \
    BOOST_PP_SEQ_FOR_EACH(CONFIG_EACH, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)); \
}

template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
{
  return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

#define INITIALIZE(className)                   \
struct initializer {                            \
  initializer() {                               \
  char* aVoid = (char*)this;                    \
  aVoid -= offsetOf(&className::myInitializer); \
  className* ptr = (className*)aVoid;           \
  ptr->configure(#className);                   \
} };                                            \
initializer myInitializer;

//class Configurable
//{
//    public:
//        virtual void configure() = 0;
//};

#endif /* _CONFIGURATION_ */
