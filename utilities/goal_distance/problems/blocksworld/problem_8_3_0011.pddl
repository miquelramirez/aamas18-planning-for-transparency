
(define (problem blocks_words)
(:domain blocks)
(:objects

M O T H E R W A - block
)
(:init
(HANDEMPTY)
(CLEAR M)
(ON M O)
(ONTABLE O)
(CLEAR E)
(ONTABLE E)
(CLEAR T)
(ON T W)
(ONTABLE W)
(CLEAR H)
(ONTABLE H)
(CLEAR R)
(ON R A)
(ONTABLE A)
)
(:goal (and
(CLEAR T)
(ONTABLE W)
(ON T H)
(ON H A)
(ON A W)
))
)