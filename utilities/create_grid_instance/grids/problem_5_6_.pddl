(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30)
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
		(adj P11 P16)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P7)
		(adj P12 P17)
		(adj P13 P14)
		(adj P13 P12)
		(adj P13 P8)
		(adj P13 P18)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P9)
		(adj P14 P19)
		(adj P15 P14)
		(adj P15 P10)
		(adj P15 P20)
		(adj P16 P17)
		(adj P16 P11)
		(adj P16 P21)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P12)
		(adj P17 P22)
		(adj P18 P19)
		(adj P18 P17)
		(adj P18 P13)
		(adj P18 P23)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P14)
		(adj P19 P24)
		(adj P20 P19)
		(adj P20 P15)
		(adj P20 P25)
		(adj P21 P22)
		(adj P21 P16)
		(adj P21 P26)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P17)
		(adj P22 P27)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P18)
		(adj P23 P28)
		(adj P24 P25)
		(adj P24 P23)
		(adj P24 P19)
		(adj P24 P29)
		(adj P25 P24)
		(adj P25 P20)
		(adj P25 P30)
		(adj P26 P27)
		(adj P26 P21)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P22)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P23)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P24)
		(adj P30 P29)
		(adj P30 P25)
		(pos P1)
	)
	(:goal
		(and
			(pos P25)
		)
	)
)
