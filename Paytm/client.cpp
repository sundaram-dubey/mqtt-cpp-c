#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <map>
#include <cctype>
#include <thread>
#include <bits/stdc++.h>
#include <chrono>
#include "mqtt/client.h"


using namespace std;


const std::string SERVER_ADDRESS("tcp://broker.emqx.io:1883");
const std::string CLIENT_ID("i_am_true_alpha_1");
const std::string TOPIC("/dubesundaram99@gmail.com/sundaram");
const std::string TOPIC1("/ravi123sehravat@gmail.com/narendra");

const std::string PAYLOAD1 { "Hello World!" };

const char* PAYLOAD2 = "Hi there!";
const char* PAYLOAD3 = "Is anyone listening?";


const int QOS = 1;


class sample_mem_persistence : virtual public mqtt::iclient_persistence
{
	// Whether the store is open
	bool open_;

	// Use an STL map to store shared persistence pointers
	// against string keys.
	std::map<std::string, std::string> store_;

public:
	sample_mem_persistence() : open_(false) {}

	// "Open" the store
	void open(const std::string& clientId, const std::string& serverURI) override {
		std::cout << "[Opening persistence store for '" << clientId
			<< "' at '" << serverURI << "']" << std::endl;
		open_ = true;
	}

	// Close the persistent store that was previously opened.
	void close() override {
		std::cout << "[Closing persistence store.]" << std::endl;
		open_ = false;
	}

	// Clears persistence, so that it no longer contains any persisted data.
	void clear() override {
		std::cout << "[Clearing persistence store.]" << std::endl;
		store_.clear();
	}

	// Returns whether or not data is persisted using the specified key.
	bool contains_key(const std::string &key) override {
		return store_.find(key) != store_.end();
	}

	// Returns the keys in this persistent data store.
	const mqtt::string_collection& keys() const override {
		static mqtt::string_collection ks;
		ks.clear();
		for (const auto& k : store_)
			ks.push_back(k.first);
		return ks;
	}

	// Puts the specified data into the persistent store.
	void put(const std::string& key, const std::vector<mqtt::string_view>& bufs) override {
		std::cout << "[Persisting data with key '"
			<< key << "']" << std::endl;
		std::string str;
		for (const auto& b : bufs)
			str += b.str();
		store_[key] = std::move(str);
	}

	// Gets the specified data out of the persistent store.
	mqtt::string_view get(const std::string& key) const override {
		std::cout << "[Searching persistence for key '"
			<< key << "']" << std::endl;
		auto p = store_.find(key);
		if (p == store_.end())
			throw mqtt::persistence_exception();
		std::cout << "[Found persistence data for key '"
			<< key << "']" << std::endl;

		return mqtt::string_view(p->second);
	}

	// Remove the data for the specified key.
	void remove(const std::string &key) override {
		std::cout << "[Persistence removing key '" << key << "']" << std::endl;
		auto p = store_.find(key);
		if (p == store_.end())
			throw mqtt::persistence_exception();
		store_.erase(p);
		std::cout << "[Persistence key removed '" << key << "']" << std::endl;
	}
};

/////////////////////////////////////////////////////////////////////////////
// Class to receive callbacks

class user_callback : public virtual mqtt::callback
{
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		std::cout << "\n\t[Delivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << "]" << std::endl;
	}

public:
};





/////////////////////////////////////////////////////////////////////////////

/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */
class callback : public virtual mqtt::callback
{
	mqtt::client& cli_;

	void connected(const std::string& cause) override {
		std::cout << "\nConnected: " << cause << std::endl;
		//cli_.subscribe(TOPIC, QOS);
		std::cout << std::endl;
	}

	// Callback for when the connection is lost.
	// This will initiate the attempt to manually reconnect.
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost";
		if (!cause.empty())
			std::cout << ": " << cause << std::endl;
		std::cout << std::endl;
	}

	// Callback for when a message arrives.
	void message_arrived(mqtt::const_message_ptr msg) override { // msg -> get_topic()
		std::cout << msg->get_payload_str() << std::endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
	callback(mqtt::client& cli) : cli_(cli) {}
};

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

	/// create publishing connection
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(false);
	connOpts.set_automatic_reconnect(true);

	mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);

	callback cb(cli);
	cli.set_callback(cb);


	sample_mem_persistence persist;
	mqtt::client client(SERVER_ADDRESS, "I_an_alpha_now"); /// will add &persist later




	user_callback cb1;
	client.set_callback(cb1);

	mqtt::connect_options connOpts1;
	connOpts1.set_keep_alive_interval(20);
	connOpts1.set_clean_session(true);
	




	// Start the connection.

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		cli.connect(connOpts);
		cli.subscribe(TOPIC, QOS);
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << std::endl;
		return 1;
	}

	// Just block till user tells us to quit.



	// // Disconnect

	// try {
	// 	std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
	// 	cli.disconnect();
	// 	std::cout << "OK" << std::endl;
	// }
	// catch (const mqtt::exception& exc) {
	// 	std::cerr << exc.what() << std::endl;
	// 	return 1;
	// }




	try {
		std::cout << "\nConnecting..." << std::endl;
		client.connect(connOpts1);
		std::cout << "...OK" << std::endl;

		// First use a message pointer.

		cout << "Enter msg: " << endl;
		string msg;
		getline(cin, msg);
		
		std::cout << "\nSending message..." << std::endl;
		auto pubmsg = mqtt::make_message(TOPIC, msg);
		pubmsg->set_qos(QOS);
		client.publish(pubmsg);
		std::cout << "...OK" << std::endl;

		/*  other methods to publish message .....


		// Now try with itemized publish.
       
		std::cout << "\nSending next message..." << std::endl;
		client.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2)+1);
		std::cout << "...OK" << std::endl;

		// Now try with a listener, no token, and non-heap message

		std::cout << "\nSending final message..." << std::endl;
		client.publish(mqtt::message(TOPIC, PAYLOAD3, QOS, false));
		std::cout << "OK" << std::endl;



		*/



		// // Disconnect
		// std::cout << "\nDisconnecting..." << std::endl;
		// client.disconnect();
		// std::cout << "...OK" << std::endl;
	}
	catch (const mqtt::persistence_exception& exc) {
		std::cerr << "Persistence Error: " << exc.what() << " ["
			<< exc.get_reason_code() << "]" << std::endl;
		return 1;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}





	

 	return 0;
}

