#ifndef NctiDisplayParticleObject_H
#define NctiDisplayParticleObject_H
#include "NctiDisplayBasePhysicalObj.h"
namespace NCTI
{
	
	/**
	* @brief The particle object
	*/
	class DECL_NCTI_OBJECT NctiDisplayParticleObject : public NctiDisplayBasePhysicalObj
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayParticleObject)
	public:
		virtual ~NctiDisplayParticleObject();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
		virtual EnumNctiResult ActivateData(
			NctiDisplayDocCustomContainer* i_pDisplayDocCustomContainer,
			const std::vector<NCTI_MODEL_TAG>& i_ModelBodyVec);
		void Compress(int)override;
		void UnCompress(int)override;
		int InitPackedData()override;
		SimulationStateType GetState() const;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	private:
		NCTI_VERSION(1, Ncti_Double, m_dRadius, sd_read_double);
		NCTI_VERSION(1, Ncti_Long, m_PackedSubNum, sd_read_long);
		NCTI_VERSION_MODIFY(1, std::vector<Ncti_Float>, m_positions, sd_read_packed);
		NCTI_VERSION(1, Ncti_Boolean, m_bSquareModel, sd_read_bool);

		//
		std::vector<NctiMeshPacked> m_MeshPackedPosVec;
		bool m_PackedIsSamePos;
	public:
		
		/**
		* @brief set points
		* @param[in] pts, the vector of NctiPosition
		*/
		void SetPoints(const std::vector<NctiPosition>& pts);

		/**
		* @brief set points
		* @param[in] pts, the vector of Ncti_Float
		*/
		void SetPoints(const std::vector<Ncti_Float>& pts);

		/**
		* @brief get points
		* @return the vector of Ncti_Float
		*/
		const std::vector<Ncti_Float>& GetPoints() { return m_positions; }

		/**
		* @brief set radius
		* @param[in] dRadius, the radius
		*/
		void SetRadius(double dRadius);

		/**
		* @brief get radius
		* @return Ncti_Double, the radius
		*/
		Ncti_Double GetRadius() { return m_dRadius; };

		/**
		* @brief set sphere display
		* @param[in] bval, true:show sphere false:show square
		*/
		void SetSphereModel(Ncti_Boolean bval);

		/**
		* @brief get whether the sphere is displayed
		* @return Ncti_Boolean
		*/
		Ncti_Boolean GetSphereModel(){ return m_bSquareModel; }
	private:
		void CompressPosition(int num);
		void UnCompressPosition(int num);
	};
}
#endif
