(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36)
	(:init
		(adj P1 P2)
		(adj P1 P13)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P14)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P15)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P16)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P17)
		(adj P6 P7)
		(adj P6 P5)
		(adj P6 P18)
		(adj P7 P8)
		(adj P7 P6)
		(adj P7 P19)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P20)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P21)
		(adj P10 P11)
		(adj P10 P9)
		(adj P10 P22)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P23)
		(adj P12 P11)
		(adj P12 P24)
		(adj P13 P14)
		(adj P13 P1)
		(adj P13 P25)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P2)
		(adj P14 P26)
		(adj P15 P16)
		(adj P15 P14)
		(adj P15 P3)
		(adj P15 P27)
		(adj P16 P17)
		(adj P16 P15)
		(adj P16 P4)
		(adj P16 P28)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P5)
		(adj P17 P29)
		(adj P18 P19)
		(adj P18 P17)
		(adj P18 P6)
		(adj P18 P30)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P7)
		(adj P19 P31)
		(adj P20 P21)
		(adj P20 P19)
		(adj P20 P8)
		(adj P20 P32)
		(adj P21 P22)
		(adj P21 P20)
		(adj P21 P9)
		(adj P21 P33)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P10)
		(adj P22 P34)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P11)
		(adj P23 P35)
		(adj P24 P23)
		(adj P24 P12)
		(adj P24 P36)
		(adj P25 P26)
		(adj P25 P13)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P14)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P15)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P16)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P17)
		(adj P30 P31)
		(adj P30 P29)
		(adj P30 P18)
		(adj P31 P32)
		(adj P31 P30)
		(adj P31 P19)
		(adj P32 P33)
		(adj P32 P31)
		(adj P32 P20)
		(adj P33 P34)
		(adj P33 P32)
		(adj P33 P21)
		(adj P34 P35)
		(adj P34 P33)
		(adj P34 P22)
		(adj P35 P36)
		(adj P35 P34)
		(adj P35 P23)
		(adj P36 P35)
		(adj P36 P24)
		(pos P1)
	)
	(:goal
		(and
			(pos P30)
		)
	)
)
