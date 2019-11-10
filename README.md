# Exercício calcula métricas estatísticas em C

## Descrição do exercício 
matriz_dados_metricasestatisticas.pdf no repositório
com descrição de entrada e saída esperada.

## Detalhes
Matriz é criada como apenas um vetor, para otimização de acesso à memória.

## Funções:
-Retorna menor valor da matriz<br/>
-Retorna maior valor da matriz<br/>
-Retorna mediana da matriz<br/>
-Retorna média da matriz<br/>
-Retorna variância da matriz<br/>
-Retorna desvio padrão da matriz<br/>

## sequencial_mestatisticas_test.c
Cálcula todas as métricas com o exemplo do pdf do exercício como teste.
Para compilar:<br/>
gcc sequecial_mestatisticas_test.c -o sequecial_mestatisticas_test -lm

## sequencial_mestatisticas.c
Cálcula todas as métricas, sendo necessário arquivo input.txt<br/>
Para compilar:<br/>
gcc sequecial_mestatisticas.c -o sequecial_mestatisticas -lm<br/>

## sequencial_mestatisticas_otimizado.c (studentsseq.c descrito no pdf)
Cálcula todas as métricas,otimizando as funcões maior,menor e medianda, em uma função só.<br/>
Sendo necessário arquivo input.txt<br/>
Para compilar:<br/>
gcc sequecial_mestatisticas_otimizado.c -o sequecial_mestatisticas -lm<br/>

## parallel_mestatisticas_otimizado_openmp.c (studentspar.c no pdf)
Transforma o arquivo sequencial_mestatisticas_otimizado.c em paralelo, utilizando as diretivas de openMP<br/>
Sendo necessário arquivo input.txt<br/>
Para compilar:<br/>
gcc sequecial_mestatisticas_otimizado.c -o sequecial_mestatisticas -lm<br/>
