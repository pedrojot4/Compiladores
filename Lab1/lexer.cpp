#include "lexer.h"
#include <iostream>
#include <sstream>
using std::cin;
using std::cout;
using std::stringstream;

// Construtor da classe Lexer: inicializa a tabela de palavras-chave
Lexer::Lexer()
{
    // Insere as palavras reservadas "true" e "false" na tabela de símbolos
    id_table["true"] = Id{ Tag::TRUE, "true" };
    id_table["false"] = Id{ Tag::FALSE, "false" };
}

// Método responsável por escanear e retornar o próximo token
Token Lexer::Scan()
{
    // Ignora espaços em branco, tabulações e novas linhas
    while (isspace(peek))
    {
        if (peek == '\n') line += 1; // Atualiza o número da linha
        peek = cin.get();             // Avança para o próximo caractere
    }

    // Verifica se o caractere atual é um dígito (número)
    if (isdigit(peek))
    {
        int valor = 0;
        do
        {
            valor = 10 * valor + (peek - '0');  // Constrói o valor numérico
            peek = cin.get();                   // Lê o próximo caractere
        } while (isdigit(peek));

        // Exibe o token reconhecido no formato <NUM, valor>
        cout << "<NUM," << valor << "> ";
        return Num{ valor };  // Retorna o token numérico
    }

    // Tratamento de operadores de divisão e comentários
    if (peek == '/')
    {
        peek = cin.get();  // Lê o próximo caractere

        // Comentário de linha (começando com "//")
        if (peek == '/')
        {
            while (peek != '\n') peek = cin.get();  // Ignora o restante da linha
            line += 1;  // Atualiza o número da linha
            return Scan();  // Continua escaneando após o comentário
        }

        // Comentário de bloco (começando com "/* ... */")
        if (peek == '*')
        {
            while (true)
            {
                peek = cin.get();
                if (peek == '\n') line += 1;  // Atualiza linha se necessário
                if (peek == '*' && cin.get() == '/') break;  // Fecha o comentário de bloco
            }
            peek = ' ';  // Prepara para a próxima iteração
            return Scan();  // Continua escaneando após o comentário
        }
    }

    // Reconhecimento de identificadores e palavras reservadas
    if (isalpha(peek))
    {
        stringstream ss;
        do
        {
            ss << peek;      // Concatena os caracteres em um stream
            peek = cin.get(); // Lê o próximo caractere
        } while (isalpha(peek));

        string lexema = ss.str();  // Constrói o lexema (palavra completa)
        auto it = id_table.find(lexema);

        // Se o lexema já está na tabela, retorna o token correspondente
        if (it != id_table.end())
        {
            cout << "<" << (it->second.tag == Tag::TRUE ? "TRUE" : "FALSE") 
                 << "," << it->second.name << "> ";
            return it->second;
        }

        // Caso seja um novo identificador, insere na tabela e retorna o token
        Id novo_id{ Tag::ID, lexema };
        id_table[lexema] = novo_id;
        cout << "<ID," << novo_id.name << "> ";
        return novo_id;
    }

    // Reconhecimento de caracteres isolados (símbolos e operadores)
    Token token{ peek };
    peek = ' ';  // Reseta o 'peek' para o próximo caractere
    cout << "<" << char(token.tag) << "> ";  // Exibe o token
    return token;  // Retorna o token isolado
}

// Método que inicia o processo de escaneamento
void Lexer::Start()
{
    // Continua escaneando enquanto não encontrar uma nova linha
    while (peek != '\n')
        Scan();
}
