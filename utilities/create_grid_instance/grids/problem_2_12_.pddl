(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24)
	(:init
		(adj P1 P2)
		(adj P1 P3)
		(adj P2 P1)
		(adj P2 P4)
		(adj P3 P4)
		(adj P3 P1)
		(adj P3 P5)
		(adj P4 P3)
		(adj P4 P2)
		(adj P4 P6)
		(adj P5 P6)
		(adj P5 P3)
		(adj P5 P7)
		(adj P6 P5)
		(adj P6 P4)
		(adj P6 P8)
		(adj P7 P8)
		(adj P7 P5)
		(adj P7 P9)
		(adj P8 P7)
		(adj P8 P6)
		(adj P8 P10)
		(adj P9 P10)
		(adj P9 P7)
		(adj P9 P11)
		(adj P10 P9)
		(adj P10 P8)
		(adj P10 P12)
		(adj P11 P12)
		(adj P11 P9)
		(adj P11 P13)
		(adj P12 P11)
		(adj P12 P10)
		(adj P12 P14)
		(adj P13 P14)
		(adj P13 P11)
		(adj P13 P15)
		(adj P14 P13)
		(adj P14 P12)
		(adj P14 P16)
		(adj P15 P16)
		(adj P15 P13)
		(adj P15 P17)
		(adj P16 P15)
		(adj P16 P14)
		(adj P16 P18)
		(adj P17 P18)
		(adj P17 P15)
		(adj P17 P19)
		(adj P18 P17)
		(adj P18 P16)
		(adj P18 P20)
		(adj P19 P20)
		(adj P19 P17)
		(adj P19 P21)
		(adj P20 P19)
		(adj P20 P18)
		(adj P20 P22)
		(adj P21 P22)
		(adj P21 P19)
		(adj P21 P23)
		(adj P22 P21)
		(adj P22 P20)
		(adj P22 P24)
		(adj P23 P24)
		(adj P23 P21)
		(adj P24 P23)
		(adj P24 P22)
		(pos P1)
	)
	(:goal
		(and
			(pos P20)
		)
	)
)
