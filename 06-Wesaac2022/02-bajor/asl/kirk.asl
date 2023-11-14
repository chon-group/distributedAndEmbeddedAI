// Agent agenteRemetente in project smaRemetente
uhura("07b11cf3-92cb-47b4-b321-fb5051497150").
local(bajor).

/* Initial beliefs and rules */
!conf.

/* Initial goals */

/* Plans */
+!conf <-
	.connectCN("skynet.chon.group",3273,"41ff1712-b2f0-416d-8232-fef834651e77");
	!contact.

+!contact: local(bajor) & uhura(UUID) <-
	.print("Kirk to Enterprise...");
	.print("Damage report!");
	.sendOut(UUID, achieve, damageReport).

+report(Damages)[source(X)] <- 
	.print("Damages in ", Damages);
	.print("Stay in standard orbit and wait for instructions.").
