agent(teddy).
!count.
+!count: count(V) & V < 100 <-
 ?agent(Name); ?count(N);
 .print(N,". My name is ", Name,".");
 -+count(N+1); .wait(500); !count;
.
-!count <- -count(_); +count(0); !count.




