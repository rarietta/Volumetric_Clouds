// CIS565 CUDA Raytracer: A parallel raytracer for Patrick Cozzi's CIS565: GPU Computing at the University of Pennsylvania
// Written by Yining Karl Li, Copyright (c) 2012 University of Pennsylvania
// This file includes code from:
//       Yining Karl Li's TAKUA Render, a massively parallel pathtracing renderer: http://www.yiningkarlli.com

#ifndef CUDASTRUCTS_H
#define CUDASTRUCTS_H

#include "glm/glm.hpp"
#include "cudaMat4.h"
#include <cuda_runtime.h>
#include <string>

enum GEOMTYPE{ SPHERE, CUBE, MESH };

struct ray {
	glm::vec3 origin;
	glm::vec3 direction;
};

struct voxel {
	char states;
	float density;
	float vaporProbability;
	float extinctionProbability;
	float phaseTransitionProbability;
	bool isOldCloud;
};

struct geom {
	enum GEOMTYPE type;
	int objectid;
	int materialid;
	int frames;
	glm::vec3* translations;
	glm::vec3* rotations;
	glm::vec3* scales;
	cudaMat4* transforms;
	cudaMat4* inverseTransforms;
};

struct staticGeom {
	enum GEOMTYPE type;
	int objectid;
	int materialid;
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	cudaMat4 transform;
	cudaMat4 inverseTransform;
};

struct volume {
	bool isSet;
	int volumeid;
	int materialid;
	float delt;
	float step;
	float velocity;
	glm::vec3 xyzc;
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	cudaMat4 transform;
	cudaMat4 inverseTransform;
	voxel* voxels;
};

struct light {
	int lightid;
	glm::vec3 color;
	glm::vec3 position;
};

struct cameraData {
	float delt;
	float step;
	glm::vec3 brgb;
	glm::vec3 xyzc;
	glm::vec2 resolution;
	glm::vec3 position;
	glm::vec3 view;
	glm::vec3 up;
	glm::vec3 focus;
	glm::vec2 fov;
};

struct camera {

	// volumetric data for 
	// ray marching
	float delt;					// dimenstion of square of voxel
	float step;					// size of step to be take by ray
	glm::vec3 xyzc;				// dimension of voxel grid

	// intrinsic camera stuff
	glm::vec3 position;			// eye positions
	glm::vec3 view;				// camera directions
	glm::vec3 up;				// up vectors
	glm::vec2 fov;				// y-field-of-view
	float zoom;					// camera zoom

	// render data
	glm::vec3 brgb;				// background color of render
	glm::vec3* image;			// final image
	glm::vec2 resolution;		// resolution of image
	std::string imageName;		// filename to write image to
	unsigned int iterations;	// number of iterations per frame
};

struct material{
	glm::vec3 color;
};

#endif //CUDASTRUCTS_H
