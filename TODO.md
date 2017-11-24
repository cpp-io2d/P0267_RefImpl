TO DO
=============

The process of completing a TS is fraught with unexpected labours. Before we can consider offering a TS, several tasks remain.

Separate the handler from the display surface
-------------

The display surface is primarily concerned with putting things onto the screen. This interacts with the OS through a handler which interpets messages from the OS. By separating the two, and implementing them in terms of a facade, clients can write their own handlers and even their own renderers if they so wish. A default implementation remains in place.

Exhaustive test program
-------------

Each function of the the API needs to be exercised. The test program should expose each area of the API to test. The nature of this API means that this tester could also act as a demonstrator of the API, or even a tutorial.

Input
-------------

Touch, mouse, keyboard and button input is a requirement of this API: we seek to offer IO, not just O.

Text
-------------

Text cannot be overlooked. An earlier version did include text rendering, but this was inappropriate for the task.

Sample programs
-------------

There are two sample programs currently: an incomplete version of Asteroids and a test program which writes images to files. More sample programs will be needed to demonstrate the API.

Additional renderers
-------------

The default renderer uses Cairo. More renderers based on hardware libraries such as Direct2D, Vulkan or even on drivers for Nvidia and AMD GPUs will prove the API.