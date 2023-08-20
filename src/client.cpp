#include "boost/asio.hpp"
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
  std::string data = "Arbitrary test data";
  socket.send_to(buffer(data, data.size()), remote_endpoint, 0, err);

  socket.close();

  return 0;
}
