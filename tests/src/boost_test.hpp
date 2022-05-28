#include <boost/ut.hpp>
#include <pqrs/hid/extra/boost.hpp>

void run_boost_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "boost"_test = [] {
    {
      pqrs::hid::country_code::value_t v(100);
      expect(std::hash<pqrs::hid::country_code::value_t>{}(v) ==
             pqrs::hid::country_code::hash_value(v));
    }

    {
      pqrs::hid::product_id::value_t v(100);
      expect(std::hash<pqrs::hid::product_id::value_t>{}(v) ==
             pqrs::hid::product_id::hash_value(v));
    }

    {
      pqrs::hid::usage_page::value_t v(100);
      expect(std::hash<pqrs::hid::usage_page::value_t>{}(v) ==
             pqrs::hid::usage_page::hash_value(v));
    }

    {
      pqrs::hid::usage::value_t v(100);
      expect(std::hash<pqrs::hid::usage::value_t>{}(v) ==
             pqrs::hid::usage::hash_value(v));
    }

    {
      pqrs::hid::vendor_id::value_t v(100);
      expect(std::hash<pqrs::hid::vendor_id::value_t>{}(v) ==
             pqrs::hid::vendor_id::hash_value(v));
    }
  };
}
