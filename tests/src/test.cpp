#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/hid.hpp>
#include <unordered_map>
#include <unordered_set>

TEST_CASE("country_code") {
  using t = pqrs::hid::country_code::value_t;

  t value1(1);
  t value2(2);

  REQUIRE(value1 != value2);
  REQUIRE(value1 < value2);

  std::unordered_map<t, bool> map;
  map[value1] = true;

  REQUIRE(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
}

TEST_CASE("product_id") {
  using t = pqrs::hid::product_id::value_t;

  t value1(1);
  t value2(2);

  REQUIRE(value1 != value2);
  REQUIRE(value1 < value2);

  std::unordered_map<t, bool> map;
  map[value1] = true;

  REQUIRE(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
}

TEST_CASE("usage_page") {
  using t = pqrs::hid::usage_page::value_t;

  t value1(1);
  t value2(2);

  REQUIRE(value1 != value2);
  REQUIRE(value1 < value2);

  std::unordered_map<t, bool> map;
  map[value1] = true;

  REQUIRE(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
}

TEST_CASE("usage") {
  using t = pqrs::hid::usage::value_t;

  t value1(1);
  t value2(2);

  REQUIRE(value1 != value2);
  REQUIRE(value1 < value2);

  std::unordered_map<t, bool> map;
  map[value1] = true;

  REQUIRE(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
}

TEST_CASE("vendor_id") {
  using t = pqrs::hid::vendor_id::value_t;

  t value1(1);
  t value2(2);

  REQUIRE(value1 != value2);
  REQUIRE(value1 < value2);

  std::unordered_map<t, bool> map;
  map[value1] = true;

  REQUIRE(std::hash<t>{}(t(100)) != std::hash<t>{}(t(0)));
}

TEST_CASE("pair<usage_page, usage>") {
  using pair_t = std::pair<pqrs::hid::usage_page::value_t,
                           pqrs::hid::usage::value_t>;
  std::unordered_set<pair_t> set;
  set.insert(std::make_pair(pqrs::hid::usage_page::generic_desktop, pqrs::hid::usage::generic_desktop::keyboard));
}

TEST_CASE("pair<vendor_id, product_id>") {
  using pair_t = std::pair<pqrs::hid::vendor_id::value_t,
                           pqrs::hid::product_id::value_t>;
  std::unordered_set<pair_t> set;
  set.insert(std::make_pair(pqrs::hid::vendor_id::value_t(0), pqrs::hid::product_id::value_t(0)));
}
