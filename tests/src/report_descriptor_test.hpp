#pragma once

#include <boost/ut.hpp>
#include <pqrs/hid.hpp>
#include <vector>

inline void run_report_descriptor_test() {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "report_descriptor real ELECOM descriptor"_test = [] {
    // ELECOM device (056e:00fe). This is an unmodified descriptor captured from
    // the device, with comments added at HID item boundaries. The three constant
    // bits following buttons 1-5 are driven as buttons 6-8 despite being declared
    // as padding.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        // Report 1: mouse buttons and pointing motion.
        0x05, 0x01,             // Usage Page (Generic Desktop)
        0x09, 0x02,             // Usage (Mouse)
        0xa1, 0x01,             // Collection (Application)
        0x09, 0x01,             //   Usage (Pointer)
        0xa1, 0x00,             //   Collection (Physical)
        0x85, 0x01,             //     Report ID (1)
        0x95, 0x05,             //     Report Count (5)
        0x75, 0x01,             //     Report Size (1 bit)
        0x05, 0x09,             //     Usage Page (Button)
        0x19, 0x01,             //     Usage Minimum (Button 1)
        0x29, 0x05,             //     Usage Maximum (Button 5)
        0x15, 0x00,             //     Logical Minimum (0)
        0x25, 0x01,             //     Logical Maximum (1)
        0x81, 0x02,             //     Input (Data, Variable, Absolute): buttons 1-5
        0x95, 0x01,             //     Report Count (1)
        0x75, 0x03,             //     Report Size (3 bits)
        0x81, 0x01,             //     Input (Constant): actually buttons 6-8
        0x75, 0x10,             //     Report Size (16 bits)
        0x95, 0x02,             //     Report Count (2)
        0x05, 0x01,             //     Usage Page (Generic Desktop)
        0x09, 0x30,             //     Usage (X)
        0x09, 0x31,             //     Usage (Y)
        0x16, 0x00, 0x80,       //     Logical Minimum (-32768)
        0x26, 0xff, 0x7f,       //     Logical Maximum (32767)
        0x81, 0x06,             //     Input (Data, Variable, Relative): X and Y
        0xc0,                   //   End Collection
        0xa1, 0x00,             //   Collection (Physical)
        0x95, 0x01,             //     Report Count (1)
        0x75, 0x08,             //     Report Size (8 bits)
        0x05, 0x01,             //     Usage Page (Generic Desktop)
        0x09, 0x38,             //     Usage (Wheel)
        0x15, 0x81,             //     Logical Minimum (-127)
        0x25, 0x7f,             //     Logical Maximum (127)
        0x81, 0x06,             //     Input (Data, Variable, Relative): vertical wheel
        0xc0,                   //   End Collection
        0xa1, 0x00,             //   Collection (Physical)
        0x95, 0x01,             //     Report Count (1)
        0x75, 0x08,             //     Report Size (8 bits)
        0x05, 0x0c,             //     Usage Page (Consumer)
        0x0a, 0x38, 0x02,       //     Usage (AC Pan)
        0x15, 0x81,             //     Logical Minimum (-127)
        0x25, 0x7f,             //     Logical Maximum (127)
        0x81, 0x06,             //     Input (Data, Variable, Relative): horizontal wheel
        0xc0,                   //   End Collection
        0xc0,                   // End Collection

        // Report 2: seven vendor-defined input bytes.
        0x06, 0x01, 0xff,       // Usage Page (Vendor-defined 0xff01)
        0x09, 0x00,             // Usage (0)
        0xa1, 0x01,             // Collection (Application)
        0x85, 0x02,             //   Report ID (2)
        0x09, 0x00,             //   Usage (0)
        0x15, 0x00,             //   Logical Minimum (0)
        0x26, 0xff, 0x00,       //   Logical Maximum (255)
        0x75, 0x08,             //   Report Size (8 bits)
        0x95, 0x07,             //   Report Count (7)
        0x81, 0x02,             //   Input (Data, Variable, Absolute)
        0xc0,                   // End Collection

        // Report 5: consumer control usage encoded as a 16-bit array value.
        0x05, 0x0c,             // Usage Page (Consumer)
        0x09, 0x01,             // Usage (Consumer Control)
        0xa1, 0x01,             // Collection (Application)
        0x85, 0x05,             //   Report ID (5)
        0x19, 0x00,             //   Usage Minimum (0)
        0x2a, 0x3c, 0x02,       //   Usage Maximum (0x023c)
        0x15, 0x00,             //   Logical Minimum (0)
        0x26, 0x3c, 0x02,       //   Logical Maximum (572)
        0x95, 0x01,             //   Report Count (1)
        0x75, 0x10,             //   Report Size (16 bits)
        0x81, 0x00,             //   Input (Data, Array, Absolute)
        0xc0,                   // End Collection

        // Report 3: system control buttons followed by five padding bits.
        0x05, 0x01,             // Usage Page (Generic Desktop)
        0x09, 0x80,             // Usage (System Control)
        0xa1, 0x01,             // Collection (Application)
        0x85, 0x03,             //   Report ID (3)
        0x19, 0x81,             //   Usage Minimum (System Power Down)
        0x29, 0x83,             //   Usage Maximum (System Wake Up)
        0x15, 0x00,             //   Logical Minimum (0)
        0x25, 0x01,             //   Logical Maximum (1)
        0x75, 0x01,             //   Report Size (1 bit)
        0x95, 0x03,             //   Report Count (3)
        0x81, 0x02,             //   Input (Data, Variable, Absolute)
        0x95, 0x05,             //   Report Count (5)
        0x81, 0x01,             //   Input (Constant): padding
        0xc0,                   // End Collection

        // Report 4: one vendor-defined input byte.
        0x06, 0xbc, 0xff,       // Usage Page (Vendor-defined 0xffbc)
        0x09, 0x88,             // Usage (0x88)
        0xa1, 0x01,             // Collection (Application)
        0x85, 0x04,             //   Report ID (4)
        0x95, 0x01,             //   Report Count (1)
        0x75, 0x08,             //   Report Size (8 bits)
        0x15, 0x00,             //   Logical Minimum (0)
        0x26, 0xff, 0x00,       //   Logical Maximum (255)
        0x19, 0x00,             //   Usage Minimum (0)
        0x2a, 0xff, 0x00,       //   Usage Maximum (255)
        0x81, 0x00,             //   Input (Data, Array, Absolute)
        0xc0,                   // End Collection

        // Report 6: seven vendor-defined feature bytes.
        0x06, 0x02, 0xff,       // Usage Page (Vendor-defined 0xff02)
        0x09, 0x02,             // Usage (2)
        0xa1, 0x01,             // Collection (Application)
        0x85, 0x06,             //   Report ID (6)
        0x09, 0x02,             //   Usage (2)
        0x15, 0x00,             //   Logical Minimum (0)
        0x26, 0xff, 0x00,       //   Logical Maximum (255)
        0x75, 0x08,             //   Report Size (8 bits)
        0x95, 0x07,             //   Report Count (7)
        0xb1, 0x02,             //   Feature (Data, Variable, Absolute)
        0xc0,                   // End Collection
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    auto fields = result->get_descriptor().find_report_fields(
        pqrs::hid::report_descriptor::report_type::input,
        pqrs::hid::report_id::value_t(1));
    using flag = pqrs::hid::report_descriptor::report_field_flag;
    expect(fields.size() == 5_i);

    expect(fields[0]->get_bit_offset() == 0_i);
    expect(fields[0]->get_size_bits() == 1_i);
    expect(fields[0]->get_count() == 5_i);
    expect(!fields[0]->has_flag(flag::constant));
    expect(fields[0]->has_flag(flag::variable));
    expect(fields[0]->get_usage_page() == pqrs::hid::usage_page::button);
    expect(fields[0]->get_collection_path().size() == 2_i);
    expect(fields[0]->get_collection_path()[0].get_usage().has_value());
    if (fields[0]->get_collection_path()[0].get_usage()) {
      expect(fields[0]->get_collection_path()[0].get_usage()->get_usage() ==
             pqrs::hid::usage::generic_desktop::mouse);
    }
    expect(fields[0]->get_usage_minimum().has_value());
    expect(fields[0]->get_usage_maximum().has_value());
    if (fields[0]->get_usage_minimum() && fields[0]->get_usage_maximum()) {
      expect(fields[0]->get_usage_minimum()->get_usage() == pqrs::hid::usage::value_t(1));
      expect(fields[0]->get_usage_maximum()->get_usage() == pqrs::hid::usage::value_t(5));
    }

    expect(fields[1]->get_bit_offset() == 5_i);
    expect(fields[1]->get_size_bits() == 3_i);
    expect(fields[1]->get_count() == 1_i);
    expect(fields[1]->has_flag(flag::constant));
    expect(fields[1]->get_usage_page() == pqrs::hid::usage_page::button);

    expect(fields[2]->get_bit_offset() == 8_i);
    expect(fields[2]->get_size_bits() == 16_i);
    expect(fields[2]->get_count() == 2_i);
    expect(fields[2]->has_flag(flag::relative));

    expect(fields[3]->get_bit_offset() == 40_i);
    expect(fields[4]->get_bit_offset() == 48_i);
  };

  "report_descriptor item order does not affect the report layout"_test = [] {
    // This describes the same button layout as report 1 above, but Report ID is
    // declared before the Pointer collection. A semantic parser must not depend
    // on the byte prefix used by one particular device.
    // clang-format off
    const std::vector<uint8_t> report_id_before_pointer = {
        0x05, 0x01,       // Usage Page (Generic Desktop)
        0x09, 0x02,       // Usage (Mouse)
        0xa1, 0x01,       // Collection (Application)
        0x85, 0x01,       //   Report ID (1)
        0x09, 0x01,       //   Usage (Pointer)
        0xa1, 0x00,       //   Collection (Physical)
        0x05, 0x09,       //     Usage Page (Button)
        0x19, 0x01,       //     Usage Minimum (Button 1)
        0x29, 0x05,       //     Usage Maximum (Button 5)
        0x15, 0x00,       //     Logical Minimum (0)
        0x25, 0x01,       //     Logical Maximum (1)
        0x75, 0x01,       //     Report Size (1 bit)
        0x95, 0x05,       //     Report Count (5)
        0x81, 0x02,       //     Input (Data, Variable, Absolute): buttons 1-5
        0x75, 0x03,       //     Report Size (3 bits)
        0x95, 0x01,       //     Report Count (1)
        0x81, 0x01,       //     Input (Constant): padding
        0xc0,             //   End Collection
        0xc0,             // End Collection
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(report_id_before_pointer);
    expect(result.has_value());
    if (!result) {
      return;
    }

    auto fields = result->get_descriptor().find_report_fields(
        pqrs::hid::report_descriptor::report_type::input,
        pqrs::hid::report_id::value_t(1));
    using flag = pqrs::hid::report_descriptor::report_field_flag;
    expect(fields.size() == 2_i);
    expect(fields[0]->get_bit_offset() == 0_i);
    expect(fields[1]->get_bit_offset() == 5_i);
    expect(fields[1]->has_flag(flag::constant));
  };

  "report_descriptor report ID may precede the application collection"_test = [] {
    // HID permits a Report ID outside a top-level collection. Its ownership is
    // determined when a field first uses it inside an Application Collection.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x85, 0x01, // Report ID (1)
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x09, 0x02, // Usage (Mouse)
        0xa1, 0x01, // Collection (Application)
        0x09, 0x01, //   Usage (Pointer)
        0x15, 0x00, //   Logical Minimum (0)
        0x25, 0x01, //   Logical Maximum (1)
        0x75, 0x08, //   Report Size (8 bits)
        0x95, 0x01, //   Report Count (1)
        0x81, 0x02, //   Input (Data, Variable, Absolute)
        0xc0,       // End Collection
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    auto fields = result->get_descriptor().find_report_fields(
        pqrs::hid::report_descriptor::report_type::input,
        pqrs::hid::report_id::value_t(1));
    expect(fields.size() == 1_i);
  };

  "report_descriptor report offsets are independent"_test = [] {
    // Offsets advance independently for each combination of report type and ID.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x15, 0x00, // Logical Minimum (0)
        0x25, 0x01, // Logical Maximum (1)
        0x85, 0x01, // Report ID (1)
        0x75, 0x01, // Report Size (1 bit)
        0x95, 0x08, // Report Count (8)
        0x09, 0x01, // Usage (Pointer)
        0x81, 0x02, // Input: report 1, bits 0-7
        0x09, 0x01, // Usage (Pointer)
        0x91, 0x02, // Output: report 1, bits 0-7
        0x85, 0x02, // Report ID (2)
        0x75, 0x08, // Report Size (8 bits)
        0x95, 0x02, // Report Count (2)
        0x09, 0x01, // Usage (Pointer)
        0x81, 0x02, // Input: report 2, bits 0-15
        0x85, 0x01, // Report ID (1)
        0x75, 0x04, // Report Size (4 bits)
        0x95, 0x01, // Report Count (1)
        0x09, 0x01, // Usage (Pointer)
        0x81, 0x02, // Input: report 1, bits 8-11
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    auto input1 = result->get_descriptor().find_report_fields(
        pqrs::hid::report_descriptor::report_type::input,
        pqrs::hid::report_id::value_t(1));
    auto output1 = result->get_descriptor().find_report_fields(
        pqrs::hid::report_descriptor::report_type::output,
        pqrs::hid::report_id::value_t(1));
    auto input2 = result->get_descriptor().find_report_fields(
        pqrs::hid::report_descriptor::report_type::input,
        pqrs::hid::report_id::value_t(2));

    expect(input1.size() == 2_i);
    expect(input1[0]->get_bit_offset() == 0_i);
    expect(input1[1]->get_bit_offset() == 8_i);
    expect(output1.size() == 1_i);
    expect(output1[0]->get_bit_offset() == 0_i);
    expect(input2.size() == 1_i);
    expect(input2[0]->get_bit_offset() == 0_i);
  };

  "report_descriptor equal IDs of different report types are independent"_test = [] {
    // HID identifies reports by both ID and type. Reusing numeric ID 1 for an
    // Input and an Output in separate Application Collections does not make
    // either report span a collection boundary.
    const std::vector<uint8_t> bytes = {
        0x05,
        0x01, // Usage Page (Generic Desktop)
        0x09,
        0x02, // Usage (Mouse)
        0xa1,
        0x01, // Collection (Application)
        0x85,
        0x01, //   Report ID (1)
        0x09,
        0x01, //   Usage (Pointer)
        0x15,
        0x00, //   Logical Minimum (0)
        0x25,
        0x01, //   Logical Maximum (1)
        0x75,
        0x01, //   Report Size (1 bit)
        0x95,
        0x01, //   Report Count (1)
        0x81,
        0x02, //   Input
        0xc0, // End Collection
        0x09,
        0x04, // Usage (Joystick)
        0xa1,
        0x01, // Collection (Application)
        0x85,
        0x01, //   Report ID (1)
        0x09,
        0x01, //   Usage (Pointer)
        0x91,
        0x02, //   Output
        0xc0, // End Collection
    };

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (result) {
      expect(result->get_descriptor().get_report_fields().size() == 2_i);
    }
  };

  "report_descriptor global push and pop"_test = [] {
    // Push saves the 1-bit field layout. Pop restores it after the temporary
    // 8-bit field, while the accumulated Input offset continues to advance.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x15, 0x00, // Logical Minimum (0)
        0x25, 0x01, // Logical Maximum (1)
        0x75, 0x01, // Report Size (1 bit)
        0x95, 0x01, // Report Count (1)
        0xa4,       // Push
        0x75, 0x08, // Report Size (8 bits)
        0x09, 0x01, // Usage (Pointer)
        0x81, 0x02, // Input: bits 0-7
        0xb4,       // Pop
        0x09, 0x01, // Usage (Pointer)
        0x81, 0x02, // Input: restored 1-bit field at bit 8
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& fields = result->get_descriptor().get_report_fields();
    expect(fields.size() == 2_i);
    expect(fields[0].get_size_bits() == 8_i);
    expect(fields[1].get_size_bits() == 1_i);
    expect(fields[1].get_bit_offset() == 8_i);
  };

  "report_descriptor qualified usage and unit exponent"_test = [] {
    // A four-byte Usage embeds its Usage Page in the high 16 bits. Unit
    // Exponent is exceptional in that only its low nibble is a signed value.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01,                   // Usage Page (Generic Desktop)
        0x0b, 0x34, 0x12, 0x00, 0xff, // Usage (page 0xff00, usage 0x1234)
        0x15, 0x00,                   // Logical Minimum (0)
        0x25, 0x01,                   // Logical Maximum (1)
        0x55, 0x0e,                   // Unit Exponent (-2)
        0x75, 0x08,                   // Report Size (8 bits)
        0x95, 0x01,                   // Report Count (1)
        0x81, 0x02,                   // Input (Data, Variable, Absolute)
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& field = result->get_descriptor().get_report_fields()[0];
    expect(field.get_unit_exponent() == -2_i);
    expect(field.get_usages().size() == 1_i);
    expect(field.get_usages()[0].get_usage_page() ==
           pqrs::hid::usage_page::value_t(0xff00));
    expect(field.get_usages()[0].get_usage() ==
           pqrs::hid::usage::value_t(0x1234));
  };

  "report_descriptor resolves short usages at the main item"_test = [] {
    // HID combines a short Usage with the last Usage Page in effect when the
    // Main item is encountered, rather than the page at the Usage item itself.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x09, 0x30, // Usage (0x30)
        0x05, 0x09, // Usage Page (Button), overrides the page before Input
        0x15, 0x00, // Logical Minimum (0)
        0x25, 0x01, // Logical Maximum (1)
        0x75, 0x01, // Report Size (1 bit)
        0x95, 0x01, // Report Count (1)
        0x81, 0x02, // Input (Data, Variable, Absolute)
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& field = result->get_descriptor().get_report_fields()[0];
    expect(field.get_usages().size() == 1_i);
    expect(field.get_usages()[0].get_usage_page() == pqrs::hid::usage_page::button);
    expect(field.get_usages()[0].get_usage() == pqrs::hid::usage::value_t(0x30));
  };

  "report_descriptor preserves designator and string local items"_test = [] {
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x15, 0x00, // Logical Minimum (0)
        0x25, 0x01, // Logical Maximum (1)
        0x75, 0x08, // Report Size (8 bits)
        0x95, 0x02, // Report Count (2)
        0x09, 0x01, // Usage (Pointer)
        0x39, 0x03, // Designator Index (3)
        0x39, 0x04, // Designator Index (4)
        0x79, 0x09, // String Index (9)
        0x79, 0x0a, // String Index (10)
        0x81, 0x02, // Input
        0x09, 0x01, // Usage (Pointer)
        0x49, 0x05, // Designator Minimum (5)
        0x59, 0x06, // Designator Maximum (6)
        0x89, 0x07, // String Minimum (7)
        0x99, 0x08, // String Maximum (8)
        0x81, 0x02, // Input
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& fields = result->get_descriptor().get_report_fields();
    expect(fields.size() == 2_i);
    if (fields.size() != 2) {
      return;
    }

    expect(fields[0].get_designator_indices().size() == 2_i);
    if (fields[0].get_designator_indices().size() == 2) {
      expect(fields[0].get_designator_indices()[0] == 3_i);
      expect(fields[0].get_designator_indices()[1] == 4_i);
    }
    expect(!fields[0].get_designator_minimum().has_value());
    expect(!fields[0].get_designator_maximum().has_value());
    expect(fields[0].get_string_indices().size() == 2_i);
    if (fields[0].get_string_indices().size() == 2) {
      expect(fields[0].get_string_indices()[0] == 9_i);
      expect(fields[0].get_string_indices()[1] == 10_i);
    }
    expect(!fields[0].get_string_minimum().has_value());
    expect(!fields[0].get_string_maximum().has_value());

    expect(fields[1].get_designator_indices().empty());
    expect(fields[1].get_designator_minimum().has_value());
    if (fields[1].get_designator_minimum()) {
      expect(*fields[1].get_designator_minimum() == 5_i);
    }
    expect(fields[1].get_designator_maximum().has_value());
    if (fields[1].get_designator_maximum()) {
      expect(*fields[1].get_designator_maximum() == 6_i);
    }
    expect(fields[1].get_string_indices().empty());
    expect(fields[1].get_string_minimum().has_value());
    if (fields[1].get_string_minimum()) {
      expect(*fields[1].get_string_minimum() == 7_i);
    }
    expect(fields[1].get_string_maximum().has_value());
    if (fields[1].get_string_maximum()) {
      expect(*fields[1].get_string_maximum() == 8_i);
    }
  };

  "report_descriptor physical extents inherit logical extents"_test = [] {
    // Undefined physical extents and an explicit zero pair both mean that the
    // logical extents are the effective physical extents.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x09, 0x01, // Usage (Pointer)
        0x15, 0x81, // Logical Minimum (-127)
        0x25, 0x7f, // Logical Maximum (127)
        0x75, 0x08, // Report Size (8 bits)
        0x95, 0x01, // Report Count (1)
        0x81, 0x02, // Input with undefined physical extents
        0x35, 0x00, // Physical Minimum (0)
        0x45, 0x00, // Physical Maximum (0)
        0x09, 0x01, // Usage (Pointer)
        0x81, 0x02, // Input with the explicit default pair
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& fields = result->get_descriptor().get_report_fields();
    expect(fields.size() == 2_i);
    for (const auto& field : fields) {
      expect(field.get_physical_minimum() == -127_i);
      expect(field.get_physical_maximum() == 127_i);
    }
  };

  "report_descriptor resolves maximum signs at the main item"_test = [] {
    // A Minimum may follow its Maximum. The eventual negative Minimum still
    // makes the corresponding Maximum a signed two's-complement value.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x09, 0x01, // Usage (Pointer)
        0x25, 0xff, // Logical Maximum (-1), declared first
        0x15, 0x81, // Logical Minimum (-127)
        0x45, 0xff, // Physical Maximum (-1), declared first
        0x35, 0x81, // Physical Minimum (-127)
        0x75, 0x08, // Report Size (8 bits)
        0x95, 0x01, // Report Count (1)
        0x81, 0x02, // Input (Data, Variable, Absolute)
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& field = result->get_descriptor().get_report_fields()[0];
    expect(field.get_logical_minimum() == -127_i);
    expect(field.get_logical_maximum() == -1_i);
    expect(field.get_physical_minimum() == -127_i);
    expect(field.get_physical_maximum() == -1_i);
  };

  "report_descriptor delimiter usage sets"_test = [] {
    // Each Delimiter pair describes one control. The usages inside the pair are
    // alternatives in preference order, with the first one being preferred.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x02,                   // Usage Page (Simulation Controls)
        0xa9, 0x01,                   // Delimiter (Open): control 1
        0x09, 0x20,                   //   Usage (Flight Control Stick), preferred
        0x0b, 0x01, 0x00, 0x01, 0x00, //   Usage (Generic Desktop: Pointer)
        0xa9, 0x00,                   // Delimiter (Close)
        0xa9, 0x01,                   // Delimiter (Open): control 2
        0x09, 0x21,                   //   Usage (0x21), preferred
        0x09, 0x22,                   //   Usage (0x22), alternative
        0xa9, 0x00,                   // Delimiter (Close)
        0x15, 0x00,                   // Logical Minimum (0)
        0x26, 0xff, 0x00,             // Logical Maximum (255)
        0x75, 0x08,                   // Report Size (8 bits)
        0x95, 0x02,                   // Report Count (2)
        0x81, 0x02,                   // Input (Data, Variable, Absolute)
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& field = result->get_descriptor().get_report_fields()[0];
    expect(field.get_usages().size() == 2_i);
    expect(field.get_usages()[0].get_usage() == pqrs::hid::usage::value_t(0x20));
    expect(field.get_usages()[1].get_usage() == pqrs::hid::usage::value_t(0x21));
    expect(field.get_usage_sets().size() == 2_i);
    expect(field.get_usage_sets()[0].get_usages().size() == 2_i);
    expect(field.get_usage_sets()[0].get_usages()[0].get_usage_page() ==
           pqrs::hid::usage_page::value_t(0x02));
    expect(field.get_usage_sets()[0].get_usages()[1].get_usage_page() ==
           pqrs::hid::usage_page::generic_desktop);
    expect(field.get_usage_sets()[0].get_usages()[1].get_usage() ==
           pqrs::hid::usage::generic_desktop::pointer);
  };

  "report_descriptor delimiter usage range"_test = [] {
    // Usage Minimum and Usage Maximum are valid members of a delimited set and
    // remain a range rather than being expanded into individual usages.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x09, // Usage Page (Button)
        0xa9, 0x01, // Delimiter (Open)
        0x19, 0x01, //   Usage Minimum (Button 1)
        0x29, 0x04, //   Usage Maximum (Button 4)
        0xa9, 0x00, // Delimiter (Close)
        0x15, 0x00, // Logical Minimum (0)
        0x25, 0x01, // Logical Maximum (1)
        0x75, 0x01, // Report Size (1 bit)
        0x95, 0x01, // Report Count (1)
        0x81, 0x02, // Input (Data, Variable, Absolute)
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& field = result->get_descriptor().get_report_fields()[0];
    expect(field.get_usages().size() == 1_i);
    expect(field.get_usages()[0].get_usage() == pqrs::hid::usage::value_t(1));
    expect(field.get_usage_sets().size() == 1_i);
    const auto& set = field.get_usage_sets()[0];
    expect(set.get_usages().empty());
    expect(set.get_usage_minimum().has_value());
    expect(set.get_usage_maximum().has_value());
    if (set.get_usage_minimum() && set.get_usage_maximum()) {
      expect(set.get_usage_minimum()->get_usage() == pqrs::hid::usage::value_t(1));
      expect(set.get_usage_maximum()->get_usage() == pqrs::hid::usage::value_t(4));
    }
  };

  "report_descriptor collection delimiter usage set"_test = [] {
    // Delimiters may also provide alternative identities for a non-top-level
    // collection, so the collection path retains the same grouping.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01,                   // Usage Page (Generic Desktop)
        0x09, 0x04,                   // Usage (Joystick)
        0xa1, 0x01,                   // Collection (Application)
        0x05, 0x02,                   //   Usage Page (Simulation Controls)
        0xa9, 0x01,                   //   Delimiter (Open)
        0x09, 0x20,                   //     Usage (Flight Control Stick)
        0x0b, 0x01, 0x00, 0x01, 0x00, //     Usage (Generic Desktop: Pointer)
        0xa9, 0x00,                   //   Delimiter (Close)
        0xa1, 0x00,                   //   Collection (Physical)
        0x09, 0x21,                   //     Usage (0x21)
        0x15, 0x00,                   //     Logical Minimum (0)
        0x25, 0x01,                   //     Logical Maximum (1)
        0x75, 0x08,                   //     Report Size (8 bits)
        0x95, 0x01,                   //     Report Count (1)
        0x81, 0x02,                   //     Input (Data, Variable, Absolute)
        0xc0,                         //   End Collection
        0xc0,                         // End Collection
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& path = result->get_descriptor().get_report_fields()[0].get_collection_path();
    expect(path.size() == 2_i);
    expect(path[1].get_usage().has_value());
    expect(path[1].get_usage_sets().size() == 1_i);
    expect(path[1].get_usage_sets()[0].get_usages().size() == 2_i);
  };

  "report_descriptor rejects a non-application top-level collection"_test = [] {
    // Non-Application Collections may use delimited aliases, but HID 1.11
    // requires them to be nested inside a top-level Application Collection.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x02,                   // Usage Page (Simulation Controls)
        0xa9, 0x01,                   // Delimiter (Open)
        0x09, 0x20,                   //   Usage (Flight Control Stick)
        0x0b, 0x01, 0x00, 0x01, 0x00, //   Usage (Generic Desktop: Pointer)
        0xa9, 0x00,                   // Delimiter (Close)
        0xa1, 0x00,                   // Collection (Physical)
        0x09, 0x21,                   //   Usage (0x21)
        0x15, 0x00,                   //   Logical Minimum (0)
        0x25, 0x01,                   //   Logical Maximum (1)
        0x75, 0x08,                   //   Report Size (8 bits)
        0x95, 0x01,                   //   Report Count (1)
        0x81, 0x02,                   //   Input (Data, Variable, Absolute)
        0xc0,                         // End Collection
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(
        bytes,
        pqrs::hid::report_descriptor::validation_mode::strict);
    expect(!result.has_value());
    if (!result) {
      expect(result.error().get_code() ==
             pqrs::hid::report_descriptor::parse_error_code::top_level_collection_not_application);
    }
  };

  "report_descriptor rejects a reserved long item"_test = [] {
    // HID 1.11 defines the long-item envelope but reserves every long-item tag,
    // so even a structurally complete long item is not a known descriptor item.
    // clang-format off
    const std::vector<uint8_t> bytes = {
        0xfe, 0x02, 0x01, 0xaa, 0xbb, // Long item (tag 1, two payload bytes)
    };
    // clang-format on

    auto result = pqrs::hid::report_descriptor::parse(
        bytes,
        pqrs::hid::report_descriptor::validation_mode::strict);
    expect(!result.has_value());
    if (!result) {
      expect(result.error().get_code() ==
             pqrs::hid::report_descriptor::parse_error_code::unknown_or_reserved_item);
    }
  };

  "report_descriptor accepts an explicitly declared zero-bit field"_test = [] {
    // Report Size must be declared, but unlike Report Count the HID parser
    // error table does not require its value to be nonzero.
    const std::vector<uint8_t> bytes = {
        0x05,
        0x01, // Usage Page (Generic Desktop)
        0x15,
        0x00, // Logical Minimum (0)
        0x25,
        0x00, // Logical Maximum (0)
        0x75,
        0x00, // Report Size (0 bits)
        0x95,
        0x01, // Report Count (1)
        0x81,
        0x01, // Input (Constant, Array, Absolute)
    };

    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (result) {
      expect(result->get_descriptor().get_report_fields().size() == 1_i);
      expect(result->get_descriptor().get_report_fields()[0].get_size_bits() == 0_i);
    }
  };

  "report_descriptor permissive mode returns recoverable diagnostics"_test = [] {
    const std::vector<uint8_t> bytes = {
        0x05,
        0x01, // Usage Page (Generic Desktop)
        0x09,
        0x01, // Usage (Pointer)
        0x15,
        0x00, // Logical Minimum (0)
        0x25,
        0x02, // Logical Maximum (2), too large for one bit
        0x75,
        0x01, // Report Size (1 bit)
        0x95,
        0x01, // Report Count (1)
        0x81,
        0x02, // Input (Data, Variable, Absolute)
    };

    // Permissive mode is the default because real devices often contain
    // metadata inconsistencies that do not make their bit layout ambiguous.
    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& fields = result->get_descriptor().get_report_fields();
    expect(fields.size() == 1_i);
    if (!fields.empty()) {
      // The parser reports the violation without clamping the descriptor's
      // original logical maximum to the representable one-bit range.
      expect(fields[0].get_logical_maximum() == 2_i);
    }

    const auto& diagnostics = result->get_diagnostics();
    expect(diagnostics.size() == 1_i);
    if (!diagnostics.empty()) {
      expect(diagnostics[0].get_code() ==
             pqrs::hid::report_descriptor::parse_error_code::logical_range_exceeds_report_size);
      expect(diagnostics[0].get_byte_offset() == 12_i);
    }
  };

  "report_descriptor permissive mode preserves prohibited delimiter aliases"_test = [] {
    using error_code = pqrs::hid::report_descriptor::parse_error_code;

    // HID prohibits aliases on an Application Collection, but they do not make
    // the report layout ambiguous. Permissive mode therefore keeps them on the
    // collection path and reports the violation.
    // clang-format off
    const std::vector<uint8_t> application_bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0xa9, 0x01, // Delimiter (Open)
        0x09, 0x01, // Usage (Pointer)
        0x09, 0x02, // Usage (Mouse)
        0xa9, 0x00, // Delimiter (Close)
        0xa1, 0x01, // Collection (Application)
        0x09, 0x01, //   Usage (Pointer)
        0x15, 0x00, //   Logical Minimum (0)
        0x25, 0x01, //   Logical Maximum (1)
        0x75, 0x01, //   Report Size (1 bit)
        0x95, 0x01, //   Report Count (1)
        0x81, 0x02, //   Input
        0xc0,       // End Collection
    };
    // clang-format on

    auto application_result = pqrs::hid::report_descriptor::parse(application_bytes);
    expect(application_result.has_value());
    if (application_result) {
      const auto& diagnostics = application_result->get_diagnostics();
      expect(diagnostics.size() == 1_i);
      if (!diagnostics.empty()) {
        expect(diagnostics[0].get_code() == error_code::invalid_delimiter);
        expect(diagnostics[0].get_byte_offset() == 10_i);
      }

      const auto& fields = application_result->get_descriptor().get_report_fields();
      expect(fields.size() == 1_i);
      if (!fields.empty()) {
        const auto& path = fields[0].get_collection_path();
        expect(path.size() == 1_i);
        if (!path.empty()) {
          expect(path[0].get_usage_sets().size() == 1_i);
          if (!path[0].get_usage_sets().empty()) {
            expect(path[0].get_usage_sets()[0].get_usages().size() == 2_i);
          }
        }
      }
    }

    // Delimiter aliases are likewise prohibited for Array fields, but their
    // Report Size and Count still define an unambiguous field layout.
    // clang-format off
    const std::vector<uint8_t> array_bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x15, 0x00, // Logical Minimum (0)
        0x25, 0x02, // Logical Maximum (2)
        0x75, 0x08, // Report Size (8 bits)
        0x95, 0x01, // Report Count (1)
        0xa9, 0x01, // Delimiter (Open)
        0x09, 0x01, // Usage (Pointer)
        0x09, 0x02, // Usage (Mouse)
        0xa9, 0x00, // Delimiter (Close)
        0x81, 0x00, // Input (Data, Array, Absolute)
    };
    // clang-format on

    auto array_result = pqrs::hid::report_descriptor::parse(array_bytes);
    expect(array_result.has_value());
    if (array_result) {
      const auto& diagnostics = array_result->get_diagnostics();
      expect(diagnostics.size() == 1_i);
      if (!diagnostics.empty()) {
        expect(diagnostics[0].get_code() == error_code::invalid_delimiter);
        expect(diagnostics[0].get_byte_offset() == 18_i);
      }

      const auto& fields = array_result->get_descriptor().get_report_fields();
      expect(fields.size() == 1_i);
      if (!fields.empty()) {
        expect(fields[0].get_usage_sets().size() == 1_i);
        if (!fields[0].get_usage_sets().empty()) {
          expect(fields[0].get_usage_sets()[0].get_usages().size() == 2_i);
        }
      }
    }
  };

  "report_descriptor permissive mode continues after item diagnostics"_test = [] {
    using error_code = pqrs::hid::report_descriptor::parse_error_code;

    auto expect_diagnostic = [](const std::vector<uint8_t>& bytes,
                                error_code code) {
      auto result = pqrs::hid::report_descriptor::parse(bytes);
      expect(result.has_value());
      if (!result) {
        return;
      }

      const auto& diagnostics = result->get_diagnostics();
      expect(diagnostics.size() == 1_i);
      if (!diagnostics.empty()) {
        expect(diagnostics[0].get_code() == code);
        expect(diagnostics[0].get_byte_offset() == 0_i);
      }
    };

    // These items have known boundaries and can therefore be skipped without
    // guessing the layout of any report field.
    expect_diagnostic({0x0c}, error_code::unknown_or_reserved_item);
    expect_diagnostic({0xfe, 0x00, 0x00}, error_code::unknown_or_reserved_item);
    expect_diagnostic({0x05, 0x00}, error_code::invalid_usage_page);
    expect_diagnostic({0x85, 0x00}, error_code::invalid_report_id);
    expect_diagnostic({0x95, 0x00}, error_code::invalid_report_size_or_count);
    expect_diagnostic({0xa5, 0x00, 0xb4}, error_code::invalid_item_data_size);
  };

  "report_descriptor permissive mode preserves invalid collection layout"_test = [] {
    using error_code = pqrs::hid::report_descriptor::parse_error_code;

    // A non-Application top-level Collection still has balanced boundaries.
    const std::vector<uint8_t> top_level_bytes = {
        0x09,
        0x01, // Usage (Pointer)
        0xa1,
        0x00, // Collection (Physical)
        0xc0, // End Collection
    };
    auto top_level_result = pqrs::hid::report_descriptor::parse(top_level_bytes);
    expect(top_level_result.has_value());
    if (top_level_result) {
      const auto& diagnostics = top_level_result->get_diagnostics();
      expect(diagnostics.size() == 1_i);
      if (!diagnostics.empty()) {
        expect(diagnostics[0].get_code() ==
               error_code::top_level_collection_not_application);
        expect(diagnostics[0].get_byte_offset() == 2_i);
      }
    }

    // A nested Application Collection is also retained in the path without
    // replacing ownership of the enclosing top-level Application Collection.
    // clang-format off
    const std::vector<uint8_t> nested_bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x09, 0x02, // Usage (Mouse)
        0xa1, 0x01, // Collection (Application)
        0x09, 0x01, //   Usage (Pointer)
        0xa1, 0x01, //   Collection (Application)
        0xc0,       //   End Collection
        0xc0,       // End Collection
    };
    // clang-format on
    auto nested_result = pqrs::hid::report_descriptor::parse(nested_bytes);
    expect(nested_result.has_value());
    if (nested_result) {
      const auto& diagnostics = nested_result->get_diagnostics();
      expect(diagnostics.size() == 1_i);
      if (!diagnostics.empty()) {
        expect(diagnostics[0].get_code() ==
               error_code::application_collection_not_top_level);
        expect(diagnostics[0].get_byte_offset() == 8_i);
      }
    }
  };

  "report_descriptor permissive mode preserves cross-collection report offsets"_test = [] {
    using namespace pqrs::hid::report_descriptor;

    // clang-format off
    const std::vector<uint8_t> bytes = {
        0x05, 0x01, // Usage Page (Generic Desktop)
        0x09, 0x02, // Usage (Mouse)
        0xa1, 0x01, // Collection (Application)
        0x85, 0x01, //   Report ID (1)
        0x09, 0x01, //   Usage (Pointer)
        0x15, 0x00, //   Logical Minimum (0)
        0x25, 0x01, //   Logical Maximum (1)
        0x75, 0x08, //   Report Size (8 bits)
        0x95, 0x01, //   Report Count (1)
        0x81, 0x02, //   Input
        0xc0,       // End Collection
        0x09, 0x02, // Usage (Mouse)
        0xa1, 0x01, // Collection (Application)
        0x85, 0x01, //   Report ID (1)
        0x09, 0x01, //   Usage (Pointer)
        0x81, 0x02, //   Input
        0xc0,       // End Collection
    };
    // clang-format on

    auto result = parse(bytes);
    expect(result.has_value());
    if (!result) {
      return;
    }

    const auto& diagnostics = result->get_diagnostics();
    expect(diagnostics.size() == 1_i);
    if (!diagnostics.empty()) {
      expect(diagnostics[0].get_code() ==
             parse_error_code::report_id_spans_top_level_application_collection);
      expect(diagnostics[0].get_byte_offset() == 29_i);
    }

    auto fields = result->get_descriptor().find_report_fields(
        report_type::input,
        pqrs::hid::report_id::value_t(1));
    expect(fields.size() == 2_i);
    if (fields.size() == 2) {
      expect(fields[0]->get_bit_offset() == 0_i);
      expect(fields[1]->get_bit_offset() == 8_i);
    }
  };

  "report_descriptor permissive mode preserves field validation metadata"_test = [] {
    using error_code = pqrs::hid::report_descriptor::parse_error_code;

    auto expect_diagnostic = [](const std::vector<uint8_t>& bytes,
                                error_code code) {
      auto result = pqrs::hid::report_descriptor::parse(bytes);
      expect(result.has_value());
      if (!result) {
        return;
      }

      const auto& diagnostics = result->get_diagnostics();
      expect(diagnostics.size() == 1_i);
      if (!diagnostics.empty()) {
        expect(diagnostics[0].get_code() == code);
      }
    };

    // Reversed extents remain observable to clients instead of being reordered.
    expect_diagnostic({
                          0x05,
                          0x01, // Usage Page (Generic Desktop)
                          0x09,
                          0x01, // Usage (Pointer)
                          0x15,
                          0x05, // Logical Minimum (5)
                          0x25,
                          0x01, // Logical Maximum (1)
                          0x75,
                          0x08, // Report Size (8 bits)
                          0x95,
                          0x01, // Report Count (1)
                          0x81,
                          0x02, // Input
                      },
                      error_code::invalid_extents);

    // A 32-bit element starting one bit into a byte spans five bytes.
    expect_diagnostic({
                          0x05,
                          0x01, // Usage Page (Generic Desktop)
                          0x15,
                          0x00, // Logical Minimum (0)
                          0x25,
                          0x01, // Logical Maximum (1)
                          0x75,
                          0x01, // Report Size (1 bit)
                          0x95,
                          0x01, // Report Count (1)
                          0x81,
                          0x01, // Input (Constant): one-bit padding
                          0x09,
                          0x01, // Usage (Pointer)
                          0x75,
                          0x20, // Report Size (32 bits)
                          0x81,
                          0x02, // Input
                      },
                      error_code::report_field_spans_more_than_four_bytes);

    // Buffered Bytes requires byte-aligned start and end offsets.
    expect_diagnostic({
                          0x05,
                          0x01, // Usage Page (Generic Desktop)
                          0x09,
                          0x01, // Usage (Pointer)
                          0x15,
                          0x00, // Logical Minimum (0)
                          0x25,
                          0x01, // Logical Maximum (1)
                          0x75,
                          0x04, // Report Size (4 bits)
                          0x95,
                          0x01, // Report Count (1)
                          0x82,
                          0x02,
                          0x01, // Input (Data, Variable, Buffered Bytes)
                      },
                      error_code::buffered_bytes_not_byte_aligned);
  };

  "report_descriptor permissive mode keeps structural errors fatal"_test = [] {
    // Without the Report Size payload, the next item boundary cannot be found;
    // permissive validation therefore cannot safely recover.
    const std::vector<uint8_t> bytes = {0x75};
    auto result = pqrs::hid::report_descriptor::parse(bytes);
    expect(!result.has_value());
    if (!result) {
      expect(result.error().get_code() ==
             pqrs::hid::report_descriptor::parse_error_code::unexpected_end_of_descriptor);
      expect(result.error().get_byte_offset() == 0_i);
    }
  };

  "report_descriptor malformed descriptors"_test = [] {
    using error_code = pqrs::hid::report_descriptor::parse_error_code;

    auto expect_error = [](const std::vector<uint8_t>& bytes,
                           error_code code,
                           std::optional<size_t> byte_offset = std::nullopt) {
      auto result = pqrs::hid::report_descriptor::parse(
          bytes,
          pqrs::hid::report_descriptor::validation_mode::strict);
      expect(!result.has_value());
      if (result) {
        return;
      }

      expect(result.error().get_code() == code);
      if (byte_offset) {
        expect(result.error().get_byte_offset() == *byte_offset);
      }
    };

    {
      // Report Size item without its one-byte value.
      const std::vector<uint8_t> bytes = {0x75};
      expect_error(bytes,
                   error_code::unexpected_end_of_descriptor,
                   0);
    }

    {
      // Usage Page zero is explicitly invalid, even before a Main item uses it.
      const std::vector<uint8_t> bytes = {0x05, 0x00};
      expect_error(bytes, error_code::invalid_usage_page);
    }

    {
      // The short-item encoding can carry 32 bits, but Usage Page is limited
      // to the 16-bit range.
      const std::vector<uint8_t> bytes = {
          0x07,
          0x00,
          0x00,
          0x01,
          0x00,
      };
      expect_error(bytes, error_code::invalid_usage_page);
    }

    {
      // Report Count, unlike Report Size, is required to be nonzero.
      const std::vector<uint8_t> bytes = {0x95, 0x00};
      expect_error(bytes, error_code::invalid_report_size_or_count);
    }

    {
      // Push and Pop have no data payload in the HID short-item format.
      const std::vector<uint8_t> bytes = {0xa5, 0x00};
      expect_error(bytes, error_code::invalid_item_data_size);
    }

    {
      // The same zero-length requirement applies to Pop.
      const std::vector<uint8_t> bytes = {0xb5, 0x00};
      expect_error(bytes, error_code::invalid_item_data_size);
    }

    {
      // Unknown tags and the reserved item type are standard parser errors.
      expect_error({0x30}, error_code::unknown_or_reserved_item);
      expect_error({0xc4}, error_code::unknown_or_reserved_item);
      expect_error({0x68}, error_code::unknown_or_reserved_item);
      expect_error({0x0c}, error_code::unknown_or_reserved_item);
    }

    {
      // The HID specification reserves report ID 0 for reports without IDs.
      const std::vector<uint8_t> bytes = {0x85, 0x00};
      expect_error(bytes, error_code::invalid_report_id);
    }

    {
      // If IDs are used, the first ID must precede every report Main item.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x01, // Usage (Pointer)
          0x15,
          0x00, // Logical Minimum (0)
          0x25,
          0x01, // Logical Maximum (1)
          0x75,
          0x08, // Report Size (8 bits)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x02, // Input without a Report ID
          0x85,
          0x01, // Report ID (1), too late
      };
      expect_error(bytes, error_code::report_id_declared_too_late);
    }

    {
      // Pop must not restore reserved ID 0 after Report IDs have been enabled.
      const std::vector<uint8_t> bytes = {
          0xa4, // Push the initial global state with Report ID 0
          0x85,
          0x01, // Report ID (1)
          0xb4, // Pop, restoring Report ID 0
          0x75,
          0x08, // Report Size (8 bits)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x02, // Invalid unnumbered Input
      };
      expect_error(bytes, error_code::invalid_report_id);
    }

    {
      // A Report ID declaration cannot carry into another top-level
      // Application Collection.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0x85,
          0x01, //   Report ID (1)
          0x09,
          0x01, //   Usage (Pointer)
          0x15,
          0x00, //   Logical Minimum (0)
          0x25,
          0x01, //   Logical Maximum (1)
          0x75,
          0x08, //   Report Size (8 bits)
          0x95,
          0x01, //   Report Count (1)
          0x81,
          0x02, //   Input
          0xc0, // End Collection
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0x09,
          0x01, //   Usage (Pointer)
          0x81,
          0x02, //   Input without a new Report ID declaration
      };
      expect_error(bytes,
                   error_code::report_id_spans_top_level_application_collection);
    }

    {
      // The implicit ID 0 report is still one data report and cannot contain
      // fields from two top-level Application Collections.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0x09,
          0x01, //   Usage (Pointer)
          0x15,
          0x00, //   Logical Minimum (0)
          0x25,
          0x01, //   Logical Maximum (1)
          0x75,
          0x08, //   Report Size (8 bits)
          0x95,
          0x01, //   Report Count (1)
          0x81,
          0x02, //   Input: claims the unnumbered report
          0xc0, // End Collection
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0x09,
          0x01, //   Usage (Pointer)
          0x81,
          0x02, //   Input: cannot share that report
      };
      expect_error(bytes,
                   error_code::report_id_spans_top_level_application_collection);
    }

    {
      // A Report ID declared outside a collection is still owned by the first
      // top-level Application Collection that uses it.
      const std::vector<uint8_t> bytes = {
          0x85,
          0x01, // Report ID (1), outside either collection
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0x09,
          0x01, //   Usage (Pointer)
          0x15,
          0x00, //   Logical Minimum (0)
          0x25,
          0x01, //   Logical Maximum (1)
          0x75,
          0x08, //   Report Size (8 bits)
          0x95,
          0x01, //   Report Count (1)
          0x81,
          0x02, //   Input: claims Report ID 1
          0xc0, // End Collection
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0x09,
          0x01, //   Usage (Pointer)
          0x81,
          0x02, //   Input: cannot reuse Report ID 1
      };
      expect_error(bytes,
                   error_code::report_id_spans_top_level_application_collection);
    }

    {
      // Redeclaring the same Report ID does not allow one report to belong to
      // two different top-level Application Collections.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0x85,
          0x01, //   Report ID (1)
          0x09,
          0x01, //   Usage (Pointer)
          0x15,
          0x00, //   Logical Minimum (0)
          0x25,
          0x01, //   Logical Maximum (1)
          0x75,
          0x08, //   Report Size (8 bits)
          0x95,
          0x01, //   Report Count (1)
          0x81,
          0x02, //   Input
          0xc0, // End Collection
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0x85,
          0x01, //   Report ID (1)
          0x09,
          0x01, //   Usage (Pointer)
          0x81,
          0x02, //   Input: the same ID/type report cannot span collections
          0xc0, // End Collection
      };
      expect_error(bytes,
                   error_code::report_id_spans_top_level_application_collection);
    }

    {
      // Pop without a preceding Push.
      const std::vector<uint8_t> bytes = {0xb4};
      expect_error(bytes, error_code::global_state_stack_underflow);
    }

    {
      // End Collection without a preceding Collection.
      const std::vector<uint8_t> bytes = {0xc0};
      expect_error(bytes, error_code::collection_stack_underflow);
    }

    {
      // Application Collections identify independently routed devices and
      // must therefore appear only at the top level.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x02, // Usage (Mouse)
          0xa1,
          0x01, // Collection (Application)
          0xa1,
          0x01, //   Collection (Application), invalid when nested
      };
      expect_error(bytes,
                   error_code::application_collection_not_top_level);
    }

    {
      // Long item declares two payload bytes but contains only one.
      const std::vector<uint8_t> bytes = {0xfe, 0x02, 0x01, 0xff};
      expect_error(bytes, error_code::unexpected_end_of_descriptor);
    }

    {
      // Input appears before Report Size and Report Count are declared.
      const std::vector<uint8_t> bytes = {0x81, 0x02};
      expect_error(bytes, error_code::invalid_report_size_or_count);
    }

    {
      // Usage Page and both logical bounds are required before a report field.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x01, // Usage (Pointer)
          0x75,
          0x08, // Report Size (8 bits)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x02, // Input
      };
      expect_error(bytes, error_code::missing_required_global_item);
    }

    {
      // A Data field needs a Usage; only Constant fields may omit it as
      // padding.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x15,
          0x00, // Logical Minimum (0)
          0x25,
          0x01, // Logical Maximum (1)
          0x75,
          0x01, // Report Size (1 bit)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x02, // Input (Data, Variable, Absolute)
      };
      expect_error(bytes, error_code::missing_usage);
    }

    {
      // One explicitly declared physical bound requires its counterpart at
      // the next report Main item.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x01, // Usage (Pointer)
          0x15,
          0x00, // Logical Minimum (0)
          0x25,
          0x01, // Logical Maximum (1)
          0x35,
          0x00, // Physical Minimum (0), without Physical Maximum
          0x75,
          0x01, // Report Size (1 bit)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x02, // Input
      };
      expect_error(bytes, error_code::incomplete_physical_extents);
    }

    {
      // Pairing is checked at every Main item, including Collection rather
      // than only at report-field items.
      const std::vector<uint8_t> bytes = {
          0x35,
          0x00, // Physical Minimum (0), without Physical Maximum
          0x09,
          0x01, // Usage (Pointer)
          0xa1,
          0x01, // Collection (Application)
      };
      expect_error(bytes, error_code::incomplete_physical_extents);
    }

    {
      // A one-bit unsigned field cannot represent the declared value 2.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x01, // Usage (Pointer)
          0x15,
          0x00, // Logical Minimum (0)
          0x25,
          0x02, // Logical Maximum (2)
          0x75,
          0x01, // Report Size (1 bit)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x02, // Input
      };
      expect_error(bytes, error_code::logical_range_exceeds_report_size);
    }

    {
      // Null State requires one encoding in addition to every value in the
      // logical range; 0..255 already consumes all encodings of an 8-bit field.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x01, // Usage (Pointer)
          0x15,
          0x00, // Logical Minimum (0)
          0x26,
          0xff,
          0x00, // Logical Maximum (255)
          0x75,
          0x08, // Report Size (8 bits)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x42, // Input (Data, Variable, Null State)
      };
      expect_error(bytes, error_code::logical_range_exceeds_report_size);
    }

    {
      // A 32-bit element beginning one bit into a byte would occupy five
      // bytes, which exceeds the per-element limit in HID 1.11 section 8.4.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x15,
          0x00, // Logical Minimum (0)
          0x25,
          0x01, // Logical Maximum (1)
          0x75,
          0x01, // Report Size (1 bit)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x01, // Input (Constant): one-bit padding
          0x09,
          0x01, // Usage (Pointer)
          0x75,
          0x20, // Report Size (32 bits)
          0x81,
          0x02, // Input (Data, Variable, Absolute)
      };
      expect_error(bytes,
                   error_code::report_field_spans_more_than_four_bytes);
    }

    {
      // Buffered Bytes is a byte stream, so a non-byte-sized field is not a
      // valid layout even when it begins on a byte boundary.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x01, // Usage (Pointer)
          0x15,
          0x00, // Logical Minimum (0)
          0x25,
          0x01, // Logical Maximum (1)
          0x75,
          0x01, // Report Size (1 bit)
          0x95,
          0x01, // Report Count (1)
          0x82,
          0x02,
          0x01, // Input (Data, Variable, Buffered Bytes)
      };
      expect_error(bytes, error_code::buffered_bytes_not_byte_aligned);
    }

    {
      // Designator ranges are complete ordered pairs.
      expect_error({0x49, 0x01, 0x81, 0x02},
                   error_code::invalid_designator_range);
      expect_error({0x49, 0x02, 0x59, 0x01, 0x81, 0x02},
                   error_code::invalid_designator_range);
    }

    {
      // String ranges use the same complete, ordered-pair rule.
      expect_error({0x99, 0x01, 0x81, 0x02},
                   error_code::invalid_string_range);
      expect_error({0x89, 0x02, 0x99, 0x01, 0x81, 0x02},
                   error_code::invalid_string_range);
    }

    {
      // Usage Minimum and Usage Maximum form one inseparable local range.
      const std::vector<uint8_t> bytes = {
          0x19,
          0x01, // Usage Minimum (1), without Usage Maximum
          0x81,
          0x02, // Input
      };
      expect_error(bytes, error_code::invalid_usage_range);
    }

    {
      // Logical extents must describe an ordered range.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x01, // Usage (Pointer)
          0x15,
          0x0a, // Logical Minimum (10)
          0x25,
          0x05, // Logical Maximum (5)
          0x75,
          0x08, // Report Size (8 bits)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x02, // Input
      };
      expect_error(bytes, error_code::invalid_extents);
    }

    {
      // Explicit physical extents obey the same ordering requirement.
      const std::vector<uint8_t> bytes = {
          0x05,
          0x01, // Usage Page (Generic Desktop)
          0x09,
          0x01, // Usage (Pointer)
          0x15,
          0x00, // Logical Minimum (0)
          0x25,
          0x64, // Logical Maximum (100)
          0x35,
          0x0a, // Physical Minimum (10)
          0x45,
          0x05, // Physical Maximum (5)
          0x75,
          0x08, // Report Size (8 bits)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x02, // Input
      };
      expect_error(bytes, error_code::invalid_extents);
    }

    {
      // The same pairing rule applies when only Usage Maximum is present.
      const std::vector<uint8_t> bytes = {
          0x29,
          0x01, // Usage Maximum (1), without Usage Minimum
          0x81,
          0x02, // Input
      };
      expect_error(bytes, error_code::invalid_usage_range);
    }

    {
      // A range is invalid when its maximum precedes its minimum.
      const std::vector<uint8_t> bytes = {
          0x19,
          0x02, // Usage Minimum (2)
          0x29,
          0x01, // Usage Maximum (1)
          0xa1,
          0x00, // Collection
      };
      expect_error(bytes, error_code::invalid_usage_range);
    }

    {
      // If one range end embeds a Usage Page, the other must do so as well.
      const std::vector<uint8_t> bytes = {
          0x1b,
          0x01,
          0x00,
          0x01,
          0x00, // Usage Minimum (Generic Desktop: 1), extended
          0x29,
          0x02, // Usage Maximum (2), short
          0xa1,
          0x00, // Collection
      };
      expect_error(bytes, error_code::invalid_usage_range);
    }

    {
      // The embedded Usage Pages of an extended range must agree.
      const std::vector<uint8_t> bytes = {
          0x1b,
          0x01,
          0x00,
          0x01,
          0x00, // Usage Minimum (Generic Desktop: 1), extended
          0x2b,
          0x02,
          0x00,
          0x09,
          0x00, // Usage Maximum (Button: 2), extended
          0xa1,
          0x00, // Collection
      };
      expect_error(bytes, error_code::invalid_usage_range);
    }

    {
      // Usage ranges inside Delimiter sets obey the same pairing rules.
      const std::vector<uint8_t> bytes = {
          0xa9,
          0x01, // Delimiter (Open)
          0x19,
          0x01, // Usage Minimum (1), without Usage Maximum
          0xa9,
          0x00, // Delimiter (Close)
          0x81,
          0x02, // Input
      };
      expect_error(bytes, error_code::invalid_usage_range);
    }

    {
      // Delimiter sets cannot be nested.
      const std::vector<uint8_t> bytes = {
          0xa9,
          0x01, // Delimiter (Open)
          0xa9,
          0x01, // Delimiter (Open), nested
      };
      expect_error(bytes, error_code::invalid_delimiter);
    }

    {
      // A Close item requires a preceding Open item.
      const std::vector<uint8_t> bytes = {0xa9, 0x00};
      expect_error(bytes, error_code::invalid_delimiter);
    }

    {
      // A delimited set may not contain Global items.
      const std::vector<uint8_t> bytes = {
          0xa9,
          0x01, // Delimiter (Open)
          0x05,
          0x09, // Usage Page (Button)
      };
      expect_error(bytes, error_code::invalid_delimiter);
    }

    {
      // Usage, Usage Minimum, and Usage Maximum are the only Local item forms
      // permitted inside a delimited set.
      const std::vector<uint8_t> bytes = {
          0xa9,
          0x01, // Delimiter (Open)
          0x39,
          0x01, // Designator Index (1)
      };
      expect_error(bytes, error_code::invalid_delimiter);
    }

    {
      // Top-level collections must have one unambiguous device usage.
      const std::vector<uint8_t> bytes = {
          0xa9,
          0x01, // Delimiter (Open)
          0x09,
          0x01, // Usage (1)
          0x09,
          0x02, // Usage (2)
          0xa9,
          0x00, // Delimiter (Close)
          0xa1,
          0x01, // Collection (Application)
      };
      expect_error(bytes, error_code::invalid_delimiter);
    }

    {
      // Array values index one usage list and cannot carry per-control aliases.
      const std::vector<uint8_t> bytes = {
          0xa9,
          0x01, // Delimiter (Open)
          0x09,
          0x01, // Usage (1)
          0x09,
          0x02, // Usage (2)
          0xa9,
          0x00, // Delimiter (Close)
          0x75,
          0x08, // Report Size (8 bits)
          0x95,
          0x01, // Report Count (1)
          0x81,
          0x00, // Input (Data, Array, Absolute)
      };
      expect_error(bytes, error_code::invalid_delimiter);
    }

    {
      // A Main item cannot consume an open delimiter set.
      const std::vector<uint8_t> bytes = {
          0xa9,
          0x01, // Delimiter (Open)
          0x09,
          0x01, // Usage (1)
          0xa1,
          0x00, // Collection before Delimiter (Close)
      };
      expect_error(bytes, error_code::unclosed_delimiter);
    }

    {
      // An Open item at the end of the descriptor is also incomplete.
      const std::vector<uint8_t> bytes = {
          0xa9,
          0x01, // Delimiter (Open)
          0x09,
          0x01, // Usage (1)
      };
      expect_error(bytes, error_code::unclosed_delimiter);
    }
  };
}
