
(define (problem blocks_words)
(:domain blocks)
(:objects

S T A R H C U K 
)
(:init
(HANDEMPTY)
(CLEAR T)
(ONTABLE T)
(CLEAR U)
(ONTABLE U)
(CLEAR R)
(ONTABLE R)
(CLEAR K)
(ONTABLE K)
(CLEAR C)
(ONTABLE C)
(CLEAR S)
(ON S A)
(ON A H)
(ONTABLE H)
)
(:goal (and
(CLEAR T)
(ONTABLE K)
(ON T U)
(ON U C)
(ON C K)
))
)
