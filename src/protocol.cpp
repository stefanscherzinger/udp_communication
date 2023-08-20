#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <sstream>
#include <udp_communication/protocol.h>

std::string Message::print() const
{
  std::stringstream stream;
  stream << sequence_number << ": ";

  for (const auto& value : data)
  {
    stream << value << ", ";
  }
  return stream.str();
}

std::vector<uint8_t> Message::serialize() const
{
  std::vector<uint8_t> serialized_data(Message::size());

  uint32_t seq_number_network_order = htonl(sequence_number);
  std::memcpy(serialized_data.data(), &seq_number_network_order, sizeof(sequence_number));
  std::memcpy(serialized_data.data() + sizeof(sequence_number), data.data(), sizeof(double) * data.size());

  return serialized_data;
}

Message Message::deserialize(const std::vector<uint8_t>& serialized_data)
{
  Message message;

  uint32_t sequence_number;
  std::memcpy(&sequence_number, serialized_data.data(), sizeof(message.sequence_number));
  message.sequence_number = ntohl(sequence_number);

  std::memcpy(message.data.data(),
              serialized_data.data() + sizeof(sequence_number),
              sizeof(double) * message.data.size());

  return message;
}
