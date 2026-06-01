// Declare the functions being used



int tcp_call(const char *request_json, char **response_json);
void send_http_response(int gateway_fd, const char *json_body);
void handle_http_client(int gateway_fd);
