# Animation properties available:
# frame-start-x
#	Unit: pixels
# frame-start-y
#	Unit: pixels
# frame-width
#	Unit: pixels
# frame-height
#	Unit: pixels
# frame-margin
#	Unit: pixels
#	Added when getting the next frame, fixes potential artifacting with transparancy
# frame-count
# frame-time
#	in milliseconds
# reverse
#	If present, it sets the animation to reverse play (start position - (margin + frame width))
# loop
#	If present, it makes the animation loop and never finish. If missing it halts on last frame

# This tells the program where the spritesheet can be found. Frames of a single
# animation should all be on the same line / row.
spritesheet-source "spritesheet/testsheet.png"

# This indicates the start of an animation definition which name will be
# idle. I.e. use it by calling SetAnimation("idle").
animation idle
	frame-start-x 0
	frame-start-y 0
	frame-width 30
	frame-height 21
	frame-count 1

animation run
	frame-start-x 0
	frame-start-y 0
	frame-width 30
	frame-height 21
	frame-count 8
	frame-time 100
	loop
