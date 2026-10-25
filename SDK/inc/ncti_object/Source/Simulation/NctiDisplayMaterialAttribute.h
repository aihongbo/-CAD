#ifndef NctiDisplayMaterialAttribute_H
#define NctiDisplayMaterialAttribute_H
#include "NctiDisplayBasePhysicalObj.h"
namespace NCTI
{
	//材料
	
	/**
	* @brief The material object
	*/
	class DECL_NCTI_OBJECT NctiDisplayMaterialAttribute : public NctiDisplayBasePhysicalObj
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayMaterialAttribute)
	public:
		virtual ~NctiDisplayMaterialAttribute();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
		SimulationStateType GetState() const override;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	private:
		NCTI_VERSION(1, Ncti_Double, m_E, sd_read_double);//弹性模量
		NCTI_VERSION(1, Ncti_Double, m_G, sd_read_double);//剪切模量
		NCTI_VERSION(1, Ncti_Double, m_nu, sd_read_double);//泊松比
		NCTI_VERSION(1, Ncti_Double, m_rho, sd_read_double);//密度
		NCTI_VERSION(1, Ncti_Double, m_a, sd_read_double);//热膨胀

		NCTI_VERSION(1, Ncti_Boolean, m_bE, sd_read_bool);
		NCTI_VERSION(1, Ncti_Boolean, m_bG, sd_read_bool);
		NCTI_VERSION(1, Ncti_Boolean, m_bnu, sd_read_bool);
		NCTI_VERSION(1, Ncti_Boolean, m_brho, sd_read_bool);
		NCTI_VERSION(1, Ncti_Boolean, m_ba, sd_read_bool);

	public:
		
		/**
		* @brief Set the elastic modulus
		* @param[in] i_E
		*/
		void SetE(Ncti_Double* i_E);

		/**
		* @brief Set the shear modulus
		* @param[in] i_G
		*/
		void SetG(Ncti_Double* i_G);

		/**
		* @brief Set the poisson's ratio
		* @param[in] i_NU
		*/
		void SetNU(Ncti_Double* i_NU);

		/**
		* @brief Set the Density
		* @param[in] i_RHO
		*/
		void SetRHO(Ncti_Double* i_RHO);

		/**
		* @brief Set the thermal expansion
		* @param[in] i_A
		*/
		void SetA(Ncti_Double* i_A);
	public:
		/**
		* @brief Get the elastic modulus
		* @return the elastic modulus
		*/
		Ncti_Double* GetE();

		/**
		* @brief Get the shear modulus
		* @return the shear modulus
		*/
		Ncti_Double* GetG();

		/**
		* @brief Get the poisson's ratio
		* @return the poisson's ratio
		*/
		Ncti_Double* GetNU();

		/**
		* @brief Get the Density
		* @return the Density
		*/
		Ncti_Double* GetRHO();

		/**
		* @brief Get the thermal expansion
		* @return the thermal expansion
		*/
		Ncti_Double* GetA();
	};
}
#endif
