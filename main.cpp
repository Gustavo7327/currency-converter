#include <iostream>
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
#include <sstream>
#include <algorithm>

using json = nlohmann::json;

// Callback para armazenar resposta da API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}


void showHelp() {
    std::cout << "Uso:\n"
              << "  ./cambio <MOEDA_ORIGEM> <MOEDA_DESTINO>  - Obter taxa de câmbio\n"
              << "  ./cambio -list                           - Listar todas as conversões disponíveis\n"
              << "  ./cambio -list -<MOEDA>                  - Listar conversões disponíveis para uma moeda específica (ex: -Real-Brasileiro)\n"
              << "  ./cambio -list <MOEDA_ORIGEM/MOEDA_DESTINO> - Verificar se uma conversão específica está disponível (ex: Real-Brasileiro/Dólar-Americano)\n"
              << "  ./cambio -help ou -h                     - Mostrar esta mensagem\n";
}


void listAvailableConversions(const std::string& filterCurrency = "", const std::string& targetCurrency = "") {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string url = "https://economia.awesomeapi.com.br/json/available";

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Erro ao buscar lista de moedas: " << curl_easy_strerror(res) << std::endl;
        } else {
            try {
                json jsonData = json::parse(readBuffer);

                if (!filterCurrency.empty() && !targetCurrency.empty()) {
                    std::string formattedOrig = filterCurrency;
                    std::string formattedDest = targetCurrency;
                    std::replace(formattedOrig.begin(), formattedOrig.end(), '-', ' ');
                    std::replace(formattedDest.begin(), formattedDest.end(), '-', ' ');

                    std::cout << "Verificando conversão de" << formattedOrig << " para " << formattedDest << "...\n";

                    bool found = false;
                    for (auto& [key, value] : jsonData.items()) {
                        if (value.get<std::string>().find(formattedOrig) != std::string::npos && value.get<std::string>().find(formattedDest) != std::string::npos) {
                            std::cout << "Conversão encontrada: " << key << " - " << value << "\n";
                            found = true;
                        }
                    }

                    if (!found) {
                        std::cout << "Nenhuma conversão direta encontrada entre as moedas informadas.\n";
                    }
                } else if (!filterCurrency.empty()) {
                    std::string formattedCurrency = filterCurrency;
                    std::replace(formattedCurrency.begin(), formattedCurrency.end(), '-', ' ');

                    std::cout << "Conversões disponíveis para " << formattedCurrency << ":\n";
                    bool found = false;
                    for (auto& [key, value] : jsonData.items()) {
                        if (value.get<std::string>().find(formattedCurrency) != std::string::npos) {
                            std::cout << key << " - " << value << "\n";
                            found = true;
                        }
                    }
                    if (!found) {
                        std::cout << "Nenhuma conversão encontrada para a moeda especificada.\n";
                    }
                } else {
                    std::cout << "Moedas disponíveis para conversão:\n";
                    for (auto& [key, value] : jsonData.items()) {
                        std::cout << key << " - " << value << "\n";
                    }
                }
            } catch (const json::exception& e) {
                std::cerr << "Erro ao interpretar JSON: " << e.what() << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    }
}


int main(int argc, char* argv[]) {
    if (argc == 2) {
        std::string arg = argv[1];

        if (arg == "-help" || arg == "-h") {
            showHelp();
        } else if (arg == "-list") {
            listAvailableConversions();
        } else {
            std::cerr << "Comando inválido! Use -help para ver as opções disponíveis.\n";
        }
    } else if (argc == 3) {
        std::string arg1 = argv[1];
        std::string arg2 = argv[2];

        if (arg1 == "-list") {
            if (arg2.find("/") != std::string::npos) {
                if (arg2[0] == '-') {
                    arg2 = arg2.substr(1); 
                }
                
                size_t pos = arg2.find("/");
                std::string moedaOrigem = arg2.substr(0, pos);
                std::string moedaDestino = arg2.substr(pos + 1);
                listAvailableConversions(moedaOrigem, moedaDestino);
            } else if (arg2[0] == '-') {
                listAvailableConversions(arg2.substr(1)); 
            } else {
                std::cerr << "Formato inválido! Use -list -<MOEDA> para listar opções ou <MOEDA_ORIGEM/MOEDA_DESTINO> para verificar conversão.\n";
            }
        }
        else {
            std::cerr << "Número de argumentos inválido! Use -help para ver as opções.\n";
        }
    } else {
        std::cerr << "Número de argumentos inválido! Use -help para ver as opções.\n";
    }

    return 0;
}
