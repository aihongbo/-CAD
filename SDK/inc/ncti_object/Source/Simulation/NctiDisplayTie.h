#ifndef NctiDisplayTie_H
#define NctiDisplayTie_H
#include "NctiDisplayBasePhysicalObj.h"
namespace NCTI
{
	//Tie
	/**
	* @brief The tie object
	*/
	class DECL_NCTI_OBJECT NctiDisplayTie : public NctiDisplayBasePhysicalObj
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayTie)
	public:
		virtual ~NctiDisplayTie();
	public:
		virtual void Init();
        void HighlightSegment(bool i_bOnOff)override;
		virtual EnumNctiResult UpdateDisplay();
		virtual SimulationStateType GetState() const;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	private:
		NCTI_VERSION_OBJECT(1, NctiDisplaySet*, m_pSet2, sd_read_long);
		NCTI_VERSION(1, Ncti_Integer, m_iMethodType, sd_read_long);//0:default; 1:node face 2:face face
		NCTI_VERSION(1, Ncti_Boolean, m_bThickness, sd_read_bool);//Exclude shellelement thicknesse
		NCTI_VERSION(1, Ncti_Boolean, m_bPositionToleranceDefault, sd_read_bool);//Position Tolerance
		NCTI_VERSION(1, Ncti_Double, m_dDistance, sd_read_long);//Specify distance
		NCTI_VERSION(1, Ncti_Boolean, m_bAdjust, sd_read_bool);//Adjust secondary surface initial position
		NCTI_VERSION(1, Ncti_Boolean, m_bTieRotational, sd_read_bool);//Tie rotational DOFs if applicable
		NCTI_VERSION(1, Ncti_Boolean, m_bConstraintRatioDefault, sd_read_bool);//Constraint Ratio
		NCTI_VERSION(1, Ncti_Double, m_dRatio, sd_read_long);//Ratio
	public:
		
		/**
		* @brief set the face set
		* @details the set1 is node
		* @param[in] pSet, the set
		*/
		void SetSet2(NctiDisplaySet* pSet);

		/**
		* @brief set the method type 
		* @param[in] val, 0:default; 1:node face 2:face face
		*/
		void SetMethodType(Ncti_Integer val);
		
		/**
		* @brief set the exclude shellelement thicknesse
		* @param[in] val, true or false 
		*/
		void SetThickness(Ncti_Boolean val);
		
		/**
		* @brief set the position tolerance
		* @param[in] val, true or false 
		*/
		void SetPositionTolerance(Ncti_Boolean val);
		
		/**
		* @brief set the specify distance
		* @param[in] val, the specify distance
		*/
		void SetDistance(Ncti_Double val);
		
		/**
		* @brief set the adjust control points to lie on surface
		* @param[in] val, true or false
		*/
		void SetAdjust(Ncti_Boolean val);
		
		/**
		* @brief set the tie rotational DOFs if applicable
		* @param[in] val, true or false
		*/
		void SetTieRotational(Ncti_Boolean val);
		
		/**
		* @brief set the constraint ratio
		* @param[in] val, true or false
		*/
		void SetConstraintRatio(Ncti_Boolean val);
		
		/**
		* @brief set the ratio
		* @param[in] val
		*/
		void SetRatio(Ncti_Double val);
	public:
		/**
		* @brief get the face set
		* @return the set
		*/
		NctiDisplaySet* GetSet2();

		/**
		* @brief get the coupling type 
		* @return the value
		*/
		Ncti_Integer GetMethodType();

		/**
		* @brief get the exclude shellelement thicknesse
		* @return the value
		*/
		Ncti_Boolean GetThickness();

		/**
		* @brief get the position tolerance
		* @return the value
		*/
		Ncti_Boolean GetPositionTolerance();

		/**
		* @brief get the specify distance
		* @return the value
		*/
		Ncti_Double GetDistance();

		/**
		* @brief get the adjust secondary surface initial position
		* @return the value
		*/
		Ncti_Boolean GetAdjust();

		/**
		* @brief get the tie rotational DOFs if applicable
		* @return the value
		*/
		Ncti_Boolean GetTieRotational();

		/**
		* @brief get the constraint ratio
		* @return the value
		*/
		Ncti_Boolean GetConstraintRatio();

		/**
		* @brief get the ratio
		* @return the value
		*/
		Ncti_Double GetRatio();
	};
}
#endif
