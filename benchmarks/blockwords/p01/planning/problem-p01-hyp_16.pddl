
(define (problem blocks_words)
(:domain blocks)
(:objects

D R A W O E P C - block
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
(CLEAR C)
(ONTABLE E)
(ON C O)
(ON O R)
(ON R E)
))
)
