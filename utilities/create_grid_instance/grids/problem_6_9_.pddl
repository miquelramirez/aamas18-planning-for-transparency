(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50 P51 P52 P53 P54)
	(:init
		(adj P1 P2)
		(adj P1 P7)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P8)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P9)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P10)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P11)
		(adj P6 P5)
		(adj P6 P12)
		(adj P7 P8)
		(adj P7 P1)
		(adj P7 P13)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P2)
		(adj P8 P14)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P3)
		(adj P9 P15)
		(adj P10 P11)
		(adj P10 P9)
		(adj P10 P4)
		(adj P10 P16)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P5)
		(adj P11 P17)
		(adj P12 P11)
		(adj P12 P6)
		(adj P12 P18)
		(adj P13 P14)
		(adj P13 P7)
		(adj P13 P19)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P8)
		(adj P14 P20)
		(adj P15 P16)
		(adj P15 P14)
		(adj P15 P9)
		(adj P15 P21)
		(adj P16 P17)
		(adj P16 P15)
		(adj P16 P10)
		(adj P16 P22)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P11)
		(adj P17 P23)
		(adj P18 P17)
		(adj P18 P12)
		(adj P18 P24)
		(adj P19 P20)
		(adj P19 P13)
		(adj P19 P25)
		(adj P20 P21)
		(adj P20 P19)
		(adj P20 P14)
		(adj P20 P26)
		(adj P21 P22)
		(adj P21 P20)
		(adj P21 P15)
		(adj P21 P27)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P16)
		(adj P22 P28)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P17)
		(adj P23 P29)
		(adj P24 P23)
		(adj P24 P18)
		(adj P24 P30)
		(adj P25 P26)
		(adj P25 P19)
		(adj P25 P31)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P20)
		(adj P26 P32)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P21)
		(adj P27 P33)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P22)
		(adj P28 P34)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P23)
		(adj P29 P35)
		(adj P30 P29)
		(adj P30 P24)
		(adj P30 P36)
		(adj P31 P32)
		(adj P31 P25)
		(adj P31 P37)
		(adj P32 P33)
		(adj P32 P31)
		(adj P32 P26)
		(adj P32 P38)
		(adj P33 P34)
		(adj P33 P32)
		(adj P33 P27)
		(adj P33 P39)
		(adj P34 P35)
		(adj P34 P33)
		(adj P34 P28)
		(adj P34 P40)
		(adj P35 P36)
		(adj P35 P34)
		(adj P35 P29)
		(adj P35 P41)
		(adj P36 P35)
		(adj P36 P30)
		(adj P36 P42)
		(adj P37 P38)
		(adj P37 P31)
		(adj P37 P43)
		(adj P38 P39)
		(adj P38 P37)
		(adj P38 P32)
		(adj P38 P44)
		(adj P39 P40)
		(adj P39 P38)
		(adj P39 P33)
		(adj P39 P45)
		(adj P40 P41)
		(adj P40 P39)
		(adj P40 P34)
		(adj P40 P46)
		(adj P41 P42)
		(adj P41 P40)
		(adj P41 P35)
		(adj P41 P47)
		(adj P42 P41)
		(adj P42 P36)
		(adj P42 P48)
		(adj P43 P44)
		(adj P43 P37)
		(adj P43 P49)
		(adj P44 P45)
		(adj P44 P43)
		(adj P44 P38)
		(adj P44 P50)
		(adj P45 P46)
		(adj P45 P44)
		(adj P45 P39)
		(adj P45 P51)
		(adj P46 P47)
		(adj P46 P45)
		(adj P46 P40)
		(adj P46 P52)
		(adj P47 P48)
		(adj P47 P46)
		(adj P47 P41)
		(adj P47 P53)
		(adj P48 P47)
		(adj P48 P42)
		(adj P48 P54)
		(adj P49 P50)
		(adj P49 P43)
		(adj P50 P51)
		(adj P50 P49)
		(adj P50 P44)
		(adj P51 P52)
		(adj P51 P50)
		(adj P51 P45)
		(adj P52 P53)
		(adj P52 P51)
		(adj P52 P46)
		(adj P53 P54)
		(adj P53 P52)
		(adj P53 P47)
		(adj P54 P53)
		(adj P54 P48)
		(pos P1)
	)
	(:goal
		(and
			(pos P45)
		)
	)
)
