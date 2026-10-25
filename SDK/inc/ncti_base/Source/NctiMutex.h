#ifndef NctiMutex_H
#define NctiMutex_H
#include "ncti_dcl_base.h"

#ifndef _MSC_VER
#define NCTI_USE_STD_SYNC
#endif

#ifdef NCTI_USE_STD_SYNC
#include <mutex>

#include <chrono>
#include <functional>
#include <limits>
#include <ctime>
#include <algorithm>
#else
#endif
namespace NCTI
{
#ifndef NCTI_USE_STD_SYNC
	/**
	* @brief calculate the mutex, internal use
	*/
	class DECL_NCTI_BASE NctiMutexEx {
	public:
		NctiMutexEx();
		~NctiMutexEx();

		NctiMutexEx(const NctiMutexEx&) = delete;
		NctiMutexEx& operator=(const NctiMutexEx&) = delete;
		NctiMutexEx(NctiMutexEx&&) = delete;
		NctiMutexEx& operator=(NctiMutexEx&&) = delete;

		void lock() noexcept;
		void unlock() noexcept;
		bool try_lock() noexcept;

		void* get_native_handle() const;

	private:
		class Impl;
		Impl* pImpl{ nullptr };
	};

	class DECL_NCTI_BASE NctiLockGuardEx {
	public:
		explicit NctiLockGuardEx(NctiMutexEx& mutex)noexcept;
		~NctiLockGuardEx()noexcept;

		NctiLockGuardEx(const NctiLockGuardEx&) = delete;
		NctiLockGuardEx& operator=(const NctiLockGuardEx&) = delete;

		NctiMutexEx& mutex() const noexcept { return m_mutex; }

		void release() noexcept { m_owns = false; }

		bool owns_lock() const noexcept { return m_owns; }

	private:
		NctiMutexEx& m_mutex;
		bool m_owns{ true };
	};
	using NctiMutex = NctiMutexEx;
	using NctiLockGuard = NctiLockGuardEx;
#else
	using MutexType = std::mutex;
	using NctiMutex = MutexType;
	using NctiLockGuard = std::lock_guard<MutexType>;
#endif
}
#endif // !NctiMutex_H