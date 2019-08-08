
(define (problem blocks_words)
	(:domain blocks)
(:objects 

H A B S - block
)
(:init
(HANDEMPTY)
(CLEAR A)
(ONTABLE A)
(CLEAR S)
(ONTABLE S)
(CLEAR H)
(ON H B)
(ONTABLE B)
)
(:goal (and
  (CLEAR B)
  (ONTABLE H)
  (ON B A)
  (ON A S)
  (ON S H)
))
)
