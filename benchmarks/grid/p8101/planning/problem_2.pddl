(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50 P51 P52 P53 P54 P55 P56 P57 P58 P59 P60 P61 P62 P63 P64 P65 P66 P67 P68 P69 P70 P71 P72 P73 P74 P75 P76 P77 P78 P79 P80)
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
		(adj P25 P33)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P18)
		(adj P26 P34)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P19)
		(adj P27 P35)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P20)
		(adj P28 P36)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P21)
		(adj P29 P37)
		(adj P30 P31)
		(adj P30 P29)
		(adj P30 P22)
		(adj P30 P38)
		(adj P31 P32)
		(adj P31 P30)
		(adj P31 P23)
		(adj P31 P39)
		(adj P32 P31)
		(adj P32 P24)
		(adj P32 P40)
		(adj P33 P34)
		(adj P33 P25)
		(adj P33 P41)
		(adj P34 P35)
		(adj P34 P33)
		(adj P34 P26)
		(adj P34 P42)
		(adj P35 P36)
		(adj P35 P34)
		(adj P35 P27)
		(adj P35 P43)
		(adj P36 P37)
		(adj P36 P35)
		(adj P36 P28)
		(adj P36 P44)
		(adj P37 P38)
		(adj P37 P36)
		(adj P37 P29)
		(adj P37 P45)
		(adj P38 P39)
		(adj P38 P37)
		(adj P38 P30)
		(adj P38 P46)
		(adj P39 P40)
		(adj P39 P38)
		(adj P39 P31)
		(adj P39 P47)
		(adj P40 P39)
		(adj P40 P32)
		(adj P40 P48)
		(adj P41 P42)
		(adj P41 P33)
		(adj P41 P49)
		(adj P42 P43)
		(adj P42 P41)
		(adj P42 P34)
		(adj P42 P50)
		(adj P43 P44)
		(adj P43 P42)
		(adj P43 P35)
		(adj P43 P51)
		(adj P44 P45)
		(adj P44 P43)
		(adj P44 P36)
		(adj P44 P52)
		(adj P45 P46)
		(adj P45 P44)
		(adj P45 P37)
		(adj P45 P53)
		(adj P46 P47)
		(adj P46 P45)
		(adj P46 P38)
		(adj P46 P54)
		(adj P47 P48)
		(adj P47 P46)
		(adj P47 P39)
		(adj P47 P55)
		(adj P48 P47)
		(adj P48 P40)
		(adj P48 P56)
		(adj P49 P50)
		(adj P49 P41)
		(adj P49 P57)
		(adj P50 P51)
		(adj P50 P49)
		(adj P50 P42)
		(adj P50 P58)
		(adj P51 P52)
		(adj P51 P50)
		(adj P51 P43)
		(adj P51 P59)
		(adj P52 P53)
		(adj P52 P51)
		(adj P52 P44)
		(adj P52 P60)
		(adj P53 P54)
		(adj P53 P52)
		(adj P53 P45)
		(adj P53 P61)
		(adj P54 P55)
		(adj P54 P53)
		(adj P54 P46)
		(adj P54 P62)
		(adj P55 P56)
		(adj P55 P54)
		(adj P55 P47)
		(adj P55 P63)
		(adj P56 P55)
		(adj P56 P48)
		(adj P56 P64)
		(adj P57 P58)
		(adj P57 P49)
		(adj P57 P65)
		(adj P58 P59)
		(adj P58 P57)
		(adj P58 P50)
		(adj P58 P66)
		(adj P59 P60)
		(adj P59 P58)
		(adj P59 P51)
		(adj P59 P67)
		(adj P60 P61)
		(adj P60 P59)
		(adj P60 P52)
		(adj P60 P68)
		(adj P61 P62)
		(adj P61 P60)
		(adj P61 P53)
		(adj P61 P69)
		(adj P62 P63)
		(adj P62 P61)
		(adj P62 P54)
		(adj P62 P70)
		(adj P63 P64)
		(adj P63 P62)
		(adj P63 P55)
		(adj P63 P71)
		(adj P64 P63)
		(adj P64 P56)
		(adj P64 P72)
		(adj P65 P66)
		(adj P65 P57)
		(adj P65 P73)
		(adj P66 P67)
		(adj P66 P65)
		(adj P66 P58)
		(adj P66 P74)
		(adj P67 P68)
		(adj P67 P66)
		(adj P67 P59)
		(adj P67 P75)
		(adj P68 P69)
		(adj P68 P67)
		(adj P68 P60)
		(adj P68 P76)
		(adj P69 P70)
		(adj P69 P68)
		(adj P69 P61)
		(adj P69 P77)
		(adj P70 P71)
		(adj P70 P69)
		(adj P70 P62)
		(adj P70 P78)
		(adj P71 P72)
		(adj P71 P70)
		(adj P71 P63)
		(adj P71 P79)
		(adj P72 P71)
		(adj P72 P64)
		(adj P72 P80)
		(adj P73 P74)
		(adj P73 P65)
		(adj P74 P75)
		(adj P74 P73)
		(adj P74 P66)
		(adj P75 P76)
		(adj P75 P74)
		(adj P75 P67)
		(adj P76 P77)
		(adj P76 P75)
		(adj P76 P68)
		(adj P77 P78)
		(adj P77 P76)
		(adj P77 P69)
		(adj P78 P79)
		(adj P78 P77)
		(adj P78 P70)
		(adj P79 P80)
		(adj P79 P78)
		(adj P79 P71)
		(adj P80 P79)
		(adj P80 P72)
		(pos P66)
	)
	(:goal
		(and
			(pos P73)
		)
	)
)
