#ifndef NctiUtility_H
#define NctiUtility_H
#include "ncti.h"
namespace NCTI
{
	class NctiPosition;
	class NctiVector;
	class NctiTransf;
	class NctiDisplayObject;
    class NctiRenderObject;

	/**
	   * @brief internal used
	   */
	class DECL_NCTI NctiUtility
	{
	public:
		static Ncti_Boolean ShowExistenceConditionalStyle(const char* i_which_style, const char* i_what_condition);
		static void MakeDimensionText(char*  i_szInputText, char*&  o_szOutputText);
        static NctiDisplayObject* GetSegmentDisplayObject(NCTI::NctiRenderObject* geoKey);
	};
}
#endif // !NctiUtility_H
