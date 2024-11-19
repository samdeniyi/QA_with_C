#include <iostream>
#include <curl/curl.h>
#include "json.hpp"

const std::string HF_API_KEY = "tyerytretyreyteryter";
const std::string HF_MODEL_URL = "https://api-inference.huggingface.co/models/mistralai/Mistral-7B-Instruct-v0.3/v1/chat/completions";

// Callback function to handle data received from cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string askHuggingFace(const std::string& question) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + HF_API_KEY).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Construct the JSON payload
        nlohmann::json requestData = {
            {"model", "mistralai/Mistral-7B-Instruct-v0.3"},
            {"messages", {
                {{"role", "user"}, {"content", question}}
            }},
            {"max_tokens", 500},
            {"stream", false}
        };

        std::string requestDataStr = requestData.dump();

        curl_easy_setopt(curl, CURLOPT_URL, HF_MODEL_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestDataStr.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // Parse the JSON response
    auto jsonResponse = nlohmann::json::parse(readBuffer);
    if (!jsonResponse.empty() && jsonResponse.contains("choices") && jsonResponse["choices"].size() > 0) {
        return jsonResponse["choices"][0]["message"]["content"];
    } else {
        return "Sorry, I couldn't get an answer.";
    }
}

int main() {
    std::string question;
    std::cout << "Enter your question: ";
    std::getline(std::cin, question);

    std::string answer = askHuggingFace(question);
    std::cout << "Answer from Hugging Face: " << answer << std::endl;

    return 0;
}