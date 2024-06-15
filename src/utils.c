#include <stdbool.h>
#include <unistd.h>
#include <curl/curl.h>

#include "utils.h"

bool fileExists(char *path) {
    return (access(path, F_OK) == 0);
}

void downloadImage(char *url, char *path) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(path, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}