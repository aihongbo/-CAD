#ifndef NctiDCMEXVec3d_H
#define NctiDCMEXVec3d_H
#include "dcl_ncti_object.h"
#include "ncti_base.h"
#include "NctiPosition.h"
#include <iostream>
namespace NCTI
{
	// Define a local structure for 2d vectors
	class DECL_NCTI_OBJECT NctiDCMEXVec3d
	{
	public:
		double x;
		double y;
		double z;
		NctiDCMEXVec3d() : x(0.0), y(0.0), z() {}
		NctiDCMEXVec3d(const NctiDCMEXVec3d& v) : x(v.x), y(v.y), z(v.z) {}
		NctiDCMEXVec3d(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
		NctiDCMEXVec3d(double v[3]) { x = v[0]; y = v[1]; z = v[2]; }

		NctiDCMEXVec3d normal()
		{
			NctiDCMEXVec3d norm;
			double div = sqrt(x * x + y * y + z * z);
			norm.x = x / div;
			norm.y = y / div;
			norm.z = z / div;
			return norm;
		}

		void transform_pos(Ncti_Double i_mat[4][4]);
		void transform_dir(Ncti_Double i_mat[4][4]);

		NctiDCMEXVec3d operator - () const
		{
			return NctiDCMEXVec3d(-x, -y, -z);
		}
		NctiDCMEXVec3d operator + () const
		{
			return *this;
		}

		NctiPosition to_position() const
		{
			return NctiPosition(x, y, z);
		}

		operator double* () { return &x; }

		friend std::ostream& operator<<(std::ostream& s, NctiDCMEXVec3d* v)
		{
			return s << "[" << v->x << ", " << v->y << ", " << v->z << "]";
		}
		friend std::ostream& operator<<(std::ostream& s, NctiDCMEXVec3d v) 
		{
			return s << &v;
		}

		friend NctiDCMEXVec3d operator*(double a, const NctiDCMEXVec3d& v)
		{
			return NctiDCMEXVec3d(a * v.x, a * v.y, a * v.z);
		}
		friend NctiDCMEXVec3d operator*(const NctiDCMEXVec3d& v, double a)
		{
			return NctiDCMEXVec3d(v.x * a, v.y * a, v.z * a);
		}
		friend NctiDCMEXVec3d operator/(const NctiDCMEXVec3d& v, double a)
		{
			return NctiDCMEXVec3d(v.x / a, v.y / a, v.z / a);
		}
		friend NctiDCMEXVec3d operator+(const NctiDCMEXVec3d& a, const NctiDCMEXVec3d& b)
		{
			return NctiDCMEXVec3d(a.x + b.x, a.y + b.y, a.z + b.z);
		}
		friend NctiDCMEXVec3d operator-(const NctiDCMEXVec3d& a, const NctiDCMEXVec3d& b)
		{
			return NctiDCMEXVec3d(a.x - b.x, a.y - b.y, a.z - b.z);
		}
		// scalar product
		friend double operator%(const NctiDCMEXVec3d& a, const NctiDCMEXVec3d& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}
		// cross product
		friend NctiDCMEXVec3d operator*(const NctiDCMEXVec3d& a, const NctiDCMEXVec3d& b)
		{
			return NctiDCMEXVec3d(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
		}

		void fill_array(double c[3]) const { c[0] = x; c[1] = y; c[2] = z; }

	public:
		static Ncti_Double length(const NctiDCMEXVec3d& a, const NctiDCMEXVec3d& b)
		{
			return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
		}
	};
}
#endif
