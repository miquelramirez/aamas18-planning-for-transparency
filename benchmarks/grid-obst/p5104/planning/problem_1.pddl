(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50)
	(:init
		(adj P2 P3)
		(adj P2 P7)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P8)
		(adj P6 P7)
		(adj P6 P11)
		(adj P8 P9)
		(adj P8 P3)
		(adj P8 P13)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P14)
		(adj P10 P9)
		(adj P10 P15)
		(adj P11 P12)
		(adj P11 P6)
		(adj P11 P16)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P17)
		(adj P14 P15)
		(adj P14 P9)
		(adj P14 P19)
		(adj P18 P19)
		(adj P18 P23)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P14)
		(adj P19 P24)
		(adj P20 P19)
		(adj P20 P25)
		(adj P21 P22)
		(adj P21 P26)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P27)
		(adj P24 P25)
		(adj P24 P19)
		(adj P24 P29)
		(adj P25 P24)
		(adj P25 P20)
		(adj P25 P30)
		(adj P26 P27)
		(adj P26 P21)
		(adj P26 P31)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P22)
		(adj P27 P32)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P33)
		(adj P31 P32)
		(adj P31 P26)
		(adj P31 P36)
		(adj P33 P34)
		(adj P33 P28)
		(adj P33 P38)
		(adj P35 P40)
		(adj P36 P37)
		(adj P36 P31)
		(adj P36 P41)
		(adj P38 P39)
		(adj P38 P33)
		(adj P38 P43)
		(adj P39 P40)
		(adj P39 P38)
		(adj P39 P44)
		(adj P40 P39)
		(adj P40 P35)
		(adj P40 P45)
		(adj P45 P40)
		(adj P45 P50)
		(adj P46 P47)
		(adj P47 P48)
		(adj P47 P46)
		(adj P48 P49)
		(adj P48 P47)
		(adj P49 P50)
		(adj P49 P48)
		(adj P50 P49)
		(adj P50 P45)
		(pos P41)
	)
	(:goal
		(and
			(pos P8)
		)
	)
)
