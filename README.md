How to use the application
Important: The application developed can be played only on an android device.
When the game starts, the player is prompted to a main menu, through which they can access the
game scene. Once in the game, the user can start moving around the real world to detect different
surfaces.
Once the player taps on the first detected surface, the character will spawn, and different pickups will
be spawned on new detected surfaces. To be able to reach higher or lower surfaces, the teleport pickup
must be collected. Depending on where the character needs to go, it will teleport or walk. There are
four types of pickups: teleport pickup (spawned once), score pickups, task pickups and mushroom
pickups. Each pickup has different spawning conditions and effects. On the game screen, the player
can see the tasks completion, hints for the player and the options menu button on the top right. In the
options menu the player can adjust the game settings or restart the level.

Features: Overview
The application uses Unreal Engine 5 and a marker-less approach to create a 3D platformer in
Augmented Reality. The application features: collisions with Augmented Reality elements,
distance-based Artificial Intelligence behaviour for movements, multiple pickups, multiple score
system, fall detection, customised Augmented Reality elements, winning condition system, restart
system, music, sounds, graphical effects, User Interface and animation system. Only the last two
features are fully implemented in blueprints, the remaining features are implemented using C++ code.

Design of Features: Augmented Reality-based Features
ARPlanes allow the player to detect surfaces and interact with them in different ways. The planes are
fully customised to give the user a pleasant game experience while still displaying the relevant data
that needs to be considered to correctly play the game. This aspect is considerably important as the
user needs to be able to understand how to use the application, while still having an enjoyable and
clear User Interface (Montero et al., 2019).
Customised Augmented Reality Planes; the planes are divided into
three main parts, the inner part allows the player to see the area of
the plane in front of the camera, as the player moves the device, the
inner part moves on the plane, acting like a focus lens. The second
part is characterised by a red grid, which hints the player that the
plane is reaching its boundaries. The second part’s colour fades into
the outer area. The outer area of the planes is characterised by small
grey dots, which are barely visible and indicate the end of the
current plane, hinting the player to detect more surfaces.
The planes collide with the player. Each ARPlane is a surface that the virtual player can walk on. The
presence of collision and gravity gives more realism to the player’s movement and interaction with the
planes. Once the user taps on a part of the plane, the player will walk towards it using Artificial
Intelligence. The player can also teleport on normally unreachable planes to collect the different
pickups.
Being the Navmesh detection dynamic, it might happen that the player’s path is not correct, causing
the player to fall from the planes. To correct this, a fall detection system has been implemented. When
the player falls, it is immediately teleported to the lowest plane in the scene.
Design of Features: non-Augmented Reality-based features
There are four types of pickups that have all different behaviour and spawning conditions; to spawn
them, the player must already exist in the scene. Only one teleport pickup is spawned when the player
spawns but can be collected and seen after three seconds from the player’s moment of spawn, to avoid
instant collection.
Score pickups can be spawned at minimum every second only on new detected planes, to avoid
spawning too many on the existing planes. Infinite score pickups can be collected.
Task pickups are also spawned at minimum every second on new detected planes. Only 15 task
pickups are spawned in the scene. To win, the player must collect at least 10 score pickups and 10 task
pickups, even though more score pickups can be collected to increase the score. The mushroom
pickup makes the colour of the ARPlanes quickly change, giving the player a sense of distortion and
confusion. Each pickup has a different sound when collected, allowing the player to understand what
has been collected.
Once the application is started, the player enters in the main menu, through which the game scene can
be accessed. Once the game scene is opened the user can access the options menu, which is displayed
on top of what the camera sees. Through the options menu, the player can: display the Augmented
Reality planes, turn off/on music/audio and restart the level. The last option is useful in case the game
session presents errors, usually caused by multiple planes being detected and spawned on top/bottom
of already existing ones.
User Interface (UI) is a remarkably important aspect of Augmented Reality (M. Singh and M. P.
Singh, 2013) that greatly influences the user experience while using the application. The goal of it is
not only to improve the usability of the application, but also, more specifically to AR, to let the player
understand how to interact with the real world. (Amit, 2022)
In this application, the UI hints the player on what to do and what menus can be accessed. More
specifically, in the game scene, four interfaces are displayed, two of which tell the player how many
score/task pickups have been collected and how many are remaining. The third one allows the player
to enter in the options menu and the last one represents the hints interface. At any point during the
game, the player can see what they must do (i.e.: spawn the player, detect a surface, etc…).
Augmented Reality in the application, icons have been implemented as more straightforward and aesthetically
pleasing.
To further improve the user experience, an animation system has been implemented, every virtual
object has motion or animation to improve the realism of the application. Realism is a fundamental
aspect of how the player perceives Augmented Reality. In fact, the aim of AR is to blend the real
world and the virtual world in one (Barhorst et al., 2021). If a realistic application is developed, the
boundaries between virtual world and real world are obfuscated, fulfilling the main role of
Augmented Reality.
Specifically related to the application, the player can change animation from idle to walk and run. All
the pickups rotate once spawned and possess bright colours to be quickly noticed by the player.

Implementation of Augmented Reality Features.
It is important to mention that, while the executable file for the game is available only for Android as
an APK, the code and its implementation are fully compatible with other devices.
To implement the custom ARPlane, the process was as follows. Firstly, the closest pixel of the plane
to the camera direction vector has been calculated using the closest point to a line equation.
Two cutoff values decide, based on the distance between the closest point to the camera vector and the
different pixels, whether dots, lines or full colour are displayed.
Dots, grid and the full colour circle have been obtained by isolating values already pre-existing in the
texture.
To obtain the red grid’s fade effect, the colour values of the pixels are decreased as they get farther
from the previously calculated point.
The collision with the ARPlanes was achieved by enabling collision from the player blueprint and
from the ARPlanes C++ class when each plane is generated.
Once the application starts, only one plane is detected. Once the player is spawned, the other planes
are generated and the different pickups spawn. When the first surface is detected, the teleport pickup
is also spawned at a random position, but it is hidden and not collectable.
Once the player spawns, different timers start to allow the generation of the pickups at different
locations and one timer for the “revealing” of the teleport pickup starts, which uncovers and makes
the teleport pickup collectable after 3 seconds.
To avoid the player from falling, the first .Z value of the first plane is saved and compared to the other
ones, if the other planes are at a lower Z value, then overwrite the current value and if the player’s Z
value is less than the plane’s one, teleport the player back on top of the surface.
Finally, to allow the movement of the player throughout the different planes, a Navmesh handles and
generates paths for the player at runtime using a customised agent, to guarantee precise movements to
the tap location. The size of the Navmesh is also high so that even if the player moves far from the
origin point, the Navmesh will not stop detecting and calculating paths.
To decide whether the player can teleport or walk on different surfaces, two checks are done: if the
distance between the planes is bigger than a constant value, the player is trying to reach a different
plane and the teleport pickup is collected, or if the Z value is bigger than a constant and the teleport
pickup is collected, the player teleports. In all the other situations the player walks to the destination.
Once the player reaches the destination, all the variables are reset, so that the player can move again.
To detect the player’s tap on the screen, two line trace functions deproject the screen position to the
world position, while also keeping track of what plane the player is on.


Software Architecture of the application
External features to extend the application
Given more time for development, different features would have been added. Depending on what
device the application is being run on, some problems might arise. One of them being the multiple
detection of planes on the same surface. This causes graphical and functional problems with the
custom ARPlanes. To solve this, a system of merging planes that are close in the Z-axis would be
implemented. Another useful feature could be the implementation of different movement mechanics
(jumping, flying, rolling, climbing) depending on the location of the reached surface, perhaps also
based on different characteristics of planes (horizontal/vertical). More pickups and a losing system
could be added to make the gameplay more interesting. Real world’s lighting-based mechanics could
make the game more interactive with the environment. For example, based on whether the player is
moving in the darkness or light, change the speed of the movement. Finally, enemies could be
spawned on surfaces and a crafting system could be added to give the character different weapons and
animations to fight the enemies.


Reflection: Personal Evaluation
Overall, the developed application reached the desired result, implementing the planned features.
Considerable focus was put into the software architecture of the application, following an
object-oriented approach, the application is scalable and ready to be extended with no need for radical
changes. This thanks to the structure of the ARManager and Game Manager, along with the pickup
and PlaceableCharacter parent classes. Different complicated features and their implementation in AR
have been explored such as the use of Navmesh, pathfinding and player movement, along with
collision and physics in AR.


Reflection: Challenges and Solutions devised
One of the features that took the longest has been how to use the navmesh and pathfinding in
Augmented Reality, using the planes as walkable surfaces for the character. This was due to scarce
online resources about Augmented Reality. Adding collision to the planes and handling them also
took considerable time. A flying mechanic was being developed. Due to the challenges with handling
planes’ collisions and landing points, this mechanic was replaced with the teleporting one. The base
ARPlanes did not feel user-friendly and, depending on the device, they could fill the scene quickly,
causing confusion to the player. To avoid this, the way the planes are rendered was changed, at first,
only dots were displayed. As the application evolved in complexity, a more complex yet
aesthetically-pleasing solution was devised. To increase the deployability of the application, the
originally present ARPins were removed, which caused the application to be compatible only with
ARCore. The code is now compatible with multiple devices. To avoid the player getting glitched in
the planes, the movement destinations’ Z values have all been changed to be on top of the planes.
Finally, during the development and testing, the player frequently fell from the planes, the solution
devised has been the fall detection and instant teleport on top of the lowest plane. The optimal way to
restart the game was through the StopARSession blueprint node. This node caused the ARSession to
go into fatal error for unknown reasons. After extensive trials, this has been solved by deleting the
ARPlanes manually in the HelloARManager “DestroyAllPlanes” function.


Innovation in AR
After exploring different aspects of Augmented Reality and seeing what can be done with it, there is
much more that can be achieved in AR than how it is being used, especially in video games. After
developing a platformer in Augmented Reality, it would be innovative to start developing platformers
in Augmented Reality. The only barrier is presented by the common hardware owned as some devices
perform better than other ones. It would be useful to standardise depth sensors in mobile devices to
have more performant and accurate game experiences. If this is not achievable, it would be helpful to
standardise the subsuming of planes that are close to each other in height. After implementing the
Navmesh and seeing how it behaves in an AR game setting, it would be possible to develop more
games that have Artificially Intelligent NPCs, where the player has a virtual companion that behaves
in a realistic way using Finite State Machines or Behaviour Trees and moves to different locations
using the navmesh.

References
Amit. ‘Role of UX UI on Augmented Reality Design’. Divami | Blog (blog), 15 March 2022.
https://www.divami.com/blog/role-of-ux-ui-on-augmented-reality-design.
M. Singh and M. P. Singh, "Augmented Reality Interfaces," in IEEE Internet Computing, vol. 17, no.
6, pp. 66-70, Nov.-Dec. 2013, doi: 10.1109/MIC.2013.107.
Montero, Alvaro, Telmo Zarraonandia, Paloma Diaz, and Ignacio Aedo. ‘Designing and
Implementing Interactive and Realistic Augmented Reality Experiences’. Universal Access in the
Information Society 18, no. 1 (1 March 2019): 49–61. https://doi.org/10.1007/s10209-017-0584-2.
Brannon Barhorst, Jennifer, Graeme McLean, Esta Shah, and Rhonda Mack. ‘Blending the Real
World and the Virtual World: Exploring the Role of Flow in Augmented Reality Experiences’. Journal
of Business Research 122 (1 January 2021): 423–36. https://doi.org/10.1016/j.jbusres.2020.08.041.
Background Music and Audio Effects: ‘Free Video Games Music MP3 Download - Pixabay’.
https://pixabay.com/music/search/genre/video%20games/.
Player Model and Animation: ‘Mixamo’. Accessed 14 December 2022. https://www.mixamo.com/#/.
Pickups’ models have been obtained for free in the Epic Games marketplace.
Images for background have been obtained for free in google no-copyrighted images.
