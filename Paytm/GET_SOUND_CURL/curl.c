#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct string {
  char *ptr;
  size_t len;
};

// If the output is string
void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

//write function for string

// size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
// {
//   size_t new_len = s->len + size*nmemb;
//   s->ptr = realloc(s->ptr, new_len+1);
//   if (s->ptr == NULL) {
//     fprintf(stderr, "realloc() failed\n");
//     exit(EXIT_FAILURE);
//   }
//   memcpy(s->ptr+s->len, ptr, size*nmemb);
//   s->ptr[new_len] = '\0';
//   s->len = new_len;

//   return size*nmemb;
// }


//writing in the file
size_t writefunc(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
 return fwrite(ptr, size, nmemb, stream);
}




int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  struct curl_slist *list = NULL;
  //struct curl_slist *bodylist = NULL;
  if(curl) {
    struct string s;
    init_string(&s);

    FILE *outfile;
    outfile = fopen("unbind.wav", "wb");

    /* For testing with json Data

    // curl_easy_setopt(curl, CURLOPT_URL, "https://random-data-api.com/api/address/random_address");

    */

    list = curl_slist_append(list, "Auth-Token:token");

     /* For POST REQUEST

    //bodylist = curl_slist_append(bodylist, "name:paytm");
    
    */

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
  
    curl_easy_setopt(curl, CURLOPT_URL, "URI");
    
    
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
    res = curl_easy_perform(curl);

    printf("I am awesome.%s\n", s.ptr);
    printf("And the response code is %d  \n" , res);
    free(s.ptr);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
