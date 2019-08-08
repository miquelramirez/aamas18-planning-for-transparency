(define (problem ticket_to_ride_prob_7)
 	(:domain ticket_to_ride)
 	(:objects
		P0 P1 P2 P3 P4 P5 P6  - node
		C0 C1 C2  - colour
		N0 N1 N2 N3  - number
	)
	(:init
		; Adjacency Graph: 
		(adj P5 P6 N2 C2)
		(adj P2 P5 N2 C2)
		(adj P0 P5 N3 C2)
		(adj P3 P4 N2 C0)
		(adj P3 P2 N2 C2)
		(adj P6 P3 N2 C1)

		; Numeric Operations: 
		(geq N0 N0)
		(geq N1 N0)
		(geq N1 N1)
		(geq N2 N0)
		(geq N2 N1)
		(geq N2 N2)
		(geq N3 N0)
		(geq N3 N1)
		(geq N3 N2)
		(geq N3 N3)
		(diff N0 N0 N0)
		(diff N1 N0 N1)
		(diff N1 N1 N0)
		(diff N2 N0 N2)
		(diff N2 N1 N1)
		(diff N2 N2 N0)
		(diff N3 N0 N3)
		(diff N3 N1 N2)
		(diff N3 N2 N1)
		(diff N3 N3 N0)
		(succ N0 N1)
		(succ N1 N2)
		(succ N2 N3)
		(pred N1 N0)
		(pred N2 N1)
		(pred N3 N2)

		; Initial state of players hand: 
		(numberTracks N0 C0)
		(numberTracks N0 C2)
		(numberTracks N0 C1)
	)
	(:goal
		(and
			(isPath P0 P4)
			(isPath P0 P6)
		)
	)
)
