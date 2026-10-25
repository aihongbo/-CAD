// #ifndef NctiWindowThreadTask_H
// #define NctiWindowThreadTask_H
// #include "NctiThreadTask.h"
// //#include <windows.h>
// namespace NCTI
// {
// 	class NctiWindowThreadTask : public NctiThreadTask
// 	{
// 	public:
// 		NctiWindowThreadTask();
// 		~NctiWindowThreadTask();
// 	protected:
// 		virtual NctiThreadAny run();
// 	private:
// 		Ncti_Integer m_Type;
// 		Ncti_Boolean m_quitMessageReceived;
// 	private:
// 		MSG* m_msg;
// 	public:
// 		void wait_thread();
// 		Ncti_Boolean GetState() { return m_quitMessageReceived; }
// 	public:
// 		static void WaitTask();
// 	};
// }
// #endif
