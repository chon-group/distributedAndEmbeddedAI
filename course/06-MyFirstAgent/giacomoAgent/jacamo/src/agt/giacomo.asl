/* Initial beliefs */
estoque(0).
energia(10).
recompensa(3).  
jornada(1).  
noitada(3).   
refeicao(2).  

/* Initial goals */
!curtir.

/* Plans */
+!curtir: energia(E) & noitada(N) & jornada(T) & (E>(N+T)) <-
	.print("Curtindo........ [Energia=",E-N,"]");
	.wait(2000);
	-+energia(E-N);
	!curtir.

+!curtir: energia(E) & noitada(N) & jornada(T) & (E<=(N+T)) <- 
	.print("Cansado......... ");
	!comer.

+!comer: energia(E) & (E<2*(N+T)) & noitada(N) & estoque(C) & C>0 & refeicao(V)  <-
	.print("Comendo......... [Estoque=",C-1,"] [Energia=",E+V,"]");
	-+estoque(C-1);
	-+energia(E+V);
	.wait(1000);
	!comer.
	
+!comer: energia(E) & noitada(N) & jornada(T) & (E>=2*(N+T)) <-
	.print("Satisfeito...... ");
	!curtir.

+!comer: estoque(C)<-
	.print("Acabou a comida! [Estoque=",C,"]");
	.wait(2000);
	!trabalhar.


+!trabalhar: recompensa(R) & jornada(D) & estoque(C) & energia(E)<-
	.print("Trabalhando.....");
	.wait(1000);
	-+estoque(C+R);
	-+energia(E-D);
	!comer.

+energia(N): (N < 1) <- .print("Giacomo morreu de fome"); .stopMAS.
+estoque(C): (C < 0) <- .print("Acabaram as pizzas"); .stopMAS.
