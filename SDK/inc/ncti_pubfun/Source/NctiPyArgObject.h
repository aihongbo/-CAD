#ifndef NctiPyArgObject_H
#define NctiPyArgObject_H
#include "dcl_ncti_pubfun.h"
#include "ncti_base.h"
#include "CallbackInterfaces.h"
#include "NctiTestSystemObject.h"
namespace NCTI
{
	class NctiBaseModel;
	struct ncti_DCM_bs_data;
	struct ncti_DCM_autocon_options;
	struct ncti_DCM_conic_data;
	struct ncti_DCM3_bs_data;
	struct ncti_DCM3_bs_surface_data;

	class DECL_NCTI_PUBFUN NctiPyArgObject
	{
	public:
		NctiPyArgObject(PyObject* pyArg, NctiPyErrorInfo* i_ErrorInfo);
		NctiPyArgObject(PyObject* pyArg);
		virtual ~NctiPyArgObject();
	private:
		PyObject* m_PyObject;
		NctiPyErrorInfo* m_ErrorInfo;
	public:
		Ncti_Integer Size();
		Ncti_Boolean IsNull();
		void ClearErrorInfo();
		Ncti_Boolean GetDouble(const Ncti_Integer& i_index, Ncti_Double& o_db);
		Ncti_Boolean GetBoolean(const Ncti_Integer& i_index, Ncti_Boolean& o_bo);
		Ncti_Boolean GetLong(const Ncti_Integer& i_index, Ncti_Long& o_long);
		Ncti_Boolean GetLong(const Ncti_Integer& i_index, Ncti_Integer& o_long);
		Ncti_Boolean GetStr(const Ncti_Integer& i_index, const Ncti_Char*& str);
		Ncti_Boolean GetStr(const Ncti_Integer& i_index, std::string& str);
        Ncti_Boolean GetColor(const Ncti_Integer& i_index, RGBAColor& o_color);
		Ncti_Boolean GetPosition(const Ncti_Integer& i_index, NctiPosition& o_position);
		Ncti_Boolean GetVector(const Ncti_Integer& i_index, NctiVector& o_vec);
		Ncti_Boolean GetList(const Ncti_Integer& i_index, PyObject*& pList);
		Ncti_Boolean GetDict(const Ncti_Integer& i_index, PyObject*& pDict);
		Ncti_Boolean GetFloatList(const Ncti_Integer& i_index, std::vector<Ncti_Float>& o_dbVec);
		Ncti_Boolean GetDoubleList(const Ncti_Integer& i_index, std::vector<Ncti_Double>& o_dbVec);
		Ncti_Boolean GetDoubleListList(const Ncti_Integer& i_index, std::vector < std::vector<Ncti_Double>>& o_dbVec);

        Ncti_Boolean GetPositionList(const Ncti_Integer& i_index, std::vector<Ncti_Float>& o_posVec);
		Ncti_Boolean GetPositionList(const Ncti_Integer& i_index, std::vector<NctiPosition>& o_posVec);
		Ncti_Boolean GetPositionListList(const Ncti_Integer& i_index, std::vector<std::vector<NctiPosition>>& o_posVec);
		Ncti_Boolean GetVectorList(const Ncti_Integer& i_index, std::vector<NctiVector>& o_ncvVec);
        Ncti_Boolean GetVectorList(const Ncti_Integer& i_index, std::vector<Ncti_Float>& o_ncvVec);

		Ncti_Boolean GetStrList(const Ncti_Integer& i_index, std::vector<std::string>& o_strVec);
		Ncti_Boolean GetStrList(const Ncti_Integer& i_index, std::vector<const Ncti_Char*>& o_strVec);
		Ncti_Boolean GetDictDouble(const Ncti_Integer& i_index, std::string KeyName, Ncti_Double& o_db);
		Ncti_Boolean GetDictLong(const Ncti_Integer& i_index, std::string KeyName, Ncti_Long& o_long);
		Ncti_Boolean GetDictLongList(const Ncti_Integer& i_index, std::string KeyName, std::vector<Ncti_Long>& o_longVec);
		Ncti_Boolean GetDictLongLongList(const Ncti_Integer& i_index, std::string KeyName, std::vector<Ncti_LongLong>& o_longVec);
		Ncti_Boolean GetDictBoolean(const Ncti_Integer& i_index, std::string KeyName, Ncti_Boolean& o_bool);
		Ncti_Boolean GetDictStr(const Ncti_Integer& i_index, std::string KeyName, std::string& o_str);
		Ncti_Boolean GetDictStrPairs(const Ncti_Integer& i_index, std::map<std::string, std::string>& o_pairs);
		Ncti_Boolean IsNone(const Ncti_Integer & i_index);
		Ncti_Boolean GetDisplayObject(const Ncti_Integer & i_index, NctiDisplayObject*& pDisplayObject);
		Ncti_Boolean GetDisplayObjects(const Ncti_Integer & i_index, std::vector<NctiDisplayObject*>& pDisplayObjects);
		Ncti_Boolean GetDictStrOrDisplayObject(const Ncti_Integer& i_index, const std::string& KeyName, std::string &o_str, NctiDisplayObject*& pDisplayObject);
		Ncti_Boolean GetDisplayObjectName(const Ncti_Integer& i_index, std::string& o_name);
		Ncti_Boolean GetDisplayObjectName(const Ncti_Integer& i_index, const char* &o_name);
		Ncti_Boolean GetDisplayObjectNameList(const Ncti_Integer& i_index, std::vector<std::string>& o_name);
		Ncti_Boolean GetDisplayObjectNameList(const Ncti_Integer& i_index, std::vector<const char*>& o_name);

		Ncti_Boolean GetTransform(const Ncti_Integer& i_index, NctiTransf& o_transf);
		Ncti_Boolean GetTransformList(const Ncti_Integer& i_index, std::vector<NctiTransf>& o_vtTransf);
		Ncti_Boolean GetExtrudeParam(const Ncti_Integer& i_index, NCTIExtrudeBoundParam& o_extrudeParam);
		Ncti_Boolean GetLoftParam(const Ncti_Integer& i_index, NCTIPyBodyLoftParam& o_loftParam);
		template<typename T>
		Ncti_Boolean GetLongList(const Ncti_Integer& i_index, std::vector<T>& o_longVec)
		{
			ClearErrorInfo();
			if (Size() > i_index)
			{
				Ncti_Integer num = 0;
				PyObject* argValue = NctiPyCB.GetTupleItem(m_PyObject, i_index);
				Ncti_Boolean isList = NctiPyCB.IsList(argValue);
				if (isList)
				{
					num = NctiPyCB.GetListSize(argValue);
					for (size_t i = 0; i < num; i++)
					{
						PyObject* argData = NctiPyCB.GetListItem(argValue, i);
						if (NctiPyCB.IsNumber(argData))
						{
							T olong = (T)NctiPyCB.GetLong(argData);
							o_longVec.push_back(olong);
						}
					}
				}
				if (!isList ||o_longVec.size() != num)
				{
					m_ErrorInfo->m_ErrorCode = PY_ARGUMENT_TYPE_ERROR;
					m_ErrorInfo->m_ErrorIndex = i_index;
					m_ErrorInfo->m_correctType.push_back(PY_DATA_LIST_NUMBER);
					return false;
				}
				else
					return true;
			}
			return false;
		}
	private:
		Ncti_Boolean getLongListData(PyObject* i_pyData, std::vector <Ncti_Long>&  o_valueList);
		Ncti_Boolean getStringListData(PyObject* i_pyData, std::vector <std::string>& o_valueList);
		Ncti_Boolean getVectorListData(PyObject* i_pyData, std::vector <NCTI::NctiVector>& o_valueList);
		Ncti_Boolean getDoubleListData(PyObject* i_pyData, std::vector <Ncti_Double>& o_valueList);
	};
	class DECL_NCTI_PUBFUN NctiPyArgObjectItem
	{
	public:
		NctiPyArgObjectItem(PyObject* pyArg, NctiPyErrorInfo* i_ErrorInfo);
		NctiPyArgObjectItem(PyObject* pyArg);
		virtual ~NctiPyArgObjectItem();
		Ncti_Boolean GetDictStr(std::string KeyName, std::string& o_str);
		Ncti_Boolean GetDictLong(std::string KeyName, Ncti_Long& o_long);
		Ncti_Boolean GetDictDouble(std::string KeyName, Ncti_Double& o_db);
		Ncti_Boolean GetDictPosition(std::string KeyName, NctiPosition& o_position);
		Ncti_Boolean GetDictVector(std::string KeyName, NctiVector& o_vec);
		Ncti_Boolean GetDictDisplayObject(std::string KeyName, NctiDisplayObject*& o_obj);
		Ncti_Boolean GetDictLongList(const std::string& i_sKeyName, std::vector<Ncti_Long>& o_vtLongValues);
		Ncti_Boolean GetDictNameList(const std::string& i_sKeyName, std::vector<std::string>& o_vtNameValues);
		void ClearErrorInfo();
	private:
		PyObject* m_PyObject;
		NctiPyErrorInfo* m_ErrorInfo;
	};
	class DECL_NCTI_PUBFUN NctiPyArgObjectDCM
	{
	public:

		/**
		* @brief Get Conic Data By Python Object
		* @param pBaseModel Base Model Pointer
		* @param i_argValue Python Object Argument
		* @param o_co_data Output Conic Data
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetCoDataByPyObject(NctiBaseModel* pBaseModel, PyObject* i_argValue, ncti_DCM_conic_data& o_co_data);

		/**
		* @brief Get BSpline Data By Python Object
		* @param pBaseModel Base Model Pointer
		* @param i_argValue Python Object Argument
		* @param o_bs_data Output BSpline Data
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetBSDataByPyObject(NctiBaseModel* pBaseModel, PyObject* i_argValue, ncti_DCM_bs_data& o_bs_data);

		/**
		* @brief Get 3D BSpline Data By Python Object
		* @param pBaseModel Base Model Pointer
		* @param i_argValue Python Object Argument
		* @param o_bs_data Output 3D BSpline Data
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean Get3DBSDataByPyObject(NctiBaseModel* pBaseModel, PyObject* i_argValue, ncti_DCM3_bs_data& o_bs_data);

		/**
		* @brief Get BSpline Surface Data By Python Object
		* @param pBaseModel Base Model Pointer
		* @param i_argValue Python Object Argument
		* @param o_bs_data Output BSpline Surface Data
		* @return Ncti_Boolean
		*/
		static Ncti_Boolean GetBSSurfDataByPyObject(NctiBaseModel* pBaseModel, PyObject* i_argValue, ncti_DCM3_bs_surface_data& o_bs_surf_data);

	};
}
#endif // !NctiPyArgObject_H
