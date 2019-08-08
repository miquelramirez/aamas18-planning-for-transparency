(define (problem Square-Room)

(:domain navigator)
(:objects
place_7_3
place_12_1
place_11_11
place_7_12
place_12_12
place_1_6
place_3_7
place_2_5
place_1_11
place_8_5
place_10_8
place_5_5
place_11_5
place_10_7
place_7_6
place_6_10
place_12_6
place_1_1
place_4_10
place_3_2
place_2_6
place_8_2
place_4_5
place_7_5
place_12_11
place_3_12
place_1_12
place_8_12
place_3_1
place_2_11
place_9_9
place_12_8
place_3_11
place_2_1
place_8_9
place_2_12
place_9_4
place_5_1
place_7_2
place_12_2
place_11_10
place_1_5
place_3_6
place_2_2
place_1_10
place_8_6
place_4_1
place_10_9
place_9_7
place_6_4
place_5_4
place_11_4
place_10_4
place_7_1
place_6_11
place_12_7
place_11_9
place_3_5
place_2_7
place_8_3
place_4_6
place_10_10
place_9_2
place_6_1
place_7_4
place_12_4
place_2_8
place_9_8
place_6_2
place_7_11
place_12_9
place_3_10
place_8_10
place_9_11
place_1_4
place_3_9
place_1_9
place_8_7
place_4_2
place_9_6
place_6_5
place_11_7
place_10_5
place_11_8
place_1_7
place_3_4
place_2_4
place_9_12
place_8_4
place_10_11
place_9_1
place_6_6
place_5_6
place_11_2
place_10_6
place_12_5
place_1_2
place_2_9
place_8_1
place_4_4
place_10_12
place_6_3
place_11_1
place_7_10
place_12_10
place_8_11
place_2_10
place_9_10
place_10_1
place_11_12
place_7_9
place_1_8
place_9_5
place_5_2
place_11_6
place_10_2
- place
)
(:init
(connected place_7_3 place_7_2) (connected place_7_3 place_7_4) (connected place_7_3 place_6_3) (connected place_7_3 place_8_3)
(connected place_12_1 place_12_2) (connected place_12_1 place_11_1)
(connected place_11_11 place_11_10) (connected place_11_11 place_11_12) (connected place_11_11 place_10_11) (connected place_11_11 place_12_11)
(connected place_7_12 place_7_11) (connected place_7_12 place_8_12)
(connected place_12_12 place_12_11) (connected place_12_12 place_11_12)
(connected place_1_6 place_1_5) (connected place_1_6 place_1_7) (connected place_1_6 place_2_6)
(connected place_3_7 place_3_6) (connected place_3_7 place_2_7)
(connected place_2_5 place_2_4) (connected place_2_5 place_2_6) (connected place_2_5 place_1_5) (connected place_2_5 place_3_5)
(connected place_1_11 place_1_10) (connected place_1_11 place_1_12) (connected place_1_11 place_2_11)
(connected place_8_5 place_8_4) (connected place_8_5 place_8_6) (connected place_8_5 place_7_5) (connected place_8_5 place_9_5)
(connected place_10_8 place_10_7) (connected place_10_8 place_10_9) (connected place_10_8 place_9_8) (connected place_10_8 place_11_8)
(connected place_5_5 place_5_4) (connected place_5_5 place_5_6) (connected place_5_5 place_4_5) (connected place_5_5 place_6_5)
(connected place_11_5 place_11_4) (connected place_11_5 place_11_6) (connected place_11_5 place_10_5) (connected place_11_5 place_12_5)
(connected place_10_7 place_10_6) (connected place_10_7 place_10_8) (connected place_10_7 place_9_7) (connected place_10_7 place_11_7)
(connected place_7_6 place_7_5) (connected place_7_6 place_6_6) (connected place_7_6 place_8_6)
(connected place_6_10 place_6_11) (connected place_6_10 place_7_10)
(connected place_12_6 place_12_5) (connected place_12_6 place_12_7) (connected place_12_6 place_11_6)
(connected place_1_1 place_1_2) (connected place_1_1 place_2_1)
(connected place_4_10 place_3_10)
(connected place_3_2 place_3_1) (connected place_3_2 place_2_2) (connected place_3_2 place_4_2)
(connected place_2_6 place_2_5) (connected place_2_6 place_2_7) (connected place_2_6 place_1_6) (connected place_2_6 place_3_6)
(connected place_8_2 place_8_1) (connected place_8_2 place_8_3) (connected place_8_2 place_7_2) (connected place_8_2 place_9_2)
(connected place_4_5 place_4_4) (connected place_4_5 place_4_6) (connected place_4_5 place_3_5) (connected place_4_5 place_5_5)
(connected place_7_5 place_7_4) (connected place_7_5 place_7_6) (connected place_7_5 place_6_5) (connected place_7_5 place_8_5)
(connected place_12_11 place_12_10) (connected place_12_11 place_12_12) (connected place_12_11 place_11_11)
(connected place_3_12 place_3_11) (connected place_3_12 place_2_12)
(connected place_1_12 place_1_11) (connected place_1_12 place_2_12) (at place_1_12)
(connected place_8_12 place_8_11) (connected place_8_12 place_7_12) (connected place_8_12 place_9_12)
(connected place_3_1 place_3_2) (connected place_3_1 place_2_1) (connected place_3_1 place_4_1)
(connected place_2_11 place_2_10) (connected place_2_11 place_2_12) (connected place_2_11 place_1_11) (connected place_2_11 place_3_11)
(connected place_9_9 place_9_8) (connected place_9_9 place_9_10) (connected place_9_9 place_8_9) (connected place_9_9 place_10_9)
(connected place_12_8 place_12_7) (connected place_12_8 place_12_9) (connected place_12_8 place_11_8)
(connected place_3_11 place_3_10) (connected place_3_11 place_3_12) (connected place_3_11 place_2_11)
(connected place_2_1 place_2_2) (connected place_2_1 place_1_1) (connected place_2_1 place_3_1)
(connected place_8_9 place_8_10) (connected place_8_9 place_7_9) (connected place_8_9 place_9_9)
(connected place_2_12 place_2_11) (connected place_2_12 place_1_12) (connected place_2_12 place_3_12)
(connected place_9_4 place_9_5) (connected place_9_4 place_8_4) (connected place_9_4 place_10_4)
(connected place_5_1 place_5_2) (connected place_5_1 place_4_1) (connected place_5_1 place_6_1)
(connected place_7_2 place_7_1) (connected place_7_2 place_7_3) (connected place_7_2 place_6_2) (connected place_7_2 place_8_2)
(connected place_12_2 place_12_1) (connected place_12_2 place_11_2)
(connected place_11_10 place_11_9) (connected place_11_10 place_11_11) (connected place_11_10 place_10_10) (connected place_11_10 place_12_10)
(connected place_1_5 place_1_4) (connected place_1_5 place_1_6) (connected place_1_5 place_2_5)
(connected place_3_6 place_3_5) (connected place_3_6 place_3_7) (connected place_3_6 place_2_6) (connected place_3_6 place_4_6)
(connected place_2_2 place_2_1) (connected place_2_2 place_1_2) (connected place_2_2 place_3_2)
(connected place_1_10 place_1_9) (connected place_1_10 place_1_11) (connected place_1_10 place_2_10)
(connected place_8_6 place_8_5) (connected place_8_6 place_8_7) (connected place_8_6 place_7_6) (connected place_8_6 place_9_6)
(connected place_4_1 place_4_2) (connected place_4_1 place_3_1) (connected place_4_1 place_5_1)
(connected place_10_9 place_10_8) (connected place_10_9 place_10_10) (connected place_10_9 place_9_9) (connected place_10_9 place_11_9)
(connected place_9_7 place_9_6) (connected place_9_7 place_9_8) (connected place_9_7 place_8_7) (connected place_9_7 place_10_7)
(connected place_6_4 place_6_3) (connected place_6_4 place_6_5) (connected place_6_4 place_5_4) (connected place_6_4 place_7_4)
(connected place_5_4 place_5_5) (connected place_5_4 place_4_4) (connected place_5_4 place_6_4)
(connected place_11_4 place_11_5) (connected place_11_4 place_10_4) (connected place_11_4 place_12_4)
(connected place_10_4 place_10_5) (connected place_10_4 place_9_4) (connected place_10_4 place_11_4)
(connected place_7_1 place_7_2) (connected place_7_1 place_6_1) (connected place_7_1 place_8_1)
(connected place_6_11 place_6_10) (connected place_6_11 place_7_11)
(connected place_12_7 place_12_6) (connected place_12_7 place_12_8) (connected place_12_7 place_11_7)
(connected place_11_9 place_11_8) (connected place_11_9 place_11_10) (connected place_11_9 place_10_9) (connected place_11_9 place_12_9)
(connected place_3_5 place_3_4) (connected place_3_5 place_3_6) (connected place_3_5 place_2_5) (connected place_3_5 place_4_5)
(connected place_2_7 place_2_6) (connected place_2_7 place_2_8) (connected place_2_7 place_1_7) (connected place_2_7 place_3_7)
(connected place_8_3 place_8_2) (connected place_8_3 place_8_4) (connected place_8_3 place_7_3)
(connected place_4_6 place_4_5) (connected place_4_6 place_3_6) (connected place_4_6 place_5_6)
(connected place_10_10 place_10_9) (connected place_10_10 place_10_11) (connected place_10_10 place_9_10) (connected place_10_10 place_11_10)
(connected place_9_2 place_9_1) (connected place_9_2 place_8_2) (connected place_9_2 place_10_2)
(connected place_6_1 place_6_2) (connected place_6_1 place_5_1) (connected place_6_1 place_7_1)
(connected place_7_4 place_7_3) (connected place_7_4 place_7_5) (connected place_7_4 place_6_4) (connected place_7_4 place_8_4)
(connected place_12_4 place_12_5) (connected place_12_4 place_11_4)
(connected place_2_8 place_2_7) (connected place_2_8 place_2_9) (connected place_2_8 place_1_8)
(connected place_9_8 place_9_7) (connected place_9_8 place_9_9) (connected place_9_8 place_10_8)
(connected place_6_2 place_6_1) (connected place_6_2 place_6_3) (connected place_6_2 place_5_2) (connected place_6_2 place_7_2)
(connected place_7_11 place_7_10) (connected place_7_11 place_7_12) (connected place_7_11 place_6_11) (connected place_7_11 place_8_11)
(connected place_12_9 place_12_8) (connected place_12_9 place_12_10) (connected place_12_9 place_11_9)
(connected place_3_10 place_3_9) (connected place_3_10 place_3_11) (connected place_3_10 place_2_10) (connected place_3_10 place_4_10)
(connected place_8_10 place_8_9) (connected place_8_10 place_8_11) (connected place_8_10 place_7_10) (connected place_8_10 place_9_10)
(connected place_9_11 place_9_10) (connected place_9_11 place_9_12) (connected place_9_11 place_8_11) (connected place_9_11 place_10_11)
(connected place_1_4 place_1_5) (connected place_1_4 place_2_4)
(connected place_3_9 place_3_10) (connected place_3_9 place_2_9)
(connected place_1_9 place_1_8) (connected place_1_9 place_1_10) (connected place_1_9 place_2_9)
(connected place_8_7 place_8_6) (connected place_8_7 place_9_7)
(connected place_4_2 place_4_1) (connected place_4_2 place_3_2) (connected place_4_2 place_5_2)
(connected place_9_6 place_9_5) (connected place_9_6 place_9_7) (connected place_9_6 place_8_6) (connected place_9_6 place_10_6)
(connected place_6_5 place_6_4) (connected place_6_5 place_6_6) (connected place_6_5 place_5_5) (connected place_6_5 place_7_5)
(connected place_11_7 place_11_6) (connected place_11_7 place_11_8) (connected place_11_7 place_10_7) (connected place_11_7 place_12_7)
(connected place_10_5 place_10_4) (connected place_10_5 place_10_6) (connected place_10_5 place_9_5) (connected place_10_5 place_11_5)
(connected place_11_8 place_11_7) (connected place_11_8 place_11_9) (connected place_11_8 place_10_8) (connected place_11_8 place_12_8)
(connected place_1_7 place_1_6) (connected place_1_7 place_1_8) (connected place_1_7 place_2_7)
(connected place_3_4 place_3_5) (connected place_3_4 place_2_4) (connected place_3_4 place_4_4)
(connected place_2_4 place_2_5) (connected place_2_4 place_1_4) (connected place_2_4 place_3_4)
(connected place_9_12 place_9_11) (connected place_9_12 place_8_12) (connected place_9_12 place_10_12)
(connected place_8_4 place_8_3) (connected place_8_4 place_8_5) (connected place_8_4 place_7_4) (connected place_8_4 place_9_4)
(connected place_10_11 place_10_10) (connected place_10_11 place_10_12) (connected place_10_11 place_9_11) (connected place_10_11 place_11_11)
(connected place_9_1 place_9_2) (connected place_9_1 place_8_1) (connected place_9_1 place_10_1)
(connected place_6_6 place_6_5) (connected place_6_6 place_5_6) (connected place_6_6 place_7_6)
(connected place_5_6 place_5_5) (connected place_5_6 place_4_6) (connected place_5_6 place_6_6)
(connected place_11_2 place_11_1) (connected place_11_2 place_10_2) (connected place_11_2 place_12_2)
(connected place_10_6 place_10_5) (connected place_10_6 place_10_7) (connected place_10_6 place_9_6) (connected place_10_6 place_11_6)
(connected place_12_5 place_12_4) (connected place_12_5 place_12_6) (connected place_12_5 place_11_5)
(connected place_1_2 place_1_1) (connected place_1_2 place_2_2)
(connected place_2_9 place_2_8) (connected place_2_9 place_2_10) (connected place_2_9 place_1_9) (connected place_2_9 place_3_9)
(connected place_8_1 place_8_2) (connected place_8_1 place_7_1) (connected place_8_1 place_9_1)
(connected place_4_4 place_4_5) (connected place_4_4 place_3_4) (connected place_4_4 place_5_4)
(connected place_10_12 place_10_11) (connected place_10_12 place_9_12) (connected place_10_12 place_11_12)
(connected place_6_3 place_6_2) (connected place_6_3 place_6_4) (connected place_6_3 place_7_3)
(connected place_11_1 place_11_2) (connected place_11_1 place_10_1) (connected place_11_1 place_12_1)
(connected place_7_10 place_7_9) (connected place_7_10 place_7_11) (connected place_7_10 place_6_10) (connected place_7_10 place_8_10)
(connected place_12_10 place_12_9) (connected place_12_10 place_12_11) (connected place_12_10 place_11_10)
(connected place_8_11 place_8_10) (connected place_8_11 place_8_12) (connected place_8_11 place_7_11) (connected place_8_11 place_9_11)
(connected place_2_10 place_2_9) (connected place_2_10 place_2_11) (connected place_2_10 place_1_10) (connected place_2_10 place_3_10)
(connected place_9_10 place_9_9) (connected place_9_10 place_9_11) (connected place_9_10 place_8_10) (connected place_9_10 place_10_10)
(connected place_10_1 place_10_2) (connected place_10_1 place_9_1) (connected place_10_1 place_11_1)
(connected place_11_12 place_11_11) (connected place_11_12 place_10_12) (connected place_11_12 place_12_12)
(connected place_7_9 place_7_10) (connected place_7_9 place_8_9)
(connected place_1_8 place_1_7) (connected place_1_8 place_1_9) (connected place_1_8 place_2_8)
(connected place_9_5 place_9_4) (connected place_9_5 place_9_6) (connected place_9_5 place_8_5) (connected place_9_5 place_10_5)
(connected place_5_2 place_5_1) (connected place_5_2 place_4_2) (connected place_5_2 place_6_2)
(connected place_11_6 place_11_5) (connected place_11_6 place_11_7) (connected place_11_6 place_10_6) (connected place_11_6 place_12_6)
(connected place_10_2 place_10_1) (connected place_10_2 place_9_2) (connected place_10_2 place_11_2)
)
(:goal
(and
(at place_12_2)
)
)
)
