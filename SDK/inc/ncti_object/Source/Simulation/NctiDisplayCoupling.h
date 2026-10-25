#ifndef NctiDisplayCoupling_H
#define NctiDisplayCoupling_H
#include "NctiDisplaySinglePointConstraint.h"
namespace NCTI
{
	//耦合	
	/**
	* @brief The coupling object
	*/
	class DECL_NCTI_OBJECT NctiDisplayCoupling : public NctiDisplaySinglePointConstraint
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayCoupling)
	public:
		virtual ~NctiDisplayCoupling();
	public:
		virtual void Init();
        void HighlightSegment(bool i_bOnOff)override;
		virtual EnumNctiResult UpdateDisplay();
		virtual EnumNctiResult ActivateData(
			NctiDisplayDocCustomContainer* i_pDisplayDocCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		virtual SimulationStateType GetState() const;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	private:
		NCTI_VERSION_OBJECT(1, NctiDisplaySet*, m_pSet2, sd_read_long);
		NCTI_VERSION(1, Ncti_Integer, m_iCouplingType, sd_read_long);//0:Kinematic; 1:Continuum distributing 2:Structural distributing
		NCTI_VERSION(1, Ncti_Double, m_dAlpha, sd_read_long);//Thermal Expansion Coefficient( m_iCouplingType:0 Kinematic)
		NCTI_VERSION(1, Ncti_Double, m_dInfluenceRadius, sd_read_long);//-1:To outermost point on the region; >=0:Specify
		NCTI_VERSION(1, Ncti_Integer, m_iWeightingMethod, sd_read_long);// 0:Uniforrm; 1:Linear 2:Quadratic 3:Cubic(m_iCouplingType:1:Continuum distributing 2:Structural distributing )
		NCTI_VERSION(1, Ncti_Boolean, m_bAdjust, sd_read_bool);//Adjust control points to lie on surface
	public:
		
		/**
		* @brief set the face set
		* @details the set1 is node
		* @param[in] pSet, the set
		*/
		void SetSet2(NctiDisplaySet* pSet);

		/**
		* @brief set the coupling type 
		* @param[in] val, 0:Kinematic; 1:Continuum distributing 2:Structural distributing
		*/
		void SetCouplingType(Ncti_Integer val);
		
		/**
		* @brief set the thermal Expansion Coefficient
		* @param[in] val, the thermal Expansion Coefficient( m_iCouplingType:0 Kinematic)
		*/
		void SetAlpha(Ncti_Double val);
		
		/**
		* @brief set the influence radius
		* @param[in] val, -1:To outermost point on the region; >=0:Specify
		*/
		void SetInfluenceRadius(Ncti_Double val);
		
		/**
		* @brief set the adjust control points to lie on surface
		* @param[in] val
		*/
		void SetAdjust(Ncti_Boolean val);
		
		/**
		* @brief set the weighting method
		* @param[in] val, 0:Uniforrm; 1:Linear 2:Quadratic 3:Cubic(m_iCouplingType:1:Continuum distributing 2:Structural distributing )
		*/
		void SetWeightingMethod(Ncti_Integer val);
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
		Ncti_Integer GetCouplingType();
		
		/**
		* @brief get the thermal Expansion Coefficient
		* @return the value
		*/
		Ncti_Double GetAlpha();
		
		/**
		* @brief get the influence radius
		* @return the value
		*/
		Ncti_Double GetInfluenceRadius();
		
		/**
		* @brief get the adjust control points to lie on surface
		* @return the value
		*/
		Ncti_Boolean GetAdjust();
		
		/**
		* @brief get the weighting method
		* @return the value
		*/
		Ncti_Integer GetWeightingMethod();
	};
}
#endif
