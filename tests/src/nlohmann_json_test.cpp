#include <catch2/catch.hpp>

#include <pqrs/hid/extra/nlohmann_json.hpp>

TEST_CASE("nlohmann_json") {
  uint64_t u64 = 13835058055282163712ull; // 2^63 + 2^62
  int32_t i32 = 1610612736;               // 2^30 + 2^29

  //
  // primitive values
  //

  // country_code

  {
    using t = pqrs::hid::country_code::value_t;

    {
      t value1(u64);
      nlohmann::json json = value1;
      auto value2 = json.get<t>();
      REQUIRE(value1 == value2);
      REQUIRE(json.dump() == "13835058055282163712");
    }

    REQUIRE_THROWS(nlohmann::json::array().get<t>());
    REQUIRE_THROWS_AS(
        nlohmann::json().get<t>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        nlohmann::json().get<t>(),
        "json must be number, but is `null`");
    REQUIRE_THROWS_WITH(
        nlohmann::json(true).get<t>(),
        "json must be number, but is `true`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::object().get<t>(),
        "json must be number, but is `{}`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::array().get<t>(),
        "json must be number, but is `[]`");
    REQUIRE_THROWS_WITH(
        nlohmann::json("1234").get<t>(),
        "json must be number, but is `\"1234\"`");
  }

  // product_id

  {
    using t = pqrs::hid::product_id::value_t;

    {
      t value1(u64);
      nlohmann::json json = value1;
      auto value2 = json.get<t>();
      REQUIRE(value1 == value2);
      REQUIRE(json.dump() == "13835058055282163712");
    }

    REQUIRE_THROWS(nlohmann::json::array().get<t>());
    REQUIRE_THROWS_AS(
        nlohmann::json().get<t>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        nlohmann::json().get<t>(),
        "json must be number, but is `null`");
    REQUIRE_THROWS_WITH(
        nlohmann::json(true).get<t>(),
        "json must be number, but is `true`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::object().get<t>(),
        "json must be number, but is `{}`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::array().get<t>(),
        "json must be number, but is `[]`");
    REQUIRE_THROWS_WITH(
        nlohmann::json("1234").get<t>(),
        "json must be number, but is `\"1234\"`");
  }

  // usage_page

  {
    using t = pqrs::hid::usage_page::value_t;

    {
      t value1(i32);
      nlohmann::json json = value1;
      auto value2 = json.get<t>();
      REQUIRE(value1 == value2);
      REQUIRE(json.dump() == "1610612736");
    }

    REQUIRE_THROWS(nlohmann::json::array().get<t>());
    REQUIRE_THROWS_AS(
        nlohmann::json().get<t>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        nlohmann::json().get<t>(),
        "json must be number, but is `null`");
    REQUIRE_THROWS_WITH(
        nlohmann::json(true).get<t>(),
        "json must be number, but is `true`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::object().get<t>(),
        "json must be number, but is `{}`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::array().get<t>(),
        "json must be number, but is `[]`");
    REQUIRE_THROWS_WITH(
        nlohmann::json("1234").get<t>(),
        "json must be number, but is `\"1234\"`");
  }

  // usage

  {
    using t = pqrs::hid::usage::value_t;

    {
      t value1(i32);
      nlohmann::json json = value1;
      auto value2 = json.get<t>();
      REQUIRE(value1 == value2);
      REQUIRE(json.dump() == "1610612736");
    }

    REQUIRE_THROWS(nlohmann::json::array().get<t>());
    REQUIRE_THROWS_AS(
        nlohmann::json().get<t>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        nlohmann::json().get<t>(),
        "json must be number, but is `null`");
    REQUIRE_THROWS_WITH(
        nlohmann::json(true).get<t>(),
        "json must be number, but is `true`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::object().get<t>(),
        "json must be number, but is `{}`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::array().get<t>(),
        "json must be number, but is `[]`");
    REQUIRE_THROWS_WITH(
        nlohmann::json("1234").get<t>(),
        "json must be number, but is `\"1234\"`");
  }

  // vendor_id

  {
    using t = pqrs::hid::vendor_id::value_t;

    {
      t value1(u64);
      nlohmann::json json = value1;
      auto value2 = json.get<t>();
      REQUIRE(value1 == value2);
      REQUIRE(json.dump() == "13835058055282163712");
    }

    REQUIRE_THROWS(nlohmann::json::array().get<t>());
    REQUIRE_THROWS_AS(
        nlohmann::json().get<t>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        nlohmann::json().get<t>(),
        "json must be number, but is `null`");
    REQUIRE_THROWS_WITH(
        nlohmann::json(true).get<t>(),
        "json must be number, but is `true`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::object().get<t>(),
        "json must be number, but is `{}`");
    REQUIRE_THROWS_WITH(
        nlohmann::json::array().get<t>(),
        "json must be number, but is `[]`");
    REQUIRE_THROWS_WITH(
        nlohmann::json("1234").get<t>(),
        "json must be number, but is `\"1234\"`");
  }

  //
  // usage_pair
  //

  {
    using t = pqrs::hid::usage_pair;

    REQUIRE_THROWS(nlohmann::json::array().get<t>());
    REQUIRE_THROWS_AS(
        nlohmann::json().get<t>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        nlohmann::json().get<t>(),
        "json must be object, but is `null`");

    auto json = nlohmann::json::object({
        {"usage_page", 1234},
        {"usage", 5678},
    });
    pqrs::hid::usage_pair usage_pair = json;
    REQUIRE(usage_pair.get_usage_page() == pqrs::hid::usage_page::value_t(1234));
    REQUIRE(usage_pair.get_usage() == pqrs::hid::usage::value_t(5678));

    REQUIRE(json.dump() == "{\"usage\":5678,\"usage_page\":1234}");
  }
}
