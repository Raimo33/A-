
# A* Algorithm Visualizer

This project is a simple visualizer for the A* pathfinding algorithm, built using the Simple and Fast Multimedia Library (SFML). It allows users to set the start and end points, place obstacles, and visualize the pathfinding process in real-time.

## Features

 - Set start and end points for the pathfinding.
 - Place obstacles on the grid.
 - Visualize the A* pathfinding algorithm in action. 
 - Interactive controls to reset the grid and restart the visualization.

## Prerequisites

   Before you can run this project, ensure you have the
   following installed:

 - Docker
 - Make

## Setup Guide

 1. Clone the repository:
```bash
git clone https://github.com/yourusername/aStarVisualizer.git
cd aStarVisualizer
```
 2. Build the Docker image:
```bash
make docker-build
```
 3. Run the A visualizer*:
```bash
make docker-run
```
## Controls

**S** - Set the start point.
**E** - Set the end point.
**R** - Reset the grid.
**Space** - Start the A* pathfinding visualization.

## Notes

Ensure your Docker setup can access the display server to render the SFML window. You may need to configure X11 forwarding on Linux.
