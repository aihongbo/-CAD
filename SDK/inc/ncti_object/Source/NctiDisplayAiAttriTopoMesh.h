#ifndef NctiDisplayAiAttriTopoMesh_H
#define NctiDisplayAiAttriTopoMesh_H

#include "dcl_ncti_object.h"
#include "NctiDisplayMeshObject.h"
#include <map>

namespace NCTI {

    struct AiFaceAttr {
        Ncti_Double m_IsPlane;
        Ncti_Double m_IsCylinder;
        Ncti_Double m_IsCone;
        Ncti_Double m_IsSphere;
        Ncti_Double m_IsTorus;

        Ncti_Double m_Mass;
        Ncti_Double m_Rational;
        NctiPosition m_CenterMass;
    };

    struct AiEdgeAttr
    {
        Ncti_Integer m_convexity;
        Ncti_Double m_Mass;
        Ncti_Double m_IsCircle;
        Ncti_Double m_IsClose;
        Ncti_Double m_IsEllipse;
        Ncti_Double m_IsNonRationalBSplineEdgeAttribute;
        Ncti_Double m_IsRationalBSplineEdgeAttribute;
        Ncti_Double m_IsLine;
    };

    class NctiDisplayModelBody;
    class NctiRenderGeometryItem;
    
    /**
    * @brief AI tag geometric topological data
    */
    class DECL_NCTI_OBJECT NctiDisplayAiAttriTopoMesh : public NctiDisplayMeshObject
    {
        NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayAiAttriTopoMesh)
    public:
        virtual ~NctiDisplayAiAttriTopoMesh();

    public:
        virtual void Init() override;
        virtual EnumNctiResult UpdateDisplay() override;

    private:
        NCTI_READ_AND_WRITE_VERSION_FUN(1)

    private:
        std::map<NctiRenderGeometryItem*, Ncti_Integer> m_DrawVertexHelp;
        std::map<NctiRenderGeometryItem*, Ncti_Integer> m_DrawLineHelp;

        NctiDisplayModelBody* m_ModelBody;
        std::map<Ncti_Integer, NctiPosition> m_FaceIdPointMap;
        std::vector<std::pair<Ncti_Integer, Ncti_Integer>> m_FaceTopoIDs;
        std::vector<AiFaceAttr> m_FaceAttr;
        std::vector<AiEdgeAttr> m_EdgeAttr;

    public:
        
        /**
		* @brief Set geometric object
		* @param[in] i_pModelBody, geometric object
        */
        void SetModelBody(NctiDisplayModelBody* i_pModelBody);
        
        /**
		* @brief Get geometric object
		* @return the geometric object
        */
        NctiDisplayModelBody* GetModelBody() { return m_ModelBody; }
        
        /**
		* @brief Set face map data
		* @param[in] i_FaceIdPointMap, key: face id, value :face point
        */
        void SetFaceIdPointMap(const std::map<Ncti_Integer, NctiPosition>& i_FaceIdPointMap);
        
        /**
		* @brief Get face map data
		* @return the map data 
        */
        const std::map<Ncti_Integer, NctiPosition>& GetFaceIdPointMap() { return m_FaceIdPointMap; }

        
        /**
		* @brief Set the id of the face and the end id of the face edge
		* @param[in] i_FaceTopoIDs, array of the FaceTopoIDs
        */
        void SetFaceTopoIDs(const std::vector<std::pair<Ncti_Integer, Ncti_Integer>>& i_FaceTopoIDs);
        
        /**
		* @brief Get the face topo ids
		* @return the FaceTopoIDs
        */
        const std::vector<std::pair<Ncti_Integer, Ncti_Integer>>& GetFaceTopoIDs() { return m_FaceTopoIDs; }
        
        /**
        * @brief Set faces type 
		* @param[in] i_FaceAttrs, Face type
        */
        void SetFaceAttrs(const std::vector<AiFaceAttr>& i_FaceAttrs);
        
        /**
		* @brief Get faces type
        */
        const std::vector<AiFaceAttr>& GetFaceAttrs() { return m_FaceAttr; }

        /**
        * @brief Set edges type 
		* @param[in] i_EdgeAttrs, Edges type
        */
        void SetEdgeAttrs(const std::vector<AiEdgeAttr>& i_EdgeAttrs);
        
        /**
        * @brief Get edges type 
        */
        const std::vector<AiEdgeAttr>& GetEdgeAttrs() { return m_EdgeAttr; }

        
        /**
        * @brief Get  the Node index
        */
        void FindNode(NctiRenderGeometryItem* i_pRender, std::vector<Ncti_Integer>& o_NodeVec);
    };
}

#endif // !NctiDisplayAiAttriTopoMesh_H
