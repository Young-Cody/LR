
FIRST(() = {( }
FIRST()) = {) }
FIRST(*) = {* }
FIRST(+) = {+ }
FIRST(E) = {( id }
FIRST(E') = {( id }
FIRST(F) = {( id }
FIRST(T) = {( id }
FIRST(id) = {id }

FOLLOW(E) = {$ ) + }
FOLLOW(E') = {$ }
FOLLOW(F) = {$ ) * + }
FOLLOW(T) = {$ ) * + }
I0
E' -> . E , $
E -> . E + T , $
E -> . E + T , +
E -> . T , $
E -> . T , +
T -> . T * F , $
T -> . T * F , *
T -> . T * F , +
T -> . F , $
T -> . F , *
T -> . F , +
F -> . ( E ) , $
F -> . ( E ) , *
F -> . ( E ) , +
F -> . id , $
F -> . id , *
F -> . id , +
I1
E -> . E + T , )
E -> . E + T , +
E -> . T , )
E -> . T , +
T -> . T * F , )
T -> . T * F , *
T -> . T * F , +
T -> . F , )
T -> . F , *
T -> . F , +
F -> . ( E ) , )
F -> . ( E ) , *
F -> . ( E ) , +
F -> ( . E ) , $
F -> ( . E ) , )
F -> ( . E ) , *
F -> ( . E ) , +
F -> . id , )
F -> . id , *
F -> . id , +
I2
E' -> E . , $
E -> E . + T , $
E -> E . + T , +
I3
T -> F . , $
T -> F . , )
T -> F . , *
T -> F . , +
I4
E -> T . , $
E -> T . , )
E -> T . , +
T -> T . * F , $
T -> T . * F , )
T -> T . * F , *
T -> T . * F , +
I5
F -> id . , $
F -> id . , )
F -> id . , *
F -> id . , +
I6
T -> T * . F , $
T -> T * . F , )
T -> T * . F , *
T -> T * . F , +
F -> . ( E ) , $
F -> . ( E ) , )
F -> . ( E ) , *
F -> . ( E ) , +
F -> . id , $
F -> . id , )
F -> . id , *
F -> . id , +
I7
T -> T * F . , $
T -> T * F . , )
T -> T * F . , *
T -> T * F . , +
I8
E -> E + . T , $
E -> E + . T , )
E -> E + . T , +
T -> . T * F , $
T -> . T * F , )
T -> . T * F , *
T -> . T * F , +
T -> . F , $
T -> . F , )
T -> . F , *
T -> . F , +
F -> . ( E ) , $
F -> . ( E ) , )
F -> . ( E ) , *
F -> . ( E ) , +
F -> . id , $
F -> . id , )
F -> . id , *
F -> . id , +
I9
E -> E + T . , $
E -> E + T . , )
E -> E + T . , +
T -> T . * F , $
T -> T . * F , )
T -> T . * F , *
T -> T . * F , +
I11
E -> E . + T , )
E -> E . + T , +
F -> ( E . ) , $
F -> ( E . ) , )
F -> ( E . ) , *
F -> ( E . ) , +
I17
F -> ( E ) . , $
F -> ( E ) . , )
F -> ( E ) . , *
F -> ( E ) . , +

action

0  ( s1  id s5  
1  ( s1  id s5  
2  $ acc  + s8  
3  $ r4  ) r4  * r4  + r4  
4  $ r2  ) r2  * s6  + r2  
5  $ r6  ) r6  * r6  + r6  
6  ( s1  id s5  
7  $ r3  ) r3  * r3  + r3  
8  ( s1  id s5  
9  $ r1  ) r1  * s6  + r1  
11  ) s17  + s8  
17  $ r5  ) r5  * r5  + r5  

goto

0  E 2  F 3  T 4  
1  E 11  F 3  T 4  
2  
3  
4  
5  
6  F 7  
7  
8  F 3  T 9  
9  
11  
17  
0           id + id $           shift
0 id 5           + id $           reduce F -> id 
0 F 3           + id $           reduce T -> F 
0 T 4           + id $           reduce E -> T 
0 E 2           + id $           shift
0 E 2 + 8           id $           shift
0 E 2 + 8 id 5           $           reduce F -> id 
0 E 2 + 8 F 3           $           reduce T -> F 
0 E 2 + 8 T 9           $           reduce E -> E + T 
0 E 2           $           accept

0           id + id * id $           shift
0 id 5           + id * id $           reduce F -> id 
0 F 3           + id * id $           reduce T -> F 
0 T 4           + id * id $           reduce E -> T 
0 E 2           + id * id $           shift
0 E 2 + 8           id * id $           shift
0 E 2 + 8 id 5           * id $           reduce F -> id 
0 E 2 + 8 F 3           * id $           reduce T -> F 
0 E 2 + 8 T 9           * id $           shift
0 E 2 + 8 T 9 * 6           id $           shift
0 E 2 + 8 T 9 * 6 id 5           $           reduce F -> id 
0 E 2 + 8 T 9 * 6 F 7           $           reduce T -> T * F 
0 E 2 + 8 T 9           $           reduce E -> E + T 
0 E 2           $           accept

0           id * id + id $           shift
0 id 5           * id + id $           reduce F -> id 
0 F 3           * id + id $           reduce T -> F 
0 T 4           * id + id $           shift
0 T 4 * 6           id + id $           shift
0 T 4 * 6 id 5           + id $           reduce F -> id 
0 T 4 * 6 F 7           + id $           reduce T -> T * F 
0 T 4           + id $           reduce E -> T 
0 E 2           + id $           shift
0 E 2 + 8           id $           shift
0 E 2 + 8 id 5           $           reduce F -> id 
0 E 2 + 8 F 3           $           reduce T -> F 
0 E 2 + 8 T 9           $           reduce E -> E + T 
0 E 2           $           accept

0           ( id + id ) * ( id + id ) $           shift
0 ( 1           id + id ) * ( id + id ) $           shift
0 ( 1 id 5           + id ) * ( id + id ) $           reduce F -> id 
0 ( 1 F 3           + id ) * ( id + id ) $           reduce T -> F 
0 ( 1 T 4           + id ) * ( id + id ) $           reduce E -> T 
0 ( 1 E 11           + id ) * ( id + id ) $           shift
0 ( 1 E 11 + 8           id ) * ( id + id ) $           shift
0 ( 1 E 11 + 8 id 5           ) * ( id + id ) $           reduce F -> id 
0 ( 1 E 11 + 8 F 3           ) * ( id + id ) $           reduce T -> F 
0 ( 1 E 11 + 8 T 9           ) * ( id + id ) $           reduce E -> E + T 
0 ( 1 E 11           ) * ( id + id ) $           shift
0 ( 1 E 11 ) 17           * ( id + id ) $           reduce F -> ( E ) 
0 F 3           * ( id + id ) $           reduce T -> F 
0 T 4           * ( id + id ) $           shift
0 T 4 * 6           ( id + id ) $           shift
0 T 4 * 6 ( 1           id + id ) $           shift
0 T 4 * 6 ( 1 id 5           + id ) $           reduce F -> id 
0 T 4 * 6 ( 1 F 3           + id ) $           reduce T -> F 
0 T 4 * 6 ( 1 T 4           + id ) $           reduce E -> T 
0 T 4 * 6 ( 1 E 11           + id ) $           shift
0 T 4 * 6 ( 1 E 11 + 8           id ) $           shift
0 T 4 * 6 ( 1 E 11 + 8 id 5           ) $           reduce F -> id 
0 T 4 * 6 ( 1 E 11 + 8 F 3           ) $           reduce T -> F 
0 T 4 * 6 ( 1 E 11 + 8 T 9           ) $           reduce E -> E + T 
0 T 4 * 6 ( 1 E 11           ) $           shift
0 T 4 * 6 ( 1 E 11 ) 17           $           reduce F -> ( E ) 
0 T 4 * 6 F 7           $           reduce T -> T * F 
0 T 4           $           reduce E -> T 
0 E 2           $           accept

0           ( id * ( id + ( id + id ) * ( id + id ) ) ) * id $           shift
0 ( 1           id * ( id + ( id + id ) * ( id + id ) ) ) * id $           shift
0 ( 1 id 5           * ( id + ( id + id ) * ( id + id ) ) ) * id $           reduce F -> id 
0 ( 1 F 3           * ( id + ( id + id ) * ( id + id ) ) ) * id $           reduce T -> F 
0 ( 1 T 4           * ( id + ( id + id ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6           ( id + ( id + id ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1           id + ( id + id ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 id 5           + ( id + id ) * ( id + id ) ) ) * id $           reduce F -> id 
0 ( 1 T 4 * 6 ( 1 F 3           + ( id + id ) * ( id + id ) ) ) * id $           reduce T -> F 
0 ( 1 T 4 * 6 ( 1 T 4           + ( id + id ) * ( id + id ) ) ) * id $           reduce E -> T 
0 ( 1 T 4 * 6 ( 1 E 11           + ( id + id ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8           ( id + id ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1           id + id ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 id 5           + id ) * ( id + id ) ) ) * id $           reduce F -> id 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 F 3           + id ) * ( id + id ) ) ) * id $           reduce T -> F 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 T 4           + id ) * ( id + id ) ) ) * id $           reduce E -> T 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 E 11           + id ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 E 11 + 8           id ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 E 11 + 8 id 5           ) * ( id + id ) ) ) * id $           reduce F -> id 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 E 11 + 8 F 3           ) * ( id + id ) ) ) * id $           reduce T -> F 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 E 11 + 8 T 9           ) * ( id + id ) ) ) * id $           reduce E -> E + T 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 E 11           ) * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 ( 1 E 11 ) 17           * ( id + id ) ) ) * id $           reduce F -> ( E ) 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 F 3           * ( id + id ) ) ) * id $           reduce T -> F 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9           * ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6           ( id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1           id + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 id 5           + id ) ) ) * id $           reduce F -> id 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 F 3           + id ) ) ) * id $           reduce T -> F 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 T 4           + id ) ) ) * id $           reduce E -> T 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 E 11           + id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 E 11 + 8           id ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 E 11 + 8 id 5           ) ) ) * id $           reduce F -> id 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 E 11 + 8 F 3           ) ) ) * id $           reduce T -> F 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 E 11 + 8 T 9           ) ) ) * id $           reduce E -> E + T 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 E 11           ) ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 ( 1 E 11 ) 17           ) ) * id $           reduce F -> ( E ) 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9 * 6 F 7           ) ) * id $           reduce T -> T * F 
0 ( 1 T 4 * 6 ( 1 E 11 + 8 T 9           ) ) * id $           reduce E -> E + T 
0 ( 1 T 4 * 6 ( 1 E 11           ) ) * id $           shift
0 ( 1 T 4 * 6 ( 1 E 11 ) 17           ) * id $           reduce F -> ( E ) 
0 ( 1 T 4 * 6 F 7           ) * id $           reduce T -> T * F 
0 ( 1 T 4           ) * id $           reduce E -> T 
0 ( 1 E 11           ) * id $           shift
0 ( 1 E 11 ) 17           * id $           reduce F -> ( E ) 
0 F 3           * id $           reduce T -> F 
0 T 4           * id $           shift
0 T 4 * 6           id $           shift
0 T 4 * 6 id 5           $           reduce F -> id 
0 T 4 * 6 F 7           $           reduce T -> T * F 
0 T 4           $           reduce E -> T 
0 E 2           $           accept

