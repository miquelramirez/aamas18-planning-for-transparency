(define (problem p_3X4)
    (:domain grid_domain)
    (:objects P1_1 P1_2 P1_3 P1_4 P2_1 P2_2 P2_3 P2_4 P3_1 P3_2 P3_3 P3_4)
    (:init
      (adj P1_1 P2_1)
      (adj P2_1 P1_1)
      (adj P1_1 P1_2)
      (adj P1_2 P1_1)
      (adj P1_2 P2_2)
      (adj P2_2 P1_2)
      (adj P1_2 P1_3)
      (adj P1_3 P1_2)
      (adj P1_2 P1_1)
      (adj P1_1 P1_2)
      (adj P1_3 P2_3)
      (adj P2_3 P1_3)
      (adj P1_3 P1_4)
      (adj P1_4 P1_3)
      (adj P1_3 P1_2)
      (adj P1_2 P1_3)
      (adj P1_4 P2_4)
      (adj P2_4 P1_4)
      (adj P1_4 P1_3)
      (adj P1_3 P1_4)
      (adj P2_1 P1_1)
      (adj P1_1 P2_1)
      (adj P2_1 P3_1)
      (adj P3_1 P2_1)
      (adj P2_1 P2_2)
      (adj P2_2 P2_1)
      (adj P2_2 P1_2)
      (adj P1_2 P2_2)
      (adj P2_2 P3_2)
      (adj P3_2 P2_2)
      (adj P2_2 P2_3)
      (adj P2_3 P2_2)
      (adj P2_2 P2_1)
      (adj P2_1 P2_2)
      (adj P2_3 P1_3)
      (adj P1_3 P2_3)
      (adj P2_3 P3_3)
      (adj P3_3 P2_3)
      (adj P2_3 P2_4)
      (adj P2_4 P2_3)
      (adj P2_3 P2_2)
      (adj P2_2 P2_3)
      (adj P2_4 P1_4)
      (adj P1_4 P2_4)
      (adj P2_4 P3_4)
      (adj P3_4 P2_4)
      (adj P2_4 P2_3)
      (adj P2_3 P2_4)
      (adj P3_1 P2_1)
      (adj P2_1 P3_1)
      (adj P3_1 P3_2)
      (adj P3_2 P3_1)
      (adj P3_2 P2_2)
      (adj P2_2 P3_2)
      (adj P3_2 P3_3)
      (adj P3_3 P3_2)
      (adj P3_2 P3_1)
      (adj P3_1 P3_2)
      (adj P3_3 P2_3)
      (adj P2_3 P3_3)
      (adj P3_3 P3_4)
      (adj P3_4 P3_3)
      (adj P3_3 P3_2)
      (adj P3_2 P3_3)
      (adj P3_4 P2_4)
      (adj P2_4 P3_4)
      (adj P3_4 P3_3)
      (adj P3_3 P3_4)
      (pos P1_2)
  )
  (:goal
      (and
          (pos P3_3)
      )
  )
)
