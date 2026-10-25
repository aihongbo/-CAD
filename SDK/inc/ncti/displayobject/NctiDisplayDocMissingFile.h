#ifndef NctiDisplayDocMissingFile_H
#define NctiDisplayDocMissingFile_H
#include "NctiDisplayDocElement.h"
namespace NCTI
{
	/**
	* @brief Doc missing file element class
	* @details if the assembly or part is missing, it will use this class instead
	* @see NctiDisplayDocElement
	*/
	class DECL_NCTI NctiDisplayDocMissingFile : public NctiDisplayDocElement
	{
		NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplayDocMissingFile)
	public:
		/**
	   * @brief Initialization during obj class creation
	   */
		void Init(const char* i_cpFilePath);
		virtual ~NctiDisplayDocMissingFile();
	};
}
#endif // !NctiDisplayDocMissingFile_H
