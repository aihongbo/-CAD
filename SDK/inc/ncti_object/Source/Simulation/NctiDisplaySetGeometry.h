#ifndef NctiDisplaySetGeometry_H
#define NctiDisplaySetGeometry_H
#include "NctiDisplaySet.h"
#include "NctiDisplayModelBody.h"
#include "set"
#include "NctiGridPickSet.h"
namespace NCTI
{
	//set geometry
	enum DECL_NCTI_OBJECT SimulationGeoSetType
	{
		NCTI_GEO_SET_NULL = -1,
		NCTI_GEO_SET_NODE,				//point
		NCTI_GEO_SET_LINE,				//line
		NCTI_GEO_SET_FACE,				//face
		NCTI_GEO_SET_OBJECT				//object
	};

    class NctiMeshBody;
    class NctiDisplayGridMesh;
    
    /**
    * @brief The geometry set object
    */
	class DECL_NCTI_OBJECT NctiDisplaySetGeometry : public NctiDisplaySet
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySetGeometry)
	public:
        /**
        * @brief Get state
        * @retuen the state
        */
		SimulationStateType GetState() const override;
        
        /**
        * @brief Hight light object
        * param[in] i_bOnOff, true or false
        */
        void HighlightSegment(bool i_bOnOff)override;

        /**
        * @brief Get sampling points
        * @param[in] i_pDocCustomContainer, the doc contrainer
        * @param[in] normal, the normal
        * @return the array of sampling points
        */
		std::vector<NCTI::NctiPosition>  GetSimplifyCoord(NctiDisplayDocCustomContainer* i_pDocCustomContainer, std::vector<NCTI::NctiVector>* normal = nullptr)const override;

        /**
        * @brief Get element index
        * return the array element index
        */
        std::vector<Ncti_UInteger> GetElementIndex()override;

        /**
        * @brief Get sub face index
        * @return the array sub face index
        */
        std::vector<Ncti_UInteger> GetElementFaceIndex()override;
        
        /**
        * @brief Get sub object type
        * return the object type
        */
        NctiSelectType GetSelType()const override;
        
        /**
        * @brief Get grid mensh
        * @return the grid mesh
        */
        NctiDisplayGridMesh* GetGridMesh()const;
        
        /**
		* @brief Set sub object type
		* @param[in] the sub object type
        */
        void SetSelType(NctiSelectType iType);
        
        /**
        * @brief Set geometry object
        * @param[in] pObj, the geometry object
        */
        void SetObject(NctiDisplayModelBody* pObj);
        
        /**
        * @brief Set geometry type
        * @param[in] iType, the geometry type
        */
        void SetGeometryType(SimulationGeoSetType iType);
        
        /**
        * @brief Set geometry sub ids
        * @param[in] ids, the geometry sub ids
        */
        void SetSubIDs(const std::vector<Ncti_Long>& ids);
        
        /**
        * @brief Get geometry object
        * @return the geometry object
        */
        NctiDisplayModelBody* GetObject()const;
        /**
        * @brief Get geometry type
        * @return the geometry type
        */
        const SimulationGeoSetType& GetGeomType()const;

        /**
        * @brief Get geometry sub ids
        * @return the geometry sub ids
        */
        const std::vector<Ncti_Long>& GetSubIDs()const;
        
        /**
        * @brief clear link gridmesh data
        */
        void ClearMeshData();
	protected:
		NCTI_VERSION_OBJECT(1, NctiDisplayModelBody*, m_pObject, sd_read_long);//几何对象 m_iObjectType:0
		NCTI_VERSION(1, SimulationGeoSetType, m_iMeoType, sd_read_long);
        NCTI_VERSION(1, NctiSelectType, m_iSelType, sd_read_long);
		NCTI_VERSION(1, std::vector<Ncti_Long>, m_iSubIDVec, sd_read_size);//同类几何子对象 m_iObjectType:0 点 线 面 

    private:
        bool IsGridVisable()const;
        void UpdateMeshFromGeomtry();

        NCTI_READ_AND_WRITE_VERSION_FUN(1);
        //no save
        bool m_updated{false};
        std::set<NctiGridPickSet> m_picks;
	};
}
#endif
