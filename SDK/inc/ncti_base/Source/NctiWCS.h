#ifndef NctiWCS_H
#define NctiWCS_H
#include "ncti_base.h"
#include "NctiPosition.h"
#include "NctiUnitVector.h"
#include "NctiTransf.h"
namespace NCTI
{
	/**
	* @brief use to coordinate transformation
	*/
	class DECL_NCTI_BASE NctiWCS : public NCTI_BASE_CLASS
	{
	protected:
		NctiWCS();
	public:
		NctiWCS(const NctiPosition&   i_posOrigin, const NctiPosition&  i_posAxisX, const NctiPosition&  i_posAxisY);
		/**
	   * @brief get model coordinate
	   * @return NctiTransf
	   */
		NctiTransf ToModel();
		/**
	   * @brief get word coordinate
	   * @return NctiTransf
	   */
		NctiTransf ToWorld();
	protected:
		NctiPosition m_posOrigin;
		NctiUnitVector m_uvecAxisX;
		NctiUnitVector m_uvecAxisY;
		NctiTransf m_transfModel;
	};
}
#endif
