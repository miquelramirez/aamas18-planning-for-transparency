
(define (problem blocks_words)
(:domain blocks)
(:objects

D R A W O E P C 
)
(:init
(HANDEMPTY)
(CLEAR O)
(ONTABLE O)
(CLEAR R)
(ON R P)
(ONTABLE P)
(CLEAR E)
(ONTABLE E)
(CLEAR D)
(ON D A)
(ON A C)
(ONTABLE C)
(CLEAR W)
(ONTABLE W)
)
(:goal (and
(CLEAR E)
(ONTABLE R)
(ON E A)
(ON A R)
))
)