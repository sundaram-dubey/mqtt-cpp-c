#include <cpr/cpr.h>
#include<iostream>
#include<bits/stdc++.h>
#include <json/json.h>

using namespace std;
int main(int argc, char** argv) {

	string username = "maze-runnar";
	cout << "Enter github username: ";
	cin >> username ;
	cout << "\n";

    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/users/" + username});
    cout << r.status_code << endl;                  // 200
    cout << r.header["content-type"]<< endl;       // application/json; charset=utf-8
    if(r.status_code == 200) {
    cout << typeid(r.text).name() << endl;  // JSON text string
	cout << r.text << endl; 
	string x = r.text;
	Json::Value root;   
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( x.c_str(), root );
	if(parsingSuccessful)
    std::cout << "USERNAME: " << root.get("login", "A Default Value if not exists" ).asString() << std::endl;
    std::cout << "NAME: " << root.get("name", "Not found" ).asString() << std::endl;
	std::cout << "NAME: " << root.get("bio", "Not found" ).asString() << std::endl;
      

	} else{
		cout << "Something went wrong. username not found!" << endl;
	}

	string repos="yes";
	cout << "type 'y' to get repositories of user. Or type \"NO\" to quit";
	cin >> repos;
	if(repos != "NO" && repos != "no") {
		cpr::Response repo = cpr::Get(cpr::Url{"https://api.github.com/users/" + username + "/repos"});
	    cout << repo.status_code << endl;                  // 200
	    cout << repo.header["content-type"]<< endl;       // application/json; charset=utf-8
	    if(repo.status_code == 200) {
	    cout << repo.text << endl;  // JSON text string
		} else{
			cout << "Something went wrong. repositories not found for this user.!" << endl;
		}
	}
                             
}