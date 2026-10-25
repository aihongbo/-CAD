#ifndef NctiTestSystemObject_H
#define NctiTestSystemObject_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
#define NCTI_OPEN_TEST_SYSTEM
namespace NCTI
{
	enum NctiPyDataType {
		PY_DATA_STRING,
		PY_DATA_NUMBER,
		PY_DATA_VECTOR,
		PY_DATA_POINT,
		PY_DATA_LIST,
		PY_DATA_LIST_STRING,
		PY_DATA_LIST_NUMBER,
		PY_DATA_LIST_VECTOR,
		PY_DATA_LIST_POINT,
		PY_DATA_DICT,
		PY_DATA_DICT_NUMBER,
		PY_DATA_DICT_STRING,
		PY_DATA_LIST_DICT,
		PY_DATA_OBJECT,
		PY_DATA_LIST_OBJECT,
		PY_DATA_DICT_OBJECT,
		PY_DATA_TRANSFORM,
		PY_DATA_COLOR
	};
	//std::cout << "The type of " #variable " is: " << typeid(variable).name() << std::endl;

	enum NctiPyErrorCode
	{
		PY_ARGUMENT_NO_ERROR,			//参数正常
		PY_ARGUMENT_NUM_ERROR,			//参数数量不一致
		PY_ARGUMENT_TYPE_ERROR,			//参数类型错误
		PY_ARGUMENT_VALUE_ERROR,		//参数取值错误
		PY_ARGUMENT_RUN_ERROR			//运行错误
	};
	enum NctiCommandErrorCode
	{
		NCTI_COM_NO_ERROR,				//命令正常
		NCTI_COM_OBJECT_EXIST,			//对象已存在
		NCTI_COM_OBJECT_NOT_EXIST,	    //对象不存在
		NCTI_COM_SUB_OBJECT_NOT_EXIST,	//子对象不存在
		NCTI_COM_LIST_EMPTY,			//列表为空
		NCTI_COM_OBJECT_NULL,			//对象指针为空
		NCTI_COM_OBJECT_TYPE_ERROR		//对象指针类型错误
	};

	struct NctiPyErrorInfo
	{
		NctiPyErrorCode m_ErrorCode = PY_ARGUMENT_NO_ERROR;
		Ncti_Integer m_ErrorIndex = -1;
		std::vector<Ncti_Integer> m_CorrectNumber;
		std::vector<Ncti_Integer> m_correctType;
		std::vector<Ncti_Integer> m_correctValue;
	};
	struct NctiComErrorInfo
	{
		NctiCommandErrorCode m_ErrorCode = NCTI_COM_NO_ERROR;
		Ncti_Char* m_ObjectName = nullptr;
		Ncti_Integer m_CellID = -1;
	};


	struct InterfaceResult
	{
		std::string Script;
		Ncti_Double time;
		Ncti_Integer result;
		Ncti_Integer funcErrorCode;
		std::string error;
		std::string errorArgument;
		std::string info;
		Ncti_Boolean Important;
		Ncti_Double cpuUsage;
		Ncti_LongLong usedPhysicalMemory;
		Ncti_Boolean funcImplemented;
		InterfaceResult()
		{
			Script = "";
			time = 0;
			result = 0;
			funcErrorCode = 1001;//FUNC_NO_ERROR;
			errorArgument = "";
			error = "";
			Important = true;
			usedPhysicalMemory = 0;
			cpuUsage = 0.0;
			funcImplemented = true;
		}
	};
	struct TestImageResult
	{
		std::vector<unsigned char> Buffer;
		Ncti_Integer w;
		Ncti_Integer h;
		Ncti_Integer offset;
		Ncti_Integer rowPitch;
		TestImageResult()
		{
			w = 0;
			h = 0;
			offset = 0;
			rowPitch = 0;
		}
	};
	struct CheckResult
	{
		Ncti_UInteger m_type;
		std::string m_content;
		Ncti_Boolean m_ok;
		CheckResult() :m_type(-1), m_content(""), m_ok(false) {}
		CheckResult(const Ncti_UInteger& i_type, const std::string& i_content, const Ncti_Boolean& i_ok) 
			:m_type(i_type), m_content(i_content), m_ok(i_ok) {}
	};
	struct ConstraintCompare
	{
		ConstraintCompare(const std::string& pre, const std::string& after, const std::string& evaluate_type, Ncti_Boolean isOk = false, const char* errMsg = "")
			:m_evaluate_type(evaluate_type), m_constraint_pre(pre), m_constraint_after(after), m_IsOk(isOk), m_errMsg(errMsg) {}
		std::string m_evaluate_type;
		std::string m_constraint_pre;
		std::string m_constraint_after;
		Ncti_Boolean m_IsOk;
		std::string m_errMsg;
	};
	
	/**
	* @brief System object
	* @details Record the relevant logs of the command
	*/
	class DECL_NCTI_OBJECT NctiTestSystemObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiTestSystemObject)
	public:
		virtual ~NctiTestSystemObject();
	public:
		virtual void Init();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
		NCTI_READ_AND_WRITE_VERSION_FUN(2)
		NCTI_READ_AND_WRITE_VERSION_FUN(3)
	protected:
		std::vector<InterfaceResult> m_InterfaceResultVec;
		TestImageResult m_TestImageResult;
	private:
		FILE* m_ReadImageFile;
		Ncti_Char* m_pwsTempFileName;
		std::vector<std::string> m_PythonVec;
		std::vector<CheckResult> m_checkResults;
		std::vector<ConstraintCompare> m_ConstraintCompare;
		NctiPyErrorInfo m_PyErrorInfo;
		NctiComErrorInfo m_ComErrorInfo;

		Ncti_Boolean m_CaseResult;
		std::vector<std::string> m_RecordInforVec;

		std::vector<std::string> m_command_json;
		Ncti_Boolean m_cmd_rec;
		std::string m_pic_path;//生成命令截图的路径
		std::map<std::string, std::string> m_cmdDescribeMap; //命令描述，比如:cmd_ncti_create_cylinder,创建圆柱体[1]

		// 出现python命令或者中间层返回错误时，中断后续执行
		Ncti_Boolean m_StopExecWhenError; 
	public:
		
		/**
		* @brief Add interface execution information
		* @param[in] i_Script, Command script
		* @param[in] i_time, Time
		* @param[in] i_result, Result
		* @param[in] i_error, Error message
		* @param[in] i_Important, Important status
		*/
		void AddInterfaceResult(
			const std::string& i_Script,
			Ncti_Double i_time,
			Ncti_Integer i_result,
			const std::string& i_error,
			Ncti_Boolean i_Important
		);
		/**
		* @brief Add command execution information
		* @param[in] i_Result, InterfaceResult
		*/
		void AddInterfaceResult(const InterfaceResult& i_Result);

		/**
		* @brief Get all the records
		* @return the list of interfaceResult
		*/
		const std::vector<InterfaceResult>& GetInterfaceResult() { return m_InterfaceResultVec; }
		
		/**
		* @brief Set the result image
		* @param[in] i_ImageResult, TestImageResult
		*/
		void SetImageResult(const TestImageResult& i_ImageResult);
		
		/**
		* @brief Get the record picture
		* @return Image path
		*/
		const Ncti_Char* GetImageFile() { return m_pwsTempFileName; }
		
		/**
		* @brief Add Python script
		* @param[in] i_Python, Python script
		*/
		void AddPython(const std::string& i_Python);
		
		/**
		* @brief Get the list of all Python scripts
		* @return the list of all Python scripts
		*/
		const std::vector<std::string>& GetPythonVec() { return m_PythonVec; }
		
		/**
		* @brief Add CheckResult
		* @param[in] i_checkResult, CheckResult
		*/
		void AddCheckResult(const CheckResult& i_checkResult);
		
		/**
		* @brief Get the list of CheckResult
		* @return the list of all CheckResult
		*/
		const std::vector<CheckResult>& GetCheckResult();
		
		/**
		* @brief Add constraint comparison data
		* @param[in] strPre, Before constraint json
		* @param[in] strAfter, After constraint json
		* @param[in] evaluate_type, Evaluate
		* @param[in] isOk, Verify constraint result
		* @param[in] errMsg, Error message
		*/
		void AddConstraintCompare(const std::string& strPre, const std::string& strAfter, const std::string& evaluate_type, Ncti_Boolean isOk = false, const char* errMsg = "");
		
		/**
		* @brief 
		* @brief Clear constraint comparison data
		*/
		void DelConstraintCompare();
		
		/**
		* @brief Clear command execution information
		*/
		void DelInterfaceResult();
		
		/**
		* @brief Clear record information
		*/
		void DelRecordInfor();

		/**
		* @brief Get all constraint comparison data
		* @return the list of all ConstraintCompare
		*/
		std::vector<ConstraintCompare> GetConstraintCompare();
		
		/**
		* @brief Get the specified ConstraintCompare
		* @param[in] index, index
		* @param[out] o_consCom, ConstraintCompare
		* @return Result: true or false
		*/
		Ncti_Boolean GetConstraintCompare(Ncti_UInteger index, ConstraintCompare& o_consCom) const;

		/**
		* @brief Set the specified ConstraintCompare
		* @param[in] index, index
		* @param[in] o_consCom, ConstraintCompare
		* @return Result: true or false
		*/
		Ncti_Boolean SetConstraintCompare(Ncti_UInteger index, ConstraintCompare& consCom);
		
		/**
		* @brief Set the error info
		* @param[in] i_ErrorInfo, NctiPyErrorInfo
		*/
		void SetErrorInfo(NctiPyErrorInfo i_ErrorInfo);
		
		/**
		* @brief Get the error info
		* @return NctiPyErrorInfo
		*/
		NctiPyErrorInfo* GetPyErrorInfo();
		
		/**
		* @brief Get the error description
		* @return string
		*/
		std::string GetErrorInfoString();
		
		/**
		* @brief Get the command error message
		* @return NctiComErrorInfo
		*/
		NctiComErrorInfo* GetComErrorInfo();
		
		/**
		* @brief Reset the command error message
		*/
		void ResetComErrorInfo();
		
		/**
		* @brief Add record message
		* @param[in] i_str, record meaasge
		*/
		void AddRecordInfor(const std::string& i_str);
		
		/**
		* @brief Get all record messages
		*/
		const std::vector<std::string>& GetRecordInfor() { return m_RecordInforVec; }
		
		/**
		* @brief Set case result
		* @param[in] iCaseRet, Result
		*/
		void SetCaseResult(Ncti_Boolean iCaseRet);
		
		/**
		* @brief Get case result
		* @return Result
		*/
		Ncti_Boolean GetCaseResult();

		
		/**
		* @brief Set the json of the information attached to the command
		* @param[in] strJsonData, json
		*/
		void AddCommandDetails(const std::string& strJsonData);

		/**
		* @brief Get the json of the information attached to all commands
		* @return String array
		*/
		std::vector<std::string> GetCommandDetails();
		
		/**
		* @brief Whether to enable command information reading
		* @param[in] iCmdRec, true or false
		*/
		void SetCmdRec(Ncti_Boolean iCmdRec);
		
		/**
		* @brief Get to enable command information reading
		* @return true or false
		*/
		Ncti_Boolean GetCmdRec();
		
		/**
		* @brief Set the picture directory
		* @param[in] pic_path, directory
		*/
		void SetCmdPicPath(const std::string& pic_path);
		
		/**
		* @brief Get the picture directory
		* @return directory
		*/
		std::string GetCmdPicPath();
		
		/**
		* @brief Read command description
		* @param[in] path, Command description file
		*/
		void ReadCmdDes(const std::string& path);
		
		/**
		* @brief Set command description
		* @param[in] cmdDecDict, command description
		*/
		void SetCmdDecMap(std::map<std::string, std::string> cmdDecDict);
		
		/**
		* @brief Get all command description
		* @return the map of command directory
		*/
		std::map<std::string, std::string> GetCmdDesMap();
		
		/**
		* @brief Set stop exec when error
		* @param[in] iEnable, true or false
		*/
		void SetStopExecWhenError(Ncti_Boolean iEnable);
		
		/**
		* @brief Get stop exec when error
		* @return true or false
		*/
		Ncti_Boolean GetStopExecWhenError();
	};
	
}
#endif // !NctiTestSystemObject_H
