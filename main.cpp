#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace boost::asio::ip;
using namespace std;

struct SimplePoint {float x, y, z;};

int main()
{
  try
  {
    boost::asio::io_service io_service;
    cout << "Waiting for connection ... ";
    fflush(stdout);
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 10000));
    tcp::socket socket(io_service);
    acceptor.accept(socket);
    cout << " connected!";
    fflush(stdout);

    for (;;)
    {


      boost::array<std::size_t, 1> buf;
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      cout << "Size = " << buf[0] << endl;
      fflush(stdout);

      vector<char> buf_point_cloud(buf[0]);

      len = boost::asio::read(
            socket, boost::asio::buffer(buf_point_cloud),
            boost::asio::transfer_exactly(buf[0]),
             error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      cout << "Nr bytes read = " << len << endl;

      if (len % 12 != 0)
        cerr << "ERROR: size of the received point cloud in bytes is not divisible by 12!"  << endl;

      // Copy the point cloud into a vector
      vector<SimplePoint> pointCloud(len / 12);
      memcpy(&pointCloud[0], &buf_point_cloud[0], len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

