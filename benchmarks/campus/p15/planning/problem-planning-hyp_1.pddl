(define (problem bui-campus_generic_hyp-0_10_7)
(:domain campus)
(:objects
)
(:init
(= (total-cost) 0)
(at library)
)
(:goal
(and
(GROUP-MEETING-2)
(BANKING)
(LECTURE-3-TAKEN)
(LECTURE-4-TAKEN)
(GROUP-MEETING-3)
(LUNCH)
)
)
(:metric minimize (total-cost))
)
