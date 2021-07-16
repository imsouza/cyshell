# cyshell

Uma aplicação que simula o shell do Python, em C, para avaliação de expressões numéricas desenvolvida para a disciplina de Estruturas de Dados da UFES 

## Execução

#### Modo interativo
```$ make && make run```

#### Modo interativo com exibição da expressão pós-fixa
```$ make && make run args=-e```

#### Calcular expressões de um arquivo
```$ make && make run args="-s ../test/expressoes.txt"```

#### Calcular expressões de um arquivo e exibir a pós-fixa
```$ make && make run args="-e -s ../test/expressoes.txt"```

#### Checar memory leaks

```$ make && make memcheck```

#### Limpar arquivos .o
 
```$ make clean```

## OS Suporte

Linux

## Autor

Mateus Almeida

## Licença

This project is licensed under the [MIT](https://github.com/imsouza/cyshell/blob/main/LICENSE) License.