#ifndef NctiDisplayBasePhysicalObj_H
#define NctiDisplayBasePhysicalObj_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayMeshObject.h"
#include "NctiDisplaySet.h"
namespace NCTI
{
	
	/**
	* @brief the physical simulation object
	*/
	class DECL_NCTI_OBJECT NctiDisplayBasePhysicalObj : public NctiDisplayMeshObject
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayBasePhysicalObj)
	public:
		virtual ~NctiDisplayBasePhysicalObj();
	public:
		virtual void Init();
        void HighlightSegment(bool i_bOnOff)override;
	private:
		NCTI_READ_AND_WRITE_VERSION_FUN(1)
	protected:
		NCTI_VERSION(1, Ncti_Char*, m_comment, sd_read_string);
		NCTI_VERSION_OBJECT(1, NctiDisplaySet*, m_pSet, sd_read_long);
		NCTI_VERSION(1, Ncti_Double, m_dMaxSize, sd_read_double);
	protected:
		Ncti_Boolean m_IsNeedToUpdate;
	public:
		
		/**
		* @brief set the set
		* @param[in] i_pSet, the set
		* 
		*/
		void SetSet(NctiDisplaySet* i_pSet);
		
		/**
		* @brief set the max size
		* @param[in] i_dSize, the value
		*/
		void SetMaxSize(Ncti_Double i_dSize);
		
		/**
		* @brief set the comment
		* @param[in] i_comment, the comment
		*/
		void SetComment(const Ncti_Char* i_comment);
		void SetNeedToUpdate();
	public:
		/**
		* @brief get the set
		* @return the set
		*/
		NctiDisplaySet* GetSet() const { return m_pSet; }
		
		/**
		* @brief set the max size
		* @return the max value
		*/
		const Ncti_Double GetMaxSize() const { return m_dMaxSize; }

		/**
		* @brief get the comment
		* @return the comment
		*/
		const Ncti_Char* GetComment() const { return m_comment; }
		
		/**
		* @brief get the state
		* @return the state
		*/
		virtual SimulationStateType GetState() const;
	};
}
#endif
