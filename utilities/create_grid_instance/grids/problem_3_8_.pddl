(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24)
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
		(adj P10 P13)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P8)
		(adj P11 P14)
		(adj P12 P11)
		(adj P12 P9)
		(adj P12 P15)
		(adj P13 P14)
		(adj P13 P10)
		(adj P13 P16)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P11)
		(adj P14 P17)
		(adj P15 P14)
		(adj P15 P12)
		(adj P15 P18)
		(adj P16 P17)
		(adj P16 P13)
		(adj P16 P19)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P14)
		(adj P17 P20)
		(adj P18 P17)
		(adj P18 P15)
		(adj P18 P21)
		(adj P19 P20)
		(adj P19 P16)
		(adj P19 P22)
		(adj P20 P21)
		(adj P20 P19)
		(adj P20 P17)
		(adj P20 P23)
		(adj P21 P20)
		(adj P21 P18)
		(adj P21 P24)
		(adj P22 P23)
		(adj P22 P19)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P20)
		(adj P24 P23)
		(adj P24 P21)
		(pos P1)
	)
	(:goal
		(and
			(pos P20)
		)
	)
)
