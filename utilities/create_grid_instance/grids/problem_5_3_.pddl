(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15)
	(:init
		(adj P1 P2)
		(adj P1 P6)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P7)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P8)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P9)
		(adj P5 P4)
		(adj P5 P10)
		(adj P6 P7)
		(adj P6 P1)
		(adj P6 P11)
		(adj P7 P8)
		(adj P7 P6)
		(adj P7 P2)
		(adj P7 P12)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P3)
		(adj P8 P13)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P4)
		(adj P9 P14)
		(adj P10 P9)
		(adj P10 P5)
		(adj P10 P15)
		(adj P11 P12)
		(adj P11 P6)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P7)
		(adj P13 P14)
		(adj P13 P12)
		(adj P13 P8)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P9)
		(adj P15 P14)
		(adj P15 P10)
		(pos P1)
	)
	(:goal
		(and
			(pos P13)
		)
	)
)
