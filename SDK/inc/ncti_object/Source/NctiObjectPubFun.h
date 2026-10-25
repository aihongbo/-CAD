#ifndef NctiObjectPubFun_H
#define NctiObjectPubFun_H
#include "dcl_ncti_object.h"
#include "ncti.h"
#include <vector>
#include <string>
namespace NCTI
{
	class NctiDisplayDocCustomContainer;
	class NctiTransf;
	
	/**
	* @brief Geometric combination function
	*/
	class DECL_NCTI_OBJECT NctiObjectPubFun
	{
	public:
		/**
		* @brief Determine whether two entities can contain each other
		* @param[in] i_pCustomContainer, container
		* @param[in] i_TargeBody, entity
		* @param[in] i_TargeBodyTool, entity
		*/
		static Ncti_Boolean IsEnclosed(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			NCTI_MODEL_TAG i_TargeBody,
			NCTI_MODEL_TAG i_TargeBodyTool);
		
		/**
		* @brief Object geometric transformation
		* @param[in] i_Transf, transformation
		* @param[in-out] io_Body, entity
		*/
		static Ncti_Boolean transform_body(
			NctiDisplayDocCustomContainer* i_pCustomContainer,
			const NctiTransf& i_Transf,
			NCTI_MODEL_TAG& io_Body);
		/**
		* @brief Auto create a new name
		* @param[in] i_existNameVec, exist name array
		* @param[in] i_prefix, prefix of new name
		*/
		static std::string AutoName(const std::vector<const char*>& i_existNameVec, const char* i_prefix);
	};
}
#endif
