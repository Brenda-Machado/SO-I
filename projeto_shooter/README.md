# Descrição do projeto

O projeto deve implementar o Space Shooter utilizando a biblioteca de Threads no espaço de usuário desenvolvida durante o semestre. O link abaixo demonstra as funcionalidades do jogo:

https://www.youtube.com/watch?v=tDHvE9Aj8VI

Para este trabalho, deve-se considerar um subconjunto das funcionalidades do jogo original, conforme as seguintes definições:

- A espaçonave do usuário deve ser uma Thread;
- A criação das espaçonaves inimigas roxas em formato de “<”, que só se movimentam para
frente, deve ser tratada em outra Thread;
- O desenho da tela deve ser feito por uma classe Window que será uma Thread
(possivelmente de maior prioridade). A classe Window atualizará a tela usando o Timer da
biblioteca gráfica a cada FPS ou quando uma tecla for apertada (tratamento de eventos da
biblioteca);
- O tratamento da entrada do teclado deve ser realizado por outra Thread;
- Geração das minas deve ser feita por uma Thread a cada 30 segundos (note que elas
explodem e jogam tiros para todos os lados se não forem atingidas em 5 segundos);
- Criação da Thread do “Boss” após 1 minuto de jogo;
- Controle de colisões e das 3 vidas atráves de uma Thread;
- Os alunos têm a liberdade para criar outras Threads como acharem necessário.
- As teclas de entrada são as seguintes:
	+ Teclas para cima, para baixo, lado esquerdo e lado direto para controlar a espaçonave do usuário.
	+ Tecla de espaço para disparar um tiro comum (que some ao matar o primeiro inimigo) e ‘1’ para disparar o míssel (que mata todos que colidir até o final da tela).
	- ESC para sair do jogo.
- Bônus de 1 ponto: tratamento de algum outro tipo de espaçonave (branca, laranja ou amarela) em outra Thread.

A biblioteca gráfica utilizada será a Allegro (https://liballeg.org/). Documentação em:

https://github.com/liballeg/allegro_wiki/wiki/

Cada grupo terá a liberdade para desenvolver o software seguindo o paradigma de orientação a objetos do C++ obrigatoriamente. Isso signifca que o uso de programação estruturada e elementos da linguagem C terão descontos na nota (veja avaliação abaixo). O Timer da biblioteca é abstraído na classe Timer (Timer.cc e Timer.h).

