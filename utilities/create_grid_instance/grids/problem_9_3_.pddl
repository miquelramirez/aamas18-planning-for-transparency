(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27)
	(:init
		(adj P1 P2)
		(adj P1 P10)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P11)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P12)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P13)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P14)
		(adj P6 P7)
		(adj P6 P5)
		(adj P6 P15)
		(adj P7 P8)
		(adj P7 P6)
		(adj P7 P16)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P17)
		(adj P9 P8)
		(adj P9 P18)
		(adj P10 P11)
		(adj P10 P1)
		(adj P10 P19)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P2)
		(adj P11 P20)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P3)
		(adj P12 P21)
		(adj P13 P14)
		(adj P13 P12)
		(adj P13 P4)
		(adj P13 P22)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P5)
		(adj P14 P23)
		(adj P15 P16)
		(adj P15 P14)
		(adj P15 P6)
		(adj P15 P24)
		(adj P16 P17)
		(adj P16 P15)
		(adj P16 P7)
		(adj P16 P25)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P8)
		(adj P17 P26)
		(adj P18 P17)
		(adj P18 P9)
		(adj P18 P27)
		(adj P19 P20)
		(adj P19 P10)
		(adj P20 P21)
		(adj P20 P19)
		(adj P20 P11)
		(adj P21 P22)
		(adj P21 P20)
		(adj P21 P12)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P13)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P14)
		(adj P24 P25)
		(adj P24 P23)
		(adj P24 P15)
		(adj P25 P26)
		(adj P25 P24)
		(adj P25 P16)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P17)
		(adj P27 P26)
		(adj P27 P18)
		(pos P1)
	)
	(:goal
		(and
			(pos P23)
		)
	)
)