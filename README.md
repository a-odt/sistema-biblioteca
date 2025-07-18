
# Sistema de Cadastro de Usuários da Biblioteca

Projeto em C para gerenciamento de usuários de uma biblioteca. Ele permite cadastrar, buscar, listar, navegar, remover e salvar os dados dos usuários, utilizando listas duplamente encadeadas.

## Funcionalidades

- Cadastro de novos usuários com validação de:
  - Nome
  - Telefone (mín. 8 dígitos numéricos)
  - Data de nascimento (formato DD/MM/AAAA)
  - Email (formato válido com `@` e `.`)
- Busca de usuários por nome (parcial e sem distinção entre maiúsculas/minúsculas)
- Listagem de todos os usuários cadastrados
- Navegação entre usuários cadastrados (anterior e próximo)
- Remoção de usuários pelo nome exato
- Salvamento automático ou manual dos dados em arquivo `.txt`
- Interface visual simples com arte ASCII

## Tecnologias Utilizadas

- Linguagem C
- Lista duplamente encadeada
- Manipulação de arquivos (`.txt`)
- Validações de entrada
- Cross-platform (funciona em Windows e Linux)

## Como Executar

### Pré-requisitos

- Compilador C (como `gcc`)
- Terminal (CMD, Bash, etc.)

### Compilação

```bash
gcc main.c -o biblioteca
```

### Execução

```bash
./biblioteca
```

> No Windows, use `biblioteca.exe`

## Arquivo de Dados

Os dados dos usuários são salvos automaticamente (ou sob confirmação) no arquivo:

```
usuarios_biblioteca.txt
```

Formato de salvamento:  
```
Nome;Telefone;Email;Nascimento
```

## Autoria

Sistema desenvolvido por:

- Rafaela Garrão
- Davi Lira
- Julia Torres
- Maria Isabele Almeida

Versão: **1.0**

## Licença

Este projeto é apenas para fins educacionais e não possui uma licença específica. Fique à vontade para utilizar como base em seus estudos. 
