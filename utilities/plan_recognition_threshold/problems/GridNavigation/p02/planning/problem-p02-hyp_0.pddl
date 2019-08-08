(define (problem Corridor)

(:domain navigator)
(:objects
place_31_6
place_19_4
place_21_6
place_14_1
place_3_2
place_38_5
place_27_6
place_5_1
place_42_6
place_23_6
place_47_5
place_6_1
place_19_1
place_30_5
place_19_6
place_43_5
place_20_1
place_44_6
place_21_4
place_34_6
place_39_5
place_16_2
place_22_2
place_11_1
place_40_6
place_22_5
place_46_6
place_35_5
place_12_1
place_36_6
place_26_6
place_31_5
place_19_3
place_20_4
place_8_2
place_14_2
place_3_1
place_20_3
place_21_2
place_45_5
place_32_6
place_38_6
place_27_5
place_4_1
place_28_6
place_17_1
place_6_2
place_41_5
place_18_1
place_13_2
place_37_5
place_24_6
place_30_6
place_19_5
place_20_6
place_9_1
place_33_5
place_10_1
place_15_2
place_5_2
place_29_5
place_22_6
place_1_1
place_2_1
place_7_2
place_44_5
place_21_5
place_16_1
place_40_5
place_18_2
place_22_4
place_36_5
place_8_1
place_20_2
place_21_3
place_45_6
place_32_5
place_10_2
place_15_1
place_28_5
place_17_2
place_22_3
place_41_6
place_42_5
place_47_6
place_12_2
place_37_6
place_2_2
place_7_1
place_19_2
place_20_5
place_9_2
place_43_6
place_21_1
place_33_6
place_34_5
place_39_6
place_4_2
place_29_6
place_22_1
place_11_2
place_1_2
place_46_5
place_35_6
place_13_1
place_25_6
place_26_5
- place
)
(:init
(connected place_31_6 place_31_5) (connected place_31_6 place_30_6) (connected place_31_6 place_32_6)
(connected place_19_4 place_19_3) (connected place_19_4 place_19_5) (connected place_19_4 place_20_4)
(connected place_21_6 place_21_5) (connected place_21_6 place_20_6) (connected place_21_6 place_22_6)
(connected place_14_1 place_14_2) (connected place_14_1 place_13_1) (connected place_14_1 place_15_1)
(connected place_3_2 place_3_1) (connected place_3_2 place_2_2) (connected place_3_2 place_4_2)
(connected place_38_5 place_38_6) (connected place_38_5 place_37_5) (connected place_38_5 place_39_5)
(connected place_27_6 place_27_5) (connected place_27_6 place_26_6) (connected place_27_6 place_28_6)
(connected place_5_1 place_5_2) (connected place_5_1 place_4_1) (connected place_5_1 place_6_1)
(connected place_42_6 place_42_5) (connected place_42_6 place_41_6) (connected place_42_6 place_43_6)
(connected place_23_6 place_22_6) (connected place_23_6 place_24_6)
(connected place_47_5 place_47_6) (connected place_47_5 place_46_5)
(connected place_6_1 place_6_2) (connected place_6_1 place_5_1) (connected place_6_1 place_7_1)
(connected place_19_1 place_19_2) (connected place_19_1 place_18_1) (connected place_19_1 place_20_1)
(connected place_30_5 place_30_6) (connected place_30_5 place_29_5) (connected place_30_5 place_31_5)
(connected place_19_6 place_19_5) (connected place_19_6 place_20_6)
(connected place_43_5 place_43_6) (connected place_43_5 place_42_5) (connected place_43_5 place_44_5)
(connected place_20_1 place_20_2) (connected place_20_1 place_19_1) (connected place_20_1 place_21_1)
(connected place_44_6 place_44_5) (connected place_44_6 place_43_6) (connected place_44_6 place_45_6)
(connected place_21_4 place_21_3) (connected place_21_4 place_21_5) (connected place_21_4 place_20_4) (connected place_21_4 place_22_4)
(connected place_34_6 place_34_5) (connected place_34_6 place_33_6) (connected place_34_6 place_35_6)
(connected place_39_5 place_39_6) (connected place_39_5 place_38_5) (connected place_39_5 place_40_5)
(connected place_16_2 place_16_1) (connected place_16_2 place_15_2) (connected place_16_2 place_17_2)
(connected place_22_2 place_22_1) (connected place_22_2 place_22_3) (connected place_22_2 place_21_2)
(connected place_11_1 place_11_2) (connected place_11_1 place_10_1) (connected place_11_1 place_12_1)
(connected place_40_6 place_40_5) (connected place_40_6 place_39_6) (connected place_40_6 place_41_6)
(connected place_22_5 place_22_4) (connected place_22_5 place_22_6) (connected place_22_5 place_21_5)
(connected place_46_6 place_46_5) (connected place_46_6 place_45_6) (connected place_46_6 place_47_6)
(connected place_35_5 place_35_6) (connected place_35_5 place_34_5) (connected place_35_5 place_36_5)
(connected place_12_1 place_12_2) (connected place_12_1 place_11_1) (connected place_12_1 place_13_1)
(connected place_36_6 place_36_5) (connected place_36_6 place_35_6) (connected place_36_6 place_37_6)
(connected place_26_6 place_26_5) (connected place_26_6 place_25_6) (connected place_26_6 place_27_6)
(connected place_31_5 place_31_6) (connected place_31_5 place_30_5) (connected place_31_5 place_32_5)
(connected place_19_3 place_19_2) (connected place_19_3 place_19_4) (connected place_19_3 place_20_3)
(connected place_20_4 place_20_3) (connected place_20_4 place_20_5) (connected place_20_4 place_19_4) (connected place_20_4 place_21_4)
(connected place_8_2 place_8_1) (connected place_8_2 place_7_2) (connected place_8_2 place_9_2)
(connected place_14_2 place_14_1) (connected place_14_2 place_13_2) (connected place_14_2 place_15_2)
(connected place_3_1 place_3_2) (connected place_3_1 place_2_1) (connected place_3_1 place_4_1)
(connected place_20_3 place_20_2) (connected place_20_3 place_20_4) (connected place_20_3 place_19_3) (connected place_20_3 place_21_3)
(connected place_21_2 place_21_1) (connected place_21_2 place_21_3) (connected place_21_2 place_20_2) (connected place_21_2 place_22_2)
(connected place_45_5 place_45_6) (connected place_45_5 place_44_5) (connected place_45_5 place_46_5)
(connected place_32_6 place_32_5) (connected place_32_6 place_31_6) (connected place_32_6 place_33_6)
(connected place_38_6 place_38_5) (connected place_38_6 place_37_6) (connected place_38_6 place_39_6)
(connected place_27_5 place_27_6) (connected place_27_5 place_26_5) (connected place_27_5 place_28_5)
(connected place_4_1 place_4_2) (connected place_4_1 place_3_1) (connected place_4_1 place_5_1)
(connected place_28_6 place_28_5) (connected place_28_6 place_27_6) (connected place_28_6 place_29_6)
(connected place_17_1 place_17_2) (connected place_17_1 place_16_1) (connected place_17_1 place_18_1)
(connected place_6_2 place_6_1) (connected place_6_2 place_5_2) (connected place_6_2 place_7_2)
(connected place_41_5 place_41_6) (connected place_41_5 place_40_5) (connected place_41_5 place_42_5)
(connected place_18_1 place_18_2) (connected place_18_1 place_17_1) (connected place_18_1 place_19_1)
(connected place_13_2 place_13_1) (connected place_13_2 place_12_2) (connected place_13_2 place_14_2)
(connected place_37_5 place_37_6) (connected place_37_5 place_36_5) (connected place_37_5 place_38_5)
(connected place_24_6 place_23_6) (connected place_24_6 place_25_6)
(connected place_30_6 place_30_5) (connected place_30_6 place_29_6) (connected place_30_6 place_31_6)
(connected place_19_5 place_19_4) (connected place_19_5 place_19_6) (connected place_19_5 place_20_5)
(connected place_20_6 place_20_5) (connected place_20_6 place_19_6) (connected place_20_6 place_21_6)
(connected place_9_1 place_9_2) (connected place_9_1 place_8_1) (connected place_9_1 place_10_1)
(connected place_33_5 place_33_6) (connected place_33_5 place_32_5) (connected place_33_5 place_34_5)
(connected place_10_1 place_10_2) (connected place_10_1 place_9_1) (connected place_10_1 place_11_1)
(connected place_15_2 place_15_1) (connected place_15_2 place_14_2) (connected place_15_2 place_16_2)
(connected place_5_2 place_5_1) (connected place_5_2 place_4_2) (connected place_5_2 place_6_2)
(connected place_29_5 place_29_6) (connected place_29_5 place_28_5) (connected place_29_5 place_30_5)
(connected place_22_6 place_22_5) (connected place_22_6 place_21_6) (connected place_22_6 place_23_6)
(connected place_1_1 place_1_2) (connected place_1_1 place_2_1) (at place_1_1)
(connected place_2_1 place_2_2) (connected place_2_1 place_1_1) (connected place_2_1 place_3_1)
(connected place_7_2 place_7_1) (connected place_7_2 place_6_2) (connected place_7_2 place_8_2)
(connected place_44_5 place_44_6) (connected place_44_5 place_43_5) (connected place_44_5 place_45_5)
(connected place_21_5 place_21_4) (connected place_21_5 place_21_6) (connected place_21_5 place_20_5) (connected place_21_5 place_22_5)
(connected place_16_1 place_16_2) (connected place_16_1 place_15_1) (connected place_16_1 place_17_1)
(connected place_40_5 place_40_6) (connected place_40_5 place_39_5) (connected place_40_5 place_41_5)
(connected place_18_2 place_18_1) (connected place_18_2 place_17_2) (connected place_18_2 place_19_2)
(connected place_22_4 place_22_3) (connected place_22_4 place_22_5) (connected place_22_4 place_21_4)
(connected place_36_5 place_36_6) (connected place_36_5 place_35_5) (connected place_36_5 place_37_5)
(connected place_8_1 place_8_2) (connected place_8_1 place_7_1) (connected place_8_1 place_9_1)
(connected place_20_2 place_20_1) (connected place_20_2 place_20_3) (connected place_20_2 place_19_2) (connected place_20_2 place_21_2)
(connected place_21_3 place_21_2) (connected place_21_3 place_21_4) (connected place_21_3 place_20_3) (connected place_21_3 place_22_3)
(connected place_45_6 place_45_5) (connected place_45_6 place_44_6) (connected place_45_6 place_46_6)
(connected place_32_5 place_32_6) (connected place_32_5 place_31_5) (connected place_32_5 place_33_5)
(connected place_10_2 place_10_1) (connected place_10_2 place_9_2) (connected place_10_2 place_11_2)
(connected place_15_1 place_15_2) (connected place_15_1 place_14_1) (connected place_15_1 place_16_1)
(connected place_28_5 place_28_6) (connected place_28_5 place_27_5) (connected place_28_5 place_29_5)
(connected place_17_2 place_17_1) (connected place_17_2 place_16_2) (connected place_17_2 place_18_2)
(connected place_22_3 place_22_2) (connected place_22_3 place_22_4) (connected place_22_3 place_21_3)
(connected place_41_6 place_41_5) (connected place_41_6 place_40_6) (connected place_41_6 place_42_6)
(connected place_42_5 place_42_6) (connected place_42_5 place_41_5) (connected place_42_5 place_43_5)
(connected place_47_6 place_47_5) (connected place_47_6 place_46_6)
(connected place_12_2 place_12_1) (connected place_12_2 place_11_2) (connected place_12_2 place_13_2)
(connected place_37_6 place_37_5) (connected place_37_6 place_36_6) (connected place_37_6 place_38_6)
(connected place_2_2 place_2_1) (connected place_2_2 place_1_2) (connected place_2_2 place_3_2)
(connected place_7_1 place_7_2) (connected place_7_1 place_6_1) (connected place_7_1 place_8_1)
(connected place_19_2 place_19_1) (connected place_19_2 place_19_3) (connected place_19_2 place_18_2) (connected place_19_2 place_20_2)
(connected place_20_5 place_20_4) (connected place_20_5 place_20_6) (connected place_20_5 place_19_5) (connected place_20_5 place_21_5)
(connected place_9_2 place_9_1) (connected place_9_2 place_8_2) (connected place_9_2 place_10_2)
(connected place_43_6 place_43_5) (connected place_43_6 place_42_6) (connected place_43_6 place_44_6)
(connected place_21_1 place_21_2) (connected place_21_1 place_20_1) (connected place_21_1 place_22_1)
(connected place_33_6 place_33_5) (connected place_33_6 place_32_6) (connected place_33_6 place_34_6)
(connected place_34_5 place_34_6) (connected place_34_5 place_33_5) (connected place_34_5 place_35_5)
(connected place_39_6 place_39_5) (connected place_39_6 place_38_6) (connected place_39_6 place_40_6)
(connected place_4_2 place_4_1) (connected place_4_2 place_3_2) (connected place_4_2 place_5_2)
(connected place_29_6 place_29_5) (connected place_29_6 place_28_6) (connected place_29_6 place_30_6)
(connected place_22_1 place_22_2) (connected place_22_1 place_21_1)
(connected place_11_2 place_11_1) (connected place_11_2 place_10_2) (connected place_11_2 place_12_2)
(connected place_1_2 place_1_1) (connected place_1_2 place_2_2)
(connected place_46_5 place_46_6) (connected place_46_5 place_45_5) (connected place_46_5 place_47_5)
(connected place_35_6 place_35_5) (connected place_35_6 place_34_6) (connected place_35_6 place_36_6)
(connected place_13_1 place_13_2) (connected place_13_1 place_12_1) (connected place_13_1 place_14_1)
(connected place_25_6 place_24_6) (connected place_25_6 place_26_6)
(connected place_26_5 place_26_6) (connected place_26_5 place_27_5)
)
(:goal
(and
(at place_15_2)
)
)
)
