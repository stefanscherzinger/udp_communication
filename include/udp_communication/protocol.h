#include <string>
#include <vector>
#include <array>

struct Message
{
  uint32_t sequence_number;
  std::array<double, 10> data;

  static constexpr size_t size() { return sizeof(uint32_t) + sizeof(double) * 10; };
  std::string print() const;

  std::vector<uint8_t> serialize() const;
  static Message deserialize(const std::vector<uint8_t>& serialized_data);
};
