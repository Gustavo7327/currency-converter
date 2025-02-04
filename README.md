# Currency Converter

Este é um projeto de conversor de moedas que permite converter valores entre diferentes moedas utilizando taxas de câmbio atualizadas.

## Como Funciona

O conversor de moedas utiliza a API de taxas de câmbio para obter as taxas de câmbio mais recentes e realizar a conversão entre as moedas especificadas pelo usuário.

## Ferramentas Utilizadas

- API de cotações <a href="https://docs.awesomeapi.com.br/api-de-moedas">AwesomeAPI</a>
- Biblioteca nlohmann/json: Para manipulação de dados em formato JSON.
- Biblioteca cURL: Para realizar requisições HTTP à API de taxas de câmbio.

## Instalação

Antes de gerar o binário do projeto, é necessário instalar as bibliotecas `json` e `curl` utilizadas no projeto. Siga os passos abaixo para instalar as dependências e baixar o projeto na sua máquina:

### 1. Clone o repositório:
```sh
git clone https://github.com/Gustavo7327/currency-converter.git
cd currency-converter
```

### 2. Instale as bibliotecas necessárias:
- Para sistemas baseados em Debian/Ubuntu:
    ```sh
    sudo apt-get update
    sudo apt-get install nlohmann-json3-dev libcurl4-openssl-dev
    ```
- Para sistemas baseados em Red Hat/Fedora:
    ```sh
    sudo dnf install nlohmann-json3-devel libcurl-devel
    ```

## Compilação e Execução

### 1. Compile o projeto:
```sh
make
```

### 2. Execute o binário gerado:
```sh
./cambio [opções]
```

## Opções de Execução

- `./cambio -get <MOEDA_ORIGEM-MOEDA_DESTINO>`: Obter taxa de câmbio.
- `./cambio -list`: Listar todas as conversões disponíveis.
- `./cambio -list -<MOEDA>`: Listar conversões disponíveis para uma moeda específica (ex: -Real-Brasileiro).
- `./cambio -list <MOEDA_ORIGEM/MOEDA_DESTINO>`: Verificar se uma conversão específica está disponível (ex: Real-Brasileiro/Dólar-Americano).
- `./cambio -help` ou `-h`: Mostrar a mensagem de ajuda.