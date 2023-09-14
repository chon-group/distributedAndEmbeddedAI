// Agent consumer in project producerConsumer
/* Initial beliefs and rules */
foodStock(0).
energy(0).

/* Initial goals */
!goToParty.

/* Plans */
+!lunch: hungry & foodStock(C) & C>3 & energy(E) & E<=10 <-
	-+foodStock(C-3);
	-+energy(E+3);
	.print("Eating... [foodStock=",C-3,"] [energy=",E+3,"]");
	.wait(1000);
	!lunch.
	
+!lunch: energy(E) & E>10	<-
	.print("Satisfied...... [energy=",E,"]");
	-hungry;
	!goToParty.

+!lunch <-
	?foodStock(X);
	.print("Need to order food..... [foodStock=",X,"]");
	!orderFoodDelivery.

+!goToParty: energy(E) & E>5 <-
	.print("Party time !!!!");
	.wait(2000);
	-+energy(E-3);
	-hungry;
	!goToParty.

+!goToParty: energy(E) & E<=5<-
	?energy(X);
	.print("I'm without energy ... [energy=",X,"]");
	+hungry;
	!lunch.

+!orderFoodDelivery <-
	.print("I'm ordering food ...");
	.send(producer,achieve,order(sandwich,5));
	.wait(5000);
	!lunch.

+foodArrived(Product,Qtd)[source(Vendor)] <-
	?foodStock(X);
	-+foodStock(X+Qtd);
	.print("Food arrived, I'm happy!!!!");
	-foodArrived(Product,Qtd)[source(Vendor)].