Heavily modified P0267 Reference Implementation
=============

Please take a look at the [original repository](https://github.com/mikebmcl/P0267_RefImpl) first!


Overview
-------------

This repository contains an experimental fork of P0267 RefImpl, which was changed in many ways:
  * Separate backend for CoreGraphics. At this moment only MacOSX (Cocoa) supported, but nothing stops from adding support for other Apple platforms like iOS/tvOS etc.
  * Modified directory structure to support different backends.
  * CMake build scripts.
  * Simple SVG renderer as a sample of library usage.
  * Some bugfixed of original RefImpl.

CoreGraphics/Cocoa backend status
-------------
This backend is far from being complete.

What is done:
  * Geometry, transformations, filling, stroking, clipping.
  * Stroke props, brush props, dash props, render props, clip props.
  * Image surfaces - creating, loading, saving, rendering.
  * Managed output surfaces, partially.

What is lacking completely:
  * Unmanaged output surfaces.
  * Scaling options for output surfaces.
  * Mask operation.
  
What needs further study and/or implementation:
  * Surface formats.
  * Wrap modes for brushes.
  * Error codes.
  * compositing_op::dest is not supported by CoreGraphics.
  * compositing_op::saturate has different meaning in CoreGraphics.
  
