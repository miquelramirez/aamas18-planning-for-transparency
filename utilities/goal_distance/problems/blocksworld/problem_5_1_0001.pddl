
(define (problem blocks_words)
	(:domain blocks)
(:objects 

J K O I S
)
(:init
(HANDEMPTY)
(CLEAR J)
(ON J I)
(ONTABLE I)
(CLEAR O)
(ONTABLE O)
(CLEAR K)
(ONTABLE K)
(CLEAR S)
(ONTABLE S)
)
(:goal (and
(CLEAR K) (ONTABLE I) (ON K O) (ON O I)
))
)
