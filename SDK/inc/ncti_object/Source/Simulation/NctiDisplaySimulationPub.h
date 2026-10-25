#ifndef NctiDisplaySimulationPub_H
#define NctiDisplaySimulationPub_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiPosition.h"
#include <vector>
namespace NCTI
{
	class NctiDisplaySet;
	
	/**
	* @brief Simulation static class
	*/
	class NctiDisplaySimulationPub
	{
	public:
		NctiDisplaySimulationPub();
		virtual ~NctiDisplaySimulationPub();
		
		/**
		* @brief Get sampling points
		* @param[in] coor, The points
		* @param[in] maxN, max value
		* @return the array of sampling points
		*/
		static std::vector<Ncti_UInteger> GetSimplifyCoor(const std::vector<NctiPosition>& coor, Ncti_UInteger maxN);
		
		/**
		* @brief Get the maximum value of the set object
		* @param[in] pSet, The set object
		* @return the max size
		*/
		static Ncti_Double GetSetMaxSize(NctiDisplaySet* pSet);
		/**
		* @brief Get the fix maximum value of the set object
		* @param[in] pSet, The set object
		* @param[in] maxsize, The max size of set object
		* @return the fix max size
		*/
        static Ncti_Double GetSetFixSize(NctiDisplaySet* pSet,Ncti_Double maxsize);
	};
}
#endif
