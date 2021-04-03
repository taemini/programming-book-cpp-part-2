//
// async_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>

using boost::asio::ip::udp;

class server {
 public:
  server(boost::asio::io_context& io_context, short port)
      : socket_(io_context, udp::endpoint(udp::v4(), port)) {
    do_receive();
  }

  void do_receive() {
    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
          std::cout << "Received: " << bytes_recvd << std::endl;
          if (!ec && bytes_recvd > 0) {
            std::cout << sender_endpoint_.address() << ":"
                      << sender_endpoint_.port() << std::endl;
            std::cout << bytes_recvd << std::endl;
            do_send(bytes_recvd);
          } else {
            do_receive();
          }
        });
  }

  void do_send(std::size_t length) {
    socket_.async_send_to(boost::asio::buffer(data_, length), sender_endpoint_,
                          [this](boost::system::error_code /*ec*/,
                                 std::size_t /*bytes_sent*/) { do_receive(); });
  }

 private:
  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];
};

int main() {
  try {
    boost::asio::io_context io_context;
    server s(io_context, 1895);
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}