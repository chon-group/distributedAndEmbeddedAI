/* Initial beliefs and rules */
//inside.

/* Initial goals */
!conf.

/* Plans */

+!conf <-
	.print("This is Lieutenant Nyota Uhura, Communications officer");
	.connectCN("skynet.chon.group",3273,"07b11cf3-92cb-47b4-b321-fb5051497150").

+!damageReport[source(X)] <-
	.print("Commander Kirk, Deck 2 compromised!");
	.sendOut(X,tell,report("Deck 2")).
   

