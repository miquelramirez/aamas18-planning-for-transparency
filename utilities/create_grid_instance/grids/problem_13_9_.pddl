(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50 P51 P52 P53 P54 P55 P56 P57 P58 P59 P60 P61 P62 P63 P64 P65 P66 P67 P68 P69 P70 P71 P72 P73 P74 P75 P76 P77 P78 P79 P80 P81 P82 P83 P84 P85 P86 P87 P88 P89 P90 P91 P92 P93 P94 P95 P96 P97 P98 P99 P100 P101 P102 P103 P104 P105 P106 P107 P108 P109 P110 P111 P112 P113 P114 P115 P116 P117)
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
		(adj P53 P66)
		(adj P54 P55)
		(adj P54 P53)
		(adj P54 P41)
		(adj P54 P67)
		(adj P55 P56)
		(adj P55 P54)
		(adj P55 P42)
		(adj P55 P68)
		(adj P56 P57)
		(adj P56 P55)
		(adj P56 P43)
		(adj P56 P69)
		(adj P57 P58)
		(adj P57 P56)
		(adj P57 P44)
		(adj P57 P70)
		(adj P58 P59)
		(adj P58 P57)
		(adj P58 P45)
		(adj P58 P71)
		(adj P59 P60)
		(adj P59 P58)
		(adj P59 P46)
		(adj P59 P72)
		(adj P60 P61)
		(adj P60 P59)
		(adj P60 P47)
		(adj P60 P73)
		(adj P61 P62)
		(adj P61 P60)
		(adj P61 P48)
		(adj P61 P74)
		(adj P62 P63)
		(adj P62 P61)
		(adj P62 P49)
		(adj P62 P75)
		(adj P63 P64)
		(adj P63 P62)
		(adj P63 P50)
		(adj P63 P76)
		(adj P64 P65)
		(adj P64 P63)
		(adj P64 P51)
		(adj P64 P77)
		(adj P65 P64)
		(adj P65 P52)
		(adj P65 P78)
		(adj P66 P67)
		(adj P66 P53)
		(adj P66 P79)
		(adj P67 P68)
		(adj P67 P66)
		(adj P67 P54)
		(adj P67 P80)
		(adj P68 P69)
		(adj P68 P67)
		(adj P68 P55)
		(adj P68 P81)
		(adj P69 P70)
		(adj P69 P68)
		(adj P69 P56)
		(adj P69 P82)
		(adj P70 P71)
		(adj P70 P69)
		(adj P70 P57)
		(adj P70 P83)
		(adj P71 P72)
		(adj P71 P70)
		(adj P71 P58)
		(adj P71 P84)
		(adj P72 P73)
		(adj P72 P71)
		(adj P72 P59)
		(adj P72 P85)
		(adj P73 P74)
		(adj P73 P72)
		(adj P73 P60)
		(adj P73 P86)
		(adj P74 P75)
		(adj P74 P73)
		(adj P74 P61)
		(adj P74 P87)
		(adj P75 P76)
		(adj P75 P74)
		(adj P75 P62)
		(adj P75 P88)
		(adj P76 P77)
		(adj P76 P75)
		(adj P76 P63)
		(adj P76 P89)
		(adj P77 P78)
		(adj P77 P76)
		(adj P77 P64)
		(adj P77 P90)
		(adj P78 P77)
		(adj P78 P65)
		(adj P78 P91)
		(adj P79 P80)
		(adj P79 P66)
		(adj P79 P92)
		(adj P80 P81)
		(adj P80 P79)
		(adj P80 P67)
		(adj P80 P93)
		(adj P81 P82)
		(adj P81 P80)
		(adj P81 P68)
		(adj P81 P94)
		(adj P82 P83)
		(adj P82 P81)
		(adj P82 P69)
		(adj P82 P95)
		(adj P83 P84)
		(adj P83 P82)
		(adj P83 P70)
		(adj P83 P96)
		(adj P84 P85)
		(adj P84 P83)
		(adj P84 P71)
		(adj P84 P97)
		(adj P85 P86)
		(adj P85 P84)
		(adj P85 P72)
		(adj P85 P98)
		(adj P86 P87)
		(adj P86 P85)
		(adj P86 P73)
		(adj P86 P99)
		(adj P87 P88)
		(adj P87 P86)
		(adj P87 P74)
		(adj P87 P100)
		(adj P88 P89)
		(adj P88 P87)
		(adj P88 P75)
		(adj P88 P101)
		(adj P89 P90)
		(adj P89 P88)
		(adj P89 P76)
		(adj P89 P102)
		(adj P90 P91)
		(adj P90 P89)
		(adj P90 P77)
		(adj P90 P103)
		(adj P91 P90)
		(adj P91 P78)
		(adj P91 P104)
		(adj P92 P93)
		(adj P92 P79)
		(adj P92 P105)
		(adj P93 P94)
		(adj P93 P92)
		(adj P93 P80)
		(adj P93 P106)
		(adj P94 P95)
		(adj P94 P93)
		(adj P94 P81)
		(adj P94 P107)
		(adj P95 P96)
		(adj P95 P94)
		(adj P95 P82)
		(adj P95 P108)
		(adj P96 P97)
		(adj P96 P95)
		(adj P96 P83)
		(adj P96 P109)
		(adj P97 P98)
		(adj P97 P96)
		(adj P97 P84)
		(adj P97 P110)
		(adj P98 P99)
		(adj P98 P97)
		(adj P98 P85)
		(adj P98 P111)
		(adj P99 P100)
		(adj P99 P98)
		(adj P99 P86)
		(adj P99 P112)
		(adj P100 P101)
		(adj P100 P99)
		(adj P100 P87)
		(adj P100 P113)
		(adj P101 P102)
		(adj P101 P100)
		(adj P101 P88)
		(adj P101 P114)
		(adj P102 P103)
		(adj P102 P101)
		(adj P102 P89)
		(adj P102 P115)
		(adj P103 P104)
		(adj P103 P102)
		(adj P103 P90)
		(adj P103 P116)
		(adj P104 P103)
		(adj P104 P91)
		(adj P104 P117)
		(adj P105 P106)
		(adj P105 P92)
		(adj P106 P107)
		(adj P106 P105)
		(adj P106 P93)
		(adj P107 P108)
		(adj P107 P106)
		(adj P107 P94)
		(adj P108 P109)
		(adj P108 P107)
		(adj P108 P95)
		(adj P109 P110)
		(adj P109 P108)
		(adj P109 P96)
		(adj P110 P111)
		(adj P110 P109)
		(adj P110 P97)
		(adj P111 P112)
		(adj P111 P110)
		(adj P111 P98)
		(adj P112 P113)
		(adj P112 P111)
		(adj P112 P99)
		(adj P113 P114)
		(adj P113 P112)
		(adj P113 P100)
		(adj P114 P115)
		(adj P114 P113)
		(adj P114 P101)
		(adj P115 P116)
		(adj P115 P114)
		(adj P115 P102)
		(adj P116 P117)
		(adj P116 P115)
		(adj P116 P103)
		(adj P117 P116)
		(adj P117 P104)
		(pos P1)
	)
	(:goal
		(and
			(pos P96)
		)
	)
)
