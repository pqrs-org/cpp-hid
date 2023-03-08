#include <boost/ut.hpp>
#include <pqrs/hid/extra/nlohmann_json.hpp>

namespace {
using namespace boost::ut;
using namespace boost::ut::literals;

template <typename t>
void exception_test(void) {
  try {
    nlohmann::json().get<t>();
    expect(false);
  } catch (pqrs::json::unmarshal_error& ex) {
    expect(std::string("json must be number, but is `null`") == ex.what());
  } catch (...) {
    expect(false);
  }

  try {
    nlohmann::json(true).get<t>();
    expect(false);
  } catch (pqrs::json::unmarshal_error& ex) {
    expect(std::string("json must be number, but is `true`") == ex.what());
  } catch (...) {
    expect(false);
  }

  try {
    nlohmann::json::object().get<t>();
    expect(false);
  } catch (pqrs::json::unmarshal_error& ex) {
    expect(std::string("json must be number, but is `{}`") == ex.what());
  } catch (...) {
    expect(false);
  }

  try {
    nlohmann::json::array().get<t>();
    expect(false);
  } catch (pqrs::json::unmarshal_error& ex) {
    expect(std::string("json must be number, but is `[]`") == ex.what());
  } catch (...) {
    expect(false);
  }

  try {
    nlohmann::json("1234").get<t>();
    expect(false);
  } catch (pqrs::json::unmarshal_error& ex) {
    expect(std::string("json must be number, but is `\"1234\"`") == ex.what());
  } catch (...) {
    expect(false);
  }
}
} // namespace

void run_nlohmann_json_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "nlohmann_json"_test = [] {
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
        expect(value1 == value2);
        expect(json.dump() == "13835058055282163712");
      }

      exception_test<t>();
    }

    // product_id

    {
      using t = pqrs::hid::product_id::value_t;

      {
        t value1(u64);
        nlohmann::json json = value1;
        auto value2 = json.get<t>();
        expect(value1 == value2);
        expect(json.dump() == "13835058055282163712");
      }

      exception_test<t>();
    }

    // report_id

    {
      using t = pqrs::hid::report_id::value_t;

      {
        t value1(i32);
        nlohmann::json json = value1;
        auto value2 = json.get<t>();
        expect(value1 == value2);
        expect(json.dump() == "1610612736");
      }

      exception_test<t>();
    }

    // usage_page

    {
      using t = pqrs::hid::usage_page::value_t;

      {
        t value1(i32);
        nlohmann::json json = value1;
        auto value2 = json.get<t>();
        expect(value1 == value2);
        expect(json.dump() == "1610612736");
      }

      exception_test<t>();
    }

    // usage

    {
      using t = pqrs::hid::usage::value_t;

      {
        t value1(i32);
        nlohmann::json json = value1;
        auto value2 = json.get<t>();
        expect(value1 == value2);
        expect(json.dump() == "1610612736");
      }

      exception_test<t>();
    }

    // vendor_id

    {
      using t = pqrs::hid::vendor_id::value_t;

      {
        t value1(u64);
        nlohmann::json json = value1;
        auto value2 = json.get<t>();
        expect(value1 == value2);
        expect(json.dump() == "13835058055282163712");
      }

      exception_test<t>();
    }

    //
    // usage_pair
    //

    {
      using t = pqrs::hid::usage_pair;

      try {
        nlohmann::json().get<t>();
        expect(false);
      } catch (pqrs::json::unmarshal_error& ex) {
        expect(std::string("json must be object, but is `null`") == ex.what());
      } catch (...) {
        expect(false);
      }

      try {
        nlohmann::json::array().get<t>();
        expect(false);
      } catch (pqrs::json::unmarshal_error& ex) {
        expect(std::string("json must be object, but is `[]`") == ex.what());
      } catch (...) {
        expect(false);
      }

      auto json = nlohmann::json::object({
          {"usage_page", 1234},
          {"usage", 5678},
      });
      pqrs::hid::usage_pair usage_pair = json;
      expect(usage_pair.get_usage_page() == pqrs::hid::usage_page::value_t(1234));
      expect(usage_pair.get_usage() == pqrs::hid::usage::value_t(5678));

      expect(json.dump() == "{\"usage\":5678,\"usage_page\":1234}");
    }
  };
}
