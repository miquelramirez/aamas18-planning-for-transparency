(define (problem ticket_to_ride_prob_4)
 	(:domain ticket_to_ride)
 	(:objects
		P0 P1 P2 P3 P4 P5 P6 P7  - node
		C0 C1 C2  - colour
		N0 N1 N2  - number
	)
	(:init
		; Adjacency Graph: 
		(adj P5 P6 N2 C0)
		(adj P2 P0 N1 C2)
		(adj P1 P2 N2 C1)
		(adj P5 P0 N2 C0)
		(adj P7 P6 N2 C2)
		(adj P3 P4 N1 C1)

		; Numeric Operations: 
		(geq N0 N0)
		(geq N1 N0)
		(geq N1 N1)
		(geq N2 N0)
		(geq N2 N1)
		(geq N2 N2)
		(diff N0 N0 N0)
		(diff N1 N0 N1)
		(diff N1 N1 N0)
		(diff N2 N0 N2)
		(diff N2 N1 N1)
		(diff N2 N2 N0)
		(succ N0 N1)
		(succ N1 N2)
		(pred N1 N0)
		(pred N2 N1)

		; Initial state of players hand: 
		(numberTracks N0 C1)
		(numberTracks N0 C0)
		(numberTracks N0 C2)
	)
	(:goal
		(and
			(isPath P7 P4)
			(isPath P2 P3)
		)
	)
)
