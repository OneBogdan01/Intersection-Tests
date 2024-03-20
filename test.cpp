#include "pch.h"
#include "Shapes.h"


TEST(SphereIntersection, TouchingSphereInOnePoint)
{
	Ray ray;
	ray.O = float3(0, 1, 0);
	ray.D = float3(0, 0, 1);
	Sphere sphere;
	sphere.center = float3(0, 0, 5);
	sphere.radius = 1;
	sphere.Hit(ray);
	
	ASSERT_EQ(ray.t, 5);

}
TEST(SphereIntersection, TouchingSphereInTwoPoints)
{
	Ray ray;
	ray.O = float3(0, 0, 0);
	ray.D = float3(0, 0, 1);
	Sphere sphere;
	sphere.center = float3(0, 0, 5);
	sphere.radius = .5f;
	sphere.Hit(ray);

	ASSERT_EQ(ray.t, 4.5f);

}
TEST(SphereIntersection, Miss)
{
	Ray ray;
	ray.O = float3(0, 0, 6);
	ray.D = float3(0, 0, 1);
	Sphere sphere;
	sphere.center = float3(0, 0, 5);
	sphere.radius = .5f;
	sphere.Hit(ray);

	ASSERT_EQ(ray.t, 1e34f);

}
TEST(TriangleIntersection, TouchingInOnePoint)
{
	Ray ray;
	ray.O = float3(0, 0, -1);
	ray.D = float3(0, 0, 1);
	Triangle tri;//makes the boring Opengl Triangle

	tri.Hit(ray);
	
	ASSERT_EQ(ray.t, 1);

}
TEST(TriangleIntersection, TouchingOnTip)
{
Ray ray;
	ray.O = float3(0, 1, -1);
	ray.D = float3(0, 0, 1);
	Triangle tri;//makes the boring Opengl Triangle
	tri.vertex1 = float3(0, 1, 5); //the middle vertex is to the left now
	tri.Hit(ray);
	
	ASSERT_EQ(ray.t, 6);

}
TEST(TriangleIntersection, Miss)
{
Ray ray;
	ray.O = float3(0, -.01f, -1);
	ray.D = float3(0, 0, 1);
	Triangle tri;//makes the boring Opengl Triangle

	tri.Hit(ray);
	
	ASSERT_EQ(ray.t, 1e34f);

}