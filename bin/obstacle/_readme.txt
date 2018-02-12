# This specifies the type of the obstacle
type 				door

# This line specifies where the animation for said obstacle can be loaded from
animation-file 			"animation/door.txt"

# In pixels, the minimum distance the player has to be from the obstacle
# to start a gesture recorded by it
interaction-radius 		200

# The local interaction radius position, where the radius starts
interaction-local-position	50	50

# In pixels, the minimal distance the gesture start and end point need to be
# apart for it not to be a tap.
minimal-interaction-distance 	50

# The required gesture(s) to neutralize this obstacle
neutralization-gestures		leftwards rightwards

hint-string			"Swipe left or right!"

hint-local-position		50	50
