(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21)
	(:init
		(adj P1 P2)
		(adj P1 P8)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P9)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P10)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P11)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P12)
		(adj P6 P7)
		(adj P6 P5)
		(adj P6 P13)
		(adj P7 P6)
		(adj P7 P14)
		(adj P8 P9)
		(adj P8 P1)
		(adj P8 P15)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P2)
		(adj P9 P16)
		(adj P10 P11)
		(adj P10 P9)
		(adj P10 P3)
		(adj P10 P17)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P4)
		(adj P11 P18)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P5)
		(adj P12 P19)
		(adj P13 P14)
		(adj P13 P12)
		(adj P13 P6)
		(adj P13 P20)
		(adj P14 P13)
		(adj P14 P7)
		(adj P14 P21)
		(adj P15 P16)
		(adj P15 P8)
		(adj P16 P17)
		(adj P16 P15)
		(adj P16 P9)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P10)
		(adj P18 P19)
		(adj P18 P17)
		(adj P18 P11)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P12)
		(adj P20 P21)
		(adj P20 P19)
		(adj P20 P13)
		(adj P21 P20)
		(adj P21 P14)
		(pos P1)
	)
	(:goal
		(and
			(pos P18)
		)
	)
)