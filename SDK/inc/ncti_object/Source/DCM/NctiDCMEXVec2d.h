#ifndef NctiDCMEXVec2d_H
#define NctiDCMEXVec2d_H
#include "dcl_ncti_object.h"
#include "NctiDCMDef.h"
#include "ncti_base.h"
#include <iostream>
#include "NctiPosition.h"
#include "NctiVector.h"
namespace NCTI
{
	// Define a local structure for 2d vectors
	class DECL_NCTI_OBJECT NctiDCMEXVec2d
	{
	public:
		double x;
		double y;
		NctiDCMEXVec2d() : x(0.0), y(0.0) {}
		NctiDCMEXVec2d(const NctiDCMEXVec2d& v) : x(v.x), y(v.y) {}
		NctiDCMEXVec2d(double xx, double yy) : x(xx), y(yy) {}
		NctiDCMEXVec2d(double v[2]) { x = v[0]; y = v[1]; }

		NctiDCMEXVec2d normal() const
		{
			NctiDCMEXVec2d norm;
			double div = sqrt(x * x + y * y);
			norm.x = x / div;
			norm.y = y / div;
			return norm;
		}
		NCTI_DCM_logical operator == (const NctiDCMEXVec2d& v2) const;
		NCTI_DCM_logical operator != (const NctiDCMEXVec2d& v2) const
		{
			return !(*this == v2);
		}
		NctiDCMEXVec2d operator - (const NctiDCMEXVec2d& vref) const
		{
			return NctiDCMEXVec2d(x - vref.x, y - vref.y);
		}
		NctiDCMEXVec2d operator + (const NctiDCMEXVec2d& vref) const
		{
			return NctiDCMEXVec2d(x + vref.x, y + vref.y);
		}
		NctiDCMEXVec2d operator * (const double r) const
		{
			return NctiDCMEXVec2d(r * x, r * y);
		}

		NctiPosition to_position() const
		{
			return NctiPosition(x, y, 0);
		}

		NctiVector to_vector() const
		{
			return NctiVector(x, y, 0);
		}

		// Cross product
		double operator*(const NctiDCMEXVec2d& b) const
		{
			return x * b.y - y * b.x;
		}

		// Dot product
		double operator%(const NctiDCMEXVec2d& b) const
		{
			return x * b.x + y * b.y;
		}

		bool parallel(const NctiDCMEXVec2d& i_dir) const;
		bool coincident(const NctiDCMEXVec2d& i_dir) const;

		void transform_pos(const Ncti_Double i_mat[3][3]);
		void transform_dir(const Ncti_Double i_mat[3][3]);

		friend std::ostream& operator<<(std::ostream& s, NctiDCMEXVec2d v)
		{
			return s << &v;
		}
	public:
		static Ncti_Double length(const NctiDCMEXVec2d& i_pt1, const NctiDCMEXVec2d& i_pt2)
		{
			return sqrt((i_pt1.x - i_pt2.x) * (i_pt1.x - i_pt2.x) + (i_pt1.y - i_pt2.y) * (i_pt1.y - i_pt2.y));
		}
	};
}
#endif
