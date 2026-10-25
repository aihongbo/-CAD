#ifndef NctiAiModelSystemObject_H
#define NctiAiModelSystemObject_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
#include <map>
#include <set>
namespace NCTI
{
	struct AiModelData
	{
		std::string ObjName;
		Ncti_Integer type;//-1:group, 0-body, 1-face, 2-edge, 3-vertex, 4-feature(multifaces)
		std::vector<NctiPosition> pts;
		Ncti_Integer faceType;// 0 - nothing, 1- bottom
		Ncti_Integer objectId; //type为实体，为实体id；type为单元，为单元id
		std::set<Ncti_Integer> featureIds;
		AiModelData()
		{
			ObjName = "";
			type = 0;
			faceType = 0;
			objectId = 0;
		}
		bool operator == (const AiModelData& other) const
		{
			bool same  = ObjName == other.ObjName && type == other.type && faceType == other.faceType
				&& objectId == other.objectId;
			bool same_feature = featureIds == other.featureIds;
			return same && same_feature;
		}
	};
	
	/**
	* @brief AI label data
	*/
	class AITrainModelData
	{
	public:
		std::string m_ObjName;
		Ncti_Long m_cellId; //0保存的是选中的整个实体
		Ncti_Integer m_LabelIndex;
		Ncti_Integer m_StepIndex;
		AITrainModelData() :m_ObjName(""), m_cellId(0), m_LabelIndex(-1), m_StepIndex(-1) {}
		AITrainModelData(const std::string& i_name, Ncti_Long i_cell, Ncti_Integer i_labelIndex, Ncti_Integer i_StpIndex) :m_ObjName(i_name), m_cellId(i_cell), m_LabelIndex(i_labelIndex), m_StepIndex(i_StpIndex) {}
		AITrainModelData(const std::string& i_name, Ncti_Long i_cell) :m_ObjName(i_name), m_cellId(i_cell), m_LabelIndex(-1), m_StepIndex(-1) {}
		bool operator == (const AITrainModelData& other)const
		{
			return(m_ObjName == other.m_ObjName && m_cellId == other.m_cellId);
		}
	};
	
	/**
	* @brief AI label object
	*/
	class DECL_NCTI_OBJECT NctiAiModelSystemObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiAiModelSystemObject)
	public:
		virtual ~NctiAiModelSystemObject();
	public:
		virtual void Init();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_READ_AND_WRITE_VERSION_FUN(2)
			std::map<std::string, std::vector<AiModelData>> m_AiModelDataMap;
	public:
		
		/**
		* @brief Get all lables
		* @return the map of all lables
		*/
		const std::map<std::string, std::vector<AiModelData>>& GetLabelMap() { return m_AiModelDataMap; }
		
		/**
		* @brief Add lable
		* @param[in] i_str, Lable name
		* @param[in] i_data, Lable data
		*/
		void AddLable(const std::string& i_str, const AiModelData& i_data);

		/**
		* @brief Add lable
		* @param[in] i_str, Lable name
		* @param[in] i_data, The array of lable data
		*/
		void AddLable(const std::string& i_str, const std::vector<AiModelData>& i_data);
		
		/**
		* @brief Rename label
		* @param[in] oldLabel, Old lable name
		* @param[in] newLabel, New lable name
		*/
		void RenameLabel(const std::string& oldLabel, const std::string& newLabel);
		
		/**
		* @brief Remove label
		* @param[in] i_label, Lable name
		*/
		void RemoveLabel(const std::string& i_label);
		/**
		* @brief Remove object from label
		* @param[in] i_label, Lable name
		* @param[in] i_data, remove data
		*/
		void RemoveLabelObject(const std::string& i_label, const AiModelData& i_data);
	
	//AI train Label not to save
	public:
		
		/**
		* @brief Add the training of lable
		* @param[in] i_objName, Object name
		* @param[in] i_cellId, Sub object id
		* @param[in] i_label, Lable
		*/
		void AddTrainModelLabel(const std::string& i_objName, Ncti_Long i_cellId, const std::string& i_label);

		/**
		* @brief Add the training of stp
		* @param[in] i_objName, Object name
		* @param[in] i_stpName, stp name
		*/
		void AddTrainModelStp(const std::string& i_objName, const std::string& i_stpName);

		/**
		* @brief Get the training of lable
		* @param[in] i_objName, Object name
		* @param[in] i_cellId, Sub object id
		* @return lable
		*/
		std::string GetTrainLabel(const std::string& i_objName, Ncti_Long i_cellId);

		/**
		* @brief Get the training of stp
		* @param[in] i_objName, Object name
		* @param[in] i_cellId, Sub object id
		* @return name
		*/
		std::string GetTrainStpName(const std::string& i_objName, Ncti_Long i_cellId);

	private:
		std::vector<AITrainModelData> m_AITrainModelDataVec;
		std::vector<std::string> m_TrainLabels;
		std::vector<std::string> m_stpNames;
	};
}
#endif // !NctiTestSystemObject_H
