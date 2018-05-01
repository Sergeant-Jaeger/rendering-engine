Display "Solar System"  "Screen" "rgbdouble"

Format 640 480

####################
ObjectBegin "Sun"

Color .992 .721 .074

XformPush
Sphere 695 0 0 0
XformPop

ObjectEnd #Sun
#################

####################
ObjectBegin "Mercury"

Color .905 .905 .905

XformPush
Translate 825 0 0
Sphere 2.440 0 0 0
XformPop

ObjectEnd #Mercury
#################

####################
ObjectBegin "Venus"

Color .647 .486 .105

XformPush
Translate 850 0 0
Sphere 6.052 0 0 0
XformPop

ObjectEnd #Venus
#################

####################
ObjectBegin "Earth"

Color 0 0 .627

XformPush
Translate 875 0 0
Sphere 6.378 0 0 0
XformPop

ObjectEnd #Earth
#################

####################
ObjectBegin "Mars"

Color .788 .129 .094

XformPush
Translate 900 0 0
Sphere 3.397 0 0 0
XformPop

ObjectEnd #Mars
#################

####################
ObjectBegin "Jupiter"

Color .788 .564 .223

XformPush
Translate 990 0 0
Sphere 71.492 0 0 0
XformPop

ObjectEnd #Jupiter
#################

####################
ObjectBegin "Saturn"

Color .890 .878 .752

XformPush
Translate 1150 0 0
Sphere 60.268 0 0 0

Rotate "X" 45

Color .627 .321 .176

Disk 1 85 0
XformPop

ObjectEnd #Saturn
#################

####################
ObjectBegin "Uranus"

Color .776 .827 .890

XformPush
Translate 1275 0 0
Sphere 25.559 0 0 0
XformPop

ObjectEnd #Uranus
#################

####################
ObjectBegin "Neptune"

Color .266 .4 .498

XformPush
Translate 1360 0 0
Sphere 24.766 0 0 0
XformPop

ObjectEnd #Neptune
#################

####################
ObjectBegin "Pluto"

Color .388 .349 .282

XformPush
Translate 1410 0 0
Sphere 1.150 0 0 0
XformPop

ObjectEnd #Pluto --- It's still a planet!
#################

Background 0.0 0.0 0.0

CameraEye 1000 -325 0 
CameraAt  1000 1 0
CameraUp  0 0 1
CameraFOV 90

WorldBegin


AmbientLight .992 .721 .074 .25

FarLight 1 0 0  1.0  1.0  1.0  1.0
FarLight -1 -1 0  1.0  1.0  1.0  0.8

Kd 1

Surface matte

ObjectInstance Sun

ObjectInstance Mercury

ObjectInstance Venus

ObjectInstance Earth

ObjectInstance Mars

ObjectInstance Jupiter

ObjectInstance Saturn

ObjectInstance Uranus

ObjectInstance Neptune

ObjectInstance Pluto

WorldEnd