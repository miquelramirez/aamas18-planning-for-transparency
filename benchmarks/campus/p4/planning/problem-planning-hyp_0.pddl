(define (problem bui-campus_generic_hyp-0_10_19)
(:domain campus)
(:objects
)
(:init
(= (total-cost) 0)
(at library)
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