#include <gtk/gtk.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "MQTTClient.h"

#define ADDRESS "tcp://broker.emqx.io:1883"
#define CLIENTID "I_am_the_alpha_12"
#define TOPIC "/dubesundaram99@gmail.com/sundaram" // publishing
#define TOPIC1 "/ravi123sehravat@gmail.com/narendra" // subscribing to this
//#define TOPIC1       "/dubesundaram99@gmail.com/sundaram"//subscribing to this

#define PAYLOAD "Hello World!"
#define QOS 1
#define TIMEOUT 10000 L

volatile MQTTClient_deliveryToken deliveredtoken;

int counter = 0;
GtkTextBuffer * buffer;
char * output = "";
char temp[9999];

void delivered(void * context, MQTTClient_deliveryToken dt) {
  printf("Message with token value %d delivery confirmed\n", dt);
  deliveredtoken = dt;
}

int msgarrvd(void * context, char * topicName, int topicLen, MQTTClient_message * message) {
  //printf("Message arrived\n");
  //printf("   subscribing to  topic: %s\n", topicName);
  char *x = (char*) (message -> payload);
  x = strcat(x, (char*)"\n");
  gtk_text_buffer_set_text(buffer, x, -1);
  //printf( "%s\n",(char*)message->payload);
  MQTTClient_freeMessage( & message);
  MQTTClient_free(topicName);
  return 1;
}

void greet(GtkWidget * widget, GtkWidget * view) {
  g_print("%s\n", (char * ) gtk_entry_get_text(GTK_ENTRY(view)));
  MQTTClient client1;
  MQTTClient_connectOptions conn_opts1 = MQTTClient_connectOptions_initializer;
  MQTTClient_message pubmsg = MQTTClient_message_initializer;
  MQTTClient_deliveryToken token;
  int rc1; 
  output = (char * ) gtk_entry_get_text(GTK_ENTRY(view));
  if ((rc1 = MQTTClient_create( & client1, ADDRESS, CLIENTID,
      MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS) {
      printf("Failed to create client, return code %d\n", rc1);
      exit(EXIT_FAILURE);
  }

  //conn_opts1.keepAliveInterval = 20;
  conn_opts1.keepAliveInterval = 100;
  conn_opts1.cleansession = 1;
  if ((rc1 = MQTTClient_connect(client1, & conn_opts1)) != MQTTCLIENT_SUCCESS) {
    printf("Failed to connect, return code %d\n", rc1);
    exit(EXIT_FAILURE);
  }

  output  = strcat(output, temp);
  pubmsg.payload = output;
  pubmsg.payloadlen = (int) strlen(output);
  pubmsg.qos = QOS;
  pubmsg.retained = 0;
  MQTTClient_publishMessage(client1, TOPIC, & pubmsg, & token);
  if ((rc1 = MQTTClient_publishMessage(client1, TOPIC, & pubmsg, & token)) != MQTTCLIENT_SUCCESS) {
    printf("Failed to publish message, return code %d\n", rc1);
    exit(EXIT_FAILURE);
  }
  //output = strcat(output, "\n");
  strcpy(temp, output);
  //temp = output;
}

void chats(GtkWidget * widget, GtkWidget * history, GtkWidget * view) {

  //char *mytext = (char*)gtk_entry_get_text (GTK_ENTRY(view));
  //gtk_text_buffer_set_text (buffer, output, -1);
  // not setting text here for now
  // logic for history will go here, not till now found
}

void connlost(void * context, char * cause) {
  printf("\nConnection lost\n");
  printf("     cause: %s\n", cause);
}

int main(int argc, char * argv[]) {

  //mqtt subscribe window

  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  int rc;

  if ((rc = MQTTClient_create( & client, ADDRESS, "i_am_true_alpha",
      MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS) {
    printf("Failed to create client, return code %d\n", rc);
    rc = EXIT_FAILURE;
    //goto exit;
  }

  if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) != MQTTCLIENT_SUCCESS) {
    printf("Failed to set callbacks, return code %d\n", rc);
    rc = EXIT_FAILURE;
    //goto destroy_exit;
  }

  //conn_opts.keepAliveInterval = 20;
  conn_opts.keepAliveInterval = 100;
  conn_opts.cleansession = 1;
  if ((rc = MQTTClient_connect(client, & conn_opts)) != MQTTCLIENT_SUCCESS) {
    printf("Failed to connect, return code %d\n", rc);
    rc = EXIT_FAILURE;
    // goto destroy_exit;
  }

  printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
    "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
  //if ((rc = MQTTClient_subscribe(client, TOPIC, QOS)) != MQTTCLIENT_SUCCESS)
  if ((rc = MQTTClient_subscribe(client, TOPIC, QOS)) != MQTTCLIENT_SUCCESS) // ******************changes made
  {
    printf("Failed to subscribe, return code %d\n", rc);
    rc = EXIT_FAILURE;
  }

  // gui window

  GtkWidget * window;
  GtkWidget * button;

  gtk_init( & argc, & argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Chat with MQTT");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

  GtkWidget * view;

  GtkTextIter start, end;
  PangoFontDescription * font_desc;
  GdkRGBA rgba;
  GtkTextTag * tag;
  GtkCssProvider * provider;
  GtkStyleContext * context;

  view = gtk_entry_new();
  GtkWidget * history = gtk_text_view_new(); // chat history
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(history));

  gtk_text_view_set_editable(GTK_TEXT_VIEW(history), FALSE);


  gtk_entry_set_text(GTK_ENTRY(view), "Start typing...");
  gtk_entry_set_width_chars(GTK_ENTRY(view), 50);
  //s = gtk_entry_get_text (GTK_ENTRY(view));
  printf("%s", gtk_entry_get_text(GTK_ENTRY(view)));
  gtk_container_set_border_width(GTK_CONTAINER(window), 50);

  button = gtk_button_new_with_label("Send");
  gtk_widget_set_tooltip_text(button, "Send message");

  gtk_widget_set_halign(history, GTK_ALIGN_START);
  gtk_widget_set_valign(history, GTK_ALIGN_START);

  gtk_widget_set_halign(button, GTK_ALIGN_END);
  gtk_widget_set_valign(button, GTK_ALIGN_END);

  gtk_widget_set_halign(view, GTK_ALIGN_START);
  gtk_widget_set_valign(view, GTK_ALIGN_END);

  gtk_text_view_set_right_margin(GTK_TEXT_VIEW(history), 5);
  gtk_text_view_set_top_margin(GTK_TEXT_VIEW(history), 5);
  gtk_text_view_set_left_margin(GTK_TEXT_VIEW(history), 5);
  gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(history), 5);
  //  gtk_text_view_set_height(GTK_TEXT_VIEW (history), 100);

  GtkWidget * vbox;
  GtkWidget * vbox1;
  vbox = gtk_box_new(0, 0);
  vbox1 = gtk_box_new(0, 300);
  gtk_box_pack_start(GTK_BOX(vbox), history, 0, 0, 0);
  gtk_box_pack_start(GTK_BOX(vbox), view, 0, 10, 0);
  gtk_box_pack_start(GTK_BOX(vbox), button, 0, 20, 0);
  //gtk_box_pack_start(GTK_BOX(vbox1), history,0,50,0);

  gtk_container_add(GTK_CONTAINER(window), vbox);
  //gtk_container_add (GTK_CONTAINER (view), button);
  g_signal_connect(G_OBJECT(window), "destroy",
    G_CALLBACK(gtk_main_quit), NULL);
  // gtk_box_pack_start (GTK_BOX (button), view, TRUE, TRUE, 0);

  g_signal_connect(G_OBJECT(button), "clicked",
    G_CALLBACK(greet), view);

  g_signal_connect(G_OBJECT(button), "clicked",
    G_CALLBACK(chats), history);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}