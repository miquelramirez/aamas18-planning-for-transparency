(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50 P51 P52 P53 P54 P55 P56 P57 P58 P59 P60 P61 P62 P63 P64 P65 P66 P67 P68 P69 P70 P71 P72 P73 P74 P75 P76 P77 P78 P79 P80)
	(:init
		(adj P1 P2)
		(adj P1 P11)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P12)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P13)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P14)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P15)
		(adj P6 P7)
		(adj P6 P5)
		(adj P6 P16)
		(adj P7 P8)
		(adj P7 P6)
		(adj P7 P17)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P18)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P19)
		(adj P10 P9)
		(adj P10 P20)
		(adj P11 P12)
		(adj P11 P1)
		(adj P11 P21)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P2)
		(adj P12 P22)
		(adj P13 P14)
		(adj P13 P12)
		(adj P13 P3)
		(adj P13 P23)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P4)
		(adj P14 P24)
		(adj P15 P16)
		(adj P15 P14)
		(adj P15 P5)
		(adj P15 P25)
		(adj P16 P17)
		(adj P16 P15)
		(adj P16 P6)
		(adj P16 P26)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P7)
		(adj P17 P27)
		(adj P18 P19)
		(adj P18 P17)
		(adj P18 P8)
		(adj P18 P28)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P9)
		(adj P19 P29)
		(adj P20 P19)
		(adj P20 P10)
		(adj P20 P30)
		(adj P21 P22)
		(adj P21 P11)
		(adj P21 P31)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P12)
		(adj P22 P32)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P13)
		(adj P23 P33)
		(adj P24 P25)
		(adj P24 P23)
		(adj P24 P14)
		(adj P24 P34)
		(adj P25 P26)
		(adj P25 P24)
		(adj P25 P15)
		(adj P25 P35)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P16)
		(adj P26 P36)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P17)
		(adj P27 P37)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P18)
		(adj P28 P38)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P19)
		(adj P29 P39)
		(adj P30 P29)
		(adj P30 P20)
		(adj P30 P40)
		(adj P31 P32)
		(adj P31 P21)
		(adj P31 P41)
		(adj P32 P33)
		(adj P32 P31)
		(adj P32 P22)
		(adj P32 P42)
		(adj P33 P34)
		(adj P33 P32)
		(adj P33 P23)
		(adj P33 P43)
		(adj P34 P35)
		(adj P34 P33)
		(adj P34 P24)
		(adj P34 P44)
		(adj P35 P36)
		(adj P35 P34)
		(adj P35 P25)
		(adj P35 P45)
		(adj P36 P37)
		(adj P36 P35)
		(adj P36 P26)
		(adj P36 P46)
		(adj P37 P38)
		(adj P37 P36)
		(adj P37 P27)
		(adj P37 P47)
		(adj P38 P39)
		(adj P38 P37)
		(adj P38 P28)
		(adj P38 P48)
		(adj P39 P40)
		(adj P39 P38)
		(adj P39 P29)
		(adj P39 P49)
		(adj P40 P39)
		(adj P40 P30)
		(adj P40 P50)
		(adj P41 P42)
		(adj P41 P31)
		(adj P41 P51)
		(adj P42 P43)
		(adj P42 P41)
		(adj P42 P32)
		(adj P42 P52)
		(adj P43 P44)
		(adj P43 P42)
		(adj P43 P33)
		(adj P43 P53)
		(adj P44 P45)
		(adj P44 P43)
		(adj P44 P34)
		(adj P44 P54)
		(adj P45 P46)
		(adj P45 P44)
		(adj P45 P35)
		(adj P45 P55)
		(adj P46 P47)
		(adj P46 P45)
		(adj P46 P36)
		(adj P46 P56)
		(adj P47 P48)
		(adj P47 P46)
		(adj P47 P37)
		(adj P47 P57)
		(adj P48 P49)
		(adj P48 P47)
		(adj P48 P38)
		(adj P48 P58)
		(adj P49 P50)
		(adj P49 P48)
		(adj P49 P39)
		(adj P49 P59)
		(adj P50 P49)
		(adj P50 P40)
		(adj P50 P60)
		(adj P51 P52)
		(adj P51 P41)
		(adj P51 P61)
		(adj P52 P53)
		(adj P52 P51)
		(adj P52 P42)
		(adj P52 P62)
		(adj P53 P54)
		(adj P53 P52)
		(adj P53 P43)
		(adj P53 P63)
		(adj P54 P55)
		(adj P54 P53)
		(adj P54 P44)
		(adj P54 P64)
		(adj P55 P56)
		(adj P55 P54)
		(adj P55 P45)
		(adj P55 P65)
		(adj P56 P57)
		(adj P56 P55)
		(adj P56 P46)
		(adj P56 P66)
		(adj P57 P58)
		(adj P57 P56)
		(adj P57 P47)
		(adj P57 P67)
		(adj P58 P59)
		(adj P58 P57)
		(adj P58 P48)
		(adj P58 P68)
		(adj P59 P60)
		(adj P59 P58)
		(adj P59 P49)
		(adj P59 P69)
		(adj P60 P59)
		(adj P60 P50)
		(adj P60 P70)
		(adj P61 P62)
		(adj P61 P51)
		(adj P61 P71)
		(adj P62 P63)
		(adj P62 P61)
		(adj P62 P52)
		(adj P62 P72)
		(adj P63 P64)
		(adj P63 P62)
		(adj P63 P53)
		(adj P63 P73)
		(adj P64 P65)
		(adj P64 P63)
		(adj P64 P54)
		(adj P64 P74)
		(adj P65 P66)
		(adj P65 P64)
		(adj P65 P55)
		(adj P65 P75)
		(adj P66 P67)
		(adj P66 P65)
		(adj P66 P56)
		(adj P66 P76)
		(adj P67 P68)
		(adj P67 P66)
		(adj P67 P57)
		(adj P67 P77)
		(adj P68 P69)
		(adj P68 P67)
		(adj P68 P58)
		(adj P68 P78)
		(adj P69 P70)
		(adj P69 P68)
		(adj P69 P59)
		(adj P69 P79)
		(adj P70 P69)
		(adj P70 P60)
		(adj P70 P80)
		(adj P71 P72)
		(adj P71 P61)
		(adj P72 P73)
		(adj P72 P71)
		(adj P72 P62)
		(adj P73 P74)
		(adj P73 P72)
		(adj P73 P63)
		(adj P74 P75)
		(adj P74 P73)
		(adj P74 P64)
		(adj P75 P76)
		(adj P75 P74)
		(adj P75 P65)
		(adj P76 P77)
		(adj P76 P75)
		(adj P76 P66)
		(adj P77 P78)
		(adj P77 P76)
		(adj P77 P67)
		(adj P78 P79)
		(adj P78 P77)
		(adj P78 P68)
		(adj P79 P80)
		(adj P79 P78)
		(adj P79 P69)
		(adj P80 P79)
		(adj P80 P70)
		(pos P66)
	)
	(:goal
		(and
			(pos P12)
		)
	)
)
