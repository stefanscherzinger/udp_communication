#include "boost/asio.hpp"
#include <chrono>
#include <thread>

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
  while (true)
  {
    std::string data = "Arbitrary test data";
    socket.send_to(buffer(data, data.size()), remote_endpoint, 0, err);
    std::this_thread::sleep_for(std::chrono::duration<double>(1.0 / rate));
  }

  socket.close();

  return 0;
}
