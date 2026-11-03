#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARQUIVO_NOTAS "notas.txt"

//protótipos das funções
void obter_timestamp(char *buffer, size_t tamanho);
void adicionar_nota(const char *texto);
void listar_notas();
void limpar_notas();
void buscar_notas(const char *termo);
void deletar_nota(int indice_deletar);

int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("Uso:\n");
        printf(" %s add\"Sua nota aqui\"\n", argv[0]);
        printf(" %s list\n", argv[0]);
        printf(" %s clear\n", argv[0]);
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            printf("Erro: Forneça o texto da nota entre aspas.\n");
            return 1;
        }
        adicionar_nota(argv[2]);
    }
    else if (strcmp(argv[1], "list") == 0) {
        listar_notas();
    }
    else if (strcmp(argv[1], "clear") == 0){
        limpar_notas();
    }
    else if (strcmp(argv[1], "search") == 0){
        if (argc < 3) {
            printf("Erro: informe o termo de busca.\n");
            return 1;
        }
        buscar_notas(argv[2]);
    }
    else if (strcmp(argv[1], "delete") == 0) {
        if (argc < 3) {
            printf("Erro: informe o número da nota a ser removida.\n");
            return 1;
        }
        int id = atoi(argv[2]);
        if (id <= 0) {
            printf("Erro: forneça um ID válido maior que zero.\n");
            return 1;
        }
        deletar_nota(id);
    }
    else {
        printf("Comando desconhecido: %s\n", argv[1]);
        return 1;
    }
    return 0;
}

void obter_timestamp(char *buffer, size_t tamanho){
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);

    strftime(buffer, tamanho, "%Y-%m-%d %H:%M:%S", tm_info);
}

void adicionar_nota(const char *texto) {
    FILE *arquivo = fopen(ARQUIVO_NOTAS, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de notas");
        return;
    }

    char timestamp[20];
    obter_timestamp(timestamp, sizeof(timestamp));

    fprintf(arquivo, "[%s] %s\n", timestamp, texto);
    fclose(arquivo);

    printf("Nota salva com sucesso.\n");
}

void listar_notas() {
    FILE *arquivo = fopen(ARQUIVO_NOTAS, "r");
    if (arquivo == NULL) {
        printf("Nenhuma nota ou arquivo existente.\n");
        return;
    }

    char linha[256];
    int contador = 1;
    printf("--- Minhas Notas ---\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%d. %s", contador++, linha);
    }
    printf("-----------------------\n");

    fclose(arquivo);
}

void limpar_notas() {
    FILE *arquivo = fopen(ARQUIVO_NOTAS, "w");
    if (arquivo == NULL) {
        perror("Erro ao limpar as notas.\n");
        return;
    }
    fclose(arquivo);
    printf("Todas as notas foram apagadas.\n");
}

void buscar_notas(const char *termo) {
    FILE *arquivo = fopen(ARQUIVO_NOTAS, "r");
    if (arquivo == NULL) {
        printf("Nenhuma nota encontrada.\n");
        return;
        
    }
    
    char linha[256];
    int contador = 1;
    int encontradas = 0;
    
    printf("--- Resultados para '%s' ---\n", termo);
    while (fgets(linha, sizeof(linha), arquivo) != NULL ) {
        if (strstr(linha, termo) != NULL) {
            printf("%d. %s", contador, linha);
            encontradas++;
        }
        contador++;
    }
    
    if (encontradas == 0) {
        printf("Nenhuma nota encontrada com o termo informado.\n");
    }
    printf("-------------------------\n");
    
    fclose(arquivo);
}

void deletar_nota(int indice_deletar) {
    FILE *arquivo = fopen(ARQUIVO_NOTAS, "r");
    if (arquivo == NULL) {
        printf("Nenhuma nota encontrada para deletar.\n");
        return;
    }
    
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo);
        return;
    }
    
    char linha[256];
    int contador = 1;
    int deletada = 0;
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (contador == indice_deletar) {
            deletada = 1;
        } else {
            fputs(linha, temp);
        }
        contador++;
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if(deletada) {
        remove(ARQUIVO_NOTAS);
        rename("temp.txt", ARQUIVO_NOTAS);
        printf("Nota #%d removida com sucesso.\n", indice_deletar);
    } else {
        remove("temp.txt");
        printf("Nota #%d não encontrada.\n", indice_deletar);
    }
}