(define (domain ticket_to_ride)

    (:requirements
        :typing
    )

    (:types
        node
        number
        colour
    )

    (:predicates
        (adj ?start ?end - node ?tobuild - number ?ofcolour - colour)
        (isPath ?start ?end - node)
        (numberTracks ?n - number ?ofcolour - colour)

        (succ ?n ?m - number)
        (pred ?n ?m - number)
        (geq ?greater ?lesser - number)
        (diff ?n ?m ?p - number)
    )

    (:action includeEdge
        :parameters (?start ?end - node ?n ?m ?p - number ?c - colour)
        :precondition
            (and
                (adj ?start ?end ?m ?c)
                (numberTracks ?n ?c)
                (geq ?n ?m)
                (diff ?n ?m ?p)
            )
        :effect
            (and
                (not (numberTracks ?n ?c))
                (numberTracks ?p ?c)
                (isPath ?start ?end)
                (isPath ?end ?start)
            )

    )

    (:action pickUpTrack
        :parameters (?current ?next - number ?c - colour)
        :precondition
            (and
                (numberTracks ?current ?c)
                (succ ?current ?next)
            )
        :effect
            (and
                (not (numberTracks ?current ?c))
                (numberTracks ?next ?c)
            )
    )

    (:action makePath
        :parameters (?start ?end ?middle - node)
        :precondition
            (and
                (isPath ?start ?middle)
                (isPath ?middle ?end)
            )
        :effect
            (and
                (isPath ?start ?end)
                (isPath ?end ?start)
            )
    )
)
