#include <boost/asio.hpp>
#include <iostream>

int main() {
  boost::asio::io_context io_context;
  boost::asio::ip::tcp::resolver resolver{io_context};
  boost::system::error_code ec;
  // error_code reference를 인자로 제공하지 않으면 boost::system::system_error를
  // throw하게 만들 수도 있다.
  for (auto&& result : resolver.resolve("google.com", "http", ec)) {
    std::cout << result.service_name() << " " << result.host_name() << " "
              << result.endpoint() << std::endl;
  }
  if (ec) std::cout << "Error code: " << ec << std::endl;
}