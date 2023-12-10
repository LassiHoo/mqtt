#include "mqttInterface.hpp"



mqttInterface::mqttInterface(const string serverAddress, const string clientId): _cli(serverAddress,clientId)
{
}

void mqttInterface::run()
{
    	auto connOpts = mqtt::connect_options_builder()
		.clean_session(false)
		.finalize();

	try {
		// Start consumer before connecting to make sure to not miss messages

		_cli.start_consuming();

		// Connect to the server

		PLOG_DEBUG<<"Connecting to the MQTT server";
		auto tok = _cli.connect(connOpts);

		// Getting the connect response will block waiting for the
		// connection to complete.
		auto rsp = tok->get_connect_response();

		// If there is no session present, then we need to subscribe, but if
		// there is a session, then the server remembers us and our
		// subscriptions.
		if (!rsp.is_session_present())
			_cli.subscribe(TOPIC, QOS)->wait();

		PLOG_DEBUG<<"OK";

		// Consume messages
		// This just exits if the client is disconnected.
		// (See some other examples for auto or manual reconnect)
		PLOG_DEBUG<<"Waiting for messages on topic: "<<TOPIC;
	

		while (true) {
			auto msg = _cli.consume_message();
			if (!msg) break;
			PLOG_DEBUG << msg->get_topic() << ": " << msg->to_string();
		}

		// If we're here, the client was almost certainly disconnected.
		// But we check, just to make sure.

		if (_cli.is_connected()) {
			cout << "\nShutting down and disconnecting from the MQTT server..." << flush;
			_cli.unsubscribe(TOPIC)->wait();
			_cli.stop_consuming();
			_cli.disconnect()->wait();
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