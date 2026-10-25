#ifndef NctiBulletinBoard_H
#define NctiBulletinBoard_H
#include "ncti.h"
#include "NctiMutex.h"

#define NCTI_BULLETINBOARD_FUNCTIONS( BULLETINBOARD_NAME )	\
	public:\
		static const char* ID;\
		virtual const char* TypeName() const { return BULLETINBOARD_NAME::ID; };\
		virtual Ncti_Boolean IsTypeName( const char *sTypeName );

#define NCTI_BULLETINBOARD_DEF( BULLETINBOARD_NAME, IDENTITY_STRING ) \
	const char* BULLETINBOARD_NAME::ID = IDENTITY_STRING;\
	Ncti_Boolean BULLETINBOARD_NAME::IsTypeName( const char *sTypeName )\
	{\
		if ( strcmp( BULLETINBOARD_NAME::ID, sTypeName ) == 0 )\
		{\
			return true;\
		}\
		return false;\
	}

namespace NCTI
{
	class NctiBulletin;
	/**
	* @brief internal used
	*/
	class DECL_NCTI NctiBulletinBoard : public NCTI_BASE_CLASS
	{
	public:
		static const char* ID;
		virtual const char* TypeName() const;
		virtual Ncti_Boolean IsTypeName(const char *i_sTypeName);
		enum EnumNctiBulletinBoardType
		{
			NCTI_BB_NO_RECORD,
			NCTI_BB_RECORD
		};
	public:
		NctiBulletinBoard(EnumNctiBulletinBoardType i_eBulletinBoardType);
		virtual ~NctiBulletinBoard();
	public:
		void Open();
		void Close();
		Ncti_Boolean IsOpen() { return m_bOpen; };
		void SetOpen(Ncti_Boolean i_bOpen) { m_bOpen = i_bOpen; };
		NctiBulletin* GetFirstBulletin() { return m_pFirstBulletin; };
		Ncti_Boolean Add(NctiBulletin* i_pBulletin);
		void SetNext(NctiBulletinBoard* i_pBulletinBoard) { m_pNext = i_pBulletinBoard; };
		void SetPrevious(NctiBulletinBoard* i_pBulletinBoard) { m_pPrevious = i_pBulletinBoard; };
		NctiBulletinBoard* GetNext() { return m_pNext; };
		virtual Ncti_Boolean CallbackBeforeRoll(Ncti_Boolean i_bRollback);
		void Roll();
		virtual Ncti_Boolean CallbackAfterRoll(Ncti_Boolean i_bRollback);
		NctiBulletinBoard* GetPrevious() { return m_pPrevious; };
		EnumNctiBulletinBoardType GetBulletinBoardType() { return m_eBulletinBoardType; };
	private:
		EnumNctiBulletinBoardType m_eBulletinBoardType;
		Ncti_Boolean m_bOpen;
		NctiBulletin* m_pFirstBulletin;
		NctiBulletin* m_pLastBulletin;

		NctiBulletinBoard*	m_pPrevious;
		NctiBulletinBoard*	m_pNext;

		NctiMutex m_mutex;
	};
}
#endif
