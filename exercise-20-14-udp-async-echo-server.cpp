#include <boost/algorithm/string/case_conv.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace boost::asio;

struct Session : std::enable_shared_from_this<Session> {
  explicit Session(io_context& io_context)
      : socket{io_context, ip::udp::endpoint{ip::udp::v4(), 1895}} {}
  void read() {
    std::cout << "start reading..." << std::endl;
    socket.async_receive_from(
        buffer(message, 1024), sender_endpoint,
        [self = shared_from_this()](boost::system::error_code ec,
                                    std::size_t transferred) {
          std::cout << "Transferred: " << transferred << std::endl;
          if (ec) {
            std::cout << "Error: " << ec.message() << std::endl;
            return;
          } else if (transferred > 0) {
            std::cout << "Message: " << self->message << std::endl;
            std::cout << "Endpoint: " << self->sender_endpoint.address() << ":"
                      << self->sender_endpoint.port();
            boost::algorithm::to_upper(self->message);
            self->write();
          } else {
            self->read();
          }
        });
  }

  void write() {
    socket.async_send_to(buffer(message), sender_endpoint, [self=shared_from_this()](boost::system::error_code ec, std::size_t transferred){
      if (ec) return;
      // self->message.clear();
      self->read();
    });
  }

 private:
  ip::udp::socket socket;
  ip::udp::endpoint sender_endpoint;
  std::string message{"Hello WOrld"};
};

int main() {
  try {
    io_context io_context;
    auto session = std::make_shared<Session>(io_context);
    session->read();
    std::cout << "instantiated a session" << std::endl;
    io_context.run();
    std::cout << "ran" << std::endl;
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}