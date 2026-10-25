#ifndef NctiParametricManagerObject_H
#define NctiParametricManagerObject_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
#include "NctiParametricObject.h"
//#define NCTI_OPEN_FEATURE_SYSTEM
namespace NCTI
{
	class DECL_NCTI_OBJECT NctiParamVariable
	{
	public:
		Ncti_Char* m_name;
		Ncti_Char* m_comment;
		Ncti_Double m_value;
		Ncti_Boolean m_define;
		NctiParamVariable() :m_name(nullptr), m_comment(nullptr), m_value(0.0), m_define(false) {}
	};
	/**
	* @brief System object
	*/
	class DECL_NCTI_OBJECT NctiParametricManagerObject : public NctiDisplayObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiParametricManagerObject)
	public:
		virtual ~NctiParametricManagerObject();
	public:
		virtual void Init();
		virtual EnumNctiResult UpdateDisplay();
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)

	protected:
		NCTI_VERSION_OBJECT(1, std::vector<NctiParametricObject*>, m_ParmObjVec, sd_read_size);
		std::vector<Ncti_Long> m_ParmObjVecIndex;//no save
		NCTI_VERSION(1, std::vector<NctiParamVariable>, m_Variable, sd_read_size);
		//NCTI_VERSION(1, std::vector<Ncti_Char*>, m_Comment, sd_read_size);
		//NCTI_VERSION(1, std::vector<Ncti_Double>, m_Value, sd_read_size);
		//NCTI_VERSION(1, std::vector<Ncti_Boolean>, m_Define, sd_read_size);
		NCTI_VERSION(1, std::vector<Ncti_Char*>, m_Expr, sd_read_size);
	public:
		void AddParamObj(NctiParametricObject* i_pFOp);
		void SetParamObjs(const std::vector<NctiParametricObject*>& i_pFops);
		const std::vector<NctiParametricObject*>& GetParamObjs() const;

		void SetExpr(const  std::vector<Ncti_Char*> i_exprs);
		std::vector<Ncti_Char*> GetExpr();

		void SetVariable(const std::vector<NctiParamVariable>& i_variables);
		std::vector<NctiParamVariable> GetVariable() const;

	};
	
}
#endif // !NctiParametricManagerObject_H
