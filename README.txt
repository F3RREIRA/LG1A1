Projeto: Roda a Roda.
Autor: Rivaildo Ferreira

IFSP - Instituto Federal de Educação, Ciências e Tecnologia de São Paulo.
Campus São Paulo.
Tecnólogo em Análise e Desenvolvimento de Sistemas.

O projeto é o trabalho final da disciplina de Lógica de Programação, que deverá ser entregue como forma de avaliação semestral.
Trata-se de uma simulação do jogo Roda a Roda, que passa na TV.

Assim que o jogo começa, o programa sorteia uma palavra e mostra a pista na tela.
Na tela, além da pista, deverá aparecer também a identificação de cada jogador, ao todo são três jogadores e quanto, em reais, cada um ganhou até o momento.
O programa também, mostrará os espaços referentes a palavra sorteada.
A primeira rodada do jogo sempre é iniciada pelo jogador 1.
O programa irá solicitar ao jogador que "rode a roda!". 
Neste momento, o programa irá sortear um dos prêmios (valor em reais).
O valor do prêmio será apresentado e o programa irá pedir para o jogador digitar uma letra.
Quando for digitada uma letra, o programa deverá verificar se a letra faz parte de
alguma palavra a ser verificada. Caso a letra faça parte da(s) palavra(s), o programa
deverá mostrar a letra na respectiva posição da palavra e, para cada ocorrência da
letra, o prêmio do jogador deve ser atualizado.

Caso a letra não faça parte da palavra, o jogador não ganha prêmio algum neste
momento e passa a vez para o próximo jogador.
Caso seja sorteado "PASSA A VEZ", o jogador não perde o que tem até o momento,
mas não poderá jogar agora. Assim, a vez será do próximo jogador que deverá "rodar a
roda!" e proceder conforme já descrito anteriormente.

Quando faltarem 3 letras, ou menos, para completar a(s) palavra(s) o jogador da
vez deverá obrigatoriamente responder qual é(são) a(s) palavra(s). Assim, o programa
deverá fazer e exibir uma contagem regressiva de 5 segundos para depois solicitar a
digitação da(s) palavra(s). Neste caso, a resposta certa valerá o total acumulado até
o momento pelo jogador adicionado do prêmio sorteado nesta rodada.
Caso o jogador acerte a(s) palavra(s) o programa deverá mostrá-la(s) na tela e
totalizar a premiação dos jogadores até o momento, identificando, inclusive o
vencedor.

Caso o jogador errar na rodada em que faltarem 3 letras, ou menos, para completar
a(s) palavra(s), a vez deverá ser passada para o próximo jogador. Tal procedimento 
deverá acontecer até que os 3 jogadores tenham tido uma oportunidade de responder
qual(is) é(são) a(s) palavra(s).

Caso NENHUM dos três jogadores acerte na rodada em que faltarem 3 letras, ou
menos, para completar a(s) palavra(s), não será declarado vencedor algum e cada
participante termina o jogo com os respectivos valores obtidos até o momento.

Endereço: https://github.com/F3RREIRA/PFDA1.git
