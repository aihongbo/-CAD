#ifndef NctiDisplaySimulationObject_H
#define NctiDisplaySimulationObject_H
#include "ncti_base.h"
#include "dcl_ncti_object.h"
#include "NctiDisplayObject.h"
namespace NCTI
{
    enum DECL_NCTI_OBJECT SimulationStateType
    {
        NCTI_SIMULATION_INVALID = 0,
        NCTI_SIMULATION_VALID
    };
    class NctiDisplayGridMesh;
    
    /**
    * @brief The Simulation Object
    */
    class DECL_NCTI_OBJECT NctiDisplaySimulationObject : public NctiDisplayObject
    {
        NCTI_DISPLAYOBJECT_FUNCTIONS(NctiDisplaySimulationObject)
    public:
        virtual ~NctiDisplaySimulationObject();
        
        /**
		* @brief Set state
		* @param[in] iState, State
        */
        void SetState(SimulationStateType iState);
        /**
		* @brief Get state
		* @retuen the state
        */
        virtual SimulationStateType GetState() const;
    private:
        void ReadVersion_1(NctiFileInterface*); 
        void WriteVersion_1(NctiFileInterface*&);
    protected:
        NCTI_VERSION(1, SimulationStateType, m_StateType, sd_read_long);//0:invalid;1:valid
    };
}
#endif
