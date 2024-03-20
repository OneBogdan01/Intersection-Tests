#pragma once
#include <cmath>

struct float3
{
	float3() = default;

	float3(const float a, const float b, const float c) : x(a), y(b), z(c)
	{
	}

	float3(const float a) : x(a), y(a), z(a)
	{
	}

	

	
	union
	{
		struct
		{
			float x, y, z;
		};

		float cell[3];
	};

	float& operator [](const int n)
	{
		return cell[n];
	}
};
class Ray
{
public:
	void CopyToPrevRay(Ray& ray);
	Ray() = default;
	Ray(const Ray& ray);

	float3 ComputeDsign(const float3& _D) const;
	Ray(const float3 origin, const float3 direction, const float rayLength = 1e34f, const int = 0);

	float3 IntersectionPoint() ;

	//from Ray tracing in one weekend
	static Ray GetRefractedRay(const Ray& ray, const float IORRatio, bool& isReflected);



	float3 GetAbsorption(const float3& I) const; // TODO: implement
	float3 Evaluate(const float3& I) const; // TODO: implement
	// ray data
	float3 O; // ray origin //12 bytes
	float3 rD; // reciprocal ray direction
	float3 D = float3(0); // ray direction
	float3 Dsign = float3(1); // 48 bytes
	float3 rayNormal{0}; //60 bytes

	float t = 1e34f; // ray length
	bool isInsideGlass = false;



private:

};
struct Sphere
{
	Sphere(float3 c, float r) : center(c), radius(r)
	{
	}

	Sphere();
	// For ray/sphere intersection: https://gamedev.stackexchange.com/questions/96459/fast-ray-sphere-collision-code
	void Hit(Ray& r);
	

	bool IsHit(const Ray& r);
	

	float3 center;
	float radius;
};

//based on https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/
struct Triangle
{
	void SetPos(const float3& pos);
	Triangle();


	void Hit(Ray& ray);


	bool IsHit(const Ray& ray);
	

	float3 vertex0, vertex1, vertex2; //12
	float3 centroid={0}; //16
	float3 position={0}; //20

};
