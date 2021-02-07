#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"

#define ADDRESS     "tcp://broker.emqx.io:1883"
#define CLIENTID    "I_am_the_alpha"
#define TOPIC       "/dubesundaram99@gmail.com/sundaram" // publishing
//#define TOPIC1       "/ravi123sehravat@gmail.com/narendra"// subscribing to this
#define TOPIC1       "/dubesundaram99@gmail.com/sundaram"//subscribing to this

#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    //printf("Message arrived\n");
    //printf("   subscribing to  topic: %s\n", topicName);
    printf("                             kaju sent: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

int main(int argc, char* argv[])
{
    //subsribing vala
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    // publishing vala
    MQTTClient client1;
    MQTTClient_connectOptions conn_opts1 = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc1;

    // conn_opts.username = "dubesundaram99@gmail.com";
    // conn_opts.password = "5d263fb2";



    // subscribing vala***********************************************************************************************************
    /*if ((rc = MQTTClient_create(&client, ADDRESS, "i_am_ironman",
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)*/
    /*if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)*/
    if ((rc = MQTTClient_create(&client, ADDRESS, "i_am_true_alpha",
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to create client, return code %d\n", rc);
        rc = EXIT_FAILURE;
        //goto exit;
    }

    if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
        //goto destroy_exit;
    }

    //conn_opts.keepAliveInterval = 20;
    conn_opts.keepAliveInterval = 100;
    conn_opts.cleansession = 1;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        rc = EXIT_FAILURE;
       // goto destroy_exit;
    }

    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC1, CLIENTID, QOS);
    //if ((rc = MQTTClient_subscribe(client, TOPIC, QOS)) != MQTTCLIENT_SUCCESS)
    if ((rc = MQTTClient_subscribe(client, TOPIC1, QOS)) != MQTTCLIENT_SUCCESS) // ******************changes made
    {
        printf("Failed to subscribe, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }
    

    // subscribing vala***********************************************************************************************************


    // publishing vala***********************************************************************************************************

   

    if ((rc1 = MQTTClient_create(&client1, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to create client, return code %d\n", rc1);
         exit(EXIT_FAILURE);
    }

    //conn_opts1.keepAliveInterval = 20;
    conn_opts1.keepAliveInterval = 100;
    conn_opts1.cleansession = 1;
    if ((rc1 = MQTTClient_connect(client1, &conn_opts1)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc1);
        exit(EXIT_FAILURE);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = (int)strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    if ((rc = MQTTClient_publishMessage(client1, TOPIC, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to publish message, return code %d\n", rc);
         exit(EXIT_FAILURE);
    }
    */
    printf("type: \n");
    char str[100];
    fgets(str,100,stdin);
    pubmsg.payload = str;
    pubmsg.payloadlen = (int)strlen(str);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    //
    
    while(strcmp(str, "quit")!=0)
    {
        //printf("string is %c\t:" str[0]);
        pubmsg.payload = str;
        pubmsg.payloadlen = (int)strlen(str);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        MQTTClient_publishMessage(client1, TOPIC, &pubmsg, &token);
        //printf("type: \n");
        fgets(str,100,stdin);
        //printf("\n");
        if(strcmp(str, "quit")==0) break;
    }
    //
    if ((rc = MQTTClient_publishMessage(client1, TOPIC, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to publish message, return code %d\n", rc);
         exit(EXIT_FAILURE);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc1 = MQTTClient_waitForCompletion(client1, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);

    // if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
    //     printf("Failed to disconnect, return code %d\n", rc);
    // MQTTClient_destroy(&client);





    // if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
    // {
    //     printf("Failed to disconnect, return code %d\n", rc);
    //     rc = EXIT_FAILURE;
    // }

    return rc;

    // publishing vala***********************************************************************************************************
}


//        int ch;
//         do
//         {
//             ch = getchar();
//         } while (ch!='Q' && ch != 'q');