#ifndef NctiModelFunctionResult_H
#define NctiModelFunctionResult_H
#include "ncti_dcl_PluginManager.h"
#include "ncti_base.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
namespace NCTI
{
	/**
	* @brief save all the function interface result
	*/
	class DECL_NCTI_PLUGINMANAGER NctiModelFunctionResult
	{
	public:
		NctiModelFunctionResult();
		NctiModelFunctionResult(Ncti_Boolean i_result);
		NctiModelFunctionResult(NctiModelFunctionResult const& p);
		~NctiModelFunctionResult();
	public:
		/**
	   * @brief set the result state
	   * @param[in] i_boo
	   */
		void SetResult(Ncti_Boolean i_boo);
		/**
	   * @brief set the error info
	   * @param[in] i_ErrorInfo
	   */
		void SetErrorInfo(const Ncti_Char* i_ErrorInfo);
		/**
	   * @brief set the error base code
	   * @param[in] i_ErrorCode
	   */
		void SetErrorInfoByCode(Ncti_Integer i_ErrorCode);
		/**
	   * @brief add the error string
	   * @param[in] i_AddStr
	   */
		void AddErrorInfo(const std::string& i_AddStr);
		/**
	   * @brief set function implementation state
	   * @param[in] i_boo
	   */
		void SetFunctionImplementation(Ncti_Boolean i_boo);
		/**
	   * @brief add the error code
	   * @param[in] i_ErrorCode
	   */
		void SetErrorCode(Ncti_Integer i_ErrorCode);
		/**
	   * @brief set the function call string
	   * @param[in] i_ch
	   */
		void SetFUNCCALL(const std::string& i_ch);
		/**
	   * @brief set error argument
	   * @param[in] i_ErrorArgument
	   * @param[in] i_ErrorValue
	   */
		void SetErrorArgument(const std::string& i_ErrorArgument, const std::string& i_ErrorValue);
		/**
	   * @brief set error argument
	   * @param[in] i_ErrorArgument
	   */
		void SetErrorArgument(const std::string& i_ErrorArgument);
	public:
		/**
	   * @brief get the result state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetResult() { return m_result; }
		/**
	   * @brief get the function implementation state (internal used)
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsFunctionImplementation() { return m_IsFunctionImplementation; }
		/**
	   * @brief determine whether model geometry function interface
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetIsModelGeomtry() { return m_IsModelGeomtry; }
		/**
	   * @brief get the function call string
	   * @return const std::string& 
	   */
		const std::string& GetFUNCCALL() { return m_FUNCCALL; }
		/**
	   * @brief get the error code
	   * @return Ncti_Integer
	   */
		Ncti_Integer GetErrorCode() { return m_ErrorCode; }
		/**
	   * @brief get the error information
	   * @return const std::string&
	   */
		const std::string& GetErrorInfo() { return m_ErrorInfo; }
		/**
	   * @brief get the error information
	   * @return const std::string&
	   */
		const std::string& GetErrorArgument() { return m_ErrorArgument; }
		/**
	   * @brief get the function unimplementation state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetFunctionUnImplemented() { return m_IsFunctionUnImplemented; }
		/**
		* @brief set function unimplemented state
		* @param[in] i_boo
		*/
		void SetFunctionUnImplemented(Ncti_Boolean i_boo);
	private:
		//接口未实现，会继续查找（internal used）
		Ncti_Boolean m_IsFunctionImplementation;
		Ncti_Boolean m_result;
		Ncti_Boolean m_IsModelGeomtry;
		std::string m_FUNCCALL;
		//错误码
		Ncti_Integer m_ErrorCode;
		//错误参数
		std::string m_ErrorArgument;
		//错误信息
		std::string m_ErrorInfo;
		//接口未实现
		Ncti_Boolean m_IsFunctionUnImplemented{ true };

	};
	struct DECL_NCTI_PLUGINMANAGER FillectArg
	{
		NCTI_MODEL_TAG m_Body;
		std::vector<NCTI_MODEL_TAG> m_EdgesVec;
		Ncti_Double m_Radius;
		FillectArg()
		{
			m_Body = nullptr;
			m_Radius = 0.0;
		}
	};
#define HAS_IMPL(Result) \
	Result.IsFunctionImplementation()
#define HAS_N_IMPL(Result) \
	 !(Result.IsFunctionImplementation())
#define HAS_RES(Result) \
	(Result.GetResult())
#define HAS_N_RES(Result) \
	!(Result.GetResult())
	struct  DECL_NCTI_PLUGINMANAGER ThickenArg
	{
		NCTI_MODEL_TAG m_Body;
		Ncti_Double m_ForwardOffset;
		Ncti_Double m_BackwardOffset;
		ThickenArg()
		{
			m_Body = nullptr;
			m_ForwardOffset = 0.0;
			m_BackwardOffset = 0.0;
		}
	};

}

#define FUNC_NO_ERROR					1001	//功能正常
#define FUNC_GENERAL_PARAMETER_ERROR	1002	//功能参数错误
#define FUNC_MODEL_PARAMETER_ERROR		1003	//造型对象错误
#define FUNC_KERNEL_ERROR				1004	//内核错误
#define FUNC_CONSTRAINT_PARAMETER_ERROR	1005	//约束对象错误


// 默认情况下，假设类型 T 不支持输出到 ostringstream
template<typename T, typename = void>
struct has_ostream_operator : std::false_type {};

// 特化模板，检查 T 是否支持输出到 ostringstream
template<typename T>
struct has_ostream_operator<T, decltype(std::declval<std::ostringstream&>() << std::declval<T&>(), void())> : std::true_type {};

// 用于简化访问的变量模板
template<typename T>
constexpr Ncti_Boolean has_ostream_operator_v = has_ostream_operator<T>::value;

template <typename T>
auto ncti_error_to_string(const T& value)
-> std::enable_if_t<has_ostream_operator_v<T>, std::string>
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <typename T>
auto ncti_error_to_string(const T& value)
-> std::enable_if_t<!has_ostream_operator_v<T>, std::string>
{
	std::ostringstream oss;
	oss << "Unable to parse the object: " << typeid(T).name();
	return oss.str();
}

template <typename T>
auto ncti_error_to_string(const std::vector<T>& value)
-> std::enable_if_t<!has_ostream_operator_v<T>, std::string>
{
	std::ostringstream oss;
	oss << "Size " << value.size() << ".";
	oss << "Unable to parse the object:";
	oss << typeid(T).name() << ".";
	return oss.str();
}

template <typename T>
auto ncti_error_to_string(const std::vector<T>& value)
-> std::enable_if_t<has_ostream_operator_v<T>, std::string>
{
	std::ostringstream oss;
	oss << "Size " << value.size() << ".";

	for (Ncti_Integer i = 0; i < static_cast<Ncti_Integer>(value.size()); ++i)
	{
		if (i == 0)
		{
			oss << "[";
			oss << value[i];
		}
		else
		{
			oss << ", ";
			oss << value[i];
		}

		if (i == static_cast<Ncti_Integer>(value.size() - 1))
		{
			oss << "]";
		}
	}
	return oss.str();
}
/*c++ 17
template <typename T>
std::string ncti_error_to_string(const T& value) {
	if constexpr (has_ostream_operator_v<T>)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}
	else {
		std::ostringstream oss;
		oss << typeid(T).name();
		return ("Unable to parse the object:" + oss.str());
	}
}
template <typename T>
std::string ncti_error_to_string(const std::vector<T>& value)
{

	std::ostringstream oss;
	if constexpr (has_ostream_operator_v < T >)
	{
		oss << "Size " << value.size() << ".";
		for (Ncti_Integer i = 0; i < value.size(); i++)
		{
			if (i == 0)
			{
				oss << "[";
				oss << value[i];
			}
			else
			{
				oss << ", ";
				oss << value[i];
			}
			if (i == (value.size() - 1))
			{
				oss << "]";
			}
		}
		return oss.str();

	}
	else
	{
		oss << "Size " << value.size() << ".";
		oss << "Unable to parse the object:";
		oss << typeid(T).name()<<".";
		return  oss.str();
	}

}*/

#define SET_ERROR(ERRCODE, INFO, i_RESULT)\
{\
		i_RESULT.SetErrorInfoByCode(ERRCODE);\
		i_RESULT.AddErrorInfo(INFO);\
		i_RESULT.SetResult(false);\
}

#define SET_ERROR_ARG( i_ARG, i_RESULT)\
{\
		i_RESULT.SetErrorArgument(#i_ARG, ncti_error_to_string(i_ARG));\
}

//输出错误信息 错误码 错误信息 结果类
#define SET_ERROR_FINAL(ERRCODE, INFO, i_RESULT)\
{\
		SET_ERROR(ERRCODE, INFO, i_RESULT)\
		return i_RESULT;\
}

//输出错误信息 错误码 错误信息 错误参数变量 结果类
#define SET_ERROR_ARG_FINAL(ERRCODE, INFO,  i_ARG,i_RESULT)\
{\
		SET_ERROR(ERRCODE, INFO, i_RESULT)\
		SET_ERROR_ARG(i_ARG, i_RESULT)\
		return i_RESULT;\
}



#define BEGIN_TRY\
	try {

#define END_CATCH_EXCEPTION(i_RESULT)\
	}\
	catch (const std::exception&)\
	{\
		SET_ERROR_FINAL(FUNC_KERNEL_ERROR, "Kernel error.", i_RESULT)\
	}\
	catch (...)\
	{\
	SET_ERROR_FINAL(FUNC_KERNEL_ERROR, "Kernel error.", i_RESULT)\
	}


//////////////////////////////常见错误处理宏/////////////////////////////

//检查OCC对象有效性
#define CHECK_FUNC_OCC_BODY_VALID(i_BODY,i_TYPES,i_RESULT)\
{\
	NctiOCCBody* I_OCCBODY = (NctiOCCBody*)i_BODY;\
	if(I_OCCBODY == nullptr || I_OCCBODY->GetShape()->IsNull())\
	{\
		SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Body Is Nullptr.",i_BODY,i_RESULT)\
	}\
	else{\
		TopoDS_Shape* pShape = I_OCCBODY->GetShape();\
		if (i_TYPES.end() == std::find(i_TYPES.begin(),i_TYPES.end(), pShape->ShapeType()))\
		{\
			SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Body Is Error Type.",i_BODY,i_RESULT)\
		}\
	}\
}

//检查OCC对象是否为空
#define CHECK_FUNC_OCC_BODY_NULL(i_BODY,i_RESULT)\
{\
	NctiOCCBody* I_OCCBODY = (NctiOCCBody*)i_BODY;\
	if(I_OCCBODY == nullptr || I_OCCBODY->GetShape()->IsNull())\
	{\
		SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Body Is Nullptr.",i_BODY,i_RESULT)\
	}\
}

//检查OCC子对象有效性
#define CHECK_FUNC_OCC_CELL_VALID(i_SRC_BODY,i_CELL,i_TYPES,i_RESULT)\
{\
	if(i_CELL == nullptr)\
	{\
		SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Cell Is Nullptr.",i_CELL,i_RESULT)\
	}\
	else{\
		TopoDS_Shape pShape;\
		NctiOCCBody* I_OCCBODY = (NctiOCCBody*)i_SRC_BODY;\
		if(I_OCCBODY == nullptr || I_OCCBODY->GetShape()->IsNull())\
		{\
			SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Body Is Nullptr.",i_SRC_BODY,i_RESULT)\
		}\
		I_OCCBODY->get_cell_from_tag(i_CELL, pShape);\
		if(pShape.IsNull())\
		{\
			SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Cell Is Nullptr.",i_CELL,i_RESULT)\
		}\
		if (i_TYPES.end() == std::find(i_TYPES.begin(),i_TYPES.end(), pShape.ShapeType()))\
		{\
			SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Cell Is Error Type.",i_CELL,i_RESULT)\
		}\
	}\
}

//检查OCC子对象是否为空
#define CHECK_FUNC_OCC_CELL_NULL(i_SRC_BODY,i_CELL,i_RESULT)\
{\
	if(i_CELL == nullptr)\
	{\
		SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Cell Is Error Type.",i_CELL,i_RESULT)\
	}\
	else{\
		TopoDS_Shape pShape;\
		NctiOCCBody* I_OCCBODY = (NctiOCCBody*)i_SRC_BODY;\
		I_OCCBODY->get_cell_from_tag(i_CELL, pShape);\
		if(pShape.IsNull())\
		{\
			SET_ERROR_ARG_FINAL(FUNC_MODEL_PARAMETER_ERROR, "The Cell Is Error Type.",i_CELL,i_RESULT)\
		}\
	}\
}

//检查参数范围
#define CHECK_FUNC_ARGUMENT_RANGE(i_ARG, OPERATOR, i_TARGET,i_RESULT)\
{\
	if(!(i_ARG OPERATOR i_TARGET))\
	{\
		SET_ERROR_ARG_FINAL(FUNC_GENERAL_PARAMETER_ERROR, "Out OF The Valid Range.",i_ARG,i_RESULT)\
	}\
}

//检查参数Vector有效性
#define CHECK_FUNC_NCTIVECTOR_VALID(i_ARG,i_RESULT)\
{\
	if (i_ARG.len() < Precision::Approximation())\
	{\
		SET_ERROR_ARG_FINAL(FUNC_GENERAL_PARAMETER_ERROR, "NctiVector length is 0.",i_ARG,i_RESULT)\
	}\
}
//检查参数NctiAxis有效性
#define CHECK_FUNC_NCTIAXIS_VALID(i_ARG,i_RESULT)\
{\
	if(i_ARG.GetNormal().len() < Precision::Approximation() || i_ARG.GetFirstDirection().len() < Precision::Approximation())\
	{\
		SET_ERROR_ARG_FINAL(FUNC_GENERAL_PARAMETER_ERROR, "NctiAxis vector length is 0.",i_ARG,i_RESULT)\
		return i_RESULT; \
	}\
	gp_Dir vNormal(i_ARG.GetNormal().x(), i_ARG.GetNormal().y(), i_ARG.GetNormal().z());\
	gp_Dir vFirstDirection(i_ARG.GetFirstDirection().x(), i_ARG.GetFirstDirection().y(), i_ARG.GetFirstDirection().z());\
	if (vNormal.IsParallel(vFirstDirection, Precision::Confusion()))\
	{\
		SET_ERROR_ARG_FINAL(FUNC_GENERAL_PARAMETER_ERROR, "NctiAxis normal and firstDirection is parallel.",i_ARG,i_RESULT)\
		return i_RESULT; \
	}\
}

//检查集合大小
#define CHECK_FUNC_SETS_SIZE(i_LIST,OPERATOR,i_TARGETSIZE,i_RESULT)\
{\
	if(!(i_LIST.size() OPERATOR i_TARGETSIZE))\
	{\
		SET_ERROR_ARG_FINAL(FUNC_GENERAL_PARAMETER_ERROR, "List Size Error.",i_LIST,i_RESULT)\
		return i_RESULT; \
	}\
}

#endif

