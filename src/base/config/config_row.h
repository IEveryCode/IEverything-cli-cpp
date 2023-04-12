#ifndef LEVER_CONFIG_ROW_H
#define LEVER_CONFIG_ROW_H

#define CONNECT_TYPE_REMOTE "remote"

inline const char* CONFIG_ROW = R"(
{
  "type":"remote",
  "ssl": false,
  "host": "127.0.0.1:18080"
}
)";

#endif