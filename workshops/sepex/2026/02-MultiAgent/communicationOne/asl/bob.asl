curso("Introdução a Agentes Cognitivos").
evento("SEPEX 2026").
!start.
+!start <-
	!fazerSaudacao;
	!dizerNome;
	!boasVindas;
	!escolherNrdaSorte;
	!fazerNumerologia;
	.broadcast(achieve,start);
.

+!fazerSaudacao <- .time(H,M,S); !saudar(H).
+!saudar(H): H >= 6   & H <= 12 <- .print("Bom dia!").
+!saudar(H): H > 12   & H <= 17 <- .print("Boa tarde!").
+!saudar(H): (H >= 18  & H <= 23) | (H < 6 ) <- .print("Boa noite!").

+!dizerNome <- .my_name(N); .print("Meu nome é: ",N).

+!boasVindas <- ?curso(C); ?evento(E); .print("Bem-vindos à ",E); .print("Este é o minicurso ",C).

+!escolherNrdaSorte <- .random(R); N = ((R * 1000) div 1); .print("Meu numero da sorte é: ",N); +numeroDaSorte(N).

+!fazerNumerologia <- ?numeroDaSorte(N); !analisarParidade(N); .print("Procurando meu primo da sorte..."); !proximoPrimo(N).

+!analisarParidade(N): N mod 2 == 0 <- .print("Meu numero é par!").
+!analisarParidade(N): N mod 2 == 1 <- .print("Meu numero é impar!").

+!proximoPrimo(N): not achouPrimo<- Proximo = N+1; !!testarPrimo(Proximo); .wait(100); !proximoPrimo(Proximo).
+!proximoPrimo(N): achouPrimo <- ?proximoPrimodaSorte(P); .print("O próximo primo do meu numero da sorte é: ",P).

+!testarPrimo(P): not achouPrimo & P >= 2 <-!procurandoPrimo(P,2).
+!procurandoPrimo(PossivelPrimo,Divisor): Divisor*Divisor > PossivelPrimo <- +achouPrimo; +proximoPrimodaSorte(PossivelPrimo).
+!procurandoPrimo(PossivelPrimo,Divisor): PossivelPrimo mod Divisor == 0 <- 
	Dividendo = PossivelPrimo/Divisor;
	.print(PossivelPrimo," nao e primo, pois (",Dividendo,"*",Divisor,"=",PossivelPrimo,")").
+!procurandoPrimo(PossivelPrimo,Divisor): Divisor*Divisor <= PossivelPrimo & PossivelPrimo mod Divisor \== 0 <-
    NovoDivisor = Divisor + 1;
    !procurandoPrimo(PossivelPrimo,NovoDivisor).

+numeroDaSorte(N): N mod 2 == 0 <- .print("Segundo a numerologia, esse número indica que hoje estou equilibrado, paciente e reflexivo").
+numeroDaSorte(N): N mod 2 == 1 <- .print("Segundo a numerologia, esse número indica que hoje estou mais independente, criativo e aventureiro").
