#pragma once

#include "ncti_dcl_PluginManager.h"
#include "ncti_base.h"
#include <map>
#include <string>
#include <vector>

namespace NCTI
{
	enum DECL_NCTI_PLUGINMANAGER EnumNCTIPluginsType
	{
		ENUM_TYPE_GEOMENGINE = 0,  // 几何引擎
		ENUM_TYPE_CONSTRAINT,      // 约束
		ENUM_TYPE_MESH,            // 网格引擎
		ENUM_TYPE_RENDER           // 渲染
	};

	struct DECL_NCTI_PLUGINMANAGER NCTIPlugin
	{
		int			id = -1;
		const char* name = nullptr;
		const char* docName = nullptr;
		bool operator==(const NCTIPlugin& other) const
		{
			return id == other.id
				&& name == other.name
				&& docName == other.docName;
		}
	};

	typedef std::map<int, std::vector<NCTIPlugin>> MapNTCIPlugins;

	class NctiFuntionInterfaceManager;
	/**
	* @brief manager all the plugins
	* @details need to initialization when start the application
	*/
	class DECL_NCTI_PLUGINMANAGER NctiPluginsManager
	{
	public:
		~NctiPluginsManager();

		/**
	   * @brief create a golbal plugin manager
	   */
		static NctiPluginsManager* instance();

		/**
	   * @brief initialization the license,help to load other plugin license
	   */
		NctiErrorType Initlicense(const char* i_exeDir, const char* i_licPath);

		/**
	   * @brief load plugin
	   * @param[in] i_filename, the plugin file path
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean LoadPlugin(const char* i_filename);
		/**
	   * @brief unload plugin
	   * @param[in] i_name, the plugin name
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean UnLoadPlugin(const std::string& i_name);

		/**
	   * @brief get temp full path, it is a application path
	   * @return const char*, it is a application path
	   */
		const char* GetTempFullPath()const;

		/**
	   * @brief get function interface manager
	   * @return NctiFuntionInterfaceManager*
	   */
		NctiFuntionInterfaceManager* GetFuntionInterfaceManager();
		/**
	   * @brief get current working path
	   * @param[in] o_chPath, need to release the char point
	   */
		void getCurrentWorkingPath(char* o_chPath);

		/**
	   * @brief get machine code
	   * @return std::string
	   */
		std::string GetMachineCode();
	public:
		/**
	   * @brief get record information state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsOpenRecordInfor() { return m_IsOpenRecordInfor; }
		/**
	   * @brief set record information state
	   * @param[in] i_boo
	   */
		void SetOpenRecordInfor(Ncti_Boolean i_boo) { m_IsOpenRecordInfor = i_boo; }
		/**
	   * @brief get GEGeom information state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsCreateGEGeom() { return m_IsCreateGEGeom; }
		/**
	   * @brief set GEGeom information state,Geometric Object to Platform Object Conversion
	   * @param[in] i_boo
	   */
		void SetCreateGEGeom(Ncti_Boolean i_boo) { m_IsCreateGEGeom = i_boo; }
		/**
	   * @brief get import assembly file state,Geometric Object to Platform Object Conversion
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean IsImportAssemelFile() { return m_IsImportAssemelFile; }
		/**
	   * @brief set import assembly file state, Import files in assembly drawing format
	   * @param[in] i_boo
	   */
		void SetImportAssemelFile(Ncti_Boolean i_boo) { m_IsImportAssemelFile = i_boo; }
		/**
	   * @brief get shapes orientation state, Import files in assembly drawing format
	   * true：Use Oriented- ShapeHash and ShapeEqual if you want to consider orientation of shape in hash computing
	   * false：Use Unoriented- ShapeHash and ShapeEqual if shape orientation is negligible
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetShapesOrientation() { return m_ShapesOrientationIsUsed; }
		/**
	   * @brief set shapes orientation state
	   * true：Use Oriented- ShapeHash and ShapeEqual if you want to consider orientation of shape in hash computing
	   * false：Use Unoriented- ShapeHash and ShapeEqual if shape orientation is negligible
	   * @param[in] i_boo
	   */
		void SetShapesOrientation(Ncti_Boolean i_boo) { m_ShapesOrientationIsUsed = i_boo; }
		/**
	   * @brief get read only mesh state, AI read only mesh when not displayed!(read ncti file)
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetReadOnlyMesh() { return m_ReadOnlyMesh; }
		/**
	   * @brief set read only mesh state, AI read only mesh when not displayed!(read ncti file)
	   * @param[in] i_boo
	   */
		void SetReadOnlyMesh(Ncti_Boolean i_boo) { m_ReadOnlyMesh = i_boo; }

		/**
	   * @brief get record result state
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean GetEnableRecordResult() { return m_IsEnableRecordResult; }

		/**
	   * @brief set record result state
	   * @param[in] i_boo
	   */
		void SetEnableRecordResult(Ncti_Boolean i_boo) { m_IsEnableRecordResult = i_boo; }

		/**
	   * @brief get dll pointer
	   * @param[in] dllName, the dll name
	   */
		void* GetDll(const std::string& dllName)const;

		bool Success()const;
		void SetSysCacheDir(const char* i_chPath);
		const char* GetSysCacheDir() { return m_cpSysCacheDir; }

		/**
		* @brief Add the geometry plugin (system default plugins)
		* @param[in] EnumModelDoc, the geometry
		*/
		void AddGeometryPlugin(EnumModelDoc);
		/**
		* @brief Add the constraint plugin (system default plugins)
		* @param[in] EnumGCSDoc, the constraint
		*/
		void AddConstraintPlugin(EnumGCSDoc);
		/**
		* @brief Add the mesh plugin (system default plugins)
		* @param[in] EnumMeshDoc, the mesh
		*/
		void AddMeshPlugin(EnumMeshDoc);
		/**
		* @brief Add the plugin
		* @param[in] EnumNCTIPluginsType, the plugins type
		* @param[in] NCTIPlugin, the pligins
		* @return Ncti_Boolean
		*/
		Ncti_Boolean AddPlugin(EnumNCTIPluginsType, const NCTIPlugin&);

		/**
		* @brief get the loaded plugins
		* @param[in] EnumNCTIPluginsType, the plugins type
		* @param[in] pluginsID, the pligins id
		* @return MapNTCIPlugins
		*/
		const MapNTCIPlugins& GetLoadedPlugins();

		/**
		* @brief get the plugin
		* @return NCTIPlugin
		*/
		NCTIPlugin GetPlugin(EnumNCTIPluginsType pluginsType, int pluginsID);

		/**
		* @brief Remove the plugin
		* @param[in] EnumNCTIPluginsType, the plugins type
		* @param[in] NCTIPlugin, the pligins
		* @return Ncti_Boolean
		*/
		Ncti_Boolean RemovePlugin(EnumNCTIPluginsType pluginsType, int pluginsID);

	private:
		NctiPluginsManager();
		NctiFuntionInterfaceManager* m_FuntionInterfaceManager{ nullptr };
		std::map<std::string, void*> m_LoadDLLVec;
		Ncti_Boolean m_IsOpenRecordInfor{ false };
		Ncti_Boolean m_IsCreateGEGeom{ false };
		Ncti_Boolean m_IsImportAssemelFile{ false };
		Ncti_Boolean m_ShapesOrientationIsUsed{ false };
		Ncti_Boolean m_ReadOnlyMesh{ false };
		Ncti_Boolean m_IsEnableRecordResult{ false };
		std::string m_cpTempFullPath;
		char* m_cpSysCacheDir{ nullptr };

	private:
		class Impl;
		Impl* pImpl{ nullptr };
	};
}
