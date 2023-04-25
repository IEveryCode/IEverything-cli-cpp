//
// Created by huiyi on 2023/4/8.
//

#ifndef LEVER_WSCLIENT_H
#define LEVER_WSCLIENT_H

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

namespace Client {

  typedef websocketpp::client<websocketpp::config::asio_client> WSC;
  // 消息类型
  typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

  class WsClient {
  private:

    void onClose(websocketpp::connection_hdl& hdl);
    void onFail(websocketpp::connection_hdl& hdl);
    void onOpen(websocketpp::connection_hdl& hdl);
    void onMessage(websocketpp::connection_hdl& hdl, message_ptr& msg);
		void OnValidate(websocketpp::connection_hdl& hdl);
  public:
    WsClient();
    WsClient(const std::string&host);
    void SetConnConfig(const std::string&host);
    void SetAuth(const std::string&token);
    void Run();

  private:
    bool is_connect = false;
    std::string m_host;
    std::string m_token;
    WSC m_cli;
    WSC::connection_ptr m_conn;
  };
}


#endif //LEVER_WSCLIENT_H
