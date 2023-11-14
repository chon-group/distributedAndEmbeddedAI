!config.

+!config <-
	.port(ttyACM0).

+!phaser(X): X == priscilla <-
	.print("A equipe priscilla ativou seu phaser!");
	.act(lamp01On).

+!phaser(X): X == samu <-
	.print("A equipe samu ativou seu phaser!");
	.act(lamp02On).

+!phaser(X): X == kombione <-
	.print("A equipe kombione ativou seu phaser!");
	.act(lamp03On).

+!phaser(X): X == kitt <-
	.print("A equipe kitt ativou seu phaser!");
	.act(lamp04On).

+!phaser(X): X == robocop <-
	.print("A equipe robocop ativou seu phaser!");
	.act(lamp05On).

-!phaser(X)[source(Y)] <- 
	.print("Recebi uma mensagem desconhecida de ", Y).
