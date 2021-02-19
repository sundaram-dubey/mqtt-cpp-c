#include <cpr/cpr.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv) {

	
    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/users/maze-runnar"});
    printf("%d\n", r.status_code);

    printf("%s\n", r.text);
                             
}