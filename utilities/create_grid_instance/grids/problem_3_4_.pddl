(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12)
	(:init
		(adj P1 P2)
		(adj P1 P4)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P5)
		(adj P3 P2)
		(adj P3 P6)
		(adj P4 P5)
		(adj P4 P1)
		(adj P4 P7)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P2)
		(adj P5 P8)
		(adj P6 P5)
		(adj P6 P3)
		(adj P6 P9)
		(adj P7 P8)
		(adj P7 P4)
		(adj P7 P10)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P5)
		(adj P8 P11)
		(adj P9 P8)
		(adj P9 P6)
		(adj P9 P12)
		(adj P10 P11)
		(adj P10 P7)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P8)
		(adj P12 P11)
		(adj P12 P9)
		(pos P1)
	)
	(:goal
		(and
			(pos P10)
		)
	)
)
