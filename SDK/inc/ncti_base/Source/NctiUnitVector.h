#ifndef NctiUnitVector_H
#define NctiUnitVector_H
#include "ncti_base.h"
#include "NctiVector.h"
namespace NCTI
{
	class NctiUnitVector;
	class NctiTransf;
	NctiUnitVector operator-(NctiUnitVector const &vec_);
	NctiPosition operator*(NctiPosition const &pt_, NctiUnitVector const & vec_);
	NctiPosition operator*(NctiUnitVector const & vec_, NctiPosition const &pt_);
	NctiUnitVector normalise(NctiVector const &);
	/**
	* @brief NctiUnitVector
	* @see NctiVector
	*/
	class DECL_NCTI_BASE NctiUnitVector : public NctiVector
	{
		friend Ncti_Double operator%(NctiUnitVector const &, NctiPosition const &);
		friend NctiPosition operator*(NctiPosition const &, NctiUnitVector const &);
		friend NctiPosition operator*(NctiUnitVector const &, NctiPosition const &);
	public:
		NctiUnitVector() {};
		NctiUnitVector(Ncti_Double x, Ncti_Double y, Ncti_Double z);
		~NctiUnitVector() {};
		NctiUnitVector const &operator*=(NctiTransf const &transf_);
	};
	inline NctiPosition operator*(NctiUnitVector const &vec_, NctiPosition const &p)
	{
		NctiUnitVector t = (-vec_);
		return p * t;
	}
	inline NctiPosition operator*(NctiPosition const &p, NctiUnitVector const & vec_)
	{
		return NctiPosition(
			p.y() * vec_.z() - p.z() * vec_.y(),
			p.z() * vec_.x() - p.x() * vec_.z(),
			p.x() * vec_.y() - p.y() * vec_.x()
		);
	}
	/**
    * @brief create a new normalise NctiUnitVector
	* @return NctiTransf
	*/
	inline NctiUnitVector normalise(NctiVector const & vec_)
	{
		return NctiUnitVector(vec_.x(), vec_.y(), vec_.z());
	}
	inline NctiUnitVector operator-(NctiUnitVector const & uv)
	{
		NctiVector temp = -*(NctiVector const *)&uv;
		return *(NctiUnitVector *)&temp;
	}
#define NCTI_X_AXIS NctiUnitVector(1,0,0)
#define NCTI_Y_AXIS NctiUnitVector(0,1,0)
#define NCTI_Z_AXIS NctiUnitVector(0,0,1)
}

#endif
