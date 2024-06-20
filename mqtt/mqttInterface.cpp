#include "mqttInterface.hpp"

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <csignal>

bool running = true;

void signal_handler(int signal)
{
	PLOG_DEBUG<<"Signal received, terminating..";
	running = false;
	// do the client shutting down
}

mqttInterface::mqttInterface(const string serverAddress, const string clientId, const queue<std::string>& messageBuffer): 
							m_cli(serverAddress,clientId),
							m_message_queue(messageBuffer)
{
}

mqttInterface::~mqttInterface()
{
}
void mqttInterface::message_arrived(mqtt::const_message_ptr msg)
{
	PLOG_DEBUG<<"message arrived"<< msg->get_payload_str();
	m_message_queue.push(msg->get_payload_str());
}

void mqttInterface::run()
{
    	auto connOpts = mqtt::connect_options_builder()
		.clean_session(false)
		.finalize();
		signal(SIGINT, signal_handler);

	try {
		// Start consumer before connecting to make sure to not miss messages

		m_cli.start_consuming();

		// Connect to the server

		PLOG_DEBUG<<"Connecting to the MQTT server";
		auto tok = m_cli.connect(connOpts);

		// Getting the connect response will block waiting for the
		// connection to complete.
		auto rsp = tok->get_connect_response();

		// If there is no session present, then we need to subscribe, but if
		// there is a session, then the server remembers us and our
		// subscriptions.
		if (!rsp.is_session_present())
			m_cli.subscribe(TOPIC, QOS)->wait();

		PLOG_DEBUG<<"OK";

		// Consume messages
		// This just exits if the client is disconnected.
		// (See some other examples for auto or manual reconnect)
		PLOG_DEBUG<<"Waiting for messages on topic: "<<TOPIC;
	

		while (running) {
			auto msg = m_cli.consume_message();
			if (!msg) break;
			PLOG_DEBUG << msg->get_topic() << ": " << msg->to_string();
		}

		// If we're here, the client was almost certainly disconnected.
		// But we check, just to make sure.

		if (m_cli.is_connected()) {
			cout << "\nShutting down and disconnecting from the MQTT server..." << flush;
			m_cli.unsubscribe(TOPIC)->wait();
			m_cli.stop_consuming();
			m_cli.disconnect()->wait();
			cout << "OK" << endl;
		}
		else {
			PLOG_DEBUG<< "Client was disconnected";
		}
	}
	catch (const mqtt::exception& exc) {
		PLOG_ERROR<<"Could not start the mqtt consumer"<< exc;
	}

}