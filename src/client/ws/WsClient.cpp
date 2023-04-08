//
// Created by huiyi on 2023/4/8.
//

#include "WsClient.h"

namespace LWS {

  // Handlers
  void WsClient::onOpen(WSC *c, websocketpp::connection_hdl hdl) {
    is_connect = true;
  }

  void WsClient::onFail(WSC *c, websocketpp::connection_hdl hdl) {
    c->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
  }

  void WsClient::onMessage(WSC *c, websocketpp::connection_hdl hdl, message_ptr msg) {
    c->get_alog().write(websocketpp::log::alevel::app, "Received Reply: " + msg->get_payload());
  }

  void WsClient::onClose(WSC *c, websocketpp::connection_hdl hdl) {
    c->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
  }

  WsClient::WsClient() { m_cli.init_asio(); }

  WsClient::WsClient(const std::string &host) {
    m_cli.init_asio();
    SetConnConfig(host);
  }

  void WsClient::SetConnConfig(const std::string &host) {
    m_host = host;
    websocketpp::lib::error_code ec;
    m_conn = m_cli.get_connection(host, ec);
    m_conn->append_header("access-control-allow-origin", "*");
    if (ec) {
      //std::cout << "could not create connection because: " << ec.message() << std::endl;
      throw websocketpp::exception(ec);
    }

  }

  void WsClient::SetAuth(const std::string &token) {
    m_token = token;
    m_conn->append_header("Authorization", "bearer " + token);
  }

  void WsClient::Run() {
    m_cli.connect(m_conn);
    m_cli.run();
//     client c;
//     boost::asio::streambuf req;
//     std::ostream req_stream(&req);
//     req_stream << "GET / HTTP/1.1\r\n";
//     req_stream << "Host: " << uri << "\r\n";
//     req_stream << header_key << ": " << header_value << "\r\n";
//     req_stream << "Upgrade: websocket\r\n";
//     req_stream << "Connection: Upgrade\r\n";
//     req_stream << "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n";
//     req_stream << "Sec-WebSocket-Version: 13\r\n\r\n";
//
//     websocketpp::lib::error_code ec;
//     client::connection_ptr con = c.get_connection(uri, ec);
//     if (ec) {
//       std::cout << "连接错误：" << ec.message() << std::endl;
//       return -1;
//     }
//
//     con->set_user_agent("Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:68.0) Gecko/20100101 Firefox/68.0");
//     con->append_header("MyHeader", "MyValue");
//     con->append_header("Upgrade", "websocket");
//     con->append_header("Connection", "Upgrade");
//     con->append_header("Sec-WebSocket-Key", "x3JJHMbDL1EzLkh9GBhXDw==");
//     con->append_header("Sec-WebSocket-Version", "13");
//
//     // 将 HTTP 请求头附加到连接的握手请求中
//     std::istream req_stream2(&req);
//     std::stringstream ss;
//     ss << req_stream2.rdbuf();
//     con->append_header("Sec-WebSocket-Protocol", ss.str());

  }
}



