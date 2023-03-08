#include "boost_test.hpp"
#include "nlohmann_json_test.hpp"
#include <boost/ut.hpp>
#include <pqrs/hid.hpp>
#include <unordered_map>
#include <unordered_set>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "country_code"_test = [] {
    using t = pqrs::hid::country_code::value_t;

    t value1(1);
    t value2(2);

    expect(value1 != value2);
    expect(value1 < value2);

    std::unordered_map<t, bool> map;
    map[value1] = true;

    expect(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
  };

  "product_id"_test = [] {
    using t = pqrs::hid::product_id::value_t;

    t value1(1);
    t value2(2);

    expect(value1 != value2);
    expect(value1 < value2);

    std::unordered_map<t, bool> map;
    map[value1] = true;

    expect(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
  };

  "report_id"_test = [] {
    using t = pqrs::hid::report_id::value_t;

    t value1(1);
    t value2(2);

    expect(value1 != value2);
    expect(value1 < value2);

    std::unordered_map<t, bool> map;
    map[value1] = true;

    expect(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
  };

  "usage_page"_test = [] {
    using t = pqrs::hid::usage_page::value_t;

    t value1(1);
    t value2(2);

    expect(value1 != value2);
    expect(value1 < value2);

    std::unordered_map<t, bool> map;
    map[value1] = true;

    expect(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
  };

  "usage"_test = [] {
    using t = pqrs::hid::usage::value_t;

    t value1(1);
    t value2(2);

    expect(value1 != value2);
    expect(value1 < value2);

    std::unordered_map<t, bool> map;
    map[value1] = true;

    expect(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));

    {
      auto u = pqrs::hid::usage::keyboard_or_keypad::keyboard_1;
      ++u;
      expect(u == pqrs::hid::usage::keyboard_or_keypad::keyboard_2);
    }
  };

  "usage_pair"_test = [] {
    pqrs::hid::usage_pair usage_pair(pqrs::hid::usage_page::generic_desktop,
                                     pqrs::hid::usage::generic_desktop::keyboard);
    expect(usage_pair.get_usage_page() == pqrs::hid::usage_page::generic_desktop);
    expect(usage_pair.get_usage() == pqrs::hid::usage::generic_desktop::keyboard);

    std::unordered_map<pqrs::hid::usage_pair, bool> map;
    map[usage_pair] = true;
  };

  "vendor_id"_test = [] {
    using t = pqrs::hid::vendor_id::value_t;

    t value1(1);
    t value2(2);

    expect(value1 != value2);
    expect(value1 < value2);

    std::unordered_map<t, bool> map;
    map[value1] = true;

    expect(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
  };

  "pair<usage_page, usage>"_test = [] {
    using pair_t = std::pair<pqrs::hid::usage_page::value_t,
                             pqrs::hid::usage::value_t>;
    std::unordered_set<pair_t> set;
    set.insert(std::make_pair(pqrs::hid::usage_page::generic_desktop, pqrs::hid::usage::generic_desktop::keyboard));
  };

  "pair<vendor_id, product_id>"_test = [] {
    using pair_t = std::pair<pqrs::hid::vendor_id::value_t,
                             pqrs::hid::product_id::value_t>;
    std::unordered_set<pair_t> set;
    set.insert(std::make_pair(pqrs::hid::vendor_id::value_t(0), pqrs::hid::product_id::value_t(0)));
  };

  run_boost_test();
  run_nlohmann_json_test();

  return 0;
}
