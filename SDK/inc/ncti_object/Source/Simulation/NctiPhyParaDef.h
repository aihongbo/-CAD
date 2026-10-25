#ifndef NctiPhyParaDef_H
#define NctiPhyParaDef_H
namespace NCTI
{
	enum Ncti_Components
	{
		Ncti_Components_U1 = 1 << 0,
		Ncti_Components_U2 = 1 << 1,
		Ncti_Components_U3 = 1 << 2,
		Ncti_Components_ROT1 = 1 << 3,
		Ncti_Components_ROT2 = 1 << 4,
		Ncti_Components_ROT3 = 1 << 5
	};

	enum Ncti_OutputType
	{
		NCTI_HISTORY = 0,
		NCTI_FIELD
	};

	enum Ncti_FrequencyMode
	{
		NCTI_ORDER = 0,
		NCTI_RANGE
	};

	enum Ncti_LoadType
	{
		NCTI_UNKNOWN_LOAD = 0,
		NCTI_CONCENTRATED_FORCE,
		NCTI_PRESSURE,
		NCTI_MOMENT,
		NCTI_GRAVITY,
		NCTI_INERTIA_RELIEF
	};
}
#endif
