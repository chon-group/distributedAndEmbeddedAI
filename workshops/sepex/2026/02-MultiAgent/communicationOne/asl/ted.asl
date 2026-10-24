+!start <-    
    .my_name(N);
    .print("Olá eu sou o agente ",N);
    !darBoasVindas;
    !dizerNrdaSorte;
.

+!darBoasVindas <- 
	.broadcast(askOne,curso(_));
	.wait(curso(C)[source(S)]);
	.print("Segundo o agente ",S," este é o minicurso ",C).

+!dizerNrdaSorte <-
    .broadcast(askHow,"+!escolherNrdaSorte");
    .wait(5000);
    !escolherNrdaSorte[source(Who)].

