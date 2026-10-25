#ifndef NctiThreadAny_H
#define NctiThreadAny_H
#include "ncti_dcl_base.h"
#include <memory>
#include <vector>
namespace NCTI
{
	/**
	* @brief internal use
	*/
	class DECL_NCTI_BASE NctiThreadAny
	{
	public:
		NctiThreadAny() = default;
		~NctiThreadAny() = default;
		NctiThreadAny(const NctiThreadAny&) = delete;
		NctiThreadAny& operator=(const NctiThreadAny&) = delete;
		NctiThreadAny(NctiThreadAny&&) = default;
		NctiThreadAny& operator=(NctiThreadAny&&) = default;

		template<typename T>
		NctiThreadAny(T data) :m_base(std::make_unique<Derive<T>>(data))
		{
		}

		template<typename T>
		T cast()
		{
			Derive<T>* dp = dynamic_cast<Derive<T>*>(m_base.get());
			if (dp == nullptr)
			{
				throw "type is wrong";
			}
			return dp->m_data;
		}

	private:
		class NctiBase
		{
		public:
			virtual ~NctiBase() = default;
		};

		template<typename T>
		class Derive :public NctiBase
		{
		public:
			Derive(T data) :m_data(data)
			{
			}
			T m_data;
		};

	private:
		std::unique_ptr<NctiBase> m_base;
	};
}
#endif // !NctiThreadAny_H
