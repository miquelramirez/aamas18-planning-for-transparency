;; satplan bw_large.a blocks

(define (problem nine) 
  (:domain blocks_world)
  (:objects A B C D)
  (:init (clear B)
	 (on B A)
   (on-table A)
	 (clear D)
	 (clear C)
	 (on-table C)
	 (on-table D))
  (:goal (and (on A B) (on B C) (on C D))
	))
