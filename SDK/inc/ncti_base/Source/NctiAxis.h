#ifndef NctiAxis_H
#define NctiAxis_H
#include "ncti_base.h"
#include "NctiPosition.h"
#include "NctiVector.h"
namespace NCTI
{
	/**
	* @brief Axis class
	* @details deal axis operation, include position, normal, first direction
	* @see NctiDummyBaseClass
	*/
	class DECL_NCTI_BASE NctiAxis : public NCTI::NctiDummyBaseClass
	{
	public:
		 NctiAxis();
		 NctiAxis(const NctiPosition & i_sPosition);
		 NctiAxis(const NctiPosition& i_sPosition, const NctiVector& i_sNormal);
		 NctiAxis(const NctiPosition& i_sPosition, const NctiVector& i_sNormal, const NctiVector& i_sXDirection);
		 ~NctiAxis();
		 /**
	    * @brief get position of axis
		* @return NctiPosition
	    */
		 NctiPosition GetPosition() const{ return m_Position; }
		 /**
	    * @brief get normal of axis
		* @return NctiVector
	    */
		 NctiVector GetNormal() const { return m_vNormal; }
		 /**
		* @brief get first direction of axis
		* @return NctiVector
		*/
		 NctiVector GetFirstDirection() const { return m_firstDirection; }
		 /**
		* @brief get new mat[4][4] by axis and this
		* @param[in] axis, the input axis
		* @param[out] axis, the output value
		*/
		 void GetTransformMatrixTo(const NctiAxis& i_axis, Ncti_Double o_mat[4][4]);
		 /**
	    * @brief set position of axis
		* @param[in] i_Position
	    */
		 void SetPosition(const NctiPosition& i_Position);
		 /**
		* @brief set normal of axis
		* @param[in] i_Normal
		*/
		 void SetNormal(const NctiVector& i_Normal);
		 /**
		* @brief set first direction of axis
		* @param[in] i_firstDirection
		*/
		 void SetFirstDirection(const NctiVector& i_firstDirection);
	public:
		 NctiAxis& operator=(const NctiAxis & i_rhs);
		 friend std::ostream& operator<<(std::ostream& i_os, const NctiAxis& i_axis)
		 {
			 i_os << "Oringin  " << i_axis.GetPosition();
			 i_os << "Normal " << i_axis.GetNormal();
			 i_os << "First Direction" << i_axis.GetFirstDirection();
			 return i_os;
		 }
	private:
		NctiPosition m_Position;
		NctiVector m_vNormal;
		NctiVector m_firstDirection;
	};
}
#endif

