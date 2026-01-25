/* Initial beliefs and rules */
stock(0).		// This is a Belief that represents the pizza stock.
payment(+2).	// ... represents how many pizzas does Giacomo get by a working day?
energy(5).		// ... represents the Giacomo life energy.
workingDay(-1).	// ... represents how much energy does Giacomo lose in a working day?
partyNight(-2).	// ... represents how much energy does Giacomo lose on a party night?
lifeParameters(S,E,P,W,N) :- stock(S) &  energy(E) & payment(P) & workingDay(W) & partyNight(N). //this is a RULE!

/* Initial goals */
!startGiacomoLife.

/* Plans */
+!startGiacomoLife <- !startClock; !goToParty.
+!goToParty: lifeParameters(S,E,P,W,N) & (E+(N+W)>1) <- -+lastParty(0); -+energy(E+N); .wait(1000); !goToParty.
+!goToParty: lifeParameters(S,E,P,W,N) & (E+(N+W)<=1)<- !eat.
+!eat: lifeParameters(S,E,P,W,N) & (E<2*(-1*(N+W))) & S>0  <- -+stock(S-1); -+energy(E+1); .wait(1000); !eat.
+!eat: lifeParameters(S,E,P,W,N) & (E>=2*(-1*(N+W))) <- !goToParty.
+!eat: lifeParameters(S,E,P,W,N) & S=0  <- !work.
+!work: lifeParameters(S,E,P,W,N) <- -+stock(S+P); -+energy(E+W); !eat.
+!startClock <- +lastParty(0); !!tickingClock.
+!tickingClock <- .wait(100); ?lastParty(Time); -+lastParty(Time+100); !tickingClock.

+energy(E): E < 1 <- .print("Giacomo died of hunger!"); .stopMAS.
+stock(S): S < 0 <- .print("Without food!"); .stopMAS.
+lastParty(Time): Time > 10000 <- .print("Giacomo died of sadness!"); .stopMAS.





