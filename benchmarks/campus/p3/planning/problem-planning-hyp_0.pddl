(define (problem bui-campus_generic_hyp-0_10_17)
(:domain campus)
(:objects
)
(:init
(= (total-cost) 0)
(at cbs)
)
(:goal
(and
(BREAKFAST)
(LECTURE-1-TAKEN)
(GROUP-MEETING-1)
(LECTURE-2-TAKEN)
(COFFEE)
)
)
(:metric minimize (total-cost))
)
