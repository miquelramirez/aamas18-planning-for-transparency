
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
(CLEAR O) (ONTABLE K) (ON O I) (ON I S) (ON S J) (ON J K)
))
)
