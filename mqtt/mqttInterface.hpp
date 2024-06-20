#if !defined MQTT_INTERFACE
#define MQTT_INTERFACE

#include "mqtt/async_client.h"
#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <string>
#include <queue>

using namespace std;

const string SERVER_ADDRESS	{ "mqtt://localhost:1883" };
const string CLIENT_ID		{ "paho_cpp_async_consume" };
const string TOPIC 			{ "hello" };
const int  QOS = 1;


class mqttInterface: public virtual mqtt::callback
{
public:
    mqttInterface(const string serverAddress, const string clientId, const queue<std::string>& messageBuffer);
    ~mqttInterface();
    void message_arrived(mqtt::const_message_ptr msg) override;

    void run();

private:
    mqtt::async_client m_cli;
    queue<std::string>  m_message_queue;
};

#endif