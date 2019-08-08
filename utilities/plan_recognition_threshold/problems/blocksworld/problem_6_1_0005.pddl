
(define (problem blocks_words)
	(:domain blocks)
(:objects 

J K O I S D 
)
(:init
(HANDEMPTY)
(CLEAR D)
(ONTABLE D)
(CLEAR K)
(ONTABLE K)
(CLEAR J)
(ONTABLE J)
(CLEAR I)
(ON I S)
(ONTABLE S)
(CLEAR O)
(ONTABLE O)
)
(:goal (and
(CLEAR K) (ONTABLE I) (ON K O) (ON O I)
))
)
