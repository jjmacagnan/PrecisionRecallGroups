# Precision/Recall
# Algoritmo para Gerar Gráficos de Precision/ Recall

 - Marcela Xavier Ribeiro

# Entrada

  - Nome arquivo entrada (ver formato de arquivo de entrada, no próximo slide)
  - Número de colunas do arquivo (incluindo coluna de id e coluna de categoria).
  - String no formato [+i1,i2,...,ik] com índices dos atributos que serão usados em uma das linhas do gráfico de precision/recall. O índice do primeiro atributo do vetor de característica é 1.  Colocar sempre na ordem ik < iL para L>k.


# Arquivo de Entrada
  - Cada item deve estar separado por espaço;
  - Cada transação deve estar em uma linha diferente;
  - As linhas contem as transações ou objetos a serem analisados
  - O primeiro atributo é o identificador da imagem;
  - O segundo atributo é o identificador da categoria da imagem.
  - Os demais atributos são os dados dos vetores de características da imagem;

# Exemplo:
#    - 1 1 0.87 0.987 0.11
#   - 2 0 0.77 0.787 0.71

# Arquivo de Saída: out.plt

> - set title “Precision x Recall
> - set xlabel “Recall"
> - set ylabel “Precision"
> - plot '-' title 'attribs=natrib1’  with linespoints 1
> - ####################
> - #attribs=natrib1
> - 1 0.8
> - 2 0.2
> - 3 0.2
> - End
> - pause -1

# Arquivo - Saída

- Algoritmo eficiente:
    - Para cada pivô da base
        - Faça um ranking das imagens de acordo com a distancia em relação ao pivô
        - Faça TO variar de 1 até N (todos os objetos da base)
            - Calcule os valores de precisão e revocação para cada TO
        - Para cada intervalo de Recall encontre a média-aritmética do valor de precision e coloque nos pontos do gráfico

# Exemplo de uso cmd Windows
 - Edite o arquivo .bat
 - PrecisionRecall zernike.txt 125 [+2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,65,66,67,68,69,70,71,72,74,75,76,77,78,79,80,82,83,84,85,86,87,88,93,94,95,96,97,101,102,104,105,106,107,114,118,127,128,136,137,139,147,148,150,151,162,172,175,176,177,178,189,191,203,204,218,227,231,232,234,235,236,237]
pause -1

# Compilação do código fonte
- Use o DevC++ para abrir o projeto, arquivo PrecisionRecall.dev
- DevC++: https://sourceforge.net/projects/orwelldevcpp/



License
----

GPL-3.0 License















