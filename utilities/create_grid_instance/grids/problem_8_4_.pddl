(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32)
	(:init
		(adj P1 P2)
		(adj P1 P9)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P10)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P11)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P12)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P13)
		(adj P6 P7)
		(adj P6 P5)
		(adj P6 P14)
		(adj P7 P8)
		(adj P7 P6)
		(adj P7 P15)
		(adj P8 P7)
		(adj P8 P16)
		(adj P9 P10)
		(adj P9 P1)
		(adj P9 P17)
		(adj P10 P11)
		(adj P10 P9)
		(adj P10 P2)
		(adj P10 P18)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P3)
		(adj P11 P19)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P4)
		(adj P12 P20)
		(adj P13 P14)
		(adj P13 P12)
		(adj P13 P5)
		(adj P13 P21)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P6)
		(adj P14 P22)
		(adj P15 P16)
		(adj P15 P14)
		(adj P15 P7)
		(adj P15 P23)
		(adj P16 P15)
		(adj P16 P8)
		(adj P16 P24)
		(adj P17 P18)
		(adj P17 P9)
		(adj P17 P25)
		(adj P18 P19)
		(adj P18 P17)
		(adj P18 P10)
		(adj P18 P26)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P11)
		(adj P19 P27)
		(adj P20 P21)
		(adj P20 P19)
		(adj P20 P12)
		(adj P20 P28)
		(adj P21 P22)
		(adj P21 P20)
		(adj P21 P13)
		(adj P21 P29)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P14)
		(adj P22 P30)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P15)
		(adj P23 P31)
		(adj P24 P23)
		(adj P24 P16)
		(adj P24 P32)
		(adj P25 P26)
		(adj P25 P17)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P18)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P19)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P20)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P21)
		(adj P30 P31)
		(adj P30 P29)
		(adj P30 P22)
		(adj P31 P32)
		(adj P31 P30)
		(adj P31 P23)
		(adj P32 P31)
		(adj P32 P24)
		(pos P1)
	)
	(:goal
		(and
			(pos P27)
		)
	)
)
