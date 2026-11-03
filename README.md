# Memo CLI - Gerenciador de Notas em C

Um utilitário de linha de comando (CLI) simples e leve desenvolvido em C para gerenciamento rápido de notas textuais com *timestamp* automático.

Conceitos Estudados
- Manipulação de arquivos (`fopen`, `fgets`, `fputs`, `remove`, `rename`)
- Argumentos de linha de comando (`argc`, `argv`)
- Manipulação de strings e buscas (`strstr`, `strcmp`)
- Manipulação de datas e horários (`time.h`, `strftime`)

Como Compilar

Certifique-se de ter o GCC instalado no seu ambiente.

gcc src/memo.c -o memo


Como Usar

# Adicionar uma nota
./memo add "Estudar estruturas de dados"

# Listar todas as notas com ID
./memo list

# Buscar notas por palavra-chave
./memo search "Estudar"

# Apagar uma nota pelo ID
./memo delete 1

# Limpar todo o histórico
./memo clear
