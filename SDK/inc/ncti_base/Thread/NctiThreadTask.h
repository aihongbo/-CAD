#ifndef NctiThreadTask_H
#define NctiThreadTask_H
#include "ncti_base.h"
#include "NctiThreadAny.h"
namespace NCTI
{
	class NctiThreadResult;
	/**
	* @brief the base class of thread task
	*/
	class DECL_NCTI_BASE NctiThreadTask
	{
	public:
		NctiThreadTask();
		virtual~NctiThreadTask();

		/**
	    * @brief internal used
	    */
		void exec();

        bool isAttach()const;
        void setAttach(bool);

	protected:
        /**
        * @brief Users can customize any task type.
        * They can inherit from the T class,
        * rewrite the run method, and implement
        * custom task processing.
        * @details need to implement, override
        * @return NctiThreadAny
        */
        virtual NctiThreadAny run() = 0;

    private:
        Ncti_Boolean m_attach{false};
	};
}
#endif
