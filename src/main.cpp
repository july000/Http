#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>

int main() {
    std::string ip = "127.0.0.1";
    std::string modify_url = "http://" + ip + ":8010";

    // Change data of instance abc2 messageid 1201
    std::vector<std::string> data = {
        "255",
        "255",
        "255",
        "255",
        "255",
        "255",
        "255",
        "255",
        "255"
    };
    std::string json_data = "[";
    for (const std::string& value : data) {
        json_data += "\"" + value + "\",";
    }
    json_data.pop_back();  // Remove the trailing comma
    json_data += "]";
    
    // Making the PUT request
    CURL* curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, modify_url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode result = curl_easy_perform(curl);
        if (result == CURLE_OK) {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cout << "Response code: " << response_code << std::endl;
        } else {
            std::cerr << "Error occurred during request: " << curl_easy_strerror(result) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}