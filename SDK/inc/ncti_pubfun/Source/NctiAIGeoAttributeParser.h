#ifndef NCTIAIGEOATTRIBUTEPARSER_H
#define NCTIAIGEOATTRIBUTEPARSER_H

#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include <vector>
#include <string>
#include <map>
namespace NCTI
{
    struct GeometryAttributes
    {
        struct UVGrid
        {
            int num_srf_u = 0;
            int num_srf_v = 0;
            int num_crv_u = 0;
        };

        std::vector<std::string> face_attributes;
        std::vector<std::string> edge_attributes;
        UVGrid uvGrid;
    };

    struct StretFaceAttributes
    {
        std::vector<Ncti_Long> hole_faces;
        std::vector<Ncti_Long> bottom_faces;
        std::vector<std::vector<Ncti_Long>> other_faces;
    };

    class NctiDocument;
    /**
    * @brief AI attribute parser
    * @details Reading JSON configuration for AI feature recognition
    */
	class DECL_NCTI_PUBFUN NctiAIGeoAttributeParser
	{
	public:
        NctiAIGeoAttributeParser() = default;
    public:
       /**
	   * @brief Get geometry attributes from JSON file
	   * @param[in] i_jsonPath, the path of JSON file
	   * @param[out] o_GeoAttributes, the geometry attributes
       */
        static Ncti_Boolean GetGeoAttributes(const std::string& i_jsonPath, GeometryAttributes& o_GeoAttributes);
        /**
		* @brief Import AI recognition results into the system object
		* @param[in] i_pDocment, the document pointer
		* @param[in] i_ObjName, the object name
		* @param[in] i_ResultNameVec, the label names
		* @param[in] i_ResultFaceVecVec, the face indices corresponding to each label
		* @param[in] i_ResultBottomFaceVecVec, the bottom face indices corresponding to each label
        */
        static Ncti_Boolean ImportAiResultToSys(
            NctiDocument* i_pDocment,
            const char* i_ObjName,
            const std::vector<std::string>& i_ResultNameVec,
            const std::vector<std::vector<Ncti_Long>>& i_ResultFaceVecVec,
            const std::vector<std::vector<Ncti_Long>>& i_ResultBottomFaceVecVec);
        /**
		* @brief Set stretch face attributes
		* @param[in] objName, the object name
		* @param[in] holeData, the hole face indices
		*/
        static void SetStretFaceHoleData(const std::string& objName, const std::vector<Ncti_Long>& holeData) { m_mapFaceAttributes[objName].hole_faces = holeData; }
        /**
		* @brief Set stretch face attributes
		* @param[in] objName, the object name
		* @param[in] bottomAttributes, the bottom face indices
		* @param[in] otherFace, the other side face indices
        */
        static void SetStretFaceAttributes(const std::string& objName, const std::vector<Ncti_Long>& bottomAttributes, const std::vector<std::vector<Ncti_Long>>& otherFace) {
            m_mapFaceAttributes[objName].other_faces = otherFace;
            m_mapFaceAttributes[objName].bottom_faces = bottomAttributes;
        }
        /**
		* @brief Get stretch face attributes
		* @param[in] objName, the object name
		* @param[out] faceAttributes, the face attributes
        */
        static void GetStretFaceAttributes(const std::string& objName, StretFaceAttributes& faceAttributes);
        /**
		* @brief Set current object name in parser
		* @param[in] newName, the new object name
		* @param[in] oldName, the old object name
        */
        static void SetParserCurretObjName(const std::string& newName, const std::string& oldName) { m_pairRevceObjName = { newName , oldName }; }
        /**
		* @brief Get current object name in parser
		* @return the pair of new and old object names
        */
        static const std::pair<std::string, std::string> GetParserCurretObjName() { return m_pairRevceObjName; }

    private:
        static std::pair<std::string, std::string> m_pairRevceObjName;
        static std::map<std::string, StretFaceAttributes> m_mapFaceAttributes;
	};
}
#endif // NCTIAIGEOATTRIBUTEPARSER_H