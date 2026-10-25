#ifndef NctiTime_H
#define NctiTime_H
#include "ncti_dcl_base.h"
#include <chrono>
#include <string>
namespace NCTI
{
	/**
	* @brief use to print function time, internal use
	*/
	class DECL_NCTI_BASE NctiTime
	{
	public:
		NctiTime(const char* i_ch, bool i_booCout = true);
		virtual ~NctiTime();

        std::chrono::steady_clock::time_point getStart()const;
        double reStart();
        void SetTips(const char*i_ch);

        static double getElaspedMM(const std::chrono::steady_clock::time_point& start);
		double getElaspedMM()const;
		static std::string GetTimeNow();

	private:
		char* m_Name;
		bool m_booCout;
		std::chrono::steady_clock::time_point m_tStart;
	};
}
#endif // !NctiTime_H
