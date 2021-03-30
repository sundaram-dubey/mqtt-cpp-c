#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#include <stdio.h>

#define mbedtls_printf       printf
#define mbedtls_exit         exit
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#if defined(MBEDTLS_MD5_C)
#include "mbedtls/md5.h"
#include "mbedtls/sha512.h"
#include "mbedtls/sha256.h"

#endif




int counter =0;
GtkTextBuffer *buffer;	
char *output = "";
unsigned char output1[16];
unsigned char digest[16];
gchar *result;
void greet( GtkWidget *widget, GtkWidget *view )
{
   g_print("%s\n",  (char*)gtk_entry_get_text (GTK_ENTRY(view))); 
   int i, ret;
   char * message = (char*)gtk_entry_get_text (GTK_ENTRY(view));
    unsigned char digest[16];
    unsigned char hash[32];
   
   // str[strcspn(str, "\n")] = 0; // ignoring new line while reading input using fgets

    mbedtls_printf( "MD5(\"%s\") = ", message );

   //md5 encryption using tls

    if( ( ret = mbedtls_md5_ret( (unsigned char *) message, 1000, digest ) ) != 0 )
        mbedtls_exit( MBEDTLS_EXIT_FAILURE );

    for( i = 0; i < 16; i++ ){
        mbedtls_printf( "%02x", digest[i] );
    }
    result = g_locale_to_utf8(digest, -1, NULL, NULL, NULL);

    gtk_entry_set_text (GTK_ENTRY(view), digest);

    output = (char*) digest;
    //output1 = digest;
    mbedtls_printf( "\n" );

}

// void chats ( GtkWidget *widget, GtkWidget *history, GtkWidget *view) {
//   gtk_text_buffer_set_text (buffer, result, -1);
// }

int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *button;    

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Chat with MQTT");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);


GtkWidget *view;

GtkTextIter start, end;
PangoFontDescription *font_desc;
GdkRGBA rgba;
GtkTextTag *tag;
GtkCssProvider *provider;
GtkStyleContext *context;

  view = gtk_entry_new ();
  GtkWidget *history = gtk_text_view_new (); // chat history
  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (history));

  




  gtk_entry_set_text (GTK_ENTRY(view), "Start typing...");
  gtk_entry_set_width_chars (GTK_ENTRY(view), 50);
  //s = gtk_entry_get_text (GTK_ENTRY(view));
  printf("%s", gtk_entry_get_text (GTK_ENTRY(view)));
  gtk_container_set_border_width(GTK_CONTAINER(window), 50);

  button = gtk_button_new_with_label("MD5");
  gtk_widget_set_tooltip_text(button, "Hash");

  gtk_widget_set_halign (history, GTK_ALIGN_START);
  gtk_widget_set_valign (history, GTK_ALIGN_START);


  gtk_widget_set_halign (button, GTK_ALIGN_END);
  gtk_widget_set_valign (button, GTK_ALIGN_END);


  gtk_widget_set_halign (view, GTK_ALIGN_START);
  gtk_widget_set_valign (view, GTK_ALIGN_END);


  

  gtk_text_view_set_right_margin(GTK_TEXT_VIEW (history), 5);
	gtk_text_view_set_top_margin(GTK_TEXT_VIEW (history), 5);
  gtk_text_view_set_left_margin(GTK_TEXT_VIEW (history), 5);
  gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW (history), 5);
//	gtk_text_view_set_height(GTK_TEXT_VIEW (history), 100);
    

  GtkWidget *vbox;
  GtkWidget *vbox1;
  vbox = gtk_box_new(0,0);
  vbox1 = gtk_box_new(0, 300);
  //gtk_box_pack_start(GTK_BOX(vbox), history,0,0,0);
  gtk_box_pack_start(GTK_BOX(vbox), view, 0,10,0);
  gtk_box_pack_start(GTK_BOX(vbox), button,0,20,0);
  //gtk_box_pack_start(GTK_BOX(vbox1), history,0,50,0);
  

  gtk_container_add (GTK_CONTAINER (window), vbox);
  //gtk_container_add (GTK_CONTAINER (view), button);
  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);
     // gtk_box_pack_start (GTK_BOX (button), view, TRUE, TRUE, 0);

  g_signal_connect (G_OBJECT(button), "clicked",
   G_CALLBACK (greet), view);

  // g_signal_connect (G_OBJECT(button), "clicked",
  //  G_CALLBACK (chats), history);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}