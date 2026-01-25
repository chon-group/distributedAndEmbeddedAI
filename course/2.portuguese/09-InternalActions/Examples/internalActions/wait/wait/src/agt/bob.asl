timeSpent(0).

!clock.
!alarm(3).

+!clock: timeSpent(T) <-
	.wait(1000); 
	-+timeSpent(T+1);
    .print("Clock Ticking!");
	!clock.

+!alarm(A): A \== stop <- 
	.wait(timeSpent(A));
    !!display("Wake up, Neo...");
    +wakeUp;
	.wait(alarm(off));
    .stopMAS(2000).

+!display(M): not alarm(off) <- .wait(1000); .print(M); !display(M).
+!display(M): alarm(off) <- .print("Good morning Neo...").

+wakeUp <- .random(R); .wait(5000*R); +alarm(off).