// Agent producer in project producerConsumer

/* Initial beliefs and rules */
lastOrder(0).

/* Initial goals */

/* Plans */
+!order(Product,Qtd)[source(Client)]: lastOrder(Last) <-
	OrderNumber=(Last+1);
	-+lastOrder(OrderNumber);
	.print("Order:",OrderNumber," - Preparing ",Qtd," ",Product);
	.wait(3000);
	.send(Client,tell,foodArrived(Product,Qtd));
.