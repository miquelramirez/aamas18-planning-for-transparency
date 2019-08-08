
(define (problem blocks_words)
	(:domain blocks)
(:objects 

J K O I S D W 
)
(:init
(HANDEMPTY)
(CLEAR K)
(ON K S)
(ON S D)
(ONTABLE D)
(CLEAR J)
(ONTABLE J)
(CLEAR O)
(ONTABLE O)
(CLEAR I)
(ON I W)
(ONTABLE W)
)
(:goal (and
(CLEAR I) (ONTABLE J) (ON I S) (ON S D) (ON D J)
))
)
