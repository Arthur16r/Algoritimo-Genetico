Algoritmo Genético para Regressão Linear
Este projeto foi desenvolvido como parte de um trabalho da faculdade. O objetivo é usar um algoritmo genético para encontrar os coeficientes a e b de uma reta (do tipo y = a*x + b) que melhor se ajusta a um conjunto de pontos de referência. Em outras palavras, o algoritmo tenta aprender uma função linear a partir de exemplos.

Como o algoritmo funciona
O problema é tratado como uma evolução de indivíduos. Cada indivíduo representa uma possível solução, ou seja, um par de coeficientes a e b. A qualidade de um indivíduo é medida pelo erro quadrático médio entre os valores previstos pela reta e os valores reais dos pontos de referência. Quanto menor o erro, melhor o indivíduo.

O processo evolutivo segue os passos clássicos de um algoritmo genético:

Avaliação da população: calcula o erro de cada indivíduo.

Seleção: os melhores indivíduos têm mais chance de gerar descendentes.

Cruzamento (crossover): dois indivíduos trocam partes de seus coeficientes para formar novos indivíduos.

Mutação: pequenas alterações aleatórias são aplicadas em alguns indivíduos para manter a diversidade da população.

Elitismo: os dois melhores indivíduos de cada geração são preservados automaticamente para a próxima geração.

O algoritmo executa esse ciclo por um número definido de gerações. A cada geração, os dois melhores indivíduos são salvos em um arquivo de saída.

Estrutura do projeto
Os arquivos estão organizados da seguinte forma:

main.cpp: contém a função principal que controla a execução do algoritmo. Ele lê os parâmetros iniciais, gera os pontos de referência e executa o loop de gerações.

Funcoes.h: declara todas as estruturas de dados e funções usadas no projeto. Funciona como um índice do que está disponível.

Funcoes.cpp: implementa as funções declaradas no cabeçalho. Aqui está a lógica real do algoritmo genético, incluindo avaliação, seleção, cruzamento e mutação.

Como usar
Compile os arquivos. Se estiver usando g++, o comando seria algo como:

g++ main.cpp Funcoes.cpp -o algoritmo_genetico

Prepare o arquivo de entrada input.data dentro de uma pasta chamada src. O formato esperado é o seguinte:

A primeira linha deve conter três valores: a quantidade de indivíduos da população, o número de gerações e a probabilidade de mutação.
As linhas seguintes devem conter os coeficientes a e b dos indivíduos da população inicial, um por linha.

Um exemplo de arquivo input.data:

10 50 0.1
2.5 1.0
3.0 1.2
1.8 2.0
2.2 0.5
3.5 0.8
1.5 1.5
2.8 1.1
3.2 1.3
2.0 0.9
2.7 1.4

Neste exemplo, a população terá 10 indivíduos, o algoritmo rodará por 50 gerações e a chance de mutação é de 10 por cento. As dez linhas seguintes definem os valores iniciais de a e b para cada indivíduo.

Execute o programa. Durante a execução, nenhuma mensagem será mostrada no terminal, mas ao final ele exibirá os dois melhores indivíduos encontrados e a população final ordenada.

O programa gera um arquivo output.data contendo, para cada geração, os dois melhores indivíduos e seus respectivos erros.

Observações sobre o código
Os pontos de referência que a reta deve aproximar são gerados aleatoriamente dentro do intervalo de 0 a 14 tanto para x quanto para y. O código usa uma semente fixa (valor 1) para garantir que os resultados sejam reproduzíveis. Se quiser variar os pontos, basta alterar a semente na chamada da função GerarPontos dentro do main.

O cruzamento entre dois indivíduos é feito de forma simples: um descendente herda o coeficiente a de um dos pais e o coeficiente b do outro. A escolha de qual pai doa qual coeficiente é aleatória. A mutação adiciona um valor entre -1 e 1 ao coeficiente a ou b, escolhido aleatoriamente.

O algoritmo implementa uma proteção para evitar que o cruzamento gere filhos idênticos aos pais. Se isso acontecer repetidas vezes, ele cria um indivíduo totalmente aleatório para manter a diversidade.

A função de elitismo garante que os dois melhores indivíduos nunca sejam perdidos. Os demais indivíduos da população anterior (os piores) são descartados para dar lugar aos novos descendentes.

Possíveis limitações
O código funciona bem para demonstrar o conceito de algoritmo genético, mas algumas escolhas podem ser melhoradas. A geração dos pontos de referência é fixa e os limites dos coeficientes não são restringidos, o que pode fazer com que valores muito altos ou muito baixos apareçam. Além disso, a taxa de mutação é aplicada sobre a população inteira de forma simples, sem um mecanismo mais refinado como mutação adaptativa.

Para um trabalho de faculdade, esses pontos não chegam a ser problemas, pois o foco é entender o funcionamento do algoritmo genético e não necessariamente otimizar ao máximo a regressão. Para isso existem métodos tradicionais como mínimos quadrados.

Considerações finais
Este código foi escrito com foco na clareza. Cada função tem uma responsabilidade bem definida e os nomes escolhidos ajudam a entender o que está acontecendo. Se você estiver estudando algoritmos genéticos, este projeto pode servir como um bom ponto de partida para entender conceitos como representação de soluções, função de aptidão, seleção, cruzamento e mutação.

Se precisar adaptar o código para outros problemas, a parte mais trabalhosa será modificar a estrutura do indivíduo e a função que calcula o erro. O resto da estrutura do algoritmo genético pode ser reaproveitada.

