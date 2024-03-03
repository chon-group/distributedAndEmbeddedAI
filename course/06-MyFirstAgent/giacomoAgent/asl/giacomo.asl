/* Initial beliefs and rules */
lifeParameters(S,E,P,W,N,L) :- stock(S) &  energy(E) & payment(P) & workingDay(W) & partyNight(N) & lunch(L).  

stock(0).		// The pizza stock.
payment(+3).	// How many pizzas does Giacomo get by a working day?
energy(10).		// The Giacomo life energy.
lunch(+2).  	// How much energy does Giacomo get eating a pizza?
workingDay(-1).	// How much energy does Giacomo lose in a working day?
partyNight(-3).	// How much energy does Giacomo lose on a party night?

/* Initial goals */
!goToParty.

/* Plans */
+!goToParty: lifeParameters(S,E,P,W,N,L) & (E+(N+W)>1) <- -+energy(E+N); !goToParty.
+!goToParty: lifeParameters(S,E,P,W,N,L) & (E+(N+W)<=1)<- !eat.

+!eat: lifeParameters(S,E,P,W,N,L) & (E<2*(-1*(N+W))) & S>0 <-  -+stock(S-1); -+energy(E+L); !eat.
+!eat: lifeParameters(S,E,P,W,N,L) & (E>=2*(-1*(N+W))) <-	!goToParty.
+!eat: lifeParameters(S,E,P,W,N,L) & S=0 <-	!work.

+!work: lifeParameters(S,E,P,W,N,L) <- -+stock(S+P); -+energy(E+W); !eat.

+energy(E): E < 1 <- .print("Giacomo died of hunger!"); .stopMAS.
+stock(S): C < 0 <- .print("Without food!"); .stopMAS.













