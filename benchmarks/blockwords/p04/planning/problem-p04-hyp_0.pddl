
(define (problem blocks_words)
	(:domain blocks)
(:objects 

N A S - block
)
(:init
(HANDEMPTY)
(CLEAR N)
(ONTABLE N)
(CLEAR S)
(ONTABLE S)
(CLEAR A)
(ONTABLE A)
)
(:goal (and
  (and
  (CLEAR N)
  (ONTABLE S)
  (ON N A)
  (ON A S)
  
))
))
