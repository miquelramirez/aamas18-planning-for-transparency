(define (problem Torus)

(:domain navigator)
(:objects
place_7_3
place_14_1
place_3_2
place_27_1
place_4_5
place_28_10
place_18_10
place_23_9
place_3_11
place_27_6
place_28_1
place_5_1
place_22_7
place_23_6
place_15_10
place_24_2
place_25_3
place_4_11
place_2_7
place_5_10
place_6_1
place_7_4
place_19_1
place_24_9
place_25_4
place_26_3
place_27_10
place_16_11
place_17_10
place_20_1
place_22_11
place_26_10
place_3_4
place_27_3
place_4_7
place_28_4
place_5_6
place_16_2
place_22_2
place_23_11
place_11_1
place_12_10
place_13_11
place_28_3
place_2_10
place_7_9
place_22_5
place_12_1
place_24_4
place_1_6
place_25_1
place_2_5
place_26_6
place_5_8
place_6_7
place_7_6
place_8_2
place_24_11
place_14_2
place_25_10
place_26_1
place_3_1
place_21_2
place_22_9
place_11_10
place_26_8
place_3_6
place_27_5
place_1_10
place_4_1
place_28_6
place_5_4
place_6_11
place_17_1
place_20_10
place_21_11
place_23_5
place_10_10
place_1_3
place_4_8
place_2_8
place_6_2
place_7_11
place_18_1
place_23_2
place_13_2
place_24_6
place_1_4
place_25_7
place_2_3
place_26_4
place_27_9
place_6_5
place_9_1
place_25_8
place_3_3
place_4_4
place_28_9
place_19_10
place_8_11
place_9_10
place_10_1
place_14_11
place_15_2
place_3_8
place_27_7
place_1_8
place_4_3
place_5_2
place_6_9
place_22_6
place_23_7
place_15_11
place_24_1
place_1_1
place_4_10
place_2_6
place_5_11
place_7_5
place_24_8
place_25_5
place_2_1
place_26_2
place_27_11
place_7_2
place_16_10
place_17_11
place_22_10
place_3_5
place_4_6
place_28_11
place_5_7
place_16_1
place_18_11
place_23_8
place_3_10
place_28_2
place_18_2
place_22_4
place_23_1
place_24_3
place_1_7
place_25_2
place_2_4
place_5_9
place_6_6
place_7_7
place_8_1
place_24_10
place_25_11
place_20_2
place_22_8
place_10_2
place_11_11
place_15_1
place_26_11
place_3_7
place_27_2
place_1_11
place_28_5
place_5_5
place_6_10
place_17_2
place_22_3
place_23_10
place_12_11
place_13_10
place_2_11
place_7_8
place_23_3
place_12_2
place_24_5
place_1_5
place_2_2
place_26_7
place_6_4
place_7_1
place_19_2
place_9_2
place_25_9
place_28_8
place_19_11
place_21_1
place_8_10
place_9_11
place_14_10
place_26_9
place_3_9
place_27_4
place_1_9
place_4_2
place_28_7
place_5_3
place_6_8
place_20_11
place_21_10
place_22_1
place_23_4
place_10_11
place_11_2
place_1_2
place_4_9
place_2_9
place_6_3
place_7_10
place_13_1
place_24_7
place_25_6
place_26_5
place_27_8
- place
)
(:init
(connected place_7_3 place_7_2) (connected place_7_3 place_7_4) (connected place_7_3 place_6_3)
(connected place_14_1 place_14_2) (connected place_14_1 place_13_1) (connected place_14_1 place_15_1)
(connected place_3_2 place_3_1) (connected place_3_2 place_3_3) (connected place_3_2 place_2_2) (connected place_3_2 place_4_2)
(connected place_27_1 place_27_2) (connected place_27_1 place_26_1) (connected place_27_1 place_28_1)
(connected place_4_5 place_4_4) (connected place_4_5 place_4_6) (connected place_4_5 place_3_5) (connected place_4_5 place_5_5)
(connected place_28_10 place_28_9) (connected place_28_10 place_28_11) (connected place_28_10 place_27_10)
(connected place_18_10 place_18_11) (connected place_18_10 place_17_10) (connected place_18_10 place_19_10)
(connected place_23_9 place_23_8) (connected place_23_9 place_23_10) (connected place_23_9 place_22_9) (connected place_23_9 place_24_9)
(connected place_3_11 place_3_10) (connected place_3_11 place_2_11) (connected place_3_11 place_4_11)
(connected place_27_6 place_27_5) (connected place_27_6 place_27_7) (connected place_27_6 place_26_6) (connected place_27_6 place_28_6)
(connected place_28_1 place_28_2) (connected place_28_1 place_27_1)
(connected place_5_1 place_5_2) (connected place_5_1 place_4_1) (connected place_5_1 place_6_1)
(connected place_22_7 place_22_6) (connected place_22_7 place_22_8) (connected place_22_7 place_23_7)
(connected place_23_6 place_23_5) (connected place_23_6 place_23_7) (connected place_23_6 place_22_6) (connected place_23_6 place_24_6)
(connected place_15_10 place_15_11) (connected place_15_10 place_14_10) (connected place_15_10 place_16_10)
(connected place_24_2 place_24_1) (connected place_24_2 place_24_3) (connected place_24_2 place_23_2) (connected place_24_2 place_25_2)
(connected place_25_3 place_25_2) (connected place_25_3 place_25_4) (connected place_25_3 place_24_3) (connected place_25_3 place_26_3)
(connected place_4_11 place_4_10) (connected place_4_11 place_3_11) (connected place_4_11 place_5_11)
(connected place_2_7 place_2_6) (connected place_2_7 place_2_8) (connected place_2_7 place_1_7) (connected place_2_7 place_3_7)
(connected place_5_10 place_5_9) (connected place_5_10 place_5_11) (connected place_5_10 place_4_10) (connected place_5_10 place_6_10)
(connected place_6_1 place_6_2) (connected place_6_1 place_5_1) (connected place_6_1 place_7_1)
(connected place_7_4 place_7_3) (connected place_7_4 place_7_5) (connected place_7_4 place_6_4)
(connected place_19_1 place_19_2) (connected place_19_1 place_18_1) (connected place_19_1 place_20_1)
(connected place_24_9 place_24_8) (connected place_24_9 place_24_10) (connected place_24_9 place_23_9) (connected place_24_9 place_25_9)
(connected place_25_4 place_25_3) (connected place_25_4 place_25_5) (connected place_25_4 place_24_4) (connected place_25_4 place_26_4)
(connected place_26_3 place_26_2) (connected place_26_3 place_26_4) (connected place_26_3 place_25_3) (connected place_26_3 place_27_3)
(connected place_27_10 place_27_9) (connected place_27_10 place_27_11) (connected place_27_10 place_26_10) (connected place_27_10 place_28_10)
(connected place_16_11 place_16_10) (connected place_16_11 place_15_11) (connected place_16_11 place_17_11)
(connected place_17_10 place_17_11) (connected place_17_10 place_16_10) (connected place_17_10 place_18_10)
(connected place_20_1 place_20_2) (connected place_20_1 place_19_1) (connected place_20_1 place_21_1)
(connected place_22_11 place_22_10) (connected place_22_11 place_21_11) (connected place_22_11 place_23_11)
(connected place_26_10 place_26_9) (connected place_26_10 place_26_11) (connected place_26_10 place_25_10) (connected place_26_10 place_27_10)
(connected place_3_4 place_3_3) (connected place_3_4 place_3_5) (connected place_3_4 place_2_4) (connected place_3_4 place_4_4)
(connected place_27_3 place_27_2) (connected place_27_3 place_27_4) (connected place_27_3 place_26_3) (connected place_27_3 place_28_3)
(connected place_4_7 place_4_6) (connected place_4_7 place_4_8) (connected place_4_7 place_3_7) (connected place_4_7 place_5_7)
(connected place_28_4 place_28_3) (connected place_28_4 place_28_5) (connected place_28_4 place_27_4)
(connected place_5_6 place_5_5) (connected place_5_6 place_5_7) (connected place_5_6 place_4_6) (connected place_5_6 place_6_6)
(connected place_16_2 place_16_1) (connected place_16_2 place_15_2) (connected place_16_2 place_17_2)
(connected place_22_2 place_22_1) (connected place_22_2 place_22_3) (connected place_22_2 place_21_2) (connected place_22_2 place_23_2)
(connected place_23_11 place_23_10) (connected place_23_11 place_22_11) (connected place_23_11 place_24_11)
(connected place_11_1 place_11_2) (connected place_11_1 place_10_1) (connected place_11_1 place_12_1)
(connected place_12_10 place_12_11) (connected place_12_10 place_11_10) (connected place_12_10 place_13_10)
(connected place_13_11 place_13_10) (connected place_13_11 place_12_11) (connected place_13_11 place_14_11)
(connected place_28_3 place_28_2) (connected place_28_3 place_28_4) (connected place_28_3 place_27_3)
(connected place_2_10 place_2_9) (connected place_2_10 place_2_11) (connected place_2_10 place_1_10) (connected place_2_10 place_3_10)
(connected place_7_9 place_7_8) (connected place_7_9 place_7_10) (connected place_7_9 place_6_9)
(connected place_22_5 place_22_4) (connected place_22_5 place_22_6) (connected place_22_5 place_23_5)
(connected place_12_1 place_12_2) (connected place_12_1 place_11_1) (connected place_12_1 place_13_1)
(connected place_24_4 place_24_3) (connected place_24_4 place_24_5) (connected place_24_4 place_23_4) (connected place_24_4 place_25_4)
(connected place_1_6 place_1_5) (connected place_1_6 place_1_7) (connected place_1_6 place_2_6)
(connected place_25_1 place_25_2) (connected place_25_1 place_24_1) (connected place_25_1 place_26_1)
(connected place_2_5 place_2_4) (connected place_2_5 place_2_6) (connected place_2_5 place_1_5) (connected place_2_5 place_3_5)
(connected place_26_6 place_26_5) (connected place_26_6 place_26_7) (connected place_26_6 place_25_6) (connected place_26_6 place_27_6)
(connected place_5_8 place_5_7) (connected place_5_8 place_5_9) (connected place_5_8 place_4_8) (connected place_5_8 place_6_8)
(connected place_6_7 place_6_6) (connected place_6_7 place_6_8) (connected place_6_7 place_5_7) (connected place_6_7 place_7_7)
(connected place_7_6 place_7_5) (connected place_7_6 place_7_7) (connected place_7_6 place_6_6)
(connected place_8_2 place_8_1) (connected place_8_2 place_7_2) (connected place_8_2 place_9_2)
(connected place_24_11 place_24_10) (connected place_24_11 place_23_11) (connected place_24_11 place_25_11)
(connected place_14_2 place_14_1) (connected place_14_2 place_13_2) (connected place_14_2 place_15_2)
(connected place_25_10 place_25_9) (connected place_25_10 place_25_11) (connected place_25_10 place_24_10) (connected place_25_10 place_26_10)
(connected place_26_1 place_26_2) (connected place_26_1 place_25_1) (connected place_26_1 place_27_1)
(connected place_3_1 place_3_2) (connected place_3_1 place_2_1) (connected place_3_1 place_4_1)
(connected place_21_2 place_21_1) (connected place_21_2 place_20_2) (connected place_21_2 place_22_2)
(connected place_22_9 place_22_8) (connected place_22_9 place_22_10) (connected place_22_9 place_23_9)
(connected place_11_10 place_11_11) (connected place_11_10 place_10_10) (connected place_11_10 place_12_10)
(connected place_26_8 place_26_7) (connected place_26_8 place_26_9) (connected place_26_8 place_25_8) (connected place_26_8 place_27_8)
(connected place_3_6 place_3_5) (connected place_3_6 place_3_7) (connected place_3_6 place_2_6) (connected place_3_6 place_4_6)
(connected place_27_5 place_27_4) (connected place_27_5 place_27_6) (connected place_27_5 place_26_5) (connected place_27_5 place_28_5)
(connected place_1_10 place_1_9) (connected place_1_10 place_1_11) (connected place_1_10 place_2_10)
(connected place_4_1 place_4_2) (connected place_4_1 place_3_1) (connected place_4_1 place_5_1)
(connected place_28_6 place_28_5) (connected place_28_6 place_28_7) (connected place_28_6 place_27_6)
(connected place_5_4 place_5_3) (connected place_5_4 place_5_5) (connected place_5_4 place_4_4) (connected place_5_4 place_6_4)
(connected place_6_11 place_6_10) (connected place_6_11 place_5_11) (connected place_6_11 place_7_11)
(connected place_17_1 place_17_2) (connected place_17_1 place_16_1) (connected place_17_1 place_18_1)
(connected place_20_10 place_20_11) (connected place_20_10 place_19_10) (connected place_20_10 place_21_10)
(connected place_21_11 place_21_10) (connected place_21_11 place_20_11) (connected place_21_11 place_22_11)
(connected place_23_5 place_23_4) (connected place_23_5 place_23_6) (connected place_23_5 place_22_5) (connected place_23_5 place_24_5)
(connected place_10_10 place_10_11) (connected place_10_10 place_9_10) (connected place_10_10 place_11_10)
(connected place_1_3 place_1_2) (connected place_1_3 place_1_4) (connected place_1_3 place_2_3)
(connected place_4_8 place_4_7) (connected place_4_8 place_4_9) (connected place_4_8 place_3_8) (connected place_4_8 place_5_8)
(connected place_2_8 place_2_7) (connected place_2_8 place_2_9) (connected place_2_8 place_1_8) (connected place_2_8 place_3_8)
(connected place_6_2 place_6_1) (connected place_6_2 place_6_3) (connected place_6_2 place_5_2) (connected place_6_2 place_7_2)
(connected place_7_11 place_7_10) (connected place_7_11 place_6_11) (connected place_7_11 place_8_11)
(connected place_18_1 place_18_2) (connected place_18_1 place_17_1) (connected place_18_1 place_19_1)
(connected place_23_2 place_23_1) (connected place_23_2 place_23_3) (connected place_23_2 place_22_2) (connected place_23_2 place_24_2)
(connected place_13_2 place_13_1) (connected place_13_2 place_12_2) (connected place_13_2 place_14_2)
(connected place_24_6 place_24_5) (connected place_24_6 place_24_7) (connected place_24_6 place_23_6) (connected place_24_6 place_25_6)
(connected place_1_4 place_1_3) (connected place_1_4 place_1_5) (connected place_1_4 place_2_4)
(connected place_25_7 place_25_6) (connected place_25_7 place_25_8) (connected place_25_7 place_24_7) (connected place_25_7 place_26_7)
(connected place_2_3 place_2_2) (connected place_2_3 place_2_4) (connected place_2_3 place_1_3) (connected place_2_3 place_3_3)
(connected place_26_4 place_26_3) (connected place_26_4 place_26_5) (connected place_26_4 place_25_4) (connected place_26_4 place_27_4)
(connected place_27_9 place_27_8) (connected place_27_9 place_27_10) (connected place_27_9 place_26_9) (connected place_27_9 place_28_9)
(connected place_6_5 place_6_4) (connected place_6_5 place_6_6) (connected place_6_5 place_5_5) (connected place_6_5 place_7_5)
(connected place_9_1 place_9_2) (connected place_9_1 place_8_1) (connected place_9_1 place_10_1)
(connected place_25_8 place_25_7) (connected place_25_8 place_25_9) (connected place_25_8 place_24_8) (connected place_25_8 place_26_8)
(connected place_3_3 place_3_2) (connected place_3_3 place_3_4) (connected place_3_3 place_2_3) (connected place_3_3 place_4_3)
(connected place_4_4 place_4_3) (connected place_4_4 place_4_5) (connected place_4_4 place_3_4) (connected place_4_4 place_5_4)
(connected place_28_9 place_28_8) (connected place_28_9 place_28_10) (connected place_28_9 place_27_9)
(connected place_19_10 place_19_11) (connected place_19_10 place_18_10) (connected place_19_10 place_20_10)
(connected place_8_11 place_8_10) (connected place_8_11 place_7_11) (connected place_8_11 place_9_11)
(connected place_9_10 place_9_11) (connected place_9_10 place_8_10) (connected place_9_10 place_10_10)
(connected place_10_1 place_10_2) (connected place_10_1 place_9_1) (connected place_10_1 place_11_1)
(connected place_14_11 place_14_10) (connected place_14_11 place_13_11) (connected place_14_11 place_15_11) (at place_14_11)
(connected place_15_2 place_15_1) (connected place_15_2 place_14_2) (connected place_15_2 place_16_2)
(connected place_3_8 place_3_7) (connected place_3_8 place_3_9) (connected place_3_8 place_2_8) (connected place_3_8 place_4_8)
(connected place_27_7 place_27_6) (connected place_27_7 place_27_8) (connected place_27_7 place_26_7) (connected place_27_7 place_28_7)
(connected place_1_8 place_1_7) (connected place_1_8 place_1_9) (connected place_1_8 place_2_8)
(connected place_4_3 place_4_2) (connected place_4_3 place_4_4) (connected place_4_3 place_3_3) (connected place_4_3 place_5_3)
(connected place_5_2 place_5_1) (connected place_5_2 place_5_3) (connected place_5_2 place_4_2) (connected place_5_2 place_6_2)
(connected place_6_9 place_6_8) (connected place_6_9 place_6_10) (connected place_6_9 place_5_9) (connected place_6_9 place_7_9)
(connected place_22_6 place_22_5) (connected place_22_6 place_22_7) (connected place_22_6 place_23_6)
(connected place_23_7 place_23_6) (connected place_23_7 place_23_8) (connected place_23_7 place_22_7) (connected place_23_7 place_24_7)
(connected place_15_11 place_15_10) (connected place_15_11 place_14_11) (connected place_15_11 place_16_11)
(connected place_24_1 place_24_2) (connected place_24_1 place_23_1) (connected place_24_1 place_25_1)
(connected place_1_1 place_1_2) (connected place_1_1 place_2_1)
(connected place_4_10 place_4_9) (connected place_4_10 place_4_11) (connected place_4_10 place_3_10) (connected place_4_10 place_5_10)
(connected place_2_6 place_2_5) (connected place_2_6 place_2_7) (connected place_2_6 place_1_6) (connected place_2_6 place_3_6)
(connected place_5_11 place_5_10) (connected place_5_11 place_4_11) (connected place_5_11 place_6_11)
(connected place_7_5 place_7_4) (connected place_7_5 place_7_6) (connected place_7_5 place_6_5)
(connected place_24_8 place_24_7) (connected place_24_8 place_24_9) (connected place_24_8 place_23_8) (connected place_24_8 place_25_8)
(connected place_25_5 place_25_4) (connected place_25_5 place_25_6) (connected place_25_5 place_24_5) (connected place_25_5 place_26_5)
(connected place_2_1 place_2_2) (connected place_2_1 place_1_1) (connected place_2_1 place_3_1)
(connected place_26_2 place_26_1) (connected place_26_2 place_26_3) (connected place_26_2 place_25_2) (connected place_26_2 place_27_2)
(connected place_27_11 place_27_10) (connected place_27_11 place_26_11) (connected place_27_11 place_28_11)
(connected place_7_2 place_7_1) (connected place_7_2 place_7_3) (connected place_7_2 place_6_2) (connected place_7_2 place_8_2)
(connected place_16_10 place_16_11) (connected place_16_10 place_15_10) (connected place_16_10 place_17_10)
(connected place_17_11 place_17_10) (connected place_17_11 place_16_11) (connected place_17_11 place_18_11)
(connected place_22_10 place_22_9) (connected place_22_10 place_22_11) (connected place_22_10 place_21_10) (connected place_22_10 place_23_10)
(connected place_3_5 place_3_4) (connected place_3_5 place_3_6) (connected place_3_5 place_2_5) (connected place_3_5 place_4_5)
(connected place_4_6 place_4_5) (connected place_4_6 place_4_7) (connected place_4_6 place_3_6) (connected place_4_6 place_5_6)
(connected place_28_11 place_28_10) (connected place_28_11 place_27_11)
(connected place_5_7 place_5_6) (connected place_5_7 place_5_8) (connected place_5_7 place_4_7) (connected place_5_7 place_6_7)
(connected place_16_1 place_16_2) (connected place_16_1 place_15_1) (connected place_16_1 place_17_1)
(connected place_18_11 place_18_10) (connected place_18_11 place_17_11) (connected place_18_11 place_19_11)
(connected place_23_8 place_23_7) (connected place_23_8 place_23_9) (connected place_23_8 place_22_8) (connected place_23_8 place_24_8)
(connected place_3_10 place_3_9) (connected place_3_10 place_3_11) (connected place_3_10 place_2_10) (connected place_3_10 place_4_10)
(connected place_28_2 place_28_1) (connected place_28_2 place_28_3) (connected place_28_2 place_27_2)
(connected place_18_2 place_18_1) (connected place_18_2 place_17_2) (connected place_18_2 place_19_2)
(connected place_22_4 place_22_3) (connected place_22_4 place_22_5) (connected place_22_4 place_23_4)
(connected place_23_1 place_23_2) (connected place_23_1 place_22_1) (connected place_23_1 place_24_1)
(connected place_24_3 place_24_2) (connected place_24_3 place_24_4) (connected place_24_3 place_23_3) (connected place_24_3 place_25_3)
(connected place_1_7 place_1_6) (connected place_1_7 place_1_8) (connected place_1_7 place_2_7)
(connected place_25_2 place_25_1) (connected place_25_2 place_25_3) (connected place_25_2 place_24_2) (connected place_25_2 place_26_2)
(connected place_2_4 place_2_3) (connected place_2_4 place_2_5) (connected place_2_4 place_1_4) (connected place_2_4 place_3_4)
(connected place_5_9 place_5_8) (connected place_5_9 place_5_10) (connected place_5_9 place_4_9) (connected place_5_9 place_6_9)
(connected place_6_6 place_6_5) (connected place_6_6 place_6_7) (connected place_6_6 place_5_6) (connected place_6_6 place_7_6)
(connected place_7_7 place_7_6) (connected place_7_7 place_7_8) (connected place_7_7 place_6_7)
(connected place_8_1 place_8_2) (connected place_8_1 place_7_1) (connected place_8_1 place_9_1)
(connected place_24_10 place_24_9) (connected place_24_10 place_24_11) (connected place_24_10 place_23_10) (connected place_24_10 place_25_10)
(connected place_25_11 place_25_10) (connected place_25_11 place_24_11) (connected place_25_11 place_26_11)
(connected place_20_2 place_20_1) (connected place_20_2 place_19_2) (connected place_20_2 place_21_2)
(connected place_22_8 place_22_7) (connected place_22_8 place_22_9) (connected place_22_8 place_23_8)
(connected place_10_2 place_10_1) (connected place_10_2 place_9_2) (connected place_10_2 place_11_2)
(connected place_11_11 place_11_10) (connected place_11_11 place_10_11) (connected place_11_11 place_12_11)
(connected place_15_1 place_15_2) (connected place_15_1 place_14_1) (connected place_15_1 place_16_1)
(connected place_26_11 place_26_10) (connected place_26_11 place_25_11) (connected place_26_11 place_27_11)
(connected place_3_7 place_3_6) (connected place_3_7 place_3_8) (connected place_3_7 place_2_7) (connected place_3_7 place_4_7)
(connected place_27_2 place_27_1) (connected place_27_2 place_27_3) (connected place_27_2 place_26_2) (connected place_27_2 place_28_2)
(connected place_1_11 place_1_10) (connected place_1_11 place_2_11)
(connected place_28_5 place_28_4) (connected place_28_5 place_28_6) (connected place_28_5 place_27_5)
(connected place_5_5 place_5_4) (connected place_5_5 place_5_6) (connected place_5_5 place_4_5) (connected place_5_5 place_6_5)
(connected place_6_10 place_6_9) (connected place_6_10 place_6_11) (connected place_6_10 place_5_10) (connected place_6_10 place_7_10)
(connected place_17_2 place_17_1) (connected place_17_2 place_16_2) (connected place_17_2 place_18_2)
(connected place_22_3 place_22_2) (connected place_22_3 place_22_4) (connected place_22_3 place_23_3)
(connected place_23_10 place_23_9) (connected place_23_10 place_23_11) (connected place_23_10 place_22_10) (connected place_23_10 place_24_10)
(connected place_12_11 place_12_10) (connected place_12_11 place_11_11) (connected place_12_11 place_13_11)
(connected place_13_10 place_13_11) (connected place_13_10 place_12_10) (connected place_13_10 place_14_10)
(connected place_2_11 place_2_10) (connected place_2_11 place_1_11) (connected place_2_11 place_3_11)
(connected place_7_8 place_7_7) (connected place_7_8 place_7_9) (connected place_7_8 place_6_8)
(connected place_23_3 place_23_2) (connected place_23_3 place_23_4) (connected place_23_3 place_22_3) (connected place_23_3 place_24_3)
(connected place_12_2 place_12_1) (connected place_12_2 place_11_2) (connected place_12_2 place_13_2)
(connected place_24_5 place_24_4) (connected place_24_5 place_24_6) (connected place_24_5 place_23_5) (connected place_24_5 place_25_5)
(connected place_1_5 place_1_4) (connected place_1_5 place_1_6) (connected place_1_5 place_2_5)
(connected place_2_2 place_2_1) (connected place_2_2 place_2_3) (connected place_2_2 place_1_2) (connected place_2_2 place_3_2)
(connected place_26_7 place_26_6) (connected place_26_7 place_26_8) (connected place_26_7 place_25_7) (connected place_26_7 place_27_7)
(connected place_6_4 place_6_3) (connected place_6_4 place_6_5) (connected place_6_4 place_5_4) (connected place_6_4 place_7_4)
(connected place_7_1 place_7_2) (connected place_7_1 place_6_1) (connected place_7_1 place_8_1)
(connected place_19_2 place_19_1) (connected place_19_2 place_18_2) (connected place_19_2 place_20_2)
(connected place_9_2 place_9_1) (connected place_9_2 place_8_2) (connected place_9_2 place_10_2)
(connected place_25_9 place_25_8) (connected place_25_9 place_25_10) (connected place_25_9 place_24_9) (connected place_25_9 place_26_9)
(connected place_28_8 place_28_7) (connected place_28_8 place_28_9) (connected place_28_8 place_27_8)
(connected place_19_11 place_19_10) (connected place_19_11 place_18_11) (connected place_19_11 place_20_11)
(connected place_21_1 place_21_2) (connected place_21_1 place_20_1) (connected place_21_1 place_22_1)
(connected place_8_10 place_8_11) (connected place_8_10 place_7_10) (connected place_8_10 place_9_10)
(connected place_9_11 place_9_10) (connected place_9_11 place_8_11) (connected place_9_11 place_10_11)
(connected place_14_10 place_14_11) (connected place_14_10 place_13_10) (connected place_14_10 place_15_10)
(connected place_26_9 place_26_8) (connected place_26_9 place_26_10) (connected place_26_9 place_25_9) (connected place_26_9 place_27_9)
(connected place_3_9 place_3_8) (connected place_3_9 place_3_10) (connected place_3_9 place_2_9) (connected place_3_9 place_4_9)
(connected place_27_4 place_27_3) (connected place_27_4 place_27_5) (connected place_27_4 place_26_4) (connected place_27_4 place_28_4)
(connected place_1_9 place_1_8) (connected place_1_9 place_1_10) (connected place_1_9 place_2_9)
(connected place_4_2 place_4_1) (connected place_4_2 place_4_3) (connected place_4_2 place_3_2) (connected place_4_2 place_5_2)
(connected place_28_7 place_28_6) (connected place_28_7 place_28_8) (connected place_28_7 place_27_7)
(connected place_5_3 place_5_2) (connected place_5_3 place_5_4) (connected place_5_3 place_4_3) (connected place_5_3 place_6_3)
(connected place_6_8 place_6_7) (connected place_6_8 place_6_9) (connected place_6_8 place_5_8) (connected place_6_8 place_7_8)
(connected place_20_11 place_20_10) (connected place_20_11 place_19_11) (connected place_20_11 place_21_11)
(connected place_21_10 place_21_11) (connected place_21_10 place_20_10) (connected place_21_10 place_22_10)
(connected place_22_1 place_22_2) (connected place_22_1 place_21_1) (connected place_22_1 place_23_1)
(connected place_23_4 place_23_3) (connected place_23_4 place_23_5) (connected place_23_4 place_22_4) (connected place_23_4 place_24_4)
(connected place_10_11 place_10_10) (connected place_10_11 place_9_11) (connected place_10_11 place_11_11)
(connected place_11_2 place_11_1) (connected place_11_2 place_10_2) (connected place_11_2 place_12_2)
(connected place_1_2 place_1_1) (connected place_1_2 place_1_3) (connected place_1_2 place_2_2)
(connected place_4_9 place_4_8) (connected place_4_9 place_4_10) (connected place_4_9 place_3_9) (connected place_4_9 place_5_9)
(connected place_2_9 place_2_8) (connected place_2_9 place_2_10) (connected place_2_9 place_1_9) (connected place_2_9 place_3_9)
(connected place_6_3 place_6_2) (connected place_6_3 place_6_4) (connected place_6_3 place_5_3) (connected place_6_3 place_7_3)
(connected place_7_10 place_7_9) (connected place_7_10 place_7_11) (connected place_7_10 place_6_10) (connected place_7_10 place_8_10)
(connected place_13_1 place_13_2) (connected place_13_1 place_12_1) (connected place_13_1 place_14_1)
(connected place_24_7 place_24_6) (connected place_24_7 place_24_8) (connected place_24_7 place_23_7) (connected place_24_7 place_25_7)
(connected place_25_6 place_25_5) (connected place_25_6 place_25_7) (connected place_25_6 place_24_6) (connected place_25_6 place_26_6)
(connected place_26_5 place_26_4) (connected place_26_5 place_26_6) (connected place_26_5 place_25_5) (connected place_26_5 place_27_5)
(connected place_27_8 place_27_7) (connected place_27_8 place_27_9) (connected place_27_8 place_26_8) (connected place_27_8 place_28_8)
)
(:goal
(and
(at place_1_1)
)
)
)
