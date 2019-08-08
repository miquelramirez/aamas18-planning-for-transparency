(define (domain grid_domain)
	(:requirements :strips)
	(:predicates (pos ?x) (adj ?x1 ?x2) )

		(:action move
			:parameters (?x1 ?x2)
			:precondition (and (pos ?x1) (adj ?x1 ?x2))
			:effect (and (pos ?x2) (not (pos ?x1)))
		)

)
