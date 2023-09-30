/* Crenças Iniciais */
// Gerar UUID aleatório ---> https://www.uuidgenerator.net/
myUUID("49a13d91-5fb7-45ac-aad3-be05b6ce4c77").

skyNet("skynet.chon.group",5500).		//public SkynetServer

/* Objetivos Iniciais */
!conf.

/* Planos */
+!conf : myUUID(ID) & skyNet(Server,Port) <-
	.print("This is Lieutenant Nyota Uhura, Communications officer");
	.connectCN(Server,Port,ID).

+!damageReport[source(X)] <-
	.print("Commander Kirk, Deck 2 compromised!");
	.sendOut(X,tell,report("Deck 2")).

+communication(trying)[source(X)] <-
	.print("Entreprise Listen ",X);
	.sendOut(X,tell,communication(ok));
	-communication(trying)[source(X)].
	
+retransmit(Dest,Msg)[source(X)] <-
	.send(Dest,tell,Msg);
	-retransmit(Dest,Msg)[source(X)].
