
#include "Shapes.h"
inline float3 make_float3(const float& a, const float& b, const float& c)
{
	float3 f3;
	f3.x = a, f3.y = b, f3.z = c;
	return f3;
}
inline float3 operator-(const float3& a, float b)
{
	return make_float3(a.x - b, a.y - b, a.z - b);
}
inline float3 operator*(const float3& a, const float3& b)
{
	return make_float3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline void operator*=(float3& a, const float3& b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
}

inline float3 operator*(const float3& a, float b)
{
	return make_float3(a.x * b, a.y * b, a.z * b);
}

inline float3 operator*(float b, const float3& a)
{
	return make_float3(b * a.x, b * a.y, b * a.z);
}
inline float3 operator-(const float3& a, int b)
{
	return make_float3(a.x - static_cast<float>(b), a.y - static_cast<float>(b), a.z - static_cast<float>(b));
}
inline void operator+=(float3& a, const float3& b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
}
inline float3 cross(const float3& a, const float3& b)
{
	return make_float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
inline float dot(const float3& a, const float3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float3 operator+(const float3& a, const float3& b)
{
	return make_float3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline float3 operator/(const float3& a, const float3& b)
{
	return make_float3(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline void operator*=(float3& a, float b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
}
inline void operator/=(float3& a, const float3& b)
{
	a.x /= b.x;
	a.y /= b.y;
	a.z /= b.z;
}

inline float sqrLength(const float3& v)
{
	return dot(v, v);
}
inline float3 operator-(const float3& a, const float3& b)
{
	return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);
}



inline void operator/=(float3& a, float b)
{
	a.x /= b;
	a.y /= b;
	a.z /= b;
}

inline float3 operator/(float b, const float3& a)
{
	return make_float3(b / a.x, b / a.y, b / a.z);
}

Sphere::Sphere()
{
	center = {0};
	radius = 1;

}

void Sphere::Hit(Ray &r)
{
	
		const float3 toRay = r.O - center;
		const float b{dot(toRay, r.D)};
		const float c{sqrLength(toRay) - (radius * radius)};
		const float discriminant = b * b - c;
		if (c > 0.0f && b > 0.0f)
		{
			return;
		}
		if (discriminant < 0)
			return;

		const float rayLength{-b - sqrt(discriminant)};
		if (rayLength > r.t)
			return;
		if (rayLength < 0)
		{
			return;
		}
		// Calculate the outwards normal at the intersection point
		const float3 intersectionPoint{r.O + rayLength * r.D};
		const float3 outwardNormal{(intersectionPoint - center) / radius};

		// Inverse the normal if the ray is coming from inside the sphere
		const bool rayOutsideSphere{dot(r.D, outwardNormal) < 0};
		r.isInsideGlass = !rayOutsideSphere;
		r.t = rayLength;

	
}

bool Sphere::IsHit(const Ray &r)
{
    const float3 toRay = r.O - center;
		const float b{dot(toRay, r.D)};
		const float c{sqrLength(toRay) - (radius * radius)};
		const float discriminant = b * b - c;
		if (c > 0.0f && b > 0.0f)
		{
			return false;
		}
		if (discriminant < 0)
			return false;

		const float rayLength{-b - sqrt(discriminant)};
		if (rayLength < 0)
			return false;
		if (rayLength > r.t)
			return false;
		return true;
}

void Triangle::SetPos(const float3& pos)
{
	position = pos;
}


Triangle::Triangle()
{
	const float3 r0(0, 0, 0);
	const float3 r1(0.5f,1, 0);
	const float3 r2(1, 0, 0);
	vertex0 = r0;
	vertex1 = r1;
	vertex2 = r2;
	centroid = (vertex0 + vertex1 + vertex2) * 0.3333f;
	position = {0};
}

void Triangle::Hit(Ray &ray)
{
	float3 p1 = position, p2 = position, p3 = position;
		p1 += vertex0;
		p2 += vertex1;
		p3 += vertex2;
		const float3 edge1 = p2 - p1;
		const float3 edge2 = p3 - p1;
		const float3 h = cross(ray.D, edge2);
		const float a = dot(edge1, h);
		if (a > -0.0001f && a < 0.0001f) return; // ray parallel to triangle
		const float f = 1 / a;
		const float3 s = ray.O - p1;
		const float u = f * dot(s, h);
		if (u < 0 || u > 1) return;
		const float3 q = cross(s, edge1);
		const float v = f * dot(ray.D, q);
		if (v < 0 || u + v > 1) return;
		const float t = f * dot(edge2, q);
		if (t > 0.0001f)
		{
			if (ray.t > t)
			{
				ray.t = t;
			}
		}
}

bool Triangle::IsHit(const Ray &ray)
{
    float3 p1 = position, p2 = position, p3 = position;
		p1 += vertex0;
		p2 += vertex1;
		p3 += vertex2;
		const float3 edge1 = p2 - p1;
		const float3 edge2 = p3 - p1;
		const float3 h = cross(ray.D, edge2);
		const float a = dot(edge1, h);
		if (a > -0.0001f && a < 0.0001f) return false; // ray parallel to triangle
		const float f = 1 / a;
		const float3 s = ray.O - p1;
		const float u = f * dot(s, h);
		if (u < 0 || u > 1) return false;
		const float3 q = cross(s, edge1);
		const float v = f * dot(ray.D, q);
		if (v < 0 || u + v > 1) return false;
		const float t = f * dot(edge2, q);
		if (t < 0.0001f)
		{
			return false;
		}
		if (t > ray.t)
		{
			return false;
		}
		return true;
}

float3 Ray::IntersectionPoint()
{
   
		return O + t * D;
	
}
