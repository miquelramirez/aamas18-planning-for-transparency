(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50 P51 P52 P53 P54 P55 P56 P57 P58 P59 P60 P61 P62 P63 P64 P65)
	(:init
		(adj P1 P2)
		(adj P1 P14)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P15)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P16)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P17)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P18)
		(adj P6 P7)
		(adj P6 P5)
		(adj P6 P19)
		(adj P7 P8)
		(adj P7 P6)
		(adj P7 P20)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P21)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P22)
		(adj P10 P11)
		(adj P10 P9)
		(adj P10 P23)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P24)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P25)
		(adj P13 P12)
		(adj P13 P26)
		(adj P14 P15)
		(adj P14 P1)
		(adj P14 P27)
		(adj P15 P16)
		(adj P15 P14)
		(adj P15 P2)
		(adj P15 P28)
		(adj P16 P17)
		(adj P16 P15)
		(adj P16 P3)
		(adj P16 P29)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P4)
		(adj P17 P30)
		(adj P18 P19)
		(adj P18 P17)
		(adj P18 P5)
		(adj P18 P31)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P6)
		(adj P19 P32)
		(adj P20 P21)
		(adj P20 P19)
		(adj P20 P7)
		(adj P20 P33)
		(adj P21 P22)
		(adj P21 P20)
		(adj P21 P8)
		(adj P21 P34)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P9)
		(adj P22 P35)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P10)
		(adj P23 P36)
		(adj P24 P25)
		(adj P24 P23)
		(adj P24 P11)
		(adj P24 P37)
		(adj P25 P26)
		(adj P25 P24)
		(adj P25 P12)
		(adj P25 P38)
		(adj P26 P25)
		(adj P26 P13)
		(adj P26 P39)
		(adj P27 P28)
		(adj P27 P14)
		(adj P27 P40)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P15)
		(adj P28 P41)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P16)
		(adj P29 P42)
		(adj P30 P31)
		(adj P30 P29)
		(adj P30 P17)
		(adj P30 P43)
		(adj P31 P32)
		(adj P31 P30)
		(adj P31 P18)
		(adj P31 P44)
		(adj P32 P33)
		(adj P32 P31)
		(adj P32 P19)
		(adj P32 P45)
		(adj P33 P34)
		(adj P33 P32)
		(adj P33 P20)
		(adj P33 P46)
		(adj P34 P35)
		(adj P34 P33)
		(adj P34 P21)
		(adj P34 P47)
		(adj P35 P36)
		(adj P35 P34)
		(adj P35 P22)
		(adj P35 P48)
		(adj P36 P37)
		(adj P36 P35)
		(adj P36 P23)
		(adj P36 P49)
		(adj P37 P38)
		(adj P37 P36)
		(adj P37 P24)
		(adj P37 P50)
		(adj P38 P39)
		(adj P38 P37)
		(adj P38 P25)
		(adj P38 P51)
		(adj P39 P38)
		(adj P39 P26)
		(adj P39 P52)
		(adj P40 P41)
		(adj P40 P27)
		(adj P40 P53)
		(adj P41 P42)
		(adj P41 P40)
		(adj P41 P28)
		(adj P41 P54)
		(adj P42 P43)
		(adj P42 P41)
		(adj P42 P29)
		(adj P42 P55)
		(adj P43 P44)
		(adj P43 P42)
		(adj P43 P30)
		(adj P43 P56)
		(adj P44 P45)
		(adj P44 P43)
		(adj P44 P31)
		(adj P44 P57)
		(adj P45 P46)
		(adj P45 P44)
		(adj P45 P32)
		(adj P45 P58)
		(adj P46 P47)
		(adj P46 P45)
		(adj P46 P33)
		(adj P46 P59)
		(adj P47 P48)
		(adj P47 P46)
		(adj P47 P34)
		(adj P47 P60)
		(adj P48 P49)
		(adj P48 P47)
		(adj P48 P35)
		(adj P48 P61)
		(adj P49 P50)
		(adj P49 P48)
		(adj P49 P36)
		(adj P49 P62)
		(adj P50 P51)
		(adj P50 P49)
		(adj P50 P37)
		(adj P50 P63)
		(adj P51 P52)
		(adj P51 P50)
		(adj P51 P38)
		(adj P51 P64)
		(adj P52 P51)
		(adj P52 P39)
		(adj P52 P65)
		(adj P53 P54)
		(adj P53 P40)
		(adj P54 P55)
		(adj P54 P53)
		(adj P54 P41)
		(adj P55 P56)
		(adj P55 P54)
		(adj P55 P42)
		(adj P56 P57)
		(adj P56 P55)
		(adj P56 P43)
		(adj P57 P58)
		(adj P57 P56)
		(adj P57 P44)
		(adj P58 P59)
		(adj P58 P57)
		(adj P58 P45)
		(adj P59 P60)
		(adj P59 P58)
		(adj P59 P46)
		(adj P60 P61)
		(adj P60 P59)
		(adj P60 P47)
		(adj P61 P62)
		(adj P61 P60)
		(adj P61 P48)
		(adj P62 P63)
		(adj P62 P61)
		(adj P62 P49)
		(adj P63 P64)
		(adj P63 P62)
		(adj P63 P50)
		(adj P64 P65)
		(adj P64 P63)
		(adj P64 P51)
		(adj P65 P64)
		(adj P65 P52)
		(pos P1)
	)
	(:goal
		(and
			(pos P54)
		)
	)
)
