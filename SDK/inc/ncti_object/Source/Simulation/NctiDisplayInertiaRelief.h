#ifndef NctiDisplayInertiaRelief_H
#define NctiDisplayInertiaRelief_H
#include "NctiDisplayLoadObject.h"
#include <NctiMeshManager.h>
namespace NCTI
{
	class NctiVector;
	//惯性释放	
	/**
	* @brief The inertia relief object
	*/
	class DECL_NCTI_OBJECT NctiDisplayInertiaRelief : public NctiDisplayLoadObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayInertiaRelief)
	public:
		virtual ~NctiDisplayInertiaRelief();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_VERSION(1, std::vector<Ncti_UInteger>, m_ComponentsVec, sd_read_packed);
		NCTI_VERSION(1, NctiVector, m_Weights, sd_read_vector);
	public:
		
		/**
		* @brief Set the components
		* @param[in] iComponentsVec, the vector of components
		*/
		void SetComponentVec(const std::vector<Ncti_UInteger>& iComponentsVec);
		
		/**
		* @brief Set weights and direction
		* @param[in] pos, the unit Vector and add the weithts
		*/
		void SetWeights(const NctiVector& pos);
	public:
		
		/**
		* @brief Set the components
		* @return the vector of components
		*/
		const std::vector<Ncti_UInteger>& GetComponentVec() const { return m_ComponentsVec; }
		
		/**
		* @brief Get weights and direction
		* @rentrn the unit Vector and add the weithts
		*/
		const NctiVector& GetWeights() const { return m_Weights; }
	};
}
#endif
