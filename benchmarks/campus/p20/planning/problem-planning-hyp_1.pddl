(define (problem bui-campus_generic_hyp-0_30_51)
(:domain campus)
(:objects
)
(:init
(= (total-cost) 0)
(at angazi_cafe)
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
