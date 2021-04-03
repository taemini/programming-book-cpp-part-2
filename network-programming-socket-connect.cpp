#include <boost/asio.hpp>
#include <iostream>

int main() {
  boost::asio::io_context io_context;
  boost::asio::ip::tcp::resolver resolver{io_context};
  boost::asio::ip::tcp::socket socket{io_context};
  try {
    auto endpoint = resolver.resolve("google.com", "http");
    const auto connected_endpoint = boost::asio::connect(socket, endpoint);
    std::cout << connected_endpoint;
  } catch (boost::system::system_error& se) {
    std::cerr << "Error: " << se.what() << std::endl;
  }
}