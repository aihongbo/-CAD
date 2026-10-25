#ifndef NctiDCM3PatternConstraint_H
#define NctiDCM3PatternConstraint_H
#include "dcl_ncti_object.h"
#include <iostream>
#include <vector>
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiDCM3PatternConstraint
	{
	private:
		std::vector<double> m_fmultipliers;

	public:

		NctiDCM3PatternConstraint() {}
		NctiDCM3PatternConstraint(const std::vector<double>& i_multipliers);
		~NctiDCM3PatternConstraint() { }

		double multiplier(int i_index) { return m_fmultipliers[i_index]; }
		void set_multiplier(int i_index, double i_multi) { m_fmultipliers[i_index] = i_multi; }
	};
}
#endif
