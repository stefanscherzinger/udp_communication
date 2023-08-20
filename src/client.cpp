#include "boost/asio.hpp"
#include <chrono>
#include <thread>
#include "udp_communication/protocol.h"

using namespace boost::asio;

int main()
{
  io_service io_service;
  ip::udp::socket socket(io_service);
  ip::udp::endpoint remote_endpoint;

  socket.open(ip::udp::v4());

  constexpr int port = 9000;
  remote_endpoint = ip::udp::endpoint(ip::address::from_string("127.0.0.1"), port);

  boost::system::error_code err;

  constexpr double rate = 3.0;  // Hz
  uint32_t sequence_number = 0;

  while (true)
  {
    auto msg = Message();
    msg.sequence_number = sequence_number;
    msg.data = {0.1, 2.3, 3.4, 5.6};

    auto serialized_msg = msg.serialize();
    socket.send_to(buffer(serialized_msg, serialized_msg.size()), remote_endpoint, 0, err);
    ++sequence_number;

    std::this_thread::sleep_for(std::chrono::duration<double>(1.0 / rate));
  }

  socket.close();

  return 0;
}
