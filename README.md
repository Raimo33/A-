![Screenshot from 2024-06-13 20-24-30](https://github.com/Raimo33/A_star/assets/104778891/f390c443-c1d3-4622-8615-f9f304e8622d)
![Screenshot from 2024-06-13 20-23-43](https://github.com/Raimo33/A_star/assets/104778891/b0385ff0-dc20-46cd-a9bf-77551204d56e)
![Screenshot from 2024-06-13 20-23-10](https://github.com/Raimo33/A_star/assets/104778891/eb1ae8fa-58cd-46d0-8f2e-e5330b96e475)

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
