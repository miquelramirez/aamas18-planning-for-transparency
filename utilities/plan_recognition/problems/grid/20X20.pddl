(define (problem nine)
	(:domain grid_domain)
	(:objects  P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20 P21 P22 P23 P24 P25 P26 P27 P28 P29 P30 P31 P32 P33 P34 P35 P36 P37 P38 P39 P40 P41 P42 P43 P44 P45 P46 P47 P48 P49 P50 P51 P52 P53 P54 P55 P56 P57 P58 P59 P60 P61 P62 P63 P64 P65 P66 P67 P68 P69 P70 P71 P72 P73 P74 P75 P76 P77 P78 P79 P80 P81 P82 P83 P84 P85 P86 P87 P88 P89 P90 P91 P92 P93 P94 P95 P96 P97 P98 P99 P100 P101 P102 P103 P104 P105 P106 P107 P108 P109 P110 P111 P112 P113 P114 P115 P116 P117 P118 P119 P120 P121 P122 P123 P124 P125 P126 P127 P128 P129 P130 P131 P132 P133 P134 P135 P136 P137 P138 P139 P140 P141 P142 P143 P144 P145 P146 P147 P148 P149 P150 P151 P152 P153 P154 P155 P156 P157 P158 P159 P160 P161 P162 P163 P164 P165 P166 P167 P168 P169 P170 P171 P172 P173 P174 P175 P176 P177 P178 P179 P180 P181 P182 P183 P184 P185 P186 P187 P188 P189 P190 P191 P192 P193 P194 P195 P196 P197 P198 P199 P200 P201 P202 P203 P204 P205 P206 P207 P208 P209 P210 P211 P212 P213 P214 P215 P216 P217 P218 P219 P220 P221 P222 P223 P224 P225 P226 P227 P228 P229 P230 P231 P232 P233 P234 P235 P236 P237 P238 P239 P240 P241 P242 P243 P244 P245 P246 P247 P248 P249 P250 P251 P252 P253 P254 P255 P256 P257 P258 P259 P260 P261 P262 P263 P264 P265 P266 P267 P268 P269 P270 P271 P272 P273 P274 P275 P276 P277 P278 P279 P280 P281 P282 P283 P284 P285 P286 P287 P288 P289 P290 P291 P292 P293 P294 P295 P296 P297 P298 P299 P300 P301 P302 P303 P304 P305 P306 P307 P308 P309 P310 P311 P312 P313 P314 P315 P316 P317 P318 P319 P320 P321 P322 P323 P324 P325 P326 P327 P328 P329 P330 P331 P332 P333 P334 P335 P336 P337 P338 P339 P340 P341 P342 P343 P344 P345 P346 P347 P348 P349 P350 P351 P352 P353 P354 P355 P356 P357 P358 P359 P360 P361 P362 P363 P364 P365 P366 P367 P368 P369 P370 P371 P372 P373 P374 P375 P376 P377 P378 P379 P380 P381 P382 P383 P384 P385 P386 P387 P388 P389 P390 P391 P392 P393 P394 P395 P396 P397 P398 P399 P400)
	(:init
		(adj P1 P2)
		(adj P1 P21)
		(adj P2 P3)
		(adj P2 P1)
		(adj P2 P22)
		(adj P3 P4)
		(adj P3 P2)
		(adj P3 P23)
		(adj P4 P5)
		(adj P4 P3)
		(adj P4 P24)
		(adj P5 P6)
		(adj P5 P4)
		(adj P5 P25)
		(adj P6 P7)
		(adj P6 P5)
		(adj P6 P26)
		(adj P7 P8)
		(adj P7 P6)
		(adj P7 P27)
		(adj P8 P9)
		(adj P8 P7)
		(adj P8 P28)
		(adj P9 P10)
		(adj P9 P8)
		(adj P9 P29)
		(adj P10 P11)
		(adj P10 P9)
		(adj P10 P30)
		(adj P11 P12)
		(adj P11 P10)
		(adj P11 P31)
		(adj P12 P13)
		(adj P12 P11)
		(adj P12 P32)
		(adj P13 P14)
		(adj P13 P12)
		(adj P13 P33)
		(adj P14 P15)
		(adj P14 P13)
		(adj P14 P34)
		(adj P15 P16)
		(adj P15 P14)
		(adj P15 P35)
		(adj P16 P17)
		(adj P16 P15)
		(adj P16 P36)
		(adj P17 P18)
		(adj P17 P16)
		(adj P17 P37)
		(adj P18 P19)
		(adj P18 P17)
		(adj P18 P38)
		(adj P19 P20)
		(adj P19 P18)
		(adj P19 P39)
		(adj P20 P19)
		(adj P20 P40)
		(adj P21 P22)
		(adj P21 P1)
		(adj P21 P41)
		(adj P22 P23)
		(adj P22 P21)
		(adj P22 P2)
		(adj P22 P42)
		(adj P23 P24)
		(adj P23 P22)
		(adj P23 P3)
		(adj P23 P43)
		(adj P24 P25)
		(adj P24 P23)
		(adj P24 P4)
		(adj P24 P44)
		(adj P25 P26)
		(adj P25 P24)
		(adj P25 P5)
		(adj P25 P45)
		(adj P26 P27)
		(adj P26 P25)
		(adj P26 P6)
		(adj P26 P46)
		(adj P27 P28)
		(adj P27 P26)
		(adj P27 P7)
		(adj P27 P47)
		(adj P28 P29)
		(adj P28 P27)
		(adj P28 P8)
		(adj P28 P48)
		(adj P29 P30)
		(adj P29 P28)
		(adj P29 P9)
		(adj P29 P49)
		(adj P30 P31)
		(adj P30 P29)
		(adj P30 P10)
		(adj P30 P50)
		(adj P31 P32)
		(adj P31 P30)
		(adj P31 P11)
		(adj P31 P51)
		(adj P32 P33)
		(adj P32 P31)
		(adj P32 P12)
		(adj P32 P52)
		(adj P33 P34)
		(adj P33 P32)
		(adj P33 P13)
		(adj P33 P53)
		(adj P34 P35)
		(adj P34 P33)
		(adj P34 P14)
		(adj P34 P54)
		(adj P35 P36)
		(adj P35 P34)
		(adj P35 P15)
		(adj P35 P55)
		(adj P36 P37)
		(adj P36 P35)
		(adj P36 P16)
		(adj P36 P56)
		(adj P37 P38)
		(adj P37 P36)
		(adj P37 P17)
		(adj P37 P57)
		(adj P38 P39)
		(adj P38 P37)
		(adj P38 P18)
		(adj P38 P58)
		(adj P39 P40)
		(adj P39 P38)
		(adj P39 P19)
		(adj P39 P59)
		(adj P40 P39)
		(adj P40 P20)
		(adj P40 P60)
		(adj P41 P42)
		(adj P41 P21)
		(adj P41 P61)
		(adj P42 P43)
		(adj P42 P41)
		(adj P42 P22)
		(adj P42 P62)
		(adj P43 P44)
		(adj P43 P42)
		(adj P43 P23)
		(adj P43 P63)
		(adj P44 P45)
		(adj P44 P43)
		(adj P44 P24)
		(adj P44 P64)
		(adj P45 P46)
		(adj P45 P44)
		(adj P45 P25)
		(adj P45 P65)
		(adj P46 P47)
		(adj P46 P45)
		(adj P46 P26)
		(adj P46 P66)
		(adj P47 P48)
		(adj P47 P46)
		(adj P47 P27)
		(adj P47 P67)
		(adj P48 P49)
		(adj P48 P47)
		(adj P48 P28)
		(adj P48 P68)
		(adj P49 P50)
		(adj P49 P48)
		(adj P49 P29)
		(adj P49 P69)
		(adj P50 P51)
		(adj P50 P49)
		(adj P50 P30)
		(adj P50 P70)
		(adj P51 P52)
		(adj P51 P50)
		(adj P51 P31)
		(adj P51 P71)
		(adj P52 P53)
		(adj P52 P51)
		(adj P52 P32)
		(adj P52 P72)
		(adj P53 P54)
		(adj P53 P52)
		(adj P53 P33)
		(adj P53 P73)
		(adj P54 P55)
		(adj P54 P53)
		(adj P54 P34)
		(adj P54 P74)
		(adj P55 P56)
		(adj P55 P54)
		(adj P55 P35)
		(adj P55 P75)
		(adj P56 P57)
		(adj P56 P55)
		(adj P56 P36)
		(adj P56 P76)
		(adj P57 P58)
		(adj P57 P56)
		(adj P57 P37)
		(adj P57 P77)
		(adj P58 P59)
		(adj P58 P57)
		(adj P58 P38)
		(adj P58 P78)
		(adj P59 P60)
		(adj P59 P58)
		(adj P59 P39)
		(adj P59 P79)
		(adj P60 P59)
		(adj P60 P40)
		(adj P60 P80)
		(adj P61 P62)
		(adj P61 P41)
		(adj P61 P81)
		(adj P62 P63)
		(adj P62 P61)
		(adj P62 P42)
		(adj P62 P82)
		(adj P63 P64)
		(adj P63 P62)
		(adj P63 P43)
		(adj P63 P83)
		(adj P64 P65)
		(adj P64 P63)
		(adj P64 P44)
		(adj P64 P84)
		(adj P65 P66)
		(adj P65 P64)
		(adj P65 P45)
		(adj P65 P85)
		(adj P66 P67)
		(adj P66 P65)
		(adj P66 P46)
		(adj P66 P86)
		(adj P67 P68)
		(adj P67 P66)
		(adj P67 P47)
		(adj P67 P87)
		(adj P68 P69)
		(adj P68 P67)
		(adj P68 P48)
		(adj P68 P88)
		(adj P69 P70)
		(adj P69 P68)
		(adj P69 P49)
		(adj P69 P89)
		(adj P70 P71)
		(adj P70 P69)
		(adj P70 P50)
		(adj P70 P90)
		(adj P71 P72)
		(adj P71 P70)
		(adj P71 P51)
		(adj P71 P91)
		(adj P72 P73)
		(adj P72 P71)
		(adj P72 P52)
		(adj P72 P92)
		(adj P73 P74)
		(adj P73 P72)
		(adj P73 P53)
		(adj P73 P93)
		(adj P74 P75)
		(adj P74 P73)
		(adj P74 P54)
		(adj P74 P94)
		(adj P75 P76)
		(adj P75 P74)
		(adj P75 P55)
		(adj P75 P95)
		(adj P76 P77)
		(adj P76 P75)
		(adj P76 P56)
		(adj P76 P96)
		(adj P77 P78)
		(adj P77 P76)
		(adj P77 P57)
		(adj P77 P97)
		(adj P78 P79)
		(adj P78 P77)
		(adj P78 P58)
		(adj P78 P98)
		(adj P79 P80)
		(adj P79 P78)
		(adj P79 P59)
		(adj P79 P99)
		(adj P80 P79)
		(adj P80 P60)
		(adj P80 P100)
		(adj P81 P82)
		(adj P81 P61)
		(adj P81 P101)
		(adj P82 P83)
		(adj P82 P81)
		(adj P82 P62)
		(adj P82 P102)
		(adj P83 P84)
		(adj P83 P82)
		(adj P83 P63)
		(adj P83 P103)
		(adj P84 P85)
		(adj P84 P83)
		(adj P84 P64)
		(adj P84 P104)
		(adj P85 P86)
		(adj P85 P84)
		(adj P85 P65)
		(adj P85 P105)
		(adj P86 P87)
		(adj P86 P85)
		(adj P86 P66)
		(adj P86 P106)
		(adj P87 P88)
		(adj P87 P86)
		(adj P87 P67)
		(adj P87 P107)
		(adj P88 P89)
		(adj P88 P87)
		(adj P88 P68)
		(adj P88 P108)
		(adj P89 P90)
		(adj P89 P88)
		(adj P89 P69)
		(adj P89 P109)
		(adj P90 P91)
		(adj P90 P89)
		(adj P90 P70)
		(adj P90 P110)
		(adj P91 P92)
		(adj P91 P90)
		(adj P91 P71)
		(adj P91 P111)
		(adj P92 P93)
		(adj P92 P91)
		(adj P92 P72)
		(adj P92 P112)
		(adj P93 P94)
		(adj P93 P92)
		(adj P93 P73)
		(adj P93 P113)
		(adj P94 P95)
		(adj P94 P93)
		(adj P94 P74)
		(adj P94 P114)
		(adj P95 P96)
		(adj P95 P94)
		(adj P95 P75)
		(adj P95 P115)
		(adj P96 P97)
		(adj P96 P95)
		(adj P96 P76)
		(adj P96 P116)
		(adj P97 P98)
		(adj P97 P96)
		(adj P97 P77)
		(adj P97 P117)
		(adj P98 P99)
		(adj P98 P97)
		(adj P98 P78)
		(adj P98 P118)
		(adj P99 P100)
		(adj P99 P98)
		(adj P99 P79)
		(adj P99 P119)
		(adj P100 P99)
		(adj P100 P80)
		(adj P100 P120)
		(adj P101 P102)
		(adj P101 P81)
		(adj P101 P121)
		(adj P102 P103)
		(adj P102 P101)
		(adj P102 P82)
		(adj P102 P122)
		(adj P103 P104)
		(adj P103 P102)
		(adj P103 P83)
		(adj P103 P123)
		(adj P104 P105)
		(adj P104 P103)
		(adj P104 P84)
		(adj P104 P124)
		(adj P105 P106)
		(adj P105 P104)
		(adj P105 P85)
		(adj P105 P125)
		(adj P106 P107)
		(adj P106 P105)
		(adj P106 P86)
		(adj P106 P126)
		(adj P107 P108)
		(adj P107 P106)
		(adj P107 P87)
		(adj P107 P127)
		(adj P108 P109)
		(adj P108 P107)
		(adj P108 P88)
		(adj P108 P128)
		(adj P109 P110)
		(adj P109 P108)
		(adj P109 P89)
		(adj P109 P129)
		(adj P110 P111)
		(adj P110 P109)
		(adj P110 P90)
		(adj P110 P130)
		(adj P111 P112)
		(adj P111 P110)
		(adj P111 P91)
		(adj P111 P131)
		(adj P112 P113)
		(adj P112 P111)
		(adj P112 P92)
		(adj P112 P132)
		(adj P113 P114)
		(adj P113 P112)
		(adj P113 P93)
		(adj P113 P133)
		(adj P114 P115)
		(adj P114 P113)
		(adj P114 P94)
		(adj P114 P134)
		(adj P115 P116)
		(adj P115 P114)
		(adj P115 P95)
		(adj P115 P135)
		(adj P116 P117)
		(adj P116 P115)
		(adj P116 P96)
		(adj P116 P136)
		(adj P117 P118)
		(adj P117 P116)
		(adj P117 P97)
		(adj P117 P137)
		(adj P118 P119)
		(adj P118 P117)
		(adj P118 P98)
		(adj P118 P138)
		(adj P119 P120)
		(adj P119 P118)
		(adj P119 P99)
		(adj P119 P139)
		(adj P120 P119)
		(adj P120 P100)
		(adj P120 P140)
		(adj P121 P122)
		(adj P121 P101)
		(adj P121 P141)
		(adj P122 P123)
		(adj P122 P121)
		(adj P122 P102)
		(adj P122 P142)
		(adj P123 P124)
		(adj P123 P122)
		(adj P123 P103)
		(adj P123 P143)
		(adj P124 P125)
		(adj P124 P123)
		(adj P124 P104)
		(adj P124 P144)
		(adj P125 P126)
		(adj P125 P124)
		(adj P125 P105)
		(adj P125 P145)
		(adj P126 P127)
		(adj P126 P125)
		(adj P126 P106)
		(adj P126 P146)
		(adj P127 P128)
		(adj P127 P126)
		(adj P127 P107)
		(adj P127 P147)
		(adj P128 P129)
		(adj P128 P127)
		(adj P128 P108)
		(adj P128 P148)
		(adj P129 P130)
		(adj P129 P128)
		(adj P129 P109)
		(adj P129 P149)
		(adj P130 P131)
		(adj P130 P129)
		(adj P130 P110)
		(adj P130 P150)
		(adj P131 P132)
		(adj P131 P130)
		(adj P131 P111)
		(adj P131 P151)
		(adj P132 P133)
		(adj P132 P131)
		(adj P132 P112)
		(adj P132 P152)
		(adj P133 P134)
		(adj P133 P132)
		(adj P133 P113)
		(adj P133 P153)
		(adj P134 P135)
		(adj P134 P133)
		(adj P134 P114)
		(adj P134 P154)
		(adj P135 P136)
		(adj P135 P134)
		(adj P135 P115)
		(adj P135 P155)
		(adj P136 P137)
		(adj P136 P135)
		(adj P136 P116)
		(adj P136 P156)
		(adj P137 P138)
		(adj P137 P136)
		(adj P137 P117)
		(adj P137 P157)
		(adj P138 P139)
		(adj P138 P137)
		(adj P138 P118)
		(adj P138 P158)
		(adj P139 P140)
		(adj P139 P138)
		(adj P139 P119)
		(adj P139 P159)
		(adj P140 P139)
		(adj P140 P120)
		(adj P140 P160)
		(adj P141 P142)
		(adj P141 P121)
		(adj P141 P161)
		(adj P142 P143)
		(adj P142 P141)
		(adj P142 P122)
		(adj P142 P162)
		(adj P143 P144)
		(adj P143 P142)
		(adj P143 P123)
		(adj P143 P163)
		(adj P144 P145)
		(adj P144 P143)
		(adj P144 P124)
		(adj P144 P164)
		(adj P145 P146)
		(adj P145 P144)
		(adj P145 P125)
		(adj P145 P165)
		(adj P146 P147)
		(adj P146 P145)
		(adj P146 P126)
		(adj P146 P166)
		(adj P147 P148)
		(adj P147 P146)
		(adj P147 P127)
		(adj P147 P167)
		(adj P148 P149)
		(adj P148 P147)
		(adj P148 P128)
		(adj P148 P168)
		(adj P149 P150)
		(adj P149 P148)
		(adj P149 P129)
		(adj P149 P169)
		(adj P150 P151)
		(adj P150 P149)
		(adj P150 P130)
		(adj P150 P170)
		(adj P151 P152)
		(adj P151 P150)
		(adj P151 P131)
		(adj P151 P171)
		(adj P152 P153)
		(adj P152 P151)
		(adj P152 P132)
		(adj P152 P172)
		(adj P153 P154)
		(adj P153 P152)
		(adj P153 P133)
		(adj P153 P173)
		(adj P154 P155)
		(adj P154 P153)
		(adj P154 P134)
		(adj P154 P174)
		(adj P155 P156)
		(adj P155 P154)
		(adj P155 P135)
		(adj P155 P175)
		(adj P156 P157)
		(adj P156 P155)
		(adj P156 P136)
		(adj P156 P176)
		(adj P157 P158)
		(adj P157 P156)
		(adj P157 P137)
		(adj P157 P177)
		(adj P158 P159)
		(adj P158 P157)
		(adj P158 P138)
		(adj P158 P178)
		(adj P159 P160)
		(adj P159 P158)
		(adj P159 P139)
		(adj P159 P179)
		(adj P160 P159)
		(adj P160 P140)
		(adj P160 P180)
		(adj P161 P162)
		(adj P161 P141)
		(adj P161 P181)
		(adj P162 P163)
		(adj P162 P161)
		(adj P162 P142)
		(adj P162 P182)
		(adj P163 P164)
		(adj P163 P162)
		(adj P163 P143)
		(adj P163 P183)
		(adj P164 P165)
		(adj P164 P163)
		(adj P164 P144)
		(adj P164 P184)
		(adj P165 P166)
		(adj P165 P164)
		(adj P165 P145)
		(adj P165 P185)
		(adj P166 P167)
		(adj P166 P165)
		(adj P166 P146)
		(adj P166 P186)
		(adj P167 P168)
		(adj P167 P166)
		(adj P167 P147)
		(adj P167 P187)
		(adj P168 P169)
		(adj P168 P167)
		(adj P168 P148)
		(adj P168 P188)
		(adj P169 P170)
		(adj P169 P168)
		(adj P169 P149)
		(adj P169 P189)
		(adj P170 P171)
		(adj P170 P169)
		(adj P170 P150)
		(adj P170 P190)
		(adj P171 P172)
		(adj P171 P170)
		(adj P171 P151)
		(adj P171 P191)
		(adj P172 P173)
		(adj P172 P171)
		(adj P172 P152)
		(adj P172 P192)
		(adj P173 P174)
		(adj P173 P172)
		(adj P173 P153)
		(adj P173 P193)
		(adj P174 P175)
		(adj P174 P173)
		(adj P174 P154)
		(adj P174 P194)
		(adj P175 P176)
		(adj P175 P174)
		(adj P175 P155)
		(adj P175 P195)
		(adj P176 P177)
		(adj P176 P175)
		(adj P176 P156)
		(adj P176 P196)
		(adj P177 P178)
		(adj P177 P176)
		(adj P177 P157)
		(adj P177 P197)
		(adj P178 P179)
		(adj P178 P177)
		(adj P178 P158)
		(adj P178 P198)
		(adj P179 P180)
		(adj P179 P178)
		(adj P179 P159)
		(adj P179 P199)
		(adj P180 P179)
		(adj P180 P160)
		(adj P180 P200)
		(adj P181 P182)
		(adj P181 P161)
		(adj P181 P201)
		(adj P182 P183)
		(adj P182 P181)
		(adj P182 P162)
		(adj P182 P202)
		(adj P183 P184)
		(adj P183 P182)
		(adj P183 P163)
		(adj P183 P203)
		(adj P184 P185)
		(adj P184 P183)
		(adj P184 P164)
		(adj P184 P204)
		(adj P185 P186)
		(adj P185 P184)
		(adj P185 P165)
		(adj P185 P205)
		(adj P186 P187)
		(adj P186 P185)
		(adj P186 P166)
		(adj P186 P206)
		(adj P187 P188)
		(adj P187 P186)
		(adj P187 P167)
		(adj P187 P207)
		(adj P188 P189)
		(adj P188 P187)
		(adj P188 P168)
		(adj P188 P208)
		(adj P189 P190)
		(adj P189 P188)
		(adj P189 P169)
		(adj P189 P209)
		(adj P190 P191)
		(adj P190 P189)
		(adj P190 P170)
		(adj P190 P210)
		(adj P191 P192)
		(adj P191 P190)
		(adj P191 P171)
		(adj P191 P211)
		(adj P192 P193)
		(adj P192 P191)
		(adj P192 P172)
		(adj P192 P212)
		(adj P193 P194)
		(adj P193 P192)
		(adj P193 P173)
		(adj P193 P213)
		(adj P194 P195)
		(adj P194 P193)
		(adj P194 P174)
		(adj P194 P214)
		(adj P195 P196)
		(adj P195 P194)
		(adj P195 P175)
		(adj P195 P215)
		(adj P196 P197)
		(adj P196 P195)
		(adj P196 P176)
		(adj P196 P216)
		(adj P197 P198)
		(adj P197 P196)
		(adj P197 P177)
		(adj P197 P217)
		(adj P198 P199)
		(adj P198 P197)
		(adj P198 P178)
		(adj P198 P218)
		(adj P199 P200)
		(adj P199 P198)
		(adj P199 P179)
		(adj P199 P219)
		(adj P200 P199)
		(adj P200 P180)
		(adj P200 P220)
		(adj P201 P202)
		(adj P201 P181)
		(adj P201 P221)
		(adj P202 P203)
		(adj P202 P201)
		(adj P202 P182)
		(adj P202 P222)
		(adj P203 P204)
		(adj P203 P202)
		(adj P203 P183)
		(adj P203 P223)
		(adj P204 P205)
		(adj P204 P203)
		(adj P204 P184)
		(adj P204 P224)
		(adj P205 P206)
		(adj P205 P204)
		(adj P205 P185)
		(adj P205 P225)
		(adj P206 P207)
		(adj P206 P205)
		(adj P206 P186)
		(adj P206 P226)
		(adj P207 P208)
		(adj P207 P206)
		(adj P207 P187)
		(adj P207 P227)
		(adj P208 P209)
		(adj P208 P207)
		(adj P208 P188)
		(adj P208 P228)
		(adj P209 P210)
		(adj P209 P208)
		(adj P209 P189)
		(adj P209 P229)
		(adj P210 P211)
		(adj P210 P209)
		(adj P210 P190)
		(adj P210 P230)
		(adj P211 P212)
		(adj P211 P210)
		(adj P211 P191)
		(adj P211 P231)
		(adj P212 P213)
		(adj P212 P211)
		(adj P212 P192)
		(adj P212 P232)
		(adj P213 P214)
		(adj P213 P212)
		(adj P213 P193)
		(adj P213 P233)
		(adj P214 P215)
		(adj P214 P213)
		(adj P214 P194)
		(adj P214 P234)
		(adj P215 P216)
		(adj P215 P214)
		(adj P215 P195)
		(adj P215 P235)
		(adj P216 P217)
		(adj P216 P215)
		(adj P216 P196)
		(adj P216 P236)
		(adj P217 P218)
		(adj P217 P216)
		(adj P217 P197)
		(adj P217 P237)
		(adj P218 P219)
		(adj P218 P217)
		(adj P218 P198)
		(adj P218 P238)
		(adj P219 P220)
		(adj P219 P218)
		(adj P219 P199)
		(adj P219 P239)
		(adj P220 P219)
		(adj P220 P200)
		(adj P220 P240)
		(adj P221 P222)
		(adj P221 P201)
		(adj P221 P241)
		(adj P222 P223)
		(adj P222 P221)
		(adj P222 P202)
		(adj P222 P242)
		(adj P223 P224)
		(adj P223 P222)
		(adj P223 P203)
		(adj P223 P243)
		(adj P224 P225)
		(adj P224 P223)
		(adj P224 P204)
		(adj P224 P244)
		(adj P225 P226)
		(adj P225 P224)
		(adj P225 P205)
		(adj P225 P245)
		(adj P226 P227)
		(adj P226 P225)
		(adj P226 P206)
		(adj P226 P246)
		(adj P227 P228)
		(adj P227 P226)
		(adj P227 P207)
		(adj P227 P247)
		(adj P228 P229)
		(adj P228 P227)
		(adj P228 P208)
		(adj P228 P248)
		(adj P229 P230)
		(adj P229 P228)
		(adj P229 P209)
		(adj P229 P249)
		(adj P230 P231)
		(adj P230 P229)
		(adj P230 P210)
		(adj P230 P250)
		(adj P231 P232)
		(adj P231 P230)
		(adj P231 P211)
		(adj P231 P251)
		(adj P232 P233)
		(adj P232 P231)
		(adj P232 P212)
		(adj P232 P252)
		(adj P233 P234)
		(adj P233 P232)
		(adj P233 P213)
		(adj P233 P253)
		(adj P234 P235)
		(adj P234 P233)
		(adj P234 P214)
		(adj P234 P254)
		(adj P235 P236)
		(adj P235 P234)
		(adj P235 P215)
		(adj P235 P255)
		(adj P236 P237)
		(adj P236 P235)
		(adj P236 P216)
		(adj P236 P256)
		(adj P237 P238)
		(adj P237 P236)
		(adj P237 P217)
		(adj P237 P257)
		(adj P238 P239)
		(adj P238 P237)
		(adj P238 P218)
		(adj P238 P258)
		(adj P239 P240)
		(adj P239 P238)
		(adj P239 P219)
		(adj P239 P259)
		(adj P240 P239)
		(adj P240 P220)
		(adj P240 P260)
		(adj P241 P242)
		(adj P241 P221)
		(adj P241 P261)
		(adj P242 P243)
		(adj P242 P241)
		(adj P242 P222)
		(adj P242 P262)
		(adj P243 P244)
		(adj P243 P242)
		(adj P243 P223)
		(adj P243 P263)
		(adj P244 P245)
		(adj P244 P243)
		(adj P244 P224)
		(adj P244 P264)
		(adj P245 P246)
		(adj P245 P244)
		(adj P245 P225)
		(adj P245 P265)
		(adj P246 P247)
		(adj P246 P245)
		(adj P246 P226)
		(adj P246 P266)
		(adj P247 P248)
		(adj P247 P246)
		(adj P247 P227)
		(adj P247 P267)
		(adj P248 P249)
		(adj P248 P247)
		(adj P248 P228)
		(adj P248 P268)
		(adj P249 P250)
		(adj P249 P248)
		(adj P249 P229)
		(adj P249 P269)
		(adj P250 P251)
		(adj P250 P249)
		(adj P250 P230)
		(adj P250 P270)
		(adj P251 P252)
		(adj P251 P250)
		(adj P251 P231)
		(adj P251 P271)
		(adj P252 P253)
		(adj P252 P251)
		(adj P252 P232)
		(adj P252 P272)
		(adj P253 P254)
		(adj P253 P252)
		(adj P253 P233)
		(adj P253 P273)
		(adj P254 P255)
		(adj P254 P253)
		(adj P254 P234)
		(adj P254 P274)
		(adj P255 P256)
		(adj P255 P254)
		(adj P255 P235)
		(adj P255 P275)
		(adj P256 P257)
		(adj P256 P255)
		(adj P256 P236)
		(adj P256 P276)
		(adj P257 P258)
		(adj P257 P256)
		(adj P257 P237)
		(adj P257 P277)
		(adj P258 P259)
		(adj P258 P257)
		(adj P258 P238)
		(adj P258 P278)
		(adj P259 P260)
		(adj P259 P258)
		(adj P259 P239)
		(adj P259 P279)
		(adj P260 P259)
		(adj P260 P240)
		(adj P260 P280)
		(adj P261 P262)
		(adj P261 P241)
		(adj P261 P281)
		(adj P262 P263)
		(adj P262 P261)
		(adj P262 P242)
		(adj P262 P282)
		(adj P263 P264)
		(adj P263 P262)
		(adj P263 P243)
		(adj P263 P283)
		(adj P264 P265)
		(adj P264 P263)
		(adj P264 P244)
		(adj P264 P284)
		(adj P265 P266)
		(adj P265 P264)
		(adj P265 P245)
		(adj P265 P285)
		(adj P266 P267)
		(adj P266 P265)
		(adj P266 P246)
		(adj P266 P286)
		(adj P267 P268)
		(adj P267 P266)
		(adj P267 P247)
		(adj P267 P287)
		(adj P268 P269)
		(adj P268 P267)
		(adj P268 P248)
		(adj P268 P288)
		(adj P269 P270)
		(adj P269 P268)
		(adj P269 P249)
		(adj P269 P289)
		(adj P270 P271)
		(adj P270 P269)
		(adj P270 P250)
		(adj P270 P290)
		(adj P271 P272)
		(adj P271 P270)
		(adj P271 P251)
		(adj P271 P291)
		(adj P272 P273)
		(adj P272 P271)
		(adj P272 P252)
		(adj P272 P292)
		(adj P273 P274)
		(adj P273 P272)
		(adj P273 P253)
		(adj P273 P293)
		(adj P274 P275)
		(adj P274 P273)
		(adj P274 P254)
		(adj P274 P294)
		(adj P275 P276)
		(adj P275 P274)
		(adj P275 P255)
		(adj P275 P295)
		(adj P276 P277)
		(adj P276 P275)
		(adj P276 P256)
		(adj P276 P296)
		(adj P277 P278)
		(adj P277 P276)
		(adj P277 P257)
		(adj P277 P297)
		(adj P278 P279)
		(adj P278 P277)
		(adj P278 P258)
		(adj P278 P298)
		(adj P279 P280)
		(adj P279 P278)
		(adj P279 P259)
		(adj P279 P299)
		(adj P280 P279)
		(adj P280 P260)
		(adj P280 P300)
		(adj P281 P282)
		(adj P281 P261)
		(adj P281 P301)
		(adj P282 P283)
		(adj P282 P281)
		(adj P282 P262)
		(adj P282 P302)
		(adj P283 P284)
		(adj P283 P282)
		(adj P283 P263)
		(adj P283 P303)
		(adj P284 P285)
		(adj P284 P283)
		(adj P284 P264)
		(adj P284 P304)
		(adj P285 P286)
		(adj P285 P284)
		(adj P285 P265)
		(adj P285 P305)
		(adj P286 P287)
		(adj P286 P285)
		(adj P286 P266)
		(adj P286 P306)
		(adj P287 P288)
		(adj P287 P286)
		(adj P287 P267)
		(adj P287 P307)
		(adj P288 P289)
		(adj P288 P287)
		(adj P288 P268)
		(adj P288 P308)
		(adj P289 P290)
		(adj P289 P288)
		(adj P289 P269)
		(adj P289 P309)
		(adj P290 P291)
		(adj P290 P289)
		(adj P290 P270)
		(adj P290 P310)
		(adj P291 P292)
		(adj P291 P290)
		(adj P291 P271)
		(adj P291 P311)
		(adj P292 P293)
		(adj P292 P291)
		(adj P292 P272)
		(adj P292 P312)
		(adj P293 P294)
		(adj P293 P292)
		(adj P293 P273)
		(adj P293 P313)
		(adj P294 P295)
		(adj P294 P293)
		(adj P294 P274)
		(adj P294 P314)
		(adj P295 P296)
		(adj P295 P294)
		(adj P295 P275)
		(adj P295 P315)
		(adj P296 P297)
		(adj P296 P295)
		(adj P296 P276)
		(adj P296 P316)
		(adj P297 P298)
		(adj P297 P296)
		(adj P297 P277)
		(adj P297 P317)
		(adj P298 P299)
		(adj P298 P297)
		(adj P298 P278)
		(adj P298 P318)
		(adj P299 P300)
		(adj P299 P298)
		(adj P299 P279)
		(adj P299 P319)
		(adj P300 P299)
		(adj P300 P280)
		(adj P300 P320)
		(adj P301 P302)
		(adj P301 P281)
		(adj P301 P321)
		(adj P302 P303)
		(adj P302 P301)
		(adj P302 P282)
		(adj P302 P322)
		(adj P303 P304)
		(adj P303 P302)
		(adj P303 P283)
		(adj P303 P323)
		(adj P304 P305)
		(adj P304 P303)
		(adj P304 P284)
		(adj P304 P324)
		(adj P305 P306)
		(adj P305 P304)
		(adj P305 P285)
		(adj P305 P325)
		(adj P306 P307)
		(adj P306 P305)
		(adj P306 P286)
		(adj P306 P326)
		(adj P307 P308)
		(adj P307 P306)
		(adj P307 P287)
		(adj P307 P327)
		(adj P308 P309)
		(adj P308 P307)
		(adj P308 P288)
		(adj P308 P328)
		(adj P309 P310)
		(adj P309 P308)
		(adj P309 P289)
		(adj P309 P329)
		(adj P310 P311)
		(adj P310 P309)
		(adj P310 P290)
		(adj P310 P330)
		(adj P311 P312)
		(adj P311 P310)
		(adj P311 P291)
		(adj P311 P331)
		(adj P312 P313)
		(adj P312 P311)
		(adj P312 P292)
		(adj P312 P332)
		(adj P313 P314)
		(adj P313 P312)
		(adj P313 P293)
		(adj P313 P333)
		(adj P314 P315)
		(adj P314 P313)
		(adj P314 P294)
		(adj P314 P334)
		(adj P315 P316)
		(adj P315 P314)
		(adj P315 P295)
		(adj P315 P335)
		(adj P316 P317)
		(adj P316 P315)
		(adj P316 P296)
		(adj P316 P336)
		(adj P317 P318)
		(adj P317 P316)
		(adj P317 P297)
		(adj P317 P337)
		(adj P318 P319)
		(adj P318 P317)
		(adj P318 P298)
		(adj P318 P338)
		(adj P319 P320)
		(adj P319 P318)
		(adj P319 P299)
		(adj P319 P339)
		(adj P320 P319)
		(adj P320 P300)
		(adj P320 P340)
		(adj P321 P322)
		(adj P321 P301)
		(adj P321 P341)
		(adj P322 P323)
		(adj P322 P321)
		(adj P322 P302)
		(adj P322 P342)
		(adj P323 P324)
		(adj P323 P322)
		(adj P323 P303)
		(adj P323 P343)
		(adj P324 P325)
		(adj P324 P323)
		(adj P324 P304)
		(adj P324 P344)
		(adj P325 P326)
		(adj P325 P324)
		(adj P325 P305)
		(adj P325 P345)
		(adj P326 P327)
		(adj P326 P325)
		(adj P326 P306)
		(adj P326 P346)
		(adj P327 P328)
		(adj P327 P326)
		(adj P327 P307)
		(adj P327 P347)
		(adj P328 P329)
		(adj P328 P327)
		(adj P328 P308)
		(adj P328 P348)
		(adj P329 P330)
		(adj P329 P328)
		(adj P329 P309)
		(adj P329 P349)
		(adj P330 P331)
		(adj P330 P329)
		(adj P330 P310)
		(adj P330 P350)
		(adj P331 P332)
		(adj P331 P330)
		(adj P331 P311)
		(adj P331 P351)
		(adj P332 P333)
		(adj P332 P331)
		(adj P332 P312)
		(adj P332 P352)
		(adj P333 P334)
		(adj P333 P332)
		(adj P333 P313)
		(adj P333 P353)
		(adj P334 P335)
		(adj P334 P333)
		(adj P334 P314)
		(adj P334 P354)
		(adj P335 P336)
		(adj P335 P334)
		(adj P335 P315)
		(adj P335 P355)
		(adj P336 P337)
		(adj P336 P335)
		(adj P336 P316)
		(adj P336 P356)
		(adj P337 P338)
		(adj P337 P336)
		(adj P337 P317)
		(adj P337 P357)
		(adj P338 P339)
		(adj P338 P337)
		(adj P338 P318)
		(adj P338 P358)
		(adj P339 P340)
		(adj P339 P338)
		(adj P339 P319)
		(adj P339 P359)
		(adj P340 P339)
		(adj P340 P320)
		(adj P340 P360)
		(adj P341 P342)
		(adj P341 P321)
		(adj P341 P361)
		(adj P342 P343)
		(adj P342 P341)
		(adj P342 P322)
		(adj P342 P362)
		(adj P343 P344)
		(adj P343 P342)
		(adj P343 P323)
		(adj P343 P363)
		(adj P344 P345)
		(adj P344 P343)
		(adj P344 P324)
		(adj P344 P364)
		(adj P345 P346)
		(adj P345 P344)
		(adj P345 P325)
		(adj P345 P365)
		(adj P346 P347)
		(adj P346 P345)
		(adj P346 P326)
		(adj P346 P366)
		(adj P347 P348)
		(adj P347 P346)
		(adj P347 P327)
		(adj P347 P367)
		(adj P348 P349)
		(adj P348 P347)
		(adj P348 P328)
		(adj P348 P368)
		(adj P349 P350)
		(adj P349 P348)
		(adj P349 P329)
		(adj P349 P369)
		(adj P350 P351)
		(adj P350 P349)
		(adj P350 P330)
		(adj P350 P370)
		(adj P351 P352)
		(adj P351 P350)
		(adj P351 P331)
		(adj P351 P371)
		(adj P352 P353)
		(adj P352 P351)
		(adj P352 P332)
		(adj P352 P372)
		(adj P353 P354)
		(adj P353 P352)
		(adj P353 P333)
		(adj P353 P373)
		(adj P354 P355)
		(adj P354 P353)
		(adj P354 P334)
		(adj P354 P374)
		(adj P355 P356)
		(adj P355 P354)
		(adj P355 P335)
		(adj P355 P375)
		(adj P356 P357)
		(adj P356 P355)
		(adj P356 P336)
		(adj P356 P376)
		(adj P357 P358)
		(adj P357 P356)
		(adj P357 P337)
		(adj P357 P377)
		(adj P358 P359)
		(adj P358 P357)
		(adj P358 P338)
		(adj P358 P378)
		(adj P359 P360)
		(adj P359 P358)
		(adj P359 P339)
		(adj P359 P379)
		(adj P360 P359)
		(adj P360 P340)
		(adj P360 P380)
		(adj P361 P362)
		(adj P361 P341)
		(adj P361 P381)
		(adj P362 P363)
		(adj P362 P361)
		(adj P362 P342)
		(adj P362 P382)
		(adj P363 P364)
		(adj P363 P362)
		(adj P363 P343)
		(adj P363 P383)
		(adj P364 P365)
		(adj P364 P363)
		(adj P364 P344)
		(adj P364 P384)
		(adj P365 P366)
		(adj P365 P364)
		(adj P365 P345)
		(adj P365 P385)
		(adj P366 P367)
		(adj P366 P365)
		(adj P366 P346)
		(adj P366 P386)
		(adj P367 P368)
		(adj P367 P366)
		(adj P367 P347)
		(adj P367 P387)
		(adj P368 P369)
		(adj P368 P367)
		(adj P368 P348)
		(adj P368 P388)
		(adj P369 P370)
		(adj P369 P368)
		(adj P369 P349)
		(adj P369 P389)
		(adj P370 P371)
		(adj P370 P369)
		(adj P370 P350)
		(adj P370 P390)
		(adj P371 P372)
		(adj P371 P370)
		(adj P371 P351)
		(adj P371 P391)
		(adj P372 P373)
		(adj P372 P371)
		(adj P372 P352)
		(adj P372 P392)
		(adj P373 P374)
		(adj P373 P372)
		(adj P373 P353)
		(adj P373 P393)
		(adj P374 P375)
		(adj P374 P373)
		(adj P374 P354)
		(adj P374 P394)
		(adj P375 P376)
		(adj P375 P374)
		(adj P375 P355)
		(adj P375 P395)
		(adj P376 P377)
		(adj P376 P375)
		(adj P376 P356)
		(adj P376 P396)
		(adj P377 P378)
		(adj P377 P376)
		(adj P377 P357)
		(adj P377 P397)
		(adj P378 P379)
		(adj P378 P377)
		(adj P378 P358)
		(adj P378 P398)
		(adj P379 P380)
		(adj P379 P378)
		(adj P379 P359)
		(adj P379 P399)
		(adj P380 P379)
		(adj P380 P360)
		(adj P380 P400)
		(adj P381 P382)
		(adj P381 P361)
		(adj P382 P383)
		(adj P382 P381)
		(adj P382 P362)
		(adj P383 P384)
		(adj P383 P382)
		(adj P383 P363)
		(adj P384 P385)
		(adj P384 P383)
		(adj P384 P364)
		(adj P385 P386)
		(adj P385 P384)
		(adj P385 P365)
		(adj P386 P387)
		(adj P386 P385)
		(adj P386 P366)
		(adj P387 P388)
		(adj P387 P386)
		(adj P387 P367)
		(adj P388 P389)
		(adj P388 P387)
		(adj P388 P368)
		(adj P389 P390)
		(adj P389 P388)
		(adj P389 P369)
		(adj P390 P391)
		(adj P390 P389)
		(adj P390 P370)
		(adj P391 P392)
		(adj P391 P390)
		(adj P391 P371)
		(adj P392 P393)
		(adj P392 P391)
		(adj P392 P372)
		(adj P393 P394)
		(adj P393 P392)
		(adj P393 P373)
		(adj P394 P395)
		(adj P394 P393)
		(adj P394 P374)
		(adj P395 P396)
		(adj P395 P394)
		(adj P395 P375)
		(adj P396 P397)
		(adj P396 P395)
		(adj P396 P376)
		(adj P397 P398)
		(adj P397 P396)
		(adj P397 P377)
		(adj P398 P399)
		(adj P398 P397)
		(adj P398 P378)
		(adj P399 P400)
		(adj P399 P398)
		(adj P399 P379)
		(adj P400 P399)
		(adj P400 P380)
		(pos P382)
	)
	(:goal
		(and
			(pos P20)
		)
	)
)