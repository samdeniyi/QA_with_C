
# Hugging Face Question-Answering System in C++

This project demonstrates how to integrate with the Hugging Face API to build a Question-Answering System using C++.

## Features

- Sends user questions to Hugging Face's API and retrieves responses.
- Implements `cURL` for HTTP requests.
- Utilizes `nlohmann/json.hpp` library for JSON processing.

## Requirements

1. **cURL**: Used for making HTTP requests.
2. **nlohmann/json.hpp**: An external library for JSON parsing. Download from [nlohmann/json](https://github.com/nlohmann/json).
3. **Hugging Face API Key**: You need an API key to authenticate with the Hugging Face API.

## Installation

### Dependencies

1. Install `cURL` on your system:
   ```bash
   sudo apt-get install libcurl4-openssl-dev
   ```

2. Download the `nlohmann/json.hpp` header file:
   - Clone the repository: 
     ```bash
     git clone https://github.com/nlohmann/json.git
     ```
   - Add the `json.hpp` file to your project.

### Compilation

Compile the code using `g++`:
```bash
g++ -std=c++14 -o qa_system main.cpp -lcurl
```

## Usage

1. Run the compiled program:
   ```bash
   ./qa_system
   ```

2. Enter your question when prompted.

3. The program will send your question to the Hugging Face API and display the answer.

## Configuration

### API Key

Replace the `HF_API_KEY` in the code with your Hugging Face API key:
```cpp
const std::string HF_API_KEY = "your_hugging_face_api_key";
```

### Model URL

Ensure the `HF_MODEL_URL` is correctly set to the Hugging Face model endpoint you wish to use:
```cpp
const std::string HF_MODEL_URL = "https://api-inference.huggingface.co/models/mistralai/Mistral-7B-Instruct-v0.3/v1/chat/completions";
```

## Example

```bash
Enter your question: What is the capital of France?
Answer from Hugging Face: The capital of France is Paris.
```

## Notes

- Ensure your API key is valid and has sufficient permissions for the model endpoint.
- Handle sensitive information like API keys securely.
- Modify the JSON payload as per your specific use case.

## License

This project is open-source and can be modified for personal or educational purposes.
