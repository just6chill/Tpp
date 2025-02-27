#include "../../MessageMethods.h"
#include "../../QueryGen/QueryGen.h"
#include <curl/curl.h>

int Message::SendFile(std::string Token, std::string FilePath) {

    //setup the curl stuff
    CURL *Curl;
    CURLcode Result;
    curl_global_init(CURL_GLOBAL_ALL);
    Curl = curl_easy_init();

    //Generate the URl Query, convert The text to Encoded text
    std::string Header;
    std::string QueryURL = QueryGen(Token, "sendPhoto");

    //create the full header
    Header.append("chat_id=");
    Header.append(std::to_string(this->Data.ChatID));
    Header.append("&photo=");
    Header.append(FilePath);

    // convert the C++ strings to char
    char *URL = &QueryURL[0];
    char *CharHeader = &Header[0];

    //dew it
    if (Curl) {
        curl_easy_setopt(Curl, CURLOPT_URL, URL);
        curl_easy_setopt(Curl, CURLOPT_POSTFIELDS, CharHeader);
        Result = curl_easy_perform(Curl);
    }
    curl_easy_cleanup(Curl);

    return 0;
}