#ifndef JsonDocument_H
#define JsonDocument_H
#include "json.h"
//此类为版本升级使用（升级到新版pc替换qt的json），后续应该直接使用Json::Value更方便
namespace NCTIJson
{
	struct JSON_API JsonParseError
	{
		enum ParseError {
			NoError = 0,
			UnterminatedObject,
			MissingNameSeparator,
			UnterminatedArray,
			MissingValueSeparator,
			IllegalValue,
			TerminationByNumber,
			IllegalNumber,
			IllegalEscapeSequence,
			IllegalUTF8String,
			UnterminatedString,
			MissingObject,
			DeepNesting,
			DocumentTooLarge,
			GarbageAtEnd
		};

		int        offset;
		ParseError error;
	};

#define JsonValue Json::Value
#define JsonArray std::vector<Json::Value>

	class JSON_API JsonObject
	{
	public:
		JsonObject();
		JsonObject(const JsonValue val);
		~JsonObject();
		bool contains(const std::string& str) const;
		JsonValue value(const std::string &key) const;
		JsonValue& object();
		void insert(const std::string &key, const JsonValue &value);
		void insert(const std::string &key, const JsonArray &vals);
		bool isEmpty();
	private:
		JsonValue m_root;
	};
	
    class JSON_API JsonDocument
	{
	public:
		JsonDocument();
		~JsonDocument();
		static JsonDocument fromJson(const std::string &json, JsonParseError *error = nullptr);
		static JsonDocument fromFile(const std::string &file, JsonParseError *error = nullptr);
		void setObject(const JsonObject &object);

		enum JsonFormat {
			Indented,
			Compact
		};

		std::string toJson(); //### Merge in Qt6
		std::string toJson(JsonFormat format);
		bool saveToFile(const std::string& file);
		JsonObject& object();
	private:
		JsonObject m_jsonObject;
	};
}
#endif

