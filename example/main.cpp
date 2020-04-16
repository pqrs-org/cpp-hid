#include <pqrs/hid.hpp>
#include <unordered_map>

int main(void) {
  std::cout << "usage_page::generic_desktop: " << pqrs::hid::usage_page::generic_desktop << std::endl;
  std::cout << "usage_page::apple_vendor_keyboard: " << pqrs::hid::usage_page::apple_vendor_keyboard << std::endl;
  std::cout << "usage::keyboard_or_keypad::keyboard_spacebar: " << pqrs::hid::usage::keyboard_or_keypad::keyboard_spacebar << std::endl;

  std::unordered_map<pqrs::hid::usage_page::value_t, std::string> map;
  map[pqrs::hid::usage_page::keyboard_or_keypad] = "12345";

  return 0;
}
