# Exercício calcula métricas estatísticas em C

## Descrição do exercício 
Desenvolver código que cálcula métricas estatísticas sequencial e em seguida transforma-lo em paralelo utilizando diretivas de openmp.<br/>
Calculometricasestatisticas.pdf no repositório com descrição de entrada e saída esperada.

## Detalhes
Matriz é criada como apenas um vetor, para otimização de acesso à memória.

## Funções:
-Retorna menor valor da matriz<br/>
-Retorna maior valor da matriz<br/>
-Retorna mediana da matriz<br/>
-Retorna média da matriz<br/>
-Retorna variância da matriz<br/>
-Retorna desvio padrão da matriz<br/>

## sequencial_mestatisticas_test.c (studentsseq.c no pdf)
Cálcula todas as métricas com o exemplo do pdf do exercício como teste. (alocando a matriz exemplo estaticamente)<br/>
Para compilar:<br/>
gcc sequecial_mestatisticas_test.c -o sequecial_mestatisticas_test -lm

## parallel_mestatisticas_openmp.c (studentspar.c no pdf)
Transforma o arquivo sequencial_mestatisticas_otimizado.c em paralelo, utilizando as diretivas de openMP<br/>
Sendo necessário arquivo input.txt<br/>
Para compilar:<br/>
gcc sequecial_mestatisticas_otimizado.c -o sequecial_mestatisticas -lm<br/>
