(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50 P51 P52 P53 P54 P55 P56 P57 P58 P59 P60 P61 P62 P63 P64 P65 P66 P67 P68 P69 P70 P71 P72 P73 P74 P75 P76 P77 P78 P79 P80 P81 P82 P83 P84 P85 P86 P87 P88 P89 P90 P91 P92 P93 P94 P95 P96 P97 P98 P99 P100 P101 P102 P103 P104 P105 P106 P107 P108 P109 P110 P111 P112 P113 P114 P115 P116 P117 P118 P119 P120 P121 P122 P123 P124 P125 P126 P127 P128 P129 P130 P131 P132 P133 P134 P135 P136 P137 P138 P139 P140 P141 P142 P143 P144)
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
		(adj P25 P37)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P14)
		(adj P26 P38)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P15)
		(adj P27 P39)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P16)
		(adj P28 P40)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P17)
		(adj P29 P41)
		(adj P30 P31)
		(adj P30 P29)
		(adj P30 P18)
		(adj P30 P42)
		(adj P31 P32)
		(adj P31 P30)
		(adj P31 P19)
		(adj P31 P43)
		(adj P32 P33)
		(adj P32 P31)
		(adj P32 P20)
		(adj P32 P44)
		(adj P33 P34)
		(adj P33 P32)
		(adj P33 P21)
		(adj P33 P45)
		(adj P34 P35)
		(adj P34 P33)
		(adj P34 P22)
		(adj P34 P46)
		(adj P35 P36)
		(adj P35 P34)
		(adj P35 P23)
		(adj P35 P47)
		(adj P36 P35)
		(adj P36 P24)
		(adj P36 P48)
		(adj P37 P38)
		(adj P37 P25)
		(adj P37 P49)
		(adj P38 P39)
		(adj P38 P37)
		(adj P38 P26)
		(adj P38 P50)
		(adj P39 P40)
		(adj P39 P38)
		(adj P39 P27)
		(adj P39 P51)
		(adj P40 P41)
		(adj P40 P39)
		(adj P40 P28)
		(adj P40 P52)
		(adj P41 P42)
		(adj P41 P40)
		(adj P41 P29)
		(adj P41 P53)
		(adj P42 P43)
		(adj P42 P41)
		(adj P42 P30)
		(adj P42 P54)
		(adj P43 P44)
		(adj P43 P42)
		(adj P43 P31)
		(adj P43 P55)
		(adj P44 P45)
		(adj P44 P43)
		(adj P44 P32)
		(adj P44 P56)
		(adj P45 P46)
		(adj P45 P44)
		(adj P45 P33)
		(adj P45 P57)
		(adj P46 P47)
		(adj P46 P45)
		(adj P46 P34)
		(adj P46 P58)
		(adj P47 P48)
		(adj P47 P46)
		(adj P47 P35)
		(adj P47 P59)
		(adj P48 P47)
		(adj P48 P36)
		(adj P48 P60)
		(adj P49 P50)
		(adj P49 P37)
		(adj P49 P61)
		(adj P50 P51)
		(adj P50 P49)
		(adj P50 P38)
		(adj P50 P62)
		(adj P51 P52)
		(adj P51 P50)
		(adj P51 P39)
		(adj P51 P63)
		(adj P52 P53)
		(adj P52 P51)
		(adj P52 P40)
		(adj P52 P64)
		(adj P53 P54)
		(adj P53 P52)
		(adj P53 P41)
		(adj P53 P65)
		(adj P54 P55)
		(adj P54 P53)
		(adj P54 P42)
		(adj P54 P66)
		(adj P55 P56)
		(adj P55 P54)
		(adj P55 P43)
		(adj P55 P67)
		(adj P56 P57)
		(adj P56 P55)
		(adj P56 P44)
		(adj P56 P68)
		(adj P57 P58)
		(adj P57 P56)
		(adj P57 P45)
		(adj P57 P69)
		(adj P58 P59)
		(adj P58 P57)
		(adj P58 P46)
		(adj P58 P70)
		(adj P59 P60)
		(adj P59 P58)
		(adj P59 P47)
		(adj P59 P71)
		(adj P60 P59)
		(adj P60 P48)
		(adj P60 P72)
		(adj P61 P62)
		(adj P61 P49)
		(adj P61 P73)
		(adj P62 P63)
		(adj P62 P61)
		(adj P62 P50)
		(adj P62 P74)
		(adj P63 P64)
		(adj P63 P62)
		(adj P63 P51)
		(adj P63 P75)
		(adj P64 P65)
		(adj P64 P63)
		(adj P64 P52)
		(adj P64 P76)
		(adj P65 P66)
		(adj P65 P64)
		(adj P65 P53)
		(adj P65 P77)
		(adj P66 P67)
		(adj P66 P65)
		(adj P66 P54)
		(adj P66 P78)
		(adj P67 P68)
		(adj P67 P66)
		(adj P67 P55)
		(adj P67 P79)
		(adj P68 P69)
		(adj P68 P67)
		(adj P68 P56)
		(adj P68 P80)
		(adj P69 P70)
		(adj P69 P68)
		(adj P69 P57)
		(adj P69 P81)
		(adj P70 P71)
		(adj P70 P69)
		(adj P70 P58)
		(adj P70 P82)
		(adj P71 P72)
		(adj P71 P70)
		(adj P71 P59)
		(adj P71 P83)
		(adj P72 P71)
		(adj P72 P60)
		(adj P72 P84)
		(adj P73 P74)
		(adj P73 P61)
		(adj P73 P85)
		(adj P74 P75)
		(adj P74 P73)
		(adj P74 P62)
		(adj P74 P86)
		(adj P75 P76)
		(adj P75 P74)
		(adj P75 P63)
		(adj P75 P87)
		(adj P76 P77)
		(adj P76 P75)
		(adj P76 P64)
		(adj P76 P88)
		(adj P77 P78)
		(adj P77 P76)
		(adj P77 P65)
		(adj P77 P89)
		(adj P78 P79)
		(adj P78 P77)
		(adj P78 P66)
		(adj P78 P90)
		(adj P79 P80)
		(adj P79 P78)
		(adj P79 P67)
		(adj P79 P91)
		(adj P80 P81)
		(adj P80 P79)
		(adj P80 P68)
		(adj P80 P92)
		(adj P81 P82)
		(adj P81 P80)
		(adj P81 P69)
		(adj P81 P93)
		(adj P82 P83)
		(adj P82 P81)
		(adj P82 P70)
		(adj P82 P94)
		(adj P83 P84)
		(adj P83 P82)
		(adj P83 P71)
		(adj P83 P95)
		(adj P84 P83)
		(adj P84 P72)
		(adj P84 P96)
		(adj P85 P86)
		(adj P85 P73)
		(adj P85 P97)
		(adj P86 P87)
		(adj P86 P85)
		(adj P86 P74)
		(adj P86 P98)
		(adj P87 P88)
		(adj P87 P86)
		(adj P87 P75)
		(adj P87 P99)
		(adj P88 P89)
		(adj P88 P87)
		(adj P88 P76)
		(adj P88 P100)
		(adj P89 P90)
		(adj P89 P88)
		(adj P89 P77)
		(adj P89 P101)
		(adj P90 P91)
		(adj P90 P89)
		(adj P90 P78)
		(adj P90 P102)
		(adj P91 P92)
		(adj P91 P90)
		(adj P91 P79)
		(adj P91 P103)
		(adj P92 P93)
		(adj P92 P91)
		(adj P92 P80)
		(adj P92 P104)
		(adj P93 P94)
		(adj P93 P92)
		(adj P93 P81)
		(adj P93 P105)
		(adj P94 P95)
		(adj P94 P93)
		(adj P94 P82)
		(adj P94 P106)
		(adj P95 P96)
		(adj P95 P94)
		(adj P95 P83)
		(adj P95 P107)
		(adj P96 P95)
		(adj P96 P84)
		(adj P96 P108)
		(adj P97 P98)
		(adj P97 P85)
		(adj P97 P109)
		(adj P98 P99)
		(adj P98 P97)
		(adj P98 P86)
		(adj P98 P110)
		(adj P99 P100)
		(adj P99 P98)
		(adj P99 P87)
		(adj P99 P111)
		(adj P100 P101)
		(adj P100 P99)
		(adj P100 P88)
		(adj P100 P112)
		(adj P101 P102)
		(adj P101 P100)
		(adj P101 P89)
		(adj P101 P113)
		(adj P102 P103)
		(adj P102 P101)
		(adj P102 P90)
		(adj P102 P114)
		(adj P103 P104)
		(adj P103 P102)
		(adj P103 P91)
		(adj P103 P115)
		(adj P104 P105)
		(adj P104 P103)
		(adj P104 P92)
		(adj P104 P116)
		(adj P105 P106)
		(adj P105 P104)
		(adj P105 P93)
		(adj P105 P117)
		(adj P106 P107)
		(adj P106 P105)
		(adj P106 P94)
		(adj P106 P118)
		(adj P107 P108)
		(adj P107 P106)
		(adj P107 P95)
		(adj P107 P119)
		(adj P108 P107)
		(adj P108 P96)
		(adj P108 P120)
		(adj P109 P110)
		(adj P109 P97)
		(adj P109 P121)
		(adj P110 P111)
		(adj P110 P109)
		(adj P110 P98)
		(adj P110 P122)
		(adj P111 P112)
		(adj P111 P110)
		(adj P111 P99)
		(adj P111 P123)
		(adj P112 P113)
		(adj P112 P111)
		(adj P112 P100)
		(adj P112 P124)
		(adj P113 P114)
		(adj P113 P112)
		(adj P113 P101)
		(adj P113 P125)
		(adj P114 P115)
		(adj P114 P113)
		(adj P114 P102)
		(adj P114 P126)
		(adj P115 P116)
		(adj P115 P114)
		(adj P115 P103)
		(adj P115 P127)
		(adj P116 P117)
		(adj P116 P115)
		(adj P116 P104)
		(adj P116 P128)
		(adj P117 P118)
		(adj P117 P116)
		(adj P117 P105)
		(adj P117 P129)
		(adj P118 P119)
		(adj P118 P117)
		(adj P118 P106)
		(adj P118 P130)
		(adj P119 P120)
		(adj P119 P118)
		(adj P119 P107)
		(adj P119 P131)
		(adj P120 P119)
		(adj P120 P108)
		(adj P120 P132)
		(adj P121 P122)
		(adj P121 P109)
		(adj P121 P133)
		(adj P122 P123)
		(adj P122 P121)
		(adj P122 P110)
		(adj P122 P134)
		(adj P123 P124)
		(adj P123 P122)
		(adj P123 P111)
		(adj P123 P135)
		(adj P124 P125)
		(adj P124 P123)
		(adj P124 P112)
		(adj P124 P136)
		(adj P125 P126)
		(adj P125 P124)
		(adj P125 P113)
		(adj P125 P137)
		(adj P126 P127)
		(adj P126 P125)
		(adj P126 P114)
		(adj P126 P138)
		(adj P127 P128)
		(adj P127 P126)
		(adj P127 P115)
		(adj P127 P139)
		(adj P128 P129)
		(adj P128 P127)
		(adj P128 P116)
		(adj P128 P140)
		(adj P129 P130)
		(adj P129 P128)
		(adj P129 P117)
		(adj P129 P141)
		(adj P130 P131)
		(adj P130 P129)
		(adj P130 P118)
		(adj P130 P142)
		(adj P131 P132)
		(adj P131 P130)
		(adj P131 P119)
		(adj P131 P143)
		(adj P132 P131)
		(adj P132 P120)
		(adj P132 P144)
		(adj P133 P134)
		(adj P133 P121)
		(adj P134 P135)
		(adj P134 P133)
		(adj P134 P122)
		(adj P135 P136)
		(adj P135 P134)
		(adj P135 P123)
		(adj P136 P137)
		(adj P136 P135)
		(adj P136 P124)
		(adj P137 P138)
		(adj P137 P136)
		(adj P137 P125)
		(adj P138 P139)
		(adj P138 P137)
		(adj P138 P126)
		(adj P139 P140)
		(adj P139 P138)
		(adj P139 P127)
		(adj P140 P141)
		(adj P140 P139)
		(adj P140 P128)
		(adj P141 P142)
		(adj P141 P140)
		(adj P141 P129)
		(adj P142 P143)
		(adj P142 P141)
		(adj P142 P130)
		(adj P143 P144)
		(adj P143 P142)
		(adj P143 P131)
		(adj P144 P143)
		(adj P144 P132)
		(pos P118)
	)
	(:goal
		(and
			(pos P121)
		)
	)
)
