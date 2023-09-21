/* Crenças Iniciais */
uhuraUUID("49a13d91-5fb7-45ac-aad3-be05b6ce4c77").	//https://www.uuidgenerator.net/
myUUID("c94d0747-2faf-4902-8f0d-6d739f631305").

skyNet(skynet.chon.group,5500).				//public SkynetServer

/* Objetivo Inicial */
!contact.

/* Planos */

+!conf : myUUID(ID) & skyNet(Server,Port) <-
	.print("This is Commander James T. Kirk, Enterprise's Captain");
	.connectCN(Server,Port,ID);
	+connected;
	!testComm.

+!contact: connected & uhuraUUID(Uhura) & communication(ok)<-
	.print("Damage report!");
	.sendOut(Uhura, achieve, damageReport).

+!contact: not connected <-
	.print("Without Communication!");
	!conf.

+report(Damages)[source(X)] <- 
	.print("Damages in ", Damages);
	.print("Stay in standard orbit and wait for instructions.");
	.sendOut(X, tell, retransmit(scott, redAlert));
	.wait(2000);
	.disconnectCN.

+!testComm : connected & uhuraUUID(Uhura) & not communication(ok)<-
	.print("Kirk to Enterprise...");
	.sendOut(Uhura, tell, communication(trying)); 
	.wait(2500);
	!testComm.

+!testComm: communication(ok) <- !contact.
