(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50 P51 P52 P53 P54 P55 P56 P57 P58 P59 P60 P61 P62 P63 P64 P65 P66 P67 P68 P69 P70 P71 P72 P73 P74 P75 P76 P77 P78 P79 P80 P81 P82 P83 P84 P85 P86 P87 P88 P89 P90 P91 P92 P93 P94 P95 P96 P97 P98 P99 P100 P101 P102 P103 P104 P105 P106 P107 P108 P109 P110 P111 P112 P113 P114 P115 P116 P117 P118 P119 P120 P121 P122 P123 P124 P125 P126)
	(:init
		(adj P1 P2)
		(adj P1 P15)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P16)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P17)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P18)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P19)
		(adj P6 P7)
		(adj P6 P5)
		(adj P6 P20)
		(adj P7 P8)
		(adj P7 P6)
		(adj P7 P21)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P22)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P23)
		(adj P10 P11)
		(adj P10 P9)
		(adj P10 P24)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P25)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P26)
		(adj P13 P14)
		(adj P13 P12)
		(adj P13 P27)
		(adj P14 P13)
		(adj P14 P28)
		(adj P15 P16)
		(adj P15 P1)
		(adj P15 P29)
		(adj P16 P17)
		(adj P16 P15)
		(adj P16 P2)
		(adj P16 P30)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P3)
		(adj P17 P31)
		(adj P18 P19)
		(adj P18 P17)
		(adj P18 P4)
		(adj P18 P32)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P5)
		(adj P19 P33)
		(adj P20 P21)
		(adj P20 P19)
		(adj P20 P6)
		(adj P20 P34)
		(adj P21 P22)
		(adj P21 P20)
		(adj P21 P7)
		(adj P21 P35)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P8)
		(adj P22 P36)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P9)
		(adj P23 P37)
		(adj P24 P25)
		(adj P24 P23)
		(adj P24 P10)
		(adj P24 P38)
		(adj P25 P26)
		(adj P25 P24)
		(adj P25 P11)
		(adj P25 P39)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P12)
		(adj P26 P40)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P13)
		(adj P27 P41)
		(adj P28 P27)
		(adj P28 P14)
		(adj P28 P42)
		(adj P29 P30)
		(adj P29 P15)
		(adj P29 P43)
		(adj P30 P31)
		(adj P30 P29)
		(adj P30 P16)
		(adj P30 P44)
		(adj P31 P32)
		(adj P31 P30)
		(adj P31 P17)
		(adj P31 P45)
		(adj P32 P33)
		(adj P32 P31)
		(adj P32 P18)
		(adj P32 P46)
		(adj P33 P34)
		(adj P33 P32)
		(adj P33 P19)
		(adj P33 P47)
		(adj P34 P35)
		(adj P34 P33)
		(adj P34 P20)
		(adj P34 P48)
		(adj P35 P36)
		(adj P35 P34)
		(adj P35 P21)
		(adj P35 P49)
		(adj P36 P37)
		(adj P36 P35)
		(adj P36 P22)
		(adj P36 P50)
		(adj P37 P38)
		(adj P37 P36)
		(adj P37 P23)
		(adj P37 P51)
		(adj P38 P39)
		(adj P38 P37)
		(adj P38 P24)
		(adj P38 P52)
		(adj P39 P40)
		(adj P39 P38)
		(adj P39 P25)
		(adj P39 P53)
		(adj P40 P41)
		(adj P40 P39)
		(adj P40 P26)
		(adj P40 P54)
		(adj P41 P42)
		(adj P41 P40)
		(adj P41 P27)
		(adj P41 P55)
		(adj P42 P41)
		(adj P42 P28)
		(adj P42 P56)
		(adj P43 P44)
		(adj P43 P29)
		(adj P43 P57)
		(adj P44 P45)
		(adj P44 P43)
		(adj P44 P30)
		(adj P44 P58)
		(adj P45 P46)
		(adj P45 P44)
		(adj P45 P31)
		(adj P45 P59)
		(adj P46 P47)
		(adj P46 P45)
		(adj P46 P32)
		(adj P46 P60)
		(adj P47 P48)
		(adj P47 P46)
		(adj P47 P33)
		(adj P47 P61)
		(adj P48 P49)
		(adj P48 P47)
		(adj P48 P34)
		(adj P48 P62)
		(adj P49 P50)
		(adj P49 P48)
		(adj P49 P35)
		(adj P49 P63)
		(adj P50 P51)
		(adj P50 P49)
		(adj P50 P36)
		(adj P50 P64)
		(adj P51 P52)
		(adj P51 P50)
		(adj P51 P37)
		(adj P51 P65)
		(adj P52 P53)
		(adj P52 P51)
		(adj P52 P38)
		(adj P52 P66)
		(adj P53 P54)
		(adj P53 P52)
		(adj P53 P39)
		(adj P53 P67)
		(adj P54 P55)
		(adj P54 P53)
		(adj P54 P40)
		(adj P54 P68)
		(adj P55 P56)
		(adj P55 P54)
		(adj P55 P41)
		(adj P55 P69)
		(adj P56 P55)
		(adj P56 P42)
		(adj P56 P70)
		(adj P57 P58)
		(adj P57 P43)
		(adj P57 P71)
		(adj P58 P59)
		(adj P58 P57)
		(adj P58 P44)
		(adj P58 P72)
		(adj P59 P60)
		(adj P59 P58)
		(adj P59 P45)
		(adj P59 P73)
		(adj P60 P61)
		(adj P60 P59)
		(adj P60 P46)
		(adj P60 P74)
		(adj P61 P62)
		(adj P61 P60)
		(adj P61 P47)
		(adj P61 P75)
		(adj P62 P63)
		(adj P62 P61)
		(adj P62 P48)
		(adj P62 P76)
		(adj P63 P64)
		(adj P63 P62)
		(adj P63 P49)
		(adj P63 P77)
		(adj P64 P65)
		(adj P64 P63)
		(adj P64 P50)
		(adj P64 P78)
		(adj P65 P66)
		(adj P65 P64)
		(adj P65 P51)
		(adj P65 P79)
		(adj P66 P67)
		(adj P66 P65)
		(adj P66 P52)
		(adj P66 P80)
		(adj P67 P68)
		(adj P67 P66)
		(adj P67 P53)
		(adj P67 P81)
		(adj P68 P69)
		(adj P68 P67)
		(adj P68 P54)
		(adj P68 P82)
		(adj P69 P70)
		(adj P69 P68)
		(adj P69 P55)
		(adj P69 P83)
		(adj P70 P69)
		(adj P70 P56)
		(adj P70 P84)
		(adj P71 P72)
		(adj P71 P57)
		(adj P71 P85)
		(adj P72 P73)
		(adj P72 P71)
		(adj P72 P58)
		(adj P72 P86)
		(adj P73 P74)
		(adj P73 P72)
		(adj P73 P59)
		(adj P73 P87)
		(adj P74 P75)
		(adj P74 P73)
		(adj P74 P60)
		(adj P74 P88)
		(adj P75 P76)
		(adj P75 P74)
		(adj P75 P61)
		(adj P75 P89)
		(adj P76 P77)
		(adj P76 P75)
		(adj P76 P62)
		(adj P76 P90)
		(adj P77 P78)
		(adj P77 P76)
		(adj P77 P63)
		(adj P77 P91)
		(adj P78 P79)
		(adj P78 P77)
		(adj P78 P64)
		(adj P78 P92)
		(adj P79 P80)
		(adj P79 P78)
		(adj P79 P65)
		(adj P79 P93)
		(adj P80 P81)
		(adj P80 P79)
		(adj P80 P66)
		(adj P80 P94)
		(adj P81 P82)
		(adj P81 P80)
		(adj P81 P67)
		(adj P81 P95)
		(adj P82 P83)
		(adj P82 P81)
		(adj P82 P68)
		(adj P82 P96)
		(adj P83 P84)
		(adj P83 P82)
		(adj P83 P69)
		(adj P83 P97)
		(adj P84 P83)
		(adj P84 P70)
		(adj P84 P98)
		(adj P85 P86)
		(adj P85 P71)
		(adj P85 P99)
		(adj P86 P87)
		(adj P86 P85)
		(adj P86 P72)
		(adj P86 P100)
		(adj P87 P88)
		(adj P87 P86)
		(adj P87 P73)
		(adj P87 P101)
		(adj P88 P89)
		(adj P88 P87)
		(adj P88 P74)
		(adj P88 P102)
		(adj P89 P90)
		(adj P89 P88)
		(adj P89 P75)
		(adj P89 P103)
		(adj P90 P91)
		(adj P90 P89)
		(adj P90 P76)
		(adj P90 P104)
		(adj P91 P92)
		(adj P91 P90)
		(adj P91 P77)
		(adj P91 P105)
		(adj P92 P93)
		(adj P92 P91)
		(adj P92 P78)
		(adj P92 P106)
		(adj P93 P94)
		(adj P93 P92)
		(adj P93 P79)
		(adj P93 P107)
		(adj P94 P95)
		(adj P94 P93)
		(adj P94 P80)
		(adj P94 P108)
		(adj P95 P96)
		(adj P95 P94)
		(adj P95 P81)
		(adj P95 P109)
		(adj P96 P97)
		(adj P96 P95)
		(adj P96 P82)
		(adj P96 P110)
		(adj P97 P98)
		(adj P97 P96)
		(adj P97 P83)
		(adj P97 P111)
		(adj P98 P97)
		(adj P98 P84)
		(adj P98 P112)
		(adj P99 P100)
		(adj P99 P85)
		(adj P99 P113)
		(adj P100 P101)
		(adj P100 P99)
		(adj P100 P86)
		(adj P100 P114)
		(adj P101 P102)
		(adj P101 P100)
		(adj P101 P87)
		(adj P101 P115)
		(adj P102 P103)
		(adj P102 P101)
		(adj P102 P88)
		(adj P102 P116)
		(adj P103 P104)
		(adj P103 P102)
		(adj P103 P89)
		(adj P103 P117)
		(adj P104 P105)
		(adj P104 P103)
		(adj P104 P90)
		(adj P104 P118)
		(adj P105 P106)
		(adj P105 P104)
		(adj P105 P91)
		(adj P105 P119)
		(adj P106 P107)
		(adj P106 P105)
		(adj P106 P92)
		(adj P106 P120)
		(adj P107 P108)
		(adj P107 P106)
		(adj P107 P93)
		(adj P107 P121)
		(adj P108 P109)
		(adj P108 P107)
		(adj P108 P94)
		(adj P108 P122)
		(adj P109 P110)
		(adj P109 P108)
		(adj P109 P95)
		(adj P109 P123)
		(adj P110 P111)
		(adj P110 P109)
		(adj P110 P96)
		(adj P110 P124)
		(adj P111 P112)
		(adj P111 P110)
		(adj P111 P97)
		(adj P111 P125)
		(adj P112 P111)
		(adj P112 P98)
		(adj P112 P126)
		(adj P113 P114)
		(adj P113 P99)
		(adj P114 P115)
		(adj P114 P113)
		(adj P114 P100)
		(adj P115 P116)
		(adj P115 P114)
		(adj P115 P101)
		(adj P116 P117)
		(adj P116 P115)
		(adj P116 P102)
		(adj P117 P118)
		(adj P117 P116)
		(adj P117 P103)
		(adj P118 P119)
		(adj P118 P117)
		(adj P118 P104)
		(adj P119 P120)
		(adj P119 P118)
		(adj P119 P105)
		(adj P120 P121)
		(adj P120 P119)
		(adj P120 P106)
		(adj P121 P122)
		(adj P121 P120)
		(adj P121 P107)
		(adj P122 P123)
		(adj P122 P121)
		(adj P122 P108)
		(adj P123 P124)
		(adj P123 P122)
		(adj P123 P109)
		(adj P124 P125)
		(adj P124 P123)
		(adj P124 P110)
		(adj P125 P126)
		(adj P125 P124)
		(adj P125 P111)
		(adj P126 P125)
		(adj P126 P112)
		(pos P1)
	)
	(:goal
		(and
			(pos P103)
		)
	)
)