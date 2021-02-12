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
const std::string CLIENT_ID("I_am_the_alpha_true");
const std::string TOPIC("/dubesundaram99@gmail.com/sundaram");//subscribe
const std::string TOPIC1("/dubesundaram99@gmail.com/sundaram");//publish

//const std::string TOPIC1("/ravi123sehravat@gmail.com/narendra");//publish

const std::string USERNAME { "Sundaram" };

const int QOS = 1;



class user_callback : public virtual mqtt::callback // pub
{
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		//std::cout << "\n\t[Delivery complete for token: "
			//<< (tok ? tok->get_message_id() : -1) << "]" << std::endl;
	}

public:
};


class callback : public virtual mqtt::callback //sub
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
		std::cout <<msg->get_payload_str() << std::endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
	callback(mqtt::client& cli) : cli_(cli) {}
};


int main(int argc, char* argv[])
{

	/// create publishing connection
	mqtt::connect_options connOpts;// publishing
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(false);
	connOpts.set_automatic_reconnect(true);

	mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);

	callback cb(cli);
	cli.set_callback(cb);

	mqtt::client cli1(SERVER_ADDRESS, "see_ya_in_another_life_brother");

	callback cb1(cli1);
	cli1.set_callback(cb1);

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		cli.connect(connOpts);
		cli1.connect(connOpts);
		cli.subscribe(TOPIC, QOS);
		cli1.subscribe(TOPIC1, QOS);
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< SERVER_ADDRESS << "'" << std::endl;
		return 1;
	}

	string msg;
	getline(cin, msg);
	while(msg != "quit") {}

 	return 0;
}

