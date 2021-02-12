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

	
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(false);
	connOpts.set_automatic_reconnect(true);


	//sample_mem_persistence persist;
	mqtt::client client(SERVER_ADDRESS, "I_an_alpha_now_again"); /// will add &persist later

	user_callback cb1;
	client.set_callback(cb1);

	mqtt::connect_options connOpts1;//sub
	connOpts1.set_keep_alive_interval(20);
	connOpts1.set_clean_session(true);

	try {
		std::cout << "\nConnecting..." << std::endl;
		client.connect(connOpts1);
		std::cout << "...OK" << std::endl;

		string msg;
		getline(cin, msg);
		while(msg != "quit") {
			auto pubmsg = mqtt::make_message(TOPIC, USERNAME + ": " + msg);
			pubmsg->set_qos(QOS);
			client.publish(pubmsg);
			getline(cin, msg);
		}
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}
 	return 0;
}

