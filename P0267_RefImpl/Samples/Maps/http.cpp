#include "http.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <iostream>

using tcp = boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
namespace http = boost::beast::http;

static std::vector<std::byte> Download( const char *host, const char *port, const char *target )
{
    int version = 11;
    boost::asio::io_context ioc;
    ssl::context ctx{ssl::context::sslv23_client};
    tcp::resolver resolver{ioc};
    ssl::stream<tcp::socket> stream{ioc, ctx};
    
    if(! SSL_set_tlsext_host_name(stream.native_handle(), host)) {
        boost::system::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
        throw boost::system::system_error{ec};
    }
    
    auto const results = resolver.resolve(host, port);
    boost::asio::connect(stream.next_layer(), results.begin(), results.end());
    stream.handshake(ssl::stream_base::client);
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    http::write(stream, req);

    boost::beast::flat_buffer buffer;
    http::response_parser<http::dynamic_body> res;    
    res.body_limit(std::numeric_limits<std::uint64_t>::max());
    http::read(stream, buffer, res);
    
    boost::system::error_code ec;
    stream.shutdown(ec);
    if( ec == boost::asio::error::eof )
        ec.assign(0, ec.category());
    if( ec )
        throw boost::system::system_error{ec};

    std::stringstream ss;
    ss << res.get();
	const auto chars = ss.str();
    
    std::vector<std::byte> bytes;
	bytes.assign((const std::byte*)chars.data(),
			     (const std::byte*)chars.data() + chars.length());
    
    return bytes;
}

std::vector<std::byte> FetchOpenStreetMapData( const std::string &bounding_box )
{    
    auto query = std::string{"/api/0.6/map?bbox="} + bounding_box;
    try {
        return Download("api.openstreetmap.org", "443", query.c_str());
    } catch( boost::system::system_error se ) {
        std::cout << "Exception caught: " << se.what() << std::endl;
        return {};
    }
}
