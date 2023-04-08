#include <iostream>
#include "WsClient.h"

int main() {
  try{
    LWS::WsClient wc;
    wc.SetConnConfig("ws://127.0.0.1:18080/api/clipbrd/connect");
    wc.SetAuth("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyaWQiOjEsInZlcnNpb24iOjE2ODA5Mjk1MzgsImV4cCI6MzM3ODA1OTA3NiwiaXNzIjoidXNlciIsIm5iZiI6MTY4MDkyODUzOH0.DsrMhFjLnoB21VB8sK27obmLuE2Y3gqwtqWOpq_FD7Y");
    wc.Run();
  }catch (websocketpp::exception const & e) {
    std::cout << e.what() << std::endl;
  }


  return 0;
}
