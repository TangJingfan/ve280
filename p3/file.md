.
|-- point_t
|
|-- instruction_t
|
|-- species_t
|
|-- creature_t
|
|-- grid_t
|
|-- world_t |-- species_t
            |
            |-- creatures_t |-- location
            |               |-- direction
            |               |-- species (points to species_t array in world)
            |               |-- program ID (the step the creature should perform) start from 0
            |
            |-- grid_t |-- height
                       |-- width
                       |-- square(2d creature_t pointer)