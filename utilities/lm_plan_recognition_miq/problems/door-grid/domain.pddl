(define (domain door_grid_domain)
	(:requirements :strips)
	(:predicates (pos ?x) (adj ?x1 ?x2) (blocked ?y) (button ?x ?y))

		(:action move
			:parameters (?x1 ?x2)
			:precondition (and (pos ?x1) (adj ?x1 ?x2) (not (blocked ?x2)))
			:effect (and (pos ?x2) (not (pos ?x1)))
		)

		(:action move_push_button
		  :parameters ( ?x1 ?x2 ?y )
		  :precondition (and (pos ?x1) (adj ?x1 ?x2) (button ?x2 ?y))
		  :effect (and (pos ?x2) (not (pos ?x1)) (blocked ?y) )
		)

)
