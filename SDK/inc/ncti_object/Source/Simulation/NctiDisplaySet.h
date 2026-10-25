#ifndef NctiDisplaySet_H
#define NctiDisplaySet_H
#include "NctiDisplaySimulationObject.h"
#include "NctiPosition.h"
#include "NctiVector.h"

namespace NCTI
{
    /**
    * @brief The set object
    */
    class DECL_NCTI_OBJECT NctiDisplaySet : public NctiDisplaySimulationObject
    {
        NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySet)
    public:
        
        /**
        * @brief Get the face data
        * param[out] elemNums, the element indexs
        * param[out] faceDatas, the face indexs
        */
        bool GetFaceData(std::vector < Ncti_UInteger>& elemNums, std::vector<std::vector<Ncti_UInteger>>& faceDatas);
        
        /**
        * @brief Get the grid mesh
        */
        virtual NctiDisplayGridMesh* GetGridMesh()const;

        /**
        * @brief Get sampling points
        * @param[in] i_pDocCustomContainer, the doc contrainer
        * @param[in] normal, the normal
        * @return the array of sampling points
        */
        virtual std::vector<NCTI::NctiPosition> GetSimplifyCoord(NctiDisplayDocCustomContainer* i_pDocCustomContainer, std::vector<NCTI::NctiVector>* normal = nullptr)const;
        
        /**
        * @brief Get the element indexs
        */
        virtual std::vector<Ncti_UInteger> GetElementIndex();
        
        /**
        * @brief Get the face indexs
        */
        virtual std::vector<Ncti_UInteger> GetElementFaceIndex();

        /**
        * @brief Get sub object type
        * return the object type
        */
		virtual NctiSelectType GetSelType()const;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1);
    };

    /**
    * @brief The grid set object
    */
    class DECL_NCTI_OBJECT NctiDisplaySetGrid : public NctiDisplaySet
    {
        NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySetGrid)
	public:
        /**
        * @brief Get state
        * @retuen the state
        */
		SimulationStateType GetState() const override;
        
        /**
		* @brief Highlight segment
		* @param[in] i_bOnOff, true or false
        */
        void HighlightSegment(bool i_bOnOff)override;

        /**
        * @brief Get the grid mesh
        * @retuen the grid mesh
        */
        NctiDisplayGridMesh* GetGridMesh()const override;

        /**
        * @brief Get sub object type
        * return the object type
        */
        NctiSelectType GetSelType()const override;

        /**
		* @brief Get the element indexs
		* @return the array of element indexs
        */
        std::vector<Ncti_UInteger> GetElementIndex()override;

        /**
		* @brief Get the face indexs
		* @return the array of face indexs
        */
        std::vector<Ncti_UInteger> GetElementFaceIndex()override;

        /**
        * @brief Get sampling points
        * @param[in] i_pDocCustomContainer, the doc contrainer
        * @param[in] normal, the normal
        * @return the array of sampling points
        */
        std::vector<NCTI::NctiPosition>  GetSimplifyCoord(NctiDisplayDocCustomContainer* i_pDocCustomContainer, std::vector<NCTI::NctiVector>* normal = nullptr)const override;

        /**
        * @brief Get sub object type
        * @param[in] iType, the object type
        */
        void SetSelType(NctiSelectType iType);

        /**
		* @brief Get the element indexs
		* @param[in] vec, the array of element indexs
        */
        void SetElementIndex(const std::vector<Ncti_UInteger>& vec);

        /**
		* @brief Get the face indexs
		* @param[in] vec, the array of face indexs
        */
        void SetElementFaceIndex(const std::vector<Ncti_UInteger>& vec);

    private:
        NCTI_READ_AND_WRITE_VERSION_FUN(1);
        NCTI_VERSION(1, NctiSelectType, m_iType, sd_read_long);
        NCTI_VERSION(1, std::vector<Ncti_UInteger>, m_ElementIndexVec, sd_read_packed);
        NCTI_VERSION(1, std::vector<Ncti_UInteger>, m_ElementFaceIndexVec, sd_read_packed);
    };
}
#endif
