
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
(CLEAR O) (ONTABLE K) (ON O I) (ON I D) (ON D W) (ON W S) (ON S J) (ON J K)
))
)